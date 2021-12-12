int mot1=4;
int mot2=5;
int mot3=6;
int mot4=7;

int left=2;
int right=3;

int Left=0;
int Right=0;

void LEFT (void);
void RIGHT (void);
void STOP (void);

void setup()
{
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);

  pinMode(left,INPUT);
  pinMode(right,INPUT);

  digitalWrite(left,HIGH);
  digitalWrite(right,HIGH);
  
  
}

void loop() 
{
 
  digitalWrite(mot4, LOW);
  digitalWrite(mot3, HIGH);
  digitalWrite(mot2, LOW);
  digitalWrite(mot1, HIGH);

while(1)
{
  Left=digitalRead(left);
  Right=digitalRead(right);
  
  if((Left==1 && Right==0)==1)
  LEFT();
  else if((Right==1 && Left==0)==1)
  RIGHT();
}
}

void LEFT (void)
{
   analogWrite(mot3,0);
   analogWrite(mot4,30);
   
   
   while(Left==1)
   {
    Left=digitalRead(left);
    Right=digitalRead(right);
    if(Right==1)
    {
      int lprev=Left;
      int rprev=Right;
      STOP();
      while(((lprev==Left)&&(rprev==Right))==1)
      {
         Left=digitalRead(left);
         Right=digitalRead(right);
      }
    }
    analogWrite(mot1,255);
    analogWrite(mot2,0); 
   }
   analogWrite(mot3,255);
   analogWrite(mot4,0);
}

void RIGHT (void)
{
   analogWrite(mot1,0);
   analogWrite(mot2,30);

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
    analogWrite(mot3,255);
    analogWrite(mot4,0);
    }
   analogWrite(mot1,255);
   analogWrite(mot2,0);
}
void STOP (void)
{
analogWrite(mot1,0);
analogWrite(mot2,0);
analogWrite(mot3,0);
analogWrite(mot4,0);
  
}
