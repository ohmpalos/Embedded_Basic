// 예제 4: BCD 입력에 따른 FND 한 자리 출력 제어
// DCBA - D5, D4, D3, D2
// 10의 자리 FND(D6), 1의 자리 FND(D7) 

const int BCD_PINS[4] = {2, 3, 4, 5};
const int DIGIT_PINS[2] = {6, 7}; 

void setup() {
  // C++ 11 Range based for 문 활용
  for(int pin : BCD_PINS) pinMode(pin, OUTPUT);
  // 자리 선택 핀(6, 7)을 출력 모드로 설정하고 초기화
  for(int i=0; i<2; i++){
    pinMode(DIGIT_PINS[i], OUTPUT);
    digitalWrite(DIGIT_PINS[i], LOW); // FND all OFF, 초기화
  }
}

// BCD 출력 함수
void writeBcd(int value){
  for(int i=0; i<4; i++){
    digitalWrite(BCD_PINS[i], bitRead(value, i));
  }
}

void loop() {
  int num = 8; // 표시할 숫자
  digitalWrite(DIGIT_PINS[0], HIGH); // 10의 자리 FND ON
  digitalWrite(DIGIT_PINS[1], HIGH); // 1의 자리 FND ON
  writeBcd(num);
}





