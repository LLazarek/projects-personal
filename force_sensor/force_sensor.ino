#define coeff -0.0763401763
#define intercept 32.6997641672

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  double val = (analogRead(A0) + analogRead(A1))/2;
  Serial.println(coeff*val + intercept);
  delay(10);
}
