#include <Wire.h>

int trigPin = 8;
int echoPin = 9;

int speakerPin = 12;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // I2C 통신
  Wire.begin(8);
  // 요청 받으면 Request Event를 실행
  Wire.onRequest(requestEvent);
  
  Serial.begin(9600); //시리얼 모니터를 시작합니다.
  Serial.println("Setup");
}

// 데이터를 수신할 때
void requestEvent() {
  // 마스터에게 전달해야 할 내용
  // 1. 남은 음료의 양
  // 2. 거리 감지를 통해 컵에 음료가 없다면 부저를 울리고 마스터에게 컵이 없다는 내용 전달

  // 거리를 가지고 Master에게 신호를 보내야함
  // if(distance()){
  //
  // }
  Serial.println("장치가 연결되었습니다");
  int val1 = analogRead(A0);  // 탄산수의 수위 측정
  int val2 = analogRead(A1);  // 음료 1
  int val3 = analogRead(A2);  // 음료 2

  // water 함수에서 어떤걸 구현할지?
  // water에선 남은 음료의 양을 구해야 하고 가능하다면 실시간으로 물의 양을 알 수 있게 하는게 베스트

  water(val1, val2, val3);
  delay(100);
}
void water(int val1, int val2, int val3) {
  byte check = 0;
  // 끝부분에 살짝 닿았을 경우 센서값은 500~
  // 센서가 거의 잠기면 ~680

  // 500부터 680까지의 값을 백분율로 표시해야 함
  int per1 = val1;
  int per2 = val2;
  int per3 = val3;
  
  // 음료가 부족하면 소리를 울리고, check, 0을 전달함
  if (per1 < 20 || per2 < 20 || per3 < 20) {
    tone(speakerPin, 400);
    // Wire.write(check);
  }
  String a = (String)per1 + "/" + (String)per2 + "/" + (String)per3;
  char buf[20];
  a.toCharArray(buf,a.length()+1);

/* 남은 음료수 양이 계속 변하므로 문자열의 길이도 가변적이게 됨.
   그러므로 Master 보드에 데이터 전송할 때 쓰레기 값이 들어가지 않게 니머지를 X로 채워줌 */
  for(int i=a.length(); i<20; i++)
    buf[i] = 'X';
  
  Serial.println(buf);
  Wire.write(buf,20);
}

bool distance() { 
  // 거리감지부터 해야 함
  float duration, distance;
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  // echoPin에 HIGH 시간 저장
  duration = pulseIn(echoPin, HIGH);
  // HIGH일 때 초음파가 보냈다가 돌아오는 시간을 가지고 거리 계산
  distance = ((float)(340 * duration) / 10000) / 2;
}
void loop() {
 
}