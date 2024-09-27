#include <RH_ASK.h>
#include <SoftwareSerial.h>
#include <SPI.h>  // Not actually used but needed to compile
#include "Wire.h"
#include <MPU6050.h>
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
RH_ASK driver;
SoftwareSerial bluetooth(8, 9);
//SoftwareSerial myblue(0,1);
//motor initializations..
//motor left side
int in1 = 7;
int in2 = 4;
//motor right
int in3 = 3;
int in4 = 2;
//speed
int ena = 5;
int enb = 6;
//ultrasonic 1..
int trigPin = 12;  // Trigger
int echoPin = 13;
long duration;
float distance;
int buzzerpin = 10;
String acc = "A,C";
String obs = "O,B";
String norm = "N, N";


void setup() {



  Wire.begin();
  mpu.initialize();  //driver.init();
  if (!driver.init()) {
    Serial.println("Radio module initialization failed");
  }

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(ena, 0);
  analogWrite(enb, 0);


  //buzzer
  pinMode(buzzerpin, OUTPUT);

  //ultrasonic
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  bluetooth.begin(9600);
}



void forward() {

  analogWrite(ena, 120);
  analogWrite(enb, 120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void backward() {
  analogWrite(ena, 120);
  analogWrite(enb, 120);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void right() {
  analogWrite(ena, 120);
  analogWrite(enb, 120);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

}
void left() {
  analogWrite(ena, 120);
  analogWrite(enb, 120);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}



void loop() {

  int a = 0, o = 0, n = 0;


  //String cmd, cmd1;
  char bluetoothcmd;
  char cmd[30];
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);



  if (driver.recv(buf, &buflen)) {  // Non-blocking
    buf[buflen] = '\0';
    strcpy(cmd, (char *)buf);

  } else if (bluetooth.available()) {
    bluetoothcmd = bluetooth.read();
    cmd[0] = bluetoothcmd;
    cmd[1] = '\0';
  }


  //obsstacle condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  delay(100);
  Serial.println(distance);
  //bluetooth.println(acc);
  while (distance <= 30) {
    o = 1;
    a = 0;
    digitalWrite(buzzerpin, HIGH);
    delay(200);
    digitalWrite(buzzerpin, LOW);
    String data = String(o) + "," + String(n) + "," + String(a);
    bluetooth.println(data);

    stop();

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    delay(100);
  }




  mpu.getMotion6(&ax, &ay, &az, &gz, &gy, &gz);

  while (ax >= 10000 || ax <= -10000) {
    a = 2;
    o = 0;
    String data = String(o) + "," + String(n) + "," + String(a);
    bluetooth.println(data);
    digitalWrite(buzzerpin, HIGH);
    delay(200);
    digitalWrite(buzzerpin, LOW);
  stop();
    mpu.getMotion6(&ax, &ay, &az, &gz, &gy, &gz);
  }

  n = 3;
  String data = String(o) + "," + String(n) + "," + String(a);
  bluetooth.println(data);




    if (strcmp(cmd, "F") == 0) {
      //Serial.println("forward");
      forward();

    } else if (strcmp(cmd, "B") == 0) {
      backward();
      //Serial.println("backward");


    } else if (strcmp(cmd, "L") == 0) {
      left();
      //Serial.println("left");


    } else if (strcmp(cmd, "R") == 0) {
      right();
      // Serial.println("right");


    } else if (strcmp(cmd, "S") == 0) {
      // Serial.println("stop");
      stop();
    }
    else {
      stop();
    }
}
