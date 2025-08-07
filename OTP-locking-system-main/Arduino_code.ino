#include <Servo.h>
String dicid;
String pwd;
String otpp = "";
String numbers[4]={"3213", "213213", "543646","2231" };
int sled1=12;
int sled2=13;
Servo myservo;
void setup() {
Serial.begin(9600);
myservo.attach(9);
pinMode(sled1,1);
pinMode(sled2,1);
}
void loop() {
while (Serial.available ()==0); 
dicid=Serial.readStringUntil('\n');
if (dicid== "asdfg") {
  otp();
  digitalWrite(sled1, 1);
}
check();

}

void otp() {
    otpp = numbers [random(0, 4)];
  Serial.println (otpp+"\n");

}
void check(){
  while (Serial.available()==0);
 pwd=Serial.readStringUntil('\n');

if (pwd == otpp ){
  Serial.println ("unlocked");
  myservo.write(120); 
  digitalWrite(sled2,1); 
  digitalWrite(sled1,0);
}
if (pwd != otpp ){
  Serial.println("reset try again"); 
  myservo.write(50);
  digitalWrite(sled2,0);
  digitalWrite(sled1,1);
}
}