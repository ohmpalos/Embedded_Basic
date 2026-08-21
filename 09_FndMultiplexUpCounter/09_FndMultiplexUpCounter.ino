// 예제 9: FndMultiplexUpCounter
// 99진 상향 카운터(2자리 FND 멀티플렉싱) 제어

const int BCD_PINS[4] = {2, 3, 4, 5};
const int DIGIT_PINS[2] = {6, 7};

// FND에 표시할 전체 숫자(00~99)
int fndValue = 0;

// 숫자 증가 타이밍을 제어하기 위한 변수
unsigned long previousCountMillis = 0; // millis() 기준 시간 저장용도

void setup() {
  // 2,3,4,5,6,7핀을 모두 출력으로 설정 => for(int i=2; i<8; i++) pinMode(i, OUTPUT);
  for(int pin : BCD_PINS) pinMode(pin, OUTPUT);
  for(int pin : DIGIT_PINS) pinMode(pin, OUTPUT);
}

// BCD 출력 함수: 0~9 값을 받아 4비트 BCD 신호로 출력
void writeBcd(int num){
  for(int i= 0; i<4; i++) digitalWrite(BCD_PINS[i], bitRead(num, i));  
}

// 2자리 FND 멀티플렉싱 함수
// 한 번 호출 시: 10의 자리 => 잠깐 표시, 1의 자리 => 잠깐 표시
void multiplexFnd(int value){
  // 전체 숫자를 10의 자리와 1의 자리로 분리
  int tens = value / 10;
  int ones = value % 10; 

  // 10의 자리 표시
  // 10의 자리 숫자를 BCD 신호로 출력
  writeBcd(tens);
  digitalWrite(DIGIT_PINS[0],HIGH);
  digitalWrite(DIGIT_PINS[1],LOW);

  // 표시 유지 시간
  // LED와 사람의 눈이 인식할 수 있도록 최소 수 ms 필요
  delayMicroseconds(2000); // 2ms

  // 1의 자리 표시
  writeBcd(ones);
  digitalWrite(DIGIT_PINS[0],LOW);
  digitalWrite(DIGIT_PINS[1],HIGH);
  delayMicroseconds(2000); // 2ms
}

void loop() {
  // 멀티플렉싱 함수 호출
  // FND 표시를 위해서 매우 빠르게 반복 실행됨
  multiplexFnd(fndValue);
  // 100ms마다 숫자를 1씩 증가
  if(millis() - previousCountMillis >= 100){
    // 기준 시간 갱신
    previousCountMillis = millis();
    fndValue = (fndValue + 1) % 100; // 0~99 반복 카운트
  }

}




