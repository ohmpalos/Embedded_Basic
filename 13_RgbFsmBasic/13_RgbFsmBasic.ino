// 예제 13: FSM 기반 RGB LED 제어
// FSM + 비차단 제어: 여러 색상을 1초 간격으로 매끄럽게 전환 설계된 구조의 코드

// 하드웨어 핀 정의(상수)
const int PIN_R = 10; 
const int PIN_G = 9; 
const int PIN_B = 8; 

// FSM 상태 정의
enum State{
  INIT, // 초기 소등 상태(0)
  RED, // R LED ON(1)
  GREEN, // G LED ON(2)
  BLUE, // B LED ON(3)
  WHITE, // WHITE COLOR ON(4)
  OFF_STATE // 중간 소등 상태 정의(5)
};

// 현재 상태를 저장할 변수 선언 및 초기화
State currentState = INIT;

// 특정 상태가 시작(진입)한 시점의 아두이노 경과 시간(ms)을 저장하는 변수 선언
unsigned long stateStartTime = 0;

void setup() {
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  // 아두이노가 부팅된 직후의 최초 시간을 초기 상태(INIT) 시작 시간으로 저장
  stateStartTime = millis(); // 생략 가능! 
}

// RGB LED 제어 함수 정의
void setRgb(bool r, bool g, bool b){
  // 3항 연산자를 사용해 r, g, b 값이 1(true)이면 HIGH, 0(false)이면 LOW를 출력
  digitalWrite(PIN_R, r? HIGH : LOW);
  digitalWrite(PIN_G, g? HIGH : LOW);
  digitalWrite(PIN_B, b? HIGH : LOW);
}

void loop() {
  // 현재 시간을 now 변수에 저장
  unsigned long now = millis();

  // FSM 상태별 동작 로직 구현(분기 처리)
  switch (currentState){
    case INIT:
      setRgb(0,0,0); // 모두 LED OFF, setRgb(false, false, false)
      // 시간 검사: 현재 유지 시간이 1000ms 이상이 되었는지 확인
      if(now - stateStartTime >= 1000){
        currentState = RED; 
        stateStartTime = now;
      }
      break;

    case RED:
      setRgb(1,0,0); // R LED ON, setRgb(true, false, false)
      // 시간 검사: 현재 유지 시간이 1000ms 이상이 되었는지 확인
      if(now - stateStartTime >= 1000){
        currentState = GREEN; 
        stateStartTime = now;
      }
      break;

    case GREEN:
      setRgb(0,1,0); // G LED ON, setRgb(false, true, false)
      // 시간 검사: 현재 유지 시간이 1000ms 이상이 되었는지 확인
      if(now - stateStartTime >= 1000){
        currentState = BLUE; 
        stateStartTime = now;
      }
      break; 
    case BLUE:
      setRgb(0,0,1); // G LED ON, setRgb(false, true, false)
      // 시간 검사: 현재 유지 시간이 1000ms 이상이 되었는지 확인
      if(now - stateStartTime >= 1000){
        currentState = WHITE; 
        stateStartTime = now;
      }
      break; 

    case WHITE:
      setRgb(1,1,1); // RGB LED all ON, setRgb(true, true, true)
      // 시간 검사: 현재 유지 시간이 1000ms 이상이 되었는지 확인
      if(now - stateStartTime >= 1000){
        currentState = RED; 
        stateStartTime = now;
      }
      break;     
  }

}














