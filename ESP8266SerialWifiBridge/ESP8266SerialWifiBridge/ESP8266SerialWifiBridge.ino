#include <ESP8266WiFi.h>
#include <Ticker.h>

//#define ECHOTEST 
#define BAUDRATE 115200

#define MAX_CONFIG_LEN  100
#define MSG_HEADER "[WSB]"
#define VESRION "v1.0"
#define CONFIG_MSG_START "config:"

typedef struct {
  const char* name;
  const char* valueStr;
} param_t;


typedef struct ledSequence_t{
  uint8_t onTicks;
  uint8_t offTicks;
} ledSequence_t;

struct {
  boolean on;
  uint8_t counter;
  const ledSequence_t* currSequence;
} ledStatus;



char configMsg[MAX_CONFIG_LEN];
param_t params[] = { 
  {"SSID",""},
  {"Password",""},
  {"IPAddress",""},
  {"Gateway",""},
  {"Subnet",""},
};
#define PARAMID_SSID    0
#define PARAMID_PASSWD  1
#define PARAMID_LOCALIP  2
#define PARAMID_GATEWAY 3
#define PARAMID_SUBNET  4
#define NBPARAMS (sizeof(params)/sizeof(params[0]))
       
const ledSequence_t ledSeq_waitForConfig  =   {1,1};      
const ledSequence_t ledSeq_connecting  =      {3,3};      
const ledSequence_t ledSeq_connected  =       {1,0};      
const ledSequence_t ledSeq_clientConnected  = {10,1};      
      

WiFiServer server(8080);
WiFiClient client;
bool clientConnected = false;
Ticker ledTicker;


void setLed(boolean on) {
  ledStatus.on = on;
  digitalWrite(2, on?HIGH:LOW);
}

void setLedSequence(const struct ledSequence_t& ledSeq) {
  ledStatus.currSequence = &ledSeq;
  ledStatus.counter = 0;
  setLed(true);
}

void onLedTicker(void) {
  ledStatus.counter++;
  if (ledStatus.on) {
    if (ledStatus.counter >= ledStatus.currSequence->onTicks) {
      if (ledStatus.currSequence->offTicks) {
        setLed(false);
      } else {
        // Stay ON
      }
      ledStatus.counter = 0;
    }
  } else {
    if (ledStatus.counter >= ledStatus.currSequence->offTicks) {
      setLed(true);
      ledStatus.counter = 0;
    }
  } 
}

void flushInput(void) {
  while(Serial.available())
    Serial.read();
}

void waitForParams(void) {
  boolean done = false;
  
  while (! done) {
    
    uint8_t configMsgLen = 0; 
    boolean msgComplete = false; 
    while (! msgComplete) {
      if (Serial.available()) {
        char ch = Serial.read();
        if (ch == '\n' || ch == '\r') {
          msgComplete = true;
          configMsg[configMsgLen] = 0;
        } else {
          configMsg[configMsgLen] = ch;
          configMsgLen++;
          if (configMsgLen > MAX_CONFIG_LEN) {
            Serial.println(MSG_HEADER " ERR: Config too long");
            configMsgLen = 0;  
          }
          if (memcmp(configMsg, CONFIG_MSG_START, min(strlen(CONFIG_MSG_START), configMsgLen)) != 0 ) {
            configMsgLen = 0;
          }
        }
      }
      yield();    
    }
    
    if (strlen(configMsg) >= strlen(CONFIG_MSG_START)) {
      char* p = configMsg + sizeof(CONFIG_MSG_START)-1;
      int i;
      for (i=0; i<NBPARAMS && *p; i++) {
        params[i].valueStr = p;
        p = strchr(p, ',');
        if (p) {
          *p = 0;
          p++;
        } else {
          break;
        }
      }
      if (i==NBPARAMS-1) {
        done = true;
        Serial.println(MSG_HEADER " OK");
      } else {
        Serial.println(MSG_HEADER " ERR: Not enough parameters");
        configMsgLen = 0;
      }
    } else {
      Serial.println(MSG_HEADER " ERR: Expected \"" CONFIG_MSG_START "...\"");
    }
  
    delay(100);
    flushInput();
  }
  
}

void printParams(void) {
  int i;
  Serial.println(MSG_HEADER " Configuration parameters:");
  for (i=0; i<NBPARAMS; i++) {
    Serial.print(MSG_HEADER "    ");
    Serial.print(params[i].name);
    Serial.print(" = \"");
    Serial.print(params[i].valueStr);
    Serial.println("\"");
  }
}

void str2IpAddr(const char* str, IPAddress* ip) {
  int i;
  for (i=0; i<4; i++) {
    (*ip)[i]=atoi(str);
    Serial.println((*ip)[i]);
    str=strchr(str,'.');
    if (str)
      str++;
    else
      break;
  }
}

void setup() {
  Serial.begin(BAUDRATE);

  pinMode(2, OUTPUT);
  setLedSequence(ledSeq_waitForConfig);
  ledTicker.attach(0.1, onLedTicker); 
   
  delay(500);
  Serial.println("\n\n");
  Serial.println(MSG_HEADER " ESP8266 Serial WIFI Bridge " VESRION);
  
  waitForParams();
  printParams();
  
  setLedSequence(ledSeq_connecting);
  
  WiFi.begin(params[PARAMID_SSID].valueStr, params[PARAMID_PASSWD].valueStr);
  
  if (strlen(params[PARAMID_LOCALIP].valueStr) > 0) {
    IPAddress localIp;
    IPAddress gateway;
    IPAddress subnet;
    
    str2IpAddr(params[PARAMID_LOCALIP].valueStr, &localIp);
    str2IpAddr(params[PARAMID_GATEWAY].valueStr, &gateway);
    str2IpAddr(params[PARAMID_SUBNET].valueStr, &subnet);
    
    WiFi.config(localIp, gateway, subnet);
  }
  
  uint8 connectCnt = 0; 
  while (WiFi.status() != WL_CONNECTED ) {
    Serial.print(MSG_HEADER " Connecting ..."); 
    Serial.println(connectCnt); 
    connectCnt++;
    delay(500);
  }
  
  setLedSequence(ledSeq_connected);
  
  Serial.print(MSG_HEADER " CONNECTED! ");
  Serial.print(" IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
  server.setNoDelay(true);
}

#ifdef ECHOTEST
char echotestMsg[20];
uint8_t echotestMsgLen = 0;
void echotestProcess(char ch) {
  if (ch == '{') {
    echotestMsg[0] = '[';
    echotestMsgLen = 1;
  } else if (ch == '}') {
    echotestMsg[echotestMsgLen] = ']';
    echotestMsgLen++;
    Serial.println();
    serverClients[0].write((uint8_t*)echotestMsg, echotestMsgLen);
    echotestMsgLen = 0;
  } else {
    if (echotestMsgLen > 0) {
      echotestMsg[echotestMsgLen] = ch;
      echotestMsgLen++;
    }
  }
}
#endif

void loop() {
  if (clientConnected) {
    if (!client.connected())  {
      client.stop();
      clientConnected = false;
      setLedSequence(ledSeq_connected);
      Serial.println(MSG_HEADER " Client Disconnected");
    }
  }
  
  if (server.hasClient()) {
    if (!clientConnected) {
      client = server.available();
      clientConnected = true;
      setLedSequence(ledSeq_clientConnected);
      Serial.println(MSG_HEADER " Client Connected");  
    } else {
      //no free/disconnected spot so reject
      WiFiClient serverClient = server.available();
      serverClient.stop();
    }
  }
 
  if (clientConnected){
    if(client.available()){
      while(client.available()) {
        char ch = client.read();
        Serial.write(ch);
        #ifdef ECHOTEST
          echotestProcess(ch);
        #endif 
      }
    }
  }
  
  if(Serial.available()){
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    if (clientConnected){
      client.write(sbuf, len);
      delay(1);
    }
  }
}
