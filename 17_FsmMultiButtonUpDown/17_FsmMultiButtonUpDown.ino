// 예제 17: 독립형 3버튼 FSM 기반 가변 주기 양방향(Up/Down) 카운터 시스템
/*
ㅁ 상태 구성 및 하드웨어 동작:
 - IDLE       : FND = "00" 초기화 고정, RGB LED = OFF (소등)
 - UP_COUNT   : 1000ms(1초)마다 카운트 증가 (00~99 순환), RGB LED = GREEN
 - DOWN_COUNT : 500ms(0.5초)마다 카운트 감소 (99~00 순환), RGB LED = BLUE
 - PAUSE      : 현재 카운트 값 그대로 고정 유지 (정지), RGB LED = RED
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
  IDLE, // 초기 대기 상태(FND=00, LED OFF)
  UPCNT, // 1초 주기로 상향 카운트 상태
  DNCNT, // 0.5초 주기로 하향 카운트 상태
  PAUSE // 일시정지 상태(값 고정), R LED ON
};

// 시스템의 현재 상태를 저장할 변수 선언 및 초기화
State currentState = IDLE;

// 시간 및 디스플레이 제어 전역 변수
// 카운트 증감 타이밍(가변 주기) 제어용 타이머 변수
unsigned long lastCountMillis = 0;

// fnd에 표시할 현재 전체 수치 값(00~99) 저장할 변수
int fndValue = 0;

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

void handleSwitch(){
  int currentSw1Value = digitalRead(SW1);
  int currentSw2Value = digitalRead(SW2);
  int currentSw3Value = digitalRead(SW3);

  if(previousSw1Value == LOW && currentSw1Value == HIGH){
    currentState = UPCNT;
    lastCountMillis = millis();
  }

  if(previousSw2Value == LOW && currentSw2Value == HIGH){
    currentState = DNCNT;
    lastCountMillis = millis();
  }

  if(previousSw3Value == LOW && currentSw3Value == HIGH){
    currentState = PAUSE;
  }

  // 현재 상태를 이전 상태로 백업
  previousSw1Value = currentSw1Value;
  previousSw2Value = currentSw2Value;
  previousSw3Value = currentSw3Value;
}

void loop() {
  unsigned long now = millis();
  multiplexFnd(fndValue);
  handleSwitch();
  // 상태별 동작 로직
  switch (currentState){
    case IDLE:
      fndValue = 0;
      setRgb(0, 0, 0); // setRgb(false, false, false);
      break;

    case UPCNT:
      setRgb(0,1,0);
      if(now - lastCountMillis >= 1000){
        lastCountMillis = now;
        fndValue = (fndValue + 1) % 100; 
      }
      break;

    case DNCNT:
      setRgb(0,0,1);
      if(now - lastCountMillis >= 500){
        lastCountMillis = now;
        fndValue--;
        if(fndValue < 0){
          fndValue = 99;
        }
      }
      break;

    case PAUSE:
      setRgb(1,0,0);
      break;
  }
}











