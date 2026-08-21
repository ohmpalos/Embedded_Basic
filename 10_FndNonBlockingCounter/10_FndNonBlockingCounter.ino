// 예제 10: FndNonBlockingCounter
// 비차단 99진 상향 카운터(2자리 FND 멀티플렉싱) 제어

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

  // 현재 켜야 할 자릿수 판별하는 정적변수를 선언(true: 10의 자리, false: 1의 자리)
  static bool tensActive = true;
  // 마지막 자릿수 전환 시간을 저장하는 정적 변수 선언
  static unsigned long lastMux = 0;

  if(millis() - lastMux < 3){
    return; // 3ms가 안 지났으면 화면을 유지한 채 함수를 탈출
  }

  lastMux = millis(); // 기준 시간 갱신
  
  // 전체 숫자를 10의 자리와 1의 자리로 분리
  int tens = value / 10;
  int ones = value % 10; 

  // 조건에 따라 순차적으로 한 자릿수씩만 출력
  if(tensActive){
    // 10의 자리 출력
    writeBcd(tens);
    digitalWrite(DIGIT_PINS[0], HIGH);
    digitalWrite(DIGIT_PINS[1], LOW);
  }
  else{
    // 1의 자리 출력 
    writeBcd(ones);
    digitalWrite(DIGIT_PINS[0], LOW);
    digitalWrite(DIGIT_PINS[1], HIGH);
  }
  // 다음 3ms 뒤에는 반대쪽 자릿수가 켜지도록 토글
  tensActive = !tensActive;    
}

void loop() {
  // 현재 시간을 측정하여 now 변수에 저장
  unsigned long now = millis();

  // 멀티플렉싱 함수 호출
  // FND 표시를 위해서 매우 빠르게 반복 실행됨
  multiplexFnd(fndValue);

  // 100ms마다 숫자를 1씩 증가
  if(now - previousCountMillis >= 100){
    // 기준 시간 갱신
    previousCountMillis = now;
    fndValue = (fndValue + 1) % 100; // 0~99 반복 카운트
  }

}




