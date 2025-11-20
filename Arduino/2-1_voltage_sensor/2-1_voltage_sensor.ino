void setup() {
  Serial.begin(9600);        // Initialize serial communication
}

void loop() {
  float temp;
  int val1;                  // Declare val1 as an integer
  float val2;
  int vall = analogRead(A0); // Read the analog value from A0

  temp = vall / 4.092;
  val1 = (int)temp;          // Convert temp to an integer
  val2 = val1 / 10.0;        // Ensure floating-point division

  Serial.print("전압 : ");
  Serial.print(val2);
  Serial.println("V");
  delay(100);
}
