/****************************************************************************
 * I2C 통신, Wi-Fi 연결,링 버퍼 관리, JSON 데이터 처리, Socket.IO 서버와의 상호 작용을 위한 필수 라이브러리                                               
 ****************************************************************************/
#include <Wire.h> 
#include <WiFi.h>
#include <RingBuf.h>
#include <ArduinoJson.h>
#include <SocketIOclient.h>

/****************************************************************************
 * 세팅 값 사용자 정의                                                
 ****************************************************************************/
#define NETWORK_SSID "meryoung"
#define NETWORK_PASSWORD "20021202"
#define SERVER_NAME "monolith.luftauila.io"
#define CHANNEL_NAME "kust_322"
#define CHANNEL_KEY "kust_201"

/****************************************************************************
 * Hotspot AP configurations(Wi-Fi 네트워크 SSID 및 비밀번호를 저장)                                                
 ****************************************************************************/
const char ssid[] = NETWORK_SSID;
const char pwd[]  = NETWORK_PASSWORD;

/****************************************************************************
 * telemetry server configuration(서버 이름, URL, 포트 -> 텔레메트리 서버의 세부 정보를 저장)                                         *
 ****************************************************************************/
const char server[] = SERVER_NAME;
const char url[] = "/socket.io/?EIO=4&device=1&channel="CHANNEL_NAME"&key="CHANNEL_KEY;
const int port = 80; // telemetry port of socket.io server

// GPIO and I2C configurations
#define ESP_COMM 19 // STM32 EXTI GPIO
#define I2C_SDA  22
#define I2C_SCL  21
#define I2C_ADDR (0x0) // generall call address
#define I2C_FREQ 400000 // 400kHz fast mode
/*GPIO 핀 및 I2C 구성을 정의*/

// global flags
bool stm_handshake = false;
bool rtc_received = false;
bool server_conn = false;
/*다양한 상태를 추적하는 전역 플래그 및 변수*/

// socket.io client
SocketIOclient socketIO;
/*Socket.IO 클라이언트를 초기화*/

// log buffer
RingBuf<char, 1024> tx_buf;
char log_payload[52] = "[\"tlog\",{\"log\":\"";
/*로그 및 관련 변수를 위한 순환 버퍼를 정의*/

// server time
char rtc[19];
/*서버 시간을 저장하기 위한 문자 배열*/

/****************************************************************************
 * 필요한 하드웨어 (GPIO, I2C 및 Wi-Fi)를 설정하고 초기화, Socket.IO 클라이언트를 설정, Core 0에서 Watchdog Timer를 비활성화                                             
 ****************************************************************************/
void setup() {
  Serial.begin(115200);
  Serial.printf("Wi-Fi:\n\tSSID: %s / PW: %s\nSERVER:\n\tname: %s:%d\n\turl: %s\nI2C:\n\tFREQ: %dHz / ADDR: 0x%02x / SDA: %d / SCL: %d\n", 
  ssid, pwd, server, port, url, I2C_FREQ, I2C_ADDR, I2C_SDA, I2C_SCL);

  // init ESP_COMM
  pinMode(ESP_COMM, OUTPUT);
  digitalWrite(ESP_COMM, HIGH);

  // init I2C slave mode
  Wire.onReceive(i2c_rcv_callback);
  Wire.onRequest(i2c_req_callback);
  Wire.begin(I2C_ADDR, I2C_SDA, I2C_SCL, I2C_FREQ);

  // init Wi-Fi
  WiFi.disconnect();

  if (WiFi.getMode() & WIFI_AP) {
    WiFi.softAPdisconnect(true);
  }

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  // attach socket
  socketIO.begin(server, port, url);
  socketIO.onEvent(socketIOEvent);

  disableCore0WDT();
}

/****************************************************************************
 * socketIO.loop() 메서드를 호출하여 Socket.IO 이벤트를 처리, 서버 연결 표시기를 관리,로그 버퍼를 서버로 플러시.                                           
 ****************************************************************************/
void loop() {
  socketIO.loop();

  // server connection EXTI indicator
  if (stm_handshake && rtc_received) {
    if (WiFi.status() != WL_CONNECTED) {
      server_conn = false;
    }

    digitalWrite(ESP_COMM, server_conn ? HIGH : LOW);
  }

  // flush log buffer to server
  if (server_conn && !tx_buf.isEmpty()) {
    char pop;
    char buf[16];

    for (int x = 0; x < 16; x++) {
      tx_buf.lockedPop(pop);
      buf[x] = pop;
    }

    sprintf((log_payload + 16),
        "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\"}]",
        buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7],
        buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14], buf[15]);

    socketIO.sendEVENT(log_payload, 51);
  }
}

/****************************************************************************
 * Socket.IO 이벤트 (연결, 연결 해제 및 사용자 정의 이벤트)를 처리, 서버 RTC 시간 수정 데이터를 파싱하고 전역 변수를 업데이트합니다.                                           
 ****************************************************************************/
void socketIOEvent(socketIOmessageType_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case sIOtype_CONNECT:
      server_conn = true;
      // join default namespace (no auto join in Socket.IO V3)
      socketIO.send(sIOtype_CONNECT, "/");
      break;

    case sIOtype_EVENT: {
      // parse server RTC time fix data
      StaticJsonDocument<64> json;
      DeserializationError jsonError = deserializeJson(json, payload, length);

      if (jsonError) {
        return;
      }

      const char *event = json[0];

      if (!rtc_received && (strcmp(event, "rtc_fix") == 0)) {
        strncpy(rtc, json[1]["datetime"], 19);
        Wire.slaveWrite((uint8_t *)rtc, 19);
        rtc_received = true;
      }
      break;
    }

    case sIOtype_DISCONNECT:
      server_conn = false;
      break;

    case sIOtype_ACK:
    case sIOtype_ERROR:
    case sIOtype_BINARY_EVENT:
    case sIOtype_BINARY_ACK:
    default:
      break;
  }
}

/****************************************************************************
 * I2C 수신 이벤트를 처리, 들어오는 데이터를 해석하고 STM32 장치와의 handshake sequence를 수행, 수신된 데이터를 로깅.                                        
 ****************************************************************************/
void i2c_rcv_callback(int len) {
  int i = 0;
  char buffer[16];

  while (Wire.available()) {
    if (i < 16) {
      buffer[i++] = Wire.read();
    } else {
      Wire.read(); // just flush buffers
    }
  }

  // STM32 handshake sequence
  if (!stm_handshake) {
    if (strncmp(buffer, "READY", 5) == 0) {
      stm_handshake = true;
      digitalWrite(ESP_COMM, LOW);
    }
  }

  // log received
  else if (i == 16) {
    for (int x = 0; x < 16; x++) {
      tx_buf.lockedPushOverwrite(buffer[x]);
    }
  }
}

void i2c_req_callback(void) {
  // nothing to do; write buffer is set at rtc_fix event
}