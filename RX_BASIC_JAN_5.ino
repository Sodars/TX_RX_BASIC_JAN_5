#include <esp_now.h>
#include <WiFi.h>

int LED_PIN = 2;


//Structure example to receive data
//Must match the sender structure
typedef struct test_struct {
  int x;
  int y;
} test_struct;

//Create a struct_message called myData
test_struct myData;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 #define LED_PIN 2

  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("x: ");
  Serial.println(myData.x);
    if (myData.x == 1) {             // this part under void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
      digitalWrite(LED_PIN, HIGH);
  }
    else{
      digitalWrite(LED_PIN, LOW);                            
  }
  Serial.print("y: ");
  Serial.println(myData.y);
  Serial.println();

}
 
void setup() {
  //Initialize Serial Monitor
  pinMode (LED_PIN, OUTPUT);
  Serial.begin(115200);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
