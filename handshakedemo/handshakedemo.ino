#include <WiFi.h>
#include <WiFiUdp.h>

int Motor[6]={1,2,3,4,5,6};

//const char* ssid = "BFADT-IoT";
//const char* password = "bfaisthebest";

const char* ssid = "SpectrumSetup-53";
const char* password = "walnutgenius483";

WiFiUDP udp;
unsigned int localUdpPort = 6000;

class Check{
  private:
    byte *data;
    int leng;
  public:
    Check(byte *data, int leng){
      this->data = data;
      this->leng = leng;
    }
    void check(){
        for(int i=0; i<6; i++){

          switch(data[i]){
            case 0:
            digitalWrite(Motor[i],0);
            Serial.println("case0");
            break;

            case 1:
            digitalWrite(Motor[i],1);
            Serial.println("case1");
            break;
            
            case 2:
            Serial.println("case2");
            break;

            case 3:
            Serial.println("case3");
            break;

            case 4:
            Serial.println("case4");
            break;
          }
          
           Serial.println(data[i]);
        }
    }
};

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  for(int i=0; i<6; i++){
    pinMode(Motor[i],OUTPUT);
  }
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  udp.begin(localUdpPort);
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
 
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    byte incomingPacket[packetSize];
    int len = udp.read(incomingPacket, packetSize);
    Check check1 = Check(incomingPacket, len);
    check1.check();
    // Do something with the incoming packet
    Serial.print("Received packet with length ");
    Serial.println(len);
    Serial.print("Data: ");fuf
    for (int i = 0; i < len; i++) {
      Serial.print(incomingPacket[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
