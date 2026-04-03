#include "BluetoothSerial.h"
#define LED_BUILTIN 2
// include file system library
#include "FS.h"
// include SD card library
#include "SD.h"
// include SPI library
#include "SPI.h"
#include "string.h"

#define MOSI     23
#define MISO     19
#define SCK     18
#define CS       5

BluetoothSerial ESP_BT;
char incoming;
int temp = 0;
char* buffer = "";

void setup() {
  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("ESP32_LED_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  pinMode (LED_BUILTIN, OUTPUT);//Specify that LED pin is output

  SPIClass spi = SPIClass(VSPI);
  spi.begin(SCK, MISO, MOSI, CS);

  if (!SD.begin(CS)) 
  {
    Serial.println("SD Card MOUNT FAIL");
  }
}

// the loop function runs over and over again forever
void loop() {
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive
    Serial.print("Received:"); Serial.println(incoming); 
    temp = 1;
    }                 // wait for a second
  else if (temp == 1){
    Serial.println("Received:"); Serial.println(buffer);
    temp = 0;
  }
  if (incoming == '1')
    {
    digitalWrite(LED_BUILTIN, HIGH);
    ESP_BT.println("LED turned ON");
    }
       
  if (incoming == '0')
    {
    digitalWrite(LED_BUILTIN, LOW);
    ESP_BT.println("LED turned OFF");
    }
}
