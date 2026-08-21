// 예제 3: PWM을 이용하여 LED Dimming 제어
// R - D10(PWM)
// G - D9(PWM)
// B - D8(Digital)
// for 반복문 연습 

// RGB LED 핀 정의
const int PIN_R = 10;
const int PIN_G = 9; 
const int PIN_B = 8;

void setup() {
  // RGB LED 핀을 출력 모드로 설정
  // DDRB = 0xff; (출력 모드 설정)
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
}

void loop() {
  // R LED PWM 제어
  // 점점 밝아지는 과정
  for(int i=0; i<=255; i++){
    // PWM 출력
    analogWrite(PIN_R, i);
    // G LED OFF
    analogWrite(PIN_G, 0);
    // B LED OFF
    digitalWrite(PIN_B, LOW);
    delay(8);
  }
  // 어두워지는 과정
  for(int i=255; i>=0; i--){
    // PWM 출력
    analogWrite(PIN_R, i);
    // G LED OFF
    analogWrite(PIN_G, 0);
    // B LED OFF
    digitalWrite(PIN_B, LOW);
    delay(8);
  }

  // G LED 숨쉬기
  // 밝아지는 과정
  for(int i=0; i<256; i++){
    analogWrite(PIN_R, 0);
    analogWrite(PIN_G, i);
    digitalWrite(PIN_B, LOW);
    delay(8);
  }
  // 어두워 지는 과정
  for(int i=255; i>=0; i--){
    analogWrite(PIN_R, 0);
    analogWrite(PIN_G, i);
    digitalWrite(PIN_B, LOW);
    delay(8);
  }

  // B LED PWM 기능이 없음
  // 단순 ON/OFF 제어(5회)
  for(int j=0; j<5; j++){
    digitalWrite(PIN_B, HIGH);
    delay(100);
    digitalWrite(PIN_B, LOW);
    delay(100);
  }
}







