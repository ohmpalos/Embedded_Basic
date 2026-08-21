// 예제 1: RGB LED 순차 제어
// R-D10(PWM)
// G-D9(PWM)
// B-D8(Digital) 

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







