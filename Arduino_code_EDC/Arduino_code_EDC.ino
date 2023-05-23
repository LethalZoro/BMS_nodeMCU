#define p0 A0
#define p1 A1
#define p2 A2
#define g A3


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(p0,INPUT);
  pinMode(p1,INPUT);
  pinMode(p2,INPUT);
  pinMode(g,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float V1=analogRead(p0);
  float V2=analogRead(p1);
  float V3=analogRead(p2);
  float G  =analogRead(g);
  // float c=5/1024;
  // Serial.println(c);
  V1=V1-G;
  V2=V2-G;
  V3=V3-G;
  V1=V1*5/1024;
  V2=V2*5/1024;
  V3=V3*5/1024;
  V1=3*V1-3*V2;
  V2=3*V2-3*V3;
  V3=3*V3;
  String msg;
    msg=String("Battery 1 voltage is : ")+String(V1)+String(" volts \n")+String("Battery 2 voltage is : ")+String(V2)+String(" volts \n")+String("Battery 3 voltage is : ")+String(V3)+String(" volts ?\n ");
    delay(1000);
  Serial.println(msg);
}
