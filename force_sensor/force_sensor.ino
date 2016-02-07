#define coeff 0.1032861167
#define intercept 25.0678377612

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  double val = analogRead(A1);
  //double val = (analogRead(A0) + analogRead(A1))/2;
  Serial.println(coeff*val + intercept);
  delay(10);
}
