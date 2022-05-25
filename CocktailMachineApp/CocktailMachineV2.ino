#include <Wire.h>

 int LED1 = 2;
 int LED2 = 3;
 int LED3 = 4;

 int trigPin = 8;
 int echoPin = 9;

 int speakerPin = 12;

 void setup() {
   Serial.begin(9600); //시리얼 모니터를 시작합니다.
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);

   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);

 }

 void water(int val){
    if(val<=400){
     digitalWrite(2, LOW);
     digitalWrite(3,LOW);
     digitalWrite(4,LOW);
     tone(speakerPin, 1000);
     delay(100);
   }

   else if(400 < val && val <= 680){
     digitalWrite(2, HIGH);
     digitalWrite(3,LOW);
     digitalWrite(4,LOW);
     delay(100);
   }
    else if(680 < val && val <= 730){
     digitalWrite(2, HIGH);
     digitalWrite(3,HIGH);
     digitalWrite(4,LOW);
     delay(100);
   }
    else {
     digitalWrite(2, HIGH);
     digitalWrite(3,HIGH);
     digitalWrite(4,HIGH);
     delay(100);
   }
 }


 void loop() {

   float duration, distance; 
   digitalWrite(trigPin, HIGH);
   delay(10);
   digitalWrite(trigPin,LOW);

   // echoPin에 HIGH 시간 저장
   duration = pulseIn(echoPin, HIGH);
   // HIGH일 때 초음파가 보냈다가 돌아오는 시간을 가지고 거리 계산 
   distance = ((float)(340*duration) / 10000) / 2;

   int val = analogRead(A0);  // 수분센서의 신호를 측정합니다.
   Serial.println(val);   //시리얼 모니터에 값을 출력합니다.
   delay(100);

   Serial.print("Duration: ");
   Serial.println(duration);
   Serial.print("Distance: ");
   Serial.println (distance);

   delay(400);
   water(val);

 } 
