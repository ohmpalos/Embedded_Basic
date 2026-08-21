// 예제 6: 비차단(Non-blocking) 시간제어를 이용한 LED Toggle 제어
// millis()함수를 이용한 LED 1초 간격 토글

// LED 핀 정의(상수는 UPPER_SNAKE_CASE)
const int PIN_B = 8;

// 시간 및 상태 저장할 전역 변수
unsigned long lastTime = 0; // 마지막으로 LED 상태가 바뀐 시간을 저장
bool ledState = false; // 현재 LED 켜짐/꺼짐 상태 저장(false: 꺼짐)

void setup() {
  pinMode(PIN_B, OUTPUT);
}

void loop() {
  // 아두이노가 켜진 후 흘러간 현재 시간을 저장
  unsigned long now = millis();
  if(now - lastTime >= 1000){
    // 1초가 자났으므로 기준 시간을 현재 시간으로 갱신
    lastTime = now;
    // LED 상태 반전
    ledState =!ledState;
    // 반전된 상태를 실제 디지털 핀에 출력하여 LED ON-OFF
    digitalWrite(PIN_B, ledState);
  }
}



// // 예제 5: 2자리 FND 멀티플렉싱
// // 81 표시, delay가 짧아야 깜빡임 없음

// const int BCD_PINS[4] = {2, 3, 4, 5}; // DCBA = 5432
// const int DIGIT_PINS[2] = {6, 7}; // 10의 자리(6), 1의 자리(7)

// void setup() {
//   for(int pin : BCD_PINS) pinMode(pin, OUTPUT);
//   for(int pin : DIGIT_PINS) pinMode(pin, OUTPUT);
// }

// // BCD 출력 함수
// void writeBcd(int num){
//   for(int i=0; i<4; i++){
//     digitalWrite(BCD_PINS[i], bitRead(num, i));
//   }
// }

// void loop() {
//   int tens = 8;
//   int ones = 1;

//   // 10의 자리 FND 숫자 켜기
//   writeBcd(tens);
//   digitalWrite(DIGIT_PINS[0], HIGH); // 10의 자리 켜기
//   digitalWrite(DIGIT_PINS[1], LOW); // 1의 자리 끄기
//   delay(3);

//   // 1의 자리 FND 숫자 켜기
//   writeBcd(ones);
//   digitalWrite(DIGIT_PINS[0], LOW); // 10의 자리 끄기
//   digitalWrite(DIGIT_PINS[1], HIGH); // 1의 자리 켜기
//   delay(3);
// }







