#include <Servo.h>

Servo wristRotation;
Servo thumb;
Servo pointer;
Servo middle;
Servo ring;
Servo pinkie;

Servo foreArmRotation;
Servo foreArmBend;

int VRx = A5;
int xPosition = 0;
int mapX = 0;

int wristPin = 2;
int wristRest = 90;
int wristPos = 90;

int thumbPin =3;
int pointerPin = 4;
int middlePin = 5;
int ringPin = 6; 
int pinkiePin = 7;

int thumbIn = 0;
int pointerIn = 0;
int middleIn = 0;
int ringIn = 0;
int pinkieIn = 0;

int foreArmRotationPin = 13    ;
int foreArmBendPin = 12;

int leftPin = 7;
int rightPin = 8;

int left = 0;
int right = 0;

int elbowBendPot = A15;
int elbowRotPot = A14n ;
int wristBendPot = A13;

int elbowBendPotInput = 0;
int elbowRotPotInput = 0;
int wristBendPotInput = 0;

void setup() {
  Serial.begin(9600); 
  
  pinMode(VRx, INPUT);
  
  wristRotation.attach(wristPin);
  
  thumb.attach(thumbPin);
  pointer.attach(pointerPin);
  middle.attach(middlePin);
  ring.attach(ringPin);
  pinkie.attach(pinkiePin);

  foreArmRotation.attach(foreArmRotationPin);
  foreArmBend.attach(foreArmBendPin);

  pinMode(leftPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
}

void loop() {
   
    thumbIn = analogRead(A0);
   pointerIn = analogRead(A1);
  middleIn = analogRead(A2);
   ringIn = analogRead(A3);
   pinkieIn = analogRead(A4);

  elbowBendPotInput = analogRead(A15);
  elbowRotPotInput = analogRead(A14);
  wristBendPotInput = analogRead(A13);
//
  rotateArm();
  bendWrist();
  bendElbow();
   
  


 


 thumb.write( outPutThumb());
 pointer.write(outPutPointer());
middle.write(outPutMiddle());
ring.write(outPutRing()) ;
pinkie.write(outPutPinkie());
   
}
void bendElbow(){
  if(elbowBendPotInput > 400 && elbowBendPotInput < 600){
    foreArmBend.write(90);
  }else if(elbowBendPotInput > 600){
    int input = (elbowBendPotInput - 600)/10;
    foreArmBend.write(90 + input);    
    Serial.println(90 + input);
  }else if(elbowBendPotInput < 400){
    int input = (400 - elbowBendPotInput)/10;
    foreArmBend.write(90 - input);
    Serial.println(90 - input);
  }
   
}
void bendWrist(){
  if(wristBendPotInput > 400 && wristBendPotInput < 600){
    wristPos = 90;
  }else if(wristBendPotInput > 600){
    int input = (wristBendPotInput - 600)/6;
    wristPos = 90 + input;
  }else if(wristBendPotInput < 400){
    int input = (400 - wristBendPotInput)/6;
    wristPos = 90 - input;
  }
  //Serial.println(wristPos);
  wristRotation.write(wristPos);
}


void rotateArm(){
  if(elbowRotPotInput > 400 && elbowRotPotInput<600){
    foreArmRotation.write(90);
  }else if(elbowRotPotInput > 600){
    
    int input = (elbowRotPotInput - 600)/10;
     foreArmRotation.write(90 + input);
  }else if(elbowRotPotInput < 400){
    int input = (400 - elbowRotPotInput)/10;
    foreArmRotation.write(90 - input);
  }
  
}

int outPutPinkie(){
  int pinkiePos = updatePinkieTension();
  
  if(pinkieIn >10){
    pinkiePos += (pinkieIn /8);
  }

  if(pinkiePos  > 180){
    return 180;
  }


  return pinkiePos;
}
int updatePinkieTension(){
  int restPinkiePos = 30  ;

  if(wristPos > 80 && wristPos < 100){
    restPinkiePos = 30;
  }
  if(wristPos < 80){
    int sub = 80 - wristPos;
    sub = sub/3;
    restPinkiePos = restPinkiePos - sub;
  }
  if(wristPos > 100){
    int sub = wristPos - 100;
    restPinkiePos += sub;
  }

  return restPinkiePos;
}

int outPutRing(){
  int ringPos = updateRingTension();

  if(ringIn >40){
    ringPos -= (ringIn /10);
  }

  if(ringPos > 180){
    return 180;
  }

  return ringPos;
}
int updateRingTension(){
  int restMiddlePos = 150;
 
  if(wristPos > 80 && wristPos < 100){
    restMiddlePos = 150;
  }
  if(wristPos < 80){
    int sub = 80 - wristPos;
    sub = sub/2;
    restMiddlePos = 150 + sub ;
    ;
   }
   
  if(wristPos > 100){
    int sub = wristPos - 100;
    restMiddlePos -= sub;
  }
  if(wristPos > 170){
    restMiddlePos = 80 ;
  }

  //Serial.println(restMiddlePos);

  return restMiddlePos;
}
int outPutMiddle(){
  int middlePos = updateMiddleTension();
  if(middleIn >40){
    middlePos -= (middleIn /10);
  }

  if(middlePos > 180){
    return 180;
  }

  return middlePos;
}

int updateMiddleTension(){
    int restMiddlePos = 150;
 
  if(wristPos > 80 && wristPos < 100){
    restMiddlePos = 150;
  }
  if(wristPos < 80){
    int sub = 80 - wristPos;
    sub = sub/2;
    restMiddlePos = 150 + sub ;
    ;
   }
   
  if(wristPos > 100){
    int sub = wristPos - 100;
    restMiddlePos -= sub;
  }
  if(wristPos > 170){
    restMiddlePos = 70;
  }
  // Serial.println(restMiddlePos);

  return restMiddlePos;
}



int outPutPointer(){
  int pointerPos = updatePointerTension();
  if(pointerIn >40){
    pointerPos -= (pointerIn /10);
  }

  if(pointerPos > 180){
    return 180;
  }

  return pointerPos;
  
}
int updatePointerTension(){
  int restPointerPos = 140;
  
  if(wristPos > 80 && wristPos < 100){
    restPointerPos = 140;
  }
  if(wristPos < 80){
    int sub = 80 - wristPos;
     sub = sub/2;
     
    restPointerPos = 140 + sub ;
    ;
   }
   
  if(wristPos > 100){
    int sub = wristPos - 100;
    restPointerPos -= sub;
  }
  if(wristPos > 170){
    restPointerPos = 70;
  }
 //  Serial.println(restPointerPos);


  return restPointerPos;
}
int outPutThumb(){// this method takes the thumb tension and adds to the servo to match the angle of the potentiometer
  int thumbPos = updateThumbTension();
  
if(thumbIn >40){
    thumbPos += (thumbIn /10);
  }

  if(thumbPos > 180){
    return 180;
  }

return thumbPos;
  
}

int updateThumbTension(){ //this method retruns the correct tnesion for the angle of the wrist
  
  int restThumbPos = 30;

  if(wristPos > 80 && wristPos < 100){
    restThumbPos = 30;
  }
  if(wristPos < 80){
    int sub = 80 - wristPos;
    sub = sub/3;
    restThumbPos = restThumbPos - sub;
    ;
  }
  if(wristPos > 100){
    int sub = wristPos - 100;
    restThumbPos += sub;
  }

  return restThumbPos;
  
  }


void printPots(){
  Serial.print("thumb: ");
  Serial.print(thumbIn);
 Serial.print("| pointer: ");
  Serial.print(pointerIn);
  Serial.print("| middle: ");
  Serial.print(middleIn);
  Serial.print("| ring: ");
  Serial.print(ringIn);
  Serial.print("| pinkie: ");
  Serial.print(pinkieIn);
  Serial.println("");
}
void buttonSensor(){
    if(left == LOW){         // If button is pressing
    digitalWrite(leftPin, HIGH); // turn on LED
    }else {                          // otherwise, button is not pressing
    digitalWrite(leftPin, LOW);  // turn off LED
}
if(right == LOW){
   digitalWrite(rightPin, HIGH);} // turn on LED
  else{                           // otherwise, button is not pressing
    digitalWrite(rightPin, LOW);  // turn off LED
}

Serial.print("left");
Serial.println(left);
Serial.print("right");
Serial.println(right);
}

void joystickSensor(){
  if(mapX>450){
    wristPos ++;
  }
  if(mapX<-450){
    wristPos--;
  }
}
