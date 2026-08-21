// 예제 11: 버튼 1초 이상 Long Press 감지 및 LED 제어

// 핀 정의
const int SW1 = 13;
const int PIN_B = 8;

// 시간 및 상태 제어 변수를 선언
// 스위치를 누르기 시작한 시점의 시간을 저장할 변수 선언
unsigned long pressStartTime = 0;

// 현재 스위치가 눌려져 있는 상태인지 기록하는 변수 선언(true=눌림 상태)
bool ispressed = false;

void setup() {
  pinMode(SW1, INPUT);
  pinMode(PIN_B, OUTPUT);
}

void loop() {
  // 현재 경과 시간을 실시간으로 now 변수에 저장
  unsigned long now = millis();

  // 현재 스위치의 물리적 상태를 읽기
  int currentSw1State = digitalRead(SW1);

  // 스위치가 눌렸을 때
  if(currentSw1State == LOW){
    if(!ispressed){
    // 처음 눌린 순간
    ispressed = true; // 누름 상태로 전환
    pressStartTime = now; // 현재 시간을 누르기 시작한 시간으로 저장
    }
    else{
      // 이미 누르고 있는 상태
      // 현재 시간과 처음 누른 시간의 차이가 1000ms 이상이면 LED ON
      if(now - pressStartTime >= 1000){
        digitalWrite(PIN_B, HIGH);
      }
    }
  }
  // 스위치에서 손을 뗐을 때(HIGH 상태)
  else{
    ispressed = false;
    digitalWrite(PIN_B, LOW);
  }


}






