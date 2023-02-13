#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>


BLEService bleService("19B10000-E8F2-537E-4F6C-D104768A1214");
BLECharacteristic bleCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLENotify, 20);

void setup() {
  Serial.begin(115200);
//  while (!Serial) {
//    ;
//  }

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("AssisstoV2");
  BLE.setAdvertisedService(bleService);

  bleService.addCharacteristic(bleCharacteristic);

  bleCharacteristic.setValue("Hello World !");

  BLE.addService(bleService);
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
  
   if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("IMU initialized successfully!");
}

void loop() {
//  if (Serial.available()) {
//    String input = Serial.readStringUntil('\n');
//    bleCharacteristic.setValue(input.c_str());
//    Serial.println("Message changed to: " + input);
//  }
float AcX, AcY, AcZ;
  IMU.readAcceleration(AcX, AcY, AcZ);
  if(AcY > 0.60){
    Serial.print("tilted to right");
    bleCharacteristic.setValue("1");
    delay(2000);
  }
  else if(AcY < -0.60){
    Serial.print("tilted to left");
    bleCharacteristic.setValue("0");   
    delay(2000);
  }

  delay(100);

  BLE.poll();
}
