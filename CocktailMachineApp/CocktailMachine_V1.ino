#include <DHT.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT11  

#define WATHER_1AA 13
#define WATHER_1AB 12
#define WATHER_1BB 11
#define WATHER_1BA 10

#define WATHER_2AA 9
#define WATHER_2AB 8

DHT dht(DHTPIN, DHTTYPE); 

/* 관련 핀 상수화하기 */
#define TX 2
#define RX 3

SoftwareSerial blueToothSerial(TX, RX);   // 블루투스 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD 객체 선언 SDA A4 SCL A5


int recipes[3][4] = { {20, 20, 0, 0},   
                      {20, 0, 20, 0},
                      {20, 0, 0 ,20}};

/* 
 * 여기에서 칵테일의 양을 조절할 수 있습니다
 * volume 값과 칵테일의 양은 정비례합니다
 */
 
 int volume = 100;

void setup() {
  /* 시리얼 창 설정 */
  Serial.begin(9600);
  blueToothSerial.begin(9600);
  
  Serial.println("-- 아두이노 세팅 완료 --");
  int tmp = dht.readTemperature();
  blueToothSerial.print(String(tmp));

  pinMode(WATHER_1AA, OUTPUT);
  pinMode(WATHER_1AB, OUTPUT);
  pinMode(WATHER_1BB, OUTPUT);
  pinMode(WATHER_1BA, OUTPUT);
  pinMode(WATHER_2AA, OUTPUT);
  pinMode(WATHER_2AB, OUTPUT);

   /* Lcd 판 기본설정 */
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Cocktail");
  
  Serial.print("Temperature: ");  // 이하생략
  Serial.print(tmp);
  Serial.println(" C");

  
}

void loop() {
  if (blueToothSerial.available()){
    char message = blueToothSerial.read();

    if (message >= '0' && message <= '6') {
      Serial.print(message);
      Serial.println(" 칵테일을 만듭니다");
      
      /* 칵테일 만들기 전 LCD on */

      setLCDText("MAKING...");

      delay(3000);

      int cocktailNum = (int)(message - 48);
      
      /* 칵테일 만들기 */
      // 탄산수 
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
      
      // 사용자 선택 음료 
      digitalWrite(cocktailNum * 2 + 6, HIGH);
      digitalWrite(cocktailNum * 2 + 7, LOW);
      delay(2000);

      // 탄산수 
      digitalWrite(WATHER_1AA, LOW);
      digitalWrite(WATHER_1AB, LOW);

      // 사용자 선택 음료 
      digitalWrite(cocktailNum * 2 + 6, LOW);
      digitalWrite(cocktailNum * 2 + 7, LOW);
  
      /* 칵테일 만든 후에 LCD off */
      delay(1000);

      setLCDText("COMPLETE!");
    
      /* 
       * 완성메제지 보내기  
       * 최대한 짧게 보내는 게 좋습니다
       */
      blueToothSerial.print("9");
    } else {
      Serial.print(message);
    }
  }
}

void setLCDText(String text) {
    lcd.setCursor(0,1);
    lcd.print(text);
}
