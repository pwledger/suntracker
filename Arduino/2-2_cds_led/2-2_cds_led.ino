int CDS = A0;                       // 조도 센서 연결한 핀
int LED = 3;                        // LED 연결한 핀
 
void setup() {
  Serial.begin(9600);
  pinMode(CDS, INPUT);              // 조도 센서를 입력 핀으로 설정
  pinMode(LED,OUTPUT);              // LED를 출력 핀으로 설정
}
 
void loop() {
  int val = analogRead(CDS);        // 조도 센서의 측정 값을 val에 저장
  Serial.print("CDS_Sensor: ");
  Serial.println(val);              // 시리얼 모니터에 조도 센서의 측정 값 출력
 
  if(val > 500) {                   // 측정 값이 500 초과이면
    digitalWrite(LED, HIGH);        // LED 켜기
    Serial.println("LED ON");       // 시리얼 모니터에 출력
  }
  
  else {                            // 측정 값이 500 이하이면
    digitalWrite(LED, LOW);         // LED 끄기
    Serial.println("LED OFF");      // 시리얼 모니터에 출력
  }
 
  delay(200);                       // 0.2초 쉬고 반복(1000ms = 1s)
}
