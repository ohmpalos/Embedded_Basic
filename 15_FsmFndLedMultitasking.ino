// 예제 15: 실무형 FSM + 2자리 FND 멀티플렉싱 + LED Blink
/*
 * [실무형 프로그래밍] FSM 상태머신 + 2자리 FND 멀티플렉싱 + LED Blink
 * 
 * 1. 기능 개요
 *  - 외부 풀업 스위치를 누른 후 뗄 때(상승 모서리) IDLE <-> RUN 상태가 전환
 *  - RUN 상태: 1초마다 FND 카운트 증가(00~99 순환) 및 0.5초마다 LED가 깜빡임
 *  - IDLE 상태: FND는 "00"을 고정 표시하고 LED는 완전히 점등(ON)
 * 2. 제어 특징:
 * - delay()를 전혀 사용하지 않는 millis() 기반 Non-Blocking 구조
 * - FND 디스플레이는 시스템의 현재 상태와 무관하게 loop 내부에서 항상
 *   멀티플렉싱을 유지
*/

// BCD 입력 핀 정의
const int BCD_PINS[4] = {2, 3, 4, 5};
// 자리 선택 핀 정의
const int DIGIT_PINS[2] = {6, 7}; 
// R LED 핀 정의
const int PIN_R = 10;
// 상태 전환용 외부 풀업 스위치 입력 핀 정의
const int SW1 = 13;

// FSM 상태 정의 열거형
enum State{
  IDLE, // 대기 상태(FND -"00" 고정, R LED ON)
  RUN   // 동작 상태(1초 단위로 UPCNT, LED 0.5초 주기로 점멸)
};

// 현재 상태를 저장할 변수 선언 및 초기화
State currentState = IDLE;

// 시간 및 값을 저장할 전역 변수 선언

// RUN 상태에서 FND 카운트 증가(1초 주기)를 위한 타이머
unsigned long lastCountMillis = 0;
// RUN 상태에서 LED 점멸(0.5초 주기)을 위한 타이머
unsigned long lastBlinkMillis = 0;

// FND에 표시할 현재 전체 수치 값(00~99)을 저장할 변수
int fndValue = 0;

// RUN 상태에서 깜빡이는 LED 켜짐/꺼짐 논리 상태를 저장할 변수
bool ledState = false;

// 스위치 이전 상태값을 저장할 변수(스위치 이벤트 검출)
int previousSw1State = HIGH;

void setup() {
  // BCD 입력 핀을 출력 모드로 설정
  for(int pin : BCD_PINS) pinMode(pin, OUTPUT);
  // FND 자릿수 선택 핀 출력 모드로 설정 및 초기 소등 처리
  for(int pin : DIGIT_PINS) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  // LED 출력 및 스위치 입력 모드 설정
  pinMode(PIN_R, OUTPUT);
  pinMode(SW1, INPUT);

  // LED 초기상태에서 OFF
  digitalWrite(PIN_R, LOW); // 생략 가능!
}

// BCD 출력 함수: 0~9 값을 받아 4비트 BCD 신호로 출력
void writeBcd(int num){
  for(int i= 0; i<4; i++) digitalWrite(BCD_PINS[i], bitRead(num, i));  
}

// 멀티플렉싱 함수 정의
void multiplexFnd(int value){
  static bool tensActive = true; // 자릿수 전환용 스위칭 플래그(t: 10의 자리, f: 1의 자리)
  // 마지막으로 자릿수 교체를 진행한 시간을 저장하는 정적 변수
  static unsigned long lastMux = 0;
  
  // 비차단 잔상 타이머: 자릿수 교체 후 3ms가 지나지 않았다면 즉시 리턴
  if(millis()- lastMux < 3){
    return;
  } 

  // 자릿수 스위칭 타임 스탬프 갱신
  lastMux = millis();

  // FND 표시값을 10, 1의 자리로 분리
  int tens = value / 10;
  int ones = value % 10;

  // 3항 연산자를 활용해서 켜야할 자릿수 전원 핀 제어
  writeBcd(tensActive? tens : ones);
  digitalWrite(DIGIT_PINS[0], tensActive? HIGH : LOW);
  digitalWrite(DIGIT_PINS[1], tensActive? LOW : HIGH);

  // 다음 스위칭 주기에 반대쪽 자릿수가 켜질 수 있도록 상태 토글
  tensActive = !tensActive;
}

void handleSwitch(){
  // 현재 스위치 입력값을 저장
  int currentSw1State = digitalRead(SW1);
  // 상승 모서리 검출(직전 LOW => 현재 HIGH)
  if(previousSw1State == LOW && currentSw1State == HIGH){
    if(currentState == IDLE){ // IDLE => RUN
      currentState = RUN;
      lastCountMillis = millis();
      lastBlinkMillis = millis();
    }
    // RUN => IDLE
    else{
      currentState = IDLE;
    }
  }
  // 다음 루프 회전 시 비교할 현재 상태를 저장
  previousSw1State = currentSw1State;
}

void loop() {
  // 현재 시간을 now 변수에 저장
  unsigned long now = millis();
  // 멀티플렉싱 함수를 호출
  multiplexFnd(fndValue);
  // 스위칭 상태 전이 함수를 호출
  handleSwitch();

  // FSM 상태별 동작 처리 로직 
  // RUN 상태: Up CNT, LED Toggle
  if(currentState == RUN){
    if(now - lastCountMillis >= 1000){
      lastCountMillis = now;
      fndValue = (fndValue + 1) % 100;
    }
    if(now - lastBlinkMillis >= 500){
      lastBlinkMillis = now;
      ledState = !ledState;
      digitalWrite(PIN_R, ledState);
    }
  }
  // IDLE 상태: FND 값을 초기화 및 LED 상시 점등 고정
  else if(currentState == IDLE){
    fndValue = 0;
    digitalWrite(PIN_R, HIGH);
  }

}









