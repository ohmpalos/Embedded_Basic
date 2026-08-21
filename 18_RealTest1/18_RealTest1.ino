// 예제 18: 실전문제 1 풀이
/*
[기능 요약]
  1. INIT 초기화 동작 : 4초 동안 FND 88 점멸 및 RGB LED 순차 점등 후 IDLE 행
   |_ 88-소등-88-소등-00(유지)
   |_ R-  G  -B-소등 -R(유지)
  2. RUN1 : 2초 연출 후 0.5초 주기로 00~99 반복 증가, B LED 0.5초 간격 점멸
   |_ 88  - 88 -88 -88 -00, 11, 22, ..., 99, 00, 11,...
   |_ 소등-소등 -G  -R  -B 0.5초 점멸
  3. RUN2 : 2초 연출 후 0.5초 주기로 99~00 반복 감소, G LED 0.5초 간격 점멸
   |_ 88 - 88 - 88  - 88   - 99, 88, 77, ...00, 99, 88, ...
   |_ B  - R  - 소등 - 소등 - G 0.5초 점멸 
  4. PAUSE : 현재 숫자 유지하며 2초 ON / 2초 OFF를 2회 반복(총 8초)       후 이전 카운트 시점으로 복귀
   |_ R-G-B-소등(각 2초간)
*/

// 하드웨어 핀 정의
const int BCD_PINS[4] = {2, 3, 4, 5};
const int DIGIT_PINS[2] = {6, 7};

const int PIN_R = 10;
const int PIN_G = 9;
const int PIN_B = 8;

const int SW1 = 13;
const int SW2 = 12;
const int SW3 = 11;

// FSM 상태 정의
enum State{
  INIT, // 초기화 상태
  IDLE, // 대기 상태
  RUN1, // 증가 카운트 상태
  RUN2, // 감소 카운트 상태
  PAUSE1, // 동작 1 업 카운트 중 일시 정지 상태
  PAUSE2 // 동작 2 다운 카운트 중 일시 정지 상태 
};

// 시스템의 현재 상태를 저장할 변수 선언 및 초기화
State currentState = INIT;

// 시간 및 디스플레이 제어 전역 변수
// 특정 상태에 진입한 시간의 저장하는 변수
unsigned long stateStartTime = 0;

// fnd에 표시할 현재 전체 수치 값(00~99) 저장할 변수
int fndValue = 0;

// 동작 1, 2 도중 일시정지 버튼을 눌렸을 때, 당시의 카운트 값을 저장할 변수
int pauseValue = 0;

// 개별 스위치 상승 모서리 검출하기 위한 이전 상태 저장 변수
int previousSw1Value = HIGH;
int previousSw2Value = HIGH;
int previousSw3Value = HIGH;

void setup() {
  for(int pin : BCD_PINS) pinMode(pin, OUTPUT);
  for(int pin : DIGIT_PINS) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);

  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
// 상태 시작 시간 설정(생략 가능!)
  stateStartTime = millis();
}

// RGB LED 제어 함수
void setRgb(bool r, bool g, bool b){
  digitalWrite(PIN_R, r? HIGH : LOW);
  digitalWrite(PIN_G, g? HIGH : LOW);
  digitalWrite(PIN_B, b? HIGH : LOW);
}

// BCD 출력 함수
void writeBcd(int num){
  for(int i=0; i<4; i++){
    digitalWrite(BCD_PINS[i], bitRead(num, i));
  }
}

// 멀티플렉싱 함수
void multiplexFnd(int value){
  static bool tensActive = true;
  static unsigned long lastMux = 0;

  if(millis()- lastMux < 3) return;

  lastMux = millis();

  // 특수 처리: 넘겨받은 데이터가 -1이면 FND 전체를 소등(Blanking) 시킴
  if(value == -1){
    digitalWrite(DIGIT_PINS[0], LOW); // 10의 자리 끄기
    digitalWrite(DIGIT_PINS[1], LOW); // 1의 자리 끄기
    return;
  }

  int tens = value / 10;
  int ones = value % 10;

  if(tensActive){
    writeBcd(tens);
    digitalWrite(DIGIT_PINS[0], HIGH);
    digitalWrite(DIGIT_PINS[1], LOW);
  }
  else{
    writeBcd(ones);
    digitalWrite(DIGIT_PINS[0], LOW);
    digitalWrite(DIGIT_PINS[1], HIGH);
  }

  tensActive = !tensActive;
}

void changeState(State newState){
  currentState = newState; // 시스템 상태를 새로운 상태로 갱신
  stateStartTime = millis(); // 상태가 바뀐 방금 이 순간의 시간을 기록
}

void handleSwitch(){
  int currentSw1Value = digitalRead(SW1);
  int currentSw2Value = digitalRead(SW2);
  int currentSw3Value = digitalRead(SW3);

  // SW1을 눌렀다 떼면 => 동작 1 상태로 전환
  // 동작 1 동작 중 SW1을 눌렀다 떼면 => PAUSE1 상태로 전환
  if(previousSw1Value == LOW && currentSw1Value == HIGH){
    // IDLE 또는 RUN2 상태에서 RUN1으로 전환
    if(currentState == IDLE || currentState == RUN2){
      // currentState = RUN1;
      // stateStartTime = millis();
      changeState(RUN1);
    }
    // 이미 동작 1 상태인데 다시 SW1을 누르면 일시정지 상태 전환
    else if(currentState == RUN1){
      pauseValue = fndValue;
      changeState(PAUSE1);
    }
  }

  // SW2를 눌렀다 떼면 => 동작 2 상태로 전환
  // 동작 2 수행 중 SW2을 눌렀다 떼면 => PAUSE2 상태로 전환
  if(previousSw2Value == LOW && currentSw2Value == HIGH){
    // IDLE 또는 RUN1 상태에서 RUN2으로 전환
    if(currentState == IDLE || currentState == RUN1){
      // currentState = RUN1;
      // stateStartTime = millis();
      changeState(RUN2);
    }
    // 이미 동작 2 상태인데 다시 SW2을 누르면 일시정지 상태 전환
    else if(currentState == RUN2){
      pauseValue = fndValue;
      changeState(PAUSE2);
    }
  }

  // SW3 처리
  // 카운트가 한창 진행 중인 동작 1 또는 동작 2 상태일 때만 작동
  // &&(논리곱), ||(논리합)
  if(previousSw3Value == LOW && currentSw3Value == HIGH && (currentState == RUN1 || currentState == RUN2)){
    changeState(INIT);
  }

  // 현재 상태를 이전 상태로 백업
  previousSw1Value = currentSw1Value;
  previousSw2Value = currentSw2Value;
  previousSw3Value = currentSw3Value;
}

// INIT 동작 

void runInit(unsigned long now){
  // INIT 상태 진입 후 경과 시간을 계산
  unsigned long t = now - stateStartTime;
  if(t < 4000){
    if((t / 1000) % 2 == 0){
      fndValue = 88;
    }
    else{
      fndValue = -1;
    }
    // RGB LED 동작 처리
    if(t < 1000) setRgb(1,0,0);
    else if(t<2000) setRgb(0,1,0);
    else if(t<3000) setRgb(0,0,1);
    else setRgb(0,0,0);
  }
  else{
    // 4초가 만료되면 초기화 연출 완료 처리
    currentState = IDLE;
    fndValue = 0;
    setRgb(1,0,0);
  }
}

// IDLE 상태 함수
void runIdle(){
  fndValue = 0;
  setRgb(1,0,0);
}

// RUN1 상태 함수
void runAction1(unsigned long now){
  unsigned long t = now - stateStartTime;
  // 시작 후 최초 2초 동안 특수 연출 구간
  if(t < 2000){
    fndValue = 88;
    if(t < 500) setRgb(0,0,0);
    else if(t<1000) setRgb(0,0,0);
    else if(t<1500) setRgb(0,1,0);
    else setRgb(1,0,0);
  }
  else{
    // 2초 이후에 메인 증가 카운트 구간
    // 경과시간에서 2초 연출시간을 제외
    // 실제 카운트 동작에 필요한 경과 시간을 저장하는 변수(ct) 생성
    unsigned long ct = t - 2000;
    // 500ms마다 숫자가 1씩 증가
    // 10이 되는 순간 나머지 연산을 의해 다시 0으로 순환
    int digit = (ct / 500) % 10;
    
    fndValue = digit * 11;

    // B LED 0.5초 주기 점멸 동작 로직
    if(ct % 1000 < 500){
      setRgb(0,0,1);
    }
    else{
      setRgb(0,0,0);
    }
  }
}

// RUN2 상태 함수
void runAction2(unsigned long now){
  unsigned long t = now - stateStartTime;
  // 시작 후 최초 2초 동안 특수 연출 구간
  if(t < 2000){
    fndValue = 88;
    if(t < 500) setRgb(0,0,1);
    else if(t<1000) setRgb(1,0,0);
    else if(t<1500) setRgb(0,0,0);
    else setRgb(0,0,0);
  }
  else{
    // 2초 이후에 메인 감소 카운트 구간
    // 경과시간에서 2초 연출시간을 제외
    // 실제 카운트 동작에 필요한 경과 시간을 저장하는 변수(ct) 생성
    unsigned long ct = t - 2000;
    // 500ms마다 숫자가 1씩 증가
    // 10이 되는 순간 나머지 연산을 의해 다시 0으로 순환
    int digit = 9 - (ct / 500) % 10;
    
    fndValue = digit * 11;

    // G LED 0.5초 주기 점멸 동작 로직
    if(ct % 1000 < 500){
      setRgb(0,1,0);
    }
    else{
      setRgb(0,0,0);
    }
  }
}

// PAUSE 상태 함수
void runPause(unsigned long now, State nextState){
  unsigned long t = now - stateStartTime;

  if(t < 8000){
    if(t < 2000){
      fndValue = pauseValue;
      setRgb(1,0,0);
    }
    else if(t < 4000){
      fndValue = -1;
      setRgb(0,1,0);      
    }
    else if(t < 6000){
      fndValue = pauseValue;
      setRgb(0,0,1);
    }
    else{
      fndValue = -1;
      setRgb(0,0,0);
    }
  }
  // 8초 초기 연출 후 이전 카운트 상태로 완벽 복귀 과정
  else{
    currentState = nextState;
    // 복귀 후 카운트가 가리키고 있던 시점으로 강제로 만들기 위해 시간 왜곡
    unsigned long passed;
    if(nextState == RUN1){
      int digit = pauseValue / 11; 
      passed = digit*500 + 2000;
    }
    // 복귀 상태가 RUN2일 때
    else{
      if(nextState == RUN1){
      int digit = 9 - pauseValue / 11; 
      passed = digit*500 + 2000;
      }
    }
    stateStartTime = millis() - passed;
  }
}


void loop() {
  unsigned long now = millis();
  multiplexFnd(fndValue);
  
  // 상태 전환 스위치 처리 함수를 호출
  // 현재 상태가 INIT 상태이거나 일시정지(PAUSE1, 2) 상태가 '아닐 때만'
  // 스위치 입력을 허용
  // !(INIT 또는 PAUSE) => 코드화 => !(currentState == INIT || curtentState == PAUSE)
  // 드모르간 법칙을 적용
  // (currentState != INIT) && (curtentState != PAUSE)
  if(currentState != INIT && currentState != PAUSE1 && currentState != PAUSE2){
    handleSwitch();
  }

  // 상태별 동작 로직
  switch (currentState){
    case INIT: runInit(now); break; // 초기화 연출 실행
    case IDLE: runIdle(); break; // 대기 상태 실행
    case RUN1: runAction1(now); break; // 증가 카운트 연출/동작 실행
    case RUN2: runAction2(now); break; // 감소 카운트 연출/동작 실행
    // RUN1에서 멈춘 일시정지 동작 실행
    case PAUSE1: runPause(now, RUN1); break;
    // RUN2에서 멈춘 일시정지 동작 실행
    case PA/USE2: runPause(now, RUN2); break;    
  }
}  