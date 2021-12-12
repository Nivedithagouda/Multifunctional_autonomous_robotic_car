//for more project visit www.blackkeyhole.com
#include<SoftwareSerial.h>
#include <IRremote.h>


//IR_remote_control

////char command;
////int receiver_pin = A4;   //Connect the output pin of IR receiver at pin 4
////int vcc = A3;            //VCC for IR sensor
////int gnd = A2;  
//
//IRrecv irrecv(receiver_pin);
//decode_results results;

  
//Obsticle_avoiding
const int frontEchoPin = A1;
const int frontTriggerPin = A0;
const int leftEchoPin = 11;
const int leftTriggerPin = 10;
const int rightEchoPin = 9;
const int rightTriggerPin = 8;
const int motorL1 = 7;
const int motorL2 = 6;
const int motorR1 = 5;
const int motorR2 = 4;
volatile float maxFrontDistance = 50.00;
volatile float frontDuration, frontDistanceCm, leftDuration, leftDistanceCm, rightDuration, rightDistanceCm;
volatile float maxLeftDistance, maxRightDistance = 50.00;

//human_following
#define sensor1 13
#define sensor2 12

//Line_following
int line_left=2;
int line_right=3;
int Left=0;
int Right=0;


char command; 
int mode=0;


void setup() 
{  
  Serial.begin(115200);

  //IR_remote
//  irrecv.enableIRIn();
//  pinMode(vcc, OUTPUT);
//  pinMode(gnd, OUTPUT);
//  digitalWrite(vcc, HIGH);

  //Obsticle_avoiding
  pinMode(frontTriggerPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  //Obsticle_avoiding
  
  //human_following
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

//  //LINE_following
//  pinMode(left,INPUT);
//  pinMode(right,INPUT);
//  digitalWrite(left,HIGH);
//  digitalWrite(right,HIGH);
  
  // motors
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);
  
  
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.

}

void loop(){
  
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    //Stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    Serial.println(command);
  }

    if(command == '1'){mode=1;}    //Manual Android Application and IR Remote Control Command   
else if(command == '2'){mode=2;} //Auto Line Follower Command
else if(command =='3'){mode=3;} //Auto Obstacle Avoiding Command

 
 if (mode == 1)
    {
      Serial.println("obsticle");
      checkFrontDistance();
      if (frontDistanceCm < maxFrontDistance) {
      Serial.println("Too close");
      checkLeftDistance();
      delay(20);
      checkRightDistance();
      delay(20);
      if (leftDistanceCm < rightDistanceCm)
      moveRight();
      else if (leftDistanceCm > rightDistanceCm) {
      moveLeft();
      }
    }
    else {
      Serial.println("OK");
      moveForward();
    }
  // left distance check
     checkLeftDistance();
    if (leftDistanceCm < maxLeftDistance) {
    Serial.println("Left too close");
    delay(20);
    checkLeftDistance();
    delay(20);
    checkRightDistance();
    delay(20);
    if (leftDistanceCm > rightDistanceCm)
      moveForward();
    else if (leftDistanceCm < rightDistanceCm) {
      moveRight();
    }
    }
  // right distance check
  checkRightDistance();
  if (rightDistanceCm < maxRightDistance) {
    Serial.println("Right too close");
    delay(20);
    checkRightDistance();
    delay(20);
    checkLeftDistance();
    delay(20);
    if (rightDistanceCm > leftDistanceCm)
      moveForward();
    else if (rightDistanceCm < leftDistanceCm) {
      moveLeft();
    }
    }
    }
  
//human_hand_following
 if(mode == 2)
 {
    bool value1 = digitalRead(sensor1);
  bool value2 = digitalRead(sensor2);
  Serial.println(value2);  Serial.println(value1);

  if (value1 == 0 && value2 == 0 ) {
  moveForward();
  } else if (value1 == 1 && value2 == 1) {
    Stop();
  } else if (value1 == 0 && value2 == 1) {
    left();
  } else if (value1 == 1 && value2 == 0) {
    right();
  }
  }




 
  } 



void checkFrontDistance() {
  digitalWrite(frontTriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(frontTriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(frontTriggerPin, LOW);
  frontDuration = pulseIn(frontEchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  frontDistanceCm = frontDuration * 10 / 292 / 2;  //convertimos a distancia, en cm
  Serial.print("Distance: ");
  Serial.print(frontDistanceCm);
  Serial.println(" cm");
}
void checkLeftDistance() {
  digitalWrite(leftTriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(leftTriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  leftDistanceCm = leftDuration * 10 / 292 / 2;  //convertimos a distancia, en cm
  Serial.print("Left distance: ");
  Serial.print(leftDistanceCm);
  Serial.println(" cm");
}
void checkRightDistance() {
  digitalWrite(rightTriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(rightTriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  rightDistanceCm = rightDuration * 10 / 292 / 2;  //convertimos a distancia, en cm
  Serial.print("Right distance: ");
  Serial.print(rightDistanceCm);
  Serial.println(" cm");
}
void moveBackward() {
  Serial.println("Backward.");
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
}
void moveForward() {
  Serial.println("Forward.");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
}
void moveLeft() {
  Serial.println("Left. rotate");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
}
void moveRight() {
  Serial.println("Right rotate.");
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
}
void Stop()
{
  Serial.println("stop.");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
}


void right()
{
  Serial.println("turn left.");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
}
void left()
{
  Serial.println("turn  right.");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
}




void LINE_LEFT (void)
  {
    analogWrite(motorL2,0);
    analogWrite(motorL1,30);
   
   
    while(Left==1)
    {
      Left=digitalRead(left);
      Right=digitalRead(right);
      if(Right==1)
      {
        int lprev=Left;
        int rprev=Right;
        Stop();
        while(((lprev==Left)&&(rprev==Right))==1)
        {
           Left=digitalRead(left);
          Right=digitalRead(right);
        }
      }
      analogWrite(motorR2,255);
      analogWrite(motorR1,0); 
    }
    analogWrite(motorL2,255);
    analogWrite(motorL1,0);
    }


void LINE_RIGHT(void)
{
   analogWrite(motorR2,0);
   analogWrite(motorR1,30);

   while(Right==1)
   {
    Left=digitalRead(left);
    Right=digitalRead(right);
    if(Left==1)
    {
      int lprev=Left;
      int rprev=Right;

      while(((lprev==Left)&&(rprev==Right))==1)
      {
         Left=digitalRead(left);
         Right=digitalRead(right);
      }
    }
    analogWrite(motorL2,255);
    analogWrite(motorL1,0);
    }
   analogWrite(motorR2,255);
   analogWrite(motorR1,0);
}
