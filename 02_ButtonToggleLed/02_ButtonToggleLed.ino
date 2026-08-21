// 예제 2: 스위치 입력 기본(digitalRead()함수)
// R LED - D10
// SW1 - D13

const uint8_t PIN_R = 10;
const uint8_t SW1 = 13;
const uint8_t SW2 = 12;
const uint8_t SW3 = 11;


void setup() {
  pinMode(PIN_R, OUTPUT); // D10 핀을 출력 모드로 설정
  pinMode(SW1, INPUT); // D13 핀을 입력 모드로 설정
}

void loop() {
  // SW1 OFF - HIGH, ON - LOW
  if(!digitalRead(SW3)){
    digitalWrite(PIN_R, HIGH); // R LED ON
  }
  else{
    digitalWrite(PIN_R, LOW); // R LED OFF
  }
}






