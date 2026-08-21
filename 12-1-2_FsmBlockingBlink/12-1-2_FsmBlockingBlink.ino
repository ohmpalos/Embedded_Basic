// // 예제 12-1: FSM 유한 상태 머신을 이용한 LED Blink
// // CPU가 멈추는 Blocking 제어

// // 핀 정의
// const int PIN_G = 9;

// // 상태 정의
// // enum(Enumeration, 열거형)으로 정수 상수를 이름으로 정의
// // 여러 개의 상태를 이름으로 정의할 때 사용
// // 내부적으로는 정수값으로 저장
// // IDLE(0), RUN(1)
// enum State{
//   IDLE, // 0
//   RUN // 1
// };

// // 시스템의 현재 상태를 저장하는 변수를 선언 및 초기화
// State currentState = IDLE;

// void setup() {
//   pinMode(PIN_G, OUTPUT);
// }

// void loop() {
//   // 상태별 동작 처리 로직 구현(switch ~ case문 활용)
//   switch (currentState){
//     case IDLE: // IDLE 상태인 경우
//       digitalWrite(PIN_G, LOW);
//       currentState = RUN; // 현재 상태를 RUN 상태로 변경(전이: Transition)
//       break;

//     case RUN:
//       digitalWrite(PIN_G, HIGH);
//       currentState = IDLE;
//       break;
//     default: // 생략 가능!
//       break;    
//   }
//   delay(500); // CPU 멈춤(Blocking)
// }


// // 예제 12-2: FSM 유한 상태 머신을 이용한 LED Blink
// // CPU가 멈추지 않는 Non-Blocking 제어

// // 핀 정의
// const int PIN_B = 8;

// // FSM 상태 정의
// // enum(Enumeration, 열거형)으로 정수 상수를 이름으로 정의한 열거형 사용자 정의 자료형
// // 여러 개의 상태를 이름으로 정의할 때 사용
// // 내부적으로는 정수값으로 저장
// // IDLE(0), RUN(1)
// // State는 열거형 자료형의 이름
// enum State{
//   IDLE, // LED OFF(0)
//   RUN // LED ON(1)
// };

// // 시스템의 현재 상태를 저장하는 변수를 선언 및 초기화
// State currentState = IDLE;

// // 리택토링 추가: 각 상태가 시작된 시점의 시간(ms)을 기록할 타이머 변수
// unsigned long stateStartTime = 0;

// void setup() {
//   pinMode(PIN_B, OUTPUT);
// }

// void loop() {
//   // 아두이노가 부팅된 후 흘러간 시간을 실시간으로 측정
//   unsigned long now = millis();

//   // 상태별 동작 처리 로직 구현(switch ~ case문 활용)
//   switch (currentState){
//     case IDLE: // IDLE 상태인 경우
//       digitalWrite(PIN_B, LOW);
//       // 리팩토링 핵심: delay() 함수 대신 millis()함수를 이용하여
//       // 시간 차이를 검사
//       if(now - stateStartTime >= 500){
//         currentState = RUN; // 0.5초가 지나면 RUN 상태로 전환
//         stateStartTime = now; // RUN 상태의 시작 시간으로 타이머를 갱신
//       }
//       break;

//     case RUN:
//       digitalWrite(PIN_B, HIGH);
//       if(now - stateStartTime >= 500){
//         currentState = IDLE;
//         stateStartTime = now;
//       }
//       break;
//     default: // 생략 가능!
//       break;    
//   }
//   delay(500); // CPU 멈춤(Blocking)
// }


// 예제 12-3: FSM 유한 상태 머신을 이용한 LED Blink
// CPU가 멈추지 않는 Non-Blocking 제어
// chageState() 함수로 리팩토링

// 핀 정의
const int PIN_B = 10;

// FSM 상태 정의
// enum(Enumeration, 열거형)으로 정수 상수를 이름으로 정의한 열거형 사용자 정의 자료형
// 여러 개의 상태를 이름으로 정의할 때 사용
// 내부적으로는 정수값으로 저장
// IDLE(0), RUN(1)
// State는 열거형 자료형의 이름
enum State{
  IDLE, // LED OFF(0)
  RUN // LED ON(1)
};

// 시스템의 현재 상태를 저장하는 변수를 선언 및 초기화
State currentState = IDLE;

// 리택토링 추가: 각 상태가 시작된 시점의 시간(ms)을 기록할 타이머 변수
unsigned long stateStartTime = 0;

void setup() {
  pinMode(PIN_B, OUTPUT);
}

// 상태를 전환하는 사용자 정의 함수
void chageState(State newState){
  currentState = newState;
  stateStartTime = millis();
}

void loop() {
  // 아두이노가 부팅된 후 흘러간 시간을 실시간으로 측정
  unsigned long now = millis();

  // 상태별 동작 처리 로직 구현(switch ~ case문 활용)
  switch (currentState){
    case IDLE: // IDLE 상태인 경우
      digitalWrite(PIN_B, LOW);
      // 리팩토링 핵심: delay() 함수 대신 millis()함수를 이용하여
      // 시간 차이를 검사
      if(now - stateStartTime >= 500){
        chageState(RUN);
      }
      break;

    case RUN:
      digitalWrite(PIN_B, HIGH);
      if(now - stateStartTime >= 500){
        chageState(IDLE);
      }
      break;
    default: // 생략 가능!
      break;    
  }
  delay(500); // CPU 멈춤(Blocking)
}









