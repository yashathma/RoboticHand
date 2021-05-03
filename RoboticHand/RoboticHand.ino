//I added notes for u
#include <Servo.h>

Servo thumb;  // create servo object to control a servo
Servo pointer;
Servo middle;
Servo ring;
Servo pinkie;


//sets the max for each servo for P1
int maxThumb = 100;
int maxPointer = 130;
int maxMiddle = 90;
int maxRing = 90;
int maxPinkie = 100;




void setup() {
  Serial.begin(9600);

//declare all the servos
thumb.attach(2);
pointer.attach(3);
middle.attach(4);
ring.attach(5);
pinkie.attach(6);


//set all servos to 0 
thumb.write(0);
pointer.write(0);
middle.write(0);
ring.write(0);
pinkie.write(0);
}

void loop() {
  //read pot's
 int thumbIn = analogRead(A0);
 int pointerIn = analogRead(A1);
 int middleIn = analogRead(A2);
 int ringIn = analogRead(A3);
 int pinkieIn = analogRead(A4);



//if the input is greater than 30, only then began showing it
if(thumbIn > 30){
   thumb.write(thumbIn/5); // 1023/180 = ~5 so this translates it (applies to every servo)
}
if(pointerIn > 30){
pointer.write(pointerIn / 5);

}
if(middleIn > 30){
middle.write(middleIn / 5.9);
}
if(ringIn > 30){
 ring.write(ringIn / 5);
}
if(pinkieIn > 30){
  pinkie.write(pinkieIn / 5);

}

delay(10); //this just makes it work better idk why
      
}

 

void maxAll(){ //method for fully extended fingers
    thumb.write(maxThumb);
  pointer.write(110);
  middle.write(maxMiddle);
  ring.write(maxRing);
  pinkie.write(maxPinkie);
}

void fuckYou(){ //self explanatory
  thumb.write(maxThumb);
  pointer.write(maxPointer);
  middle.write(0);
  ring.write(maxRing);
  pinkie.write(maxPinkie);
}

void clearAll(){
    thumb.write(0);
  pointer.write(0);
  middle.write(0);
  ring.write(0);
  pinkie.write(0);
}
