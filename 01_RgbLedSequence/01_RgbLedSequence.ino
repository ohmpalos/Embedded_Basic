// GitHub 연동 테스트 2026-08-21
// 예제 1: RGB LED 순차 제어
// R-D10(PWM)
// G-D9(PWM)
// B-D8(Digital) 

/*
○ 아두이노 공식 명명(Naming Convention) 표준
● 변수명 (Variables): lowerCamelCase를 사용
   첫 글자는 소문자로 시작하고, 이어지는 단어의 첫 글자를 대문자로 씀
• 예시: ledPin, sensorValue, currentMillis
● 함수명 (Functions): lowerCamelCase를 사용. 변수명과 마찬가지로 소문자로 시작
• 예시: digitalWrite(), analogRead(), calculateTemperature()
● 클래스/라이브러리명 (Classes): UpperCamelCase(파스칼 케이스)를 사용 
   첫 글자부터 대문자로 시작
• 예시: Servo, LiquidCrystal, SoftwareSerial
● 상수 (Constants): UPPER_SNAKE_CASE를 사용
   모든 글자를 대문자로 쓰고 단어 사이를 언더바(_)로 연결
• 예시: HIGH, LOW, INPUT_PULLUP, MAX_BUFFER_SIZE
*/


// RGB LED 핀 정의
const byte PIN_R = 10;
const byte PIN_G = 9;
const byte PIN_B = 8;

void setup() {
  // RGB LED 핀(10, 9, 8) 출력 모드로 설정
  pinMode(PIN_R, OUTPUT); 
  pinMode(PIN_G, OUTPUT); 
  pinMode(PIN_B, OUTPUT); 
}

void loop() {
  // 0.5초 동안 R LED ON
  digitalWrite(PIN_R, HIGH);
  digitalWrite(PIN_G, LOW);
  digitalWrite(PIN_B, LOW);
  // delay(500); //  500mS(0.5s)
  delay(1); //  1mS(0.001s)

  // 0.5초 동안 G LED ON
  digitalWrite(PIN_R, LOW);
  digitalWrite(PIN_G, HIGH);
  // delay(500); //  500mS(0.5s)
  delay(1); //  1mS(0.001s)

  // 0.5초 동안 B LED ON
  digitalWrite(PIN_G, LOW);
  digitalWrite(PIN_B, HIGH);
  // delay(500); //  500mS(0.5s)
  delay(1); //  1mS(0.001s)

}







