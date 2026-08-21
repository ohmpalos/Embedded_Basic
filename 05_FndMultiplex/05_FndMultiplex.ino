// 예제 5: 2자리 FND 멀티플렉싱
// 81 표시, delay가 짧아야 깜빡임 없음

const int BCD_PINS[4] = {2, 3, 4, 5}; // DCBA = 5432
const int DIGIT_PINS[2] = {6, 7}; // 10의 자리(6), 1의 자리(7)

void setup() {
  for(int pin : BCD_PINS) pinMode(pin, OUTPUT);
  for(int pin : DIGIT_PINS) pinMode(pin, OUTPUT);
}

// BCD 출력 함수
void writeBcd(int num){
  for(int i=0; i<4; i++){
    digitalWrite(BCD_PINS[i], bitRead(num, i));
  }
}

void loop() {
  int tens = 8;
  int ones = 1;

  // 10의 자리 FND 숫자 켜기
  writeBcd(tens);
  digitalWrite(DIGIT_PINS[0], HIGH); // 10의 자리 켜기
  digitalWrite(DIGIT_PINS[1], LOW); // 1의 자리 끄기
  delay(3);

  // 1의 자리 FND 숫자 켜기
  writeBcd(ones);
  digitalWrite(DIGIT_PINS[0], LOW); // 10의 자리 끄기
  digitalWrite(DIGIT_PINS[1], HIGH); // 1의 자리 켜기
  delay(3);
}






