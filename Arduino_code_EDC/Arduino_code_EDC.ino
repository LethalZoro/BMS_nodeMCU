#define positive A0
#define negative A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(positive,INPUT);
  pinMode(negative,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  float Vp=analogRead(positive);
  float Vn=analogRead(negative);
  float V=Vp-Vn;
  V=V*5/1024;
  float I =69.0;
  // Serial.println(V);
  // delay(500);
  String msg;
    msg=String("The Voltage is : ")+String(V)+String(" volts ? \nThe current is : ")+String(I)+String(" A ?");
    delay(1000);
  Serial.println(msg);
}
