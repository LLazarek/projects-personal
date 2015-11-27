#define coeff -0.103792
#define intercept 26.21291046

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  double val = (analogRead(A0) + analogRead(A1))/2;
  Serial.println(coeff*val + intercept);
  delay(10);
}
