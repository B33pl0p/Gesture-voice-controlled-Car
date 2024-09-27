#include "MPU6050.h"
#include "Wire.h"
#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile
RH_ASK driver;
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  //mpu part ..
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  //mpu part end...

  //rf module part
  if (!driver.init()) {
    Serial.println("RF module init failed");
  }
}
void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

char *message;

if(ay <= -5000 || ay >= 5000){
  //forward and backward
  if (ay <= -5000) {
    //backward
   // Serial.println("b");
    message = "B";
    //check left and right while tilt
  }
  if (ay >= 5000) {
    //forward
     //  Serial.println("f");
     message = "F";  
  }
    if (ax >= 5000) {
     //   Serial.println("r");
        message = "R";
  }
  if (ax <= -5000) {
      //  Serial.println("l");
        message = "L";
  }
}
else if(ax <= -5000 || ax >= 5000) {
  //left right
  if (ax >= 5000) {
     //   Serial.println("r");  
        message = "R";
  }
  if (ax <= -5000) {
      //  Serial.println("l");
        message = "L";
  }
 
}

else {
  message = "S";
}
Serial.println(message);
  driver.send((uint8_t *)message, strlen(message));
  driver.waitPacketSent();
  delay(100);
}

