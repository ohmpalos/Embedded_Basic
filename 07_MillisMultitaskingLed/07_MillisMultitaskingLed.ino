// 예제 7: 07_MillisMultitaskingLed
// G LED는 1초 간격으로 계속 깜빡이면서, 아두이노가 멈추지 않고
// 스위치 입력까지 실시간으로 감시하여 B LED를 즉시 제어하는 코드

// 핀 번호 설정
const int PIN_G = 9;
const int PIN_B = 8;
const int SW1 = 13;

// 스위치 및 LED 관련 시간 및 상태 변수 선언
unsigned long lastTime = 0;
bool ledStateG = false;

// 스위치 및 B LED 관련 상태 변수 선언
int previousSw1State = HIGH; // 이전 버튼 상태
bool ledStateB = false; //  B LED 상태

void setup() {
  // 핀 모드 설정
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(SW1, INPUT);
  // LED 초기 상태 적용(OFF)
  digitalWrite(PIN_G, ledStateG);
  digitalWrite(PIN_B, ledStateB);
}

void loop() {
  // 현재 시간을 now 변수에 저장
  unsigned long now = millis();

  // Task 1: G LED 1초 간격 비차단 자동 토글 로직
  if(now - lastTime >= 1000){
    lastTime = now; // 기준 시간 갱신
    ledStateG = !ledStateG; // 상태 반전
    digitalWrite(PIN_G, ledStateG);
  }
  // Task 2: 실시간 버튼 입력 감지 및 B LED 토글 로직
  int currentSw1State = digitalRead(SW1);
  // 버튼이 눌린 순간을 포착(상승 모서리를 감지)
  if(previousSw1State == LOW && currentSw1State == HIGH){
    ledStateB = !ledStateB; // B LED 상태 반전
    digitalWrite(PIN_B, ledStateB);
  }
  // 다음 루프 비교를 위해서 현재 버튼 상태를 저장
  previousSw1State = currentSw1State;
}









