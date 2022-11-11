#include <NewPing.h>
#include <Servo.h>

Servo myservo;


#define TRIGGER_PIN 11 
#define ECHO_PIN 10 
#define MAX_DISTANCE 1500

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

#define motor_aPin1 A0
#define motor_aPin2 A1
#define motor_bPin1 A2
#define motor_bPin2 A3
#define motor_aEnable 5
#define motor_bEnable 6
#define OB_range 50

int i=0, pos = 0,current_distance=0;
int range0=0, range30=0, range60=0, range85=0,range90=0,range95=0, range120=0, range150=0, range180=0 ;
unsigned long previous_millis = 0;
char serialData;

void setup() 
{
 Serial.begin(9600);
 myservo.attach(9); 


pinMode(motor_aPin1,OUTPUT);
 pinMode(motor_aPin2,OUTPUT);
 pinMode(motor_bPin1,OUTPUT);
 pinMode(motor_bPin2,OUTPUT);
 pinMode(motor_aEnable,OUTPUT);
 pinMode(motor_bEnable,OUTPUT);
analogWrite(motor_aEnable,200);
analogWrite(motor_bEnable,200);


}

void brake()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);
 
}

void forward()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}

void forward_left()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);
 
}

void forward_right()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}

void backward()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
 
}

void backward_right()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
 
}
void backward_left()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,LOW);

}

void left()
{
 digitalWrite(motor_aPin1,LOW);
 digitalWrite(motor_aPin2,HIGH);
 digitalWrite(motor_bPin1,HIGH);
 digitalWrite(motor_bPin2,LOW);
 
}

void right()
{
 digitalWrite(motor_aPin1,HIGH);
 digitalWrite(motor_aPin2,LOW);
 digitalWrite(motor_bPin1,LOW);
 digitalWrite(motor_bPin2,HIGH);
 
}
int range(int pos)
{
 myservo.write(pos);
 delay(300);
 current_distance = sonar.ping_cm();
 if(current_distance==0)
 current_distance=100;
 if(current_distance > 0 && current_distance < 15){
 Serial.print("B");
 if(pos==90){ 
 backward();delay(500);}
 if(pos < 90){
 backward_right();delay(500);}
 if(pos > 90){
 backward_left();delay(500);}
 return current_distance; 
 
}}

void loop()

{


Automatic: brake();
 delay(300);

while(1){
 
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='M')
 goto Manual;


 above: range90=0;
 
 range90=range(90);
 delay(10);
 
 
 while(range90 >= OB_range ){
 
 if(millis()-previous_millis>2000){
 previous_millis=millis();
 range(180);
 delay(100); 
 range(0);
 delay(100);}
 
 range90=range(90);
 analogWrite(motor_aEnable,150);
 analogWrite(motor_bEnable,150);
 
 forward(); Serial.print("F");
 
 
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='M')
 goto Manual; 
 }
 brake();


 if(range90 <OB_range)
 { 
 analogWrite(motor_aEnable,100);
 analogWrite(motor_bEnable,100);
 brake();
 range60=0;
 range60=range(60);
 delay(200);
 range120=0;
 range120=range(120);
 delay(200);
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='M')
 goto Manual;
 
 if(range60 >OB_range || range120 >OB_range )
 {
 
 if(range60 >= range120){
 forward_right();Serial.print("R");
 delay(100);goto above;}
 
 else if(range60 < range120){
 forward_left();Serial.print("L");
 delay(100);goto above;}
 }


 if(range60 <OB_range && range120 <OB_range)
 {
above1: range30=0;
 range30=range(30);
 delay(400);
 range150=0;
 range150=range(150);
 delay(400);
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='M')
 goto Manual;
 
 if(range30 >OB_range || range150 >OB_range )
 {
 
 if(range30 >= range150){
 right();Serial.print("R");
 delay(300);goto above;}
 
 else if(range30 < range150){
 left();Serial.print("L");
 delay(300);goto above;}
 }
 if(range30 <OB_range && range150 <OB_range)
 {
 range0=0;
 range0=range(0);
 delay(500);
 range180=0;
 range180=range(180);
 delay(500);
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='M')
 goto Manual;
 
 if(range0 >OB_range || range180 >OB_range )
 {
 
 if(range0 >= range180){
 backward_right();Serial.print("R");
 delay(200);goto above;}
 
 else if(range0 < range180){
 backward_left();Serial.print("L");
 delay(200);goto above;}
 }
 if(range0 <OB_range && range180 <OB_range)
 {
 backward();Serial.print("B");
 delay(200);
 goto above1; 
 } 
 }
 } 
 }
 }

Manual: brake();
 delay(0);


 while(1){
 if(Serial.available()>0)
 serialData=Serial.read();
 if(serialData=='A')
 goto Automatic; 
 
 if(serialData=='F')
 forward(); 
 if(serialData=='B')
 backward();
 if(serialData=='S')
 brake(); 
 if(serialData=='L')
 left();
 if(serialData=='R')
 right();
 } 
}
