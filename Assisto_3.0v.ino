#include<Wire.h>
#include <Keyboard.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;

bool mode = true;
 
double x;
double y;
double z;
 
void setup(){
Keyboard.begin();
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
}
void loop(){
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

Serial.println("-----------------------------------------");
Serial.print("AngleX= ");
Serial.print(x);
 
Serial.print(" AngleY= ");
Serial.print(y);
 
Serial.print(" AngleZ= ");
Serial.println(z);
Serial.println("-----------------------------------------");

char period = 46;
char hyphen = 45;
char space = 32;
char A = 65;
char B = 66;

 if (y>210){
    Serial.println("Head tilted to the front");
    Keyboard.press(space);
    Keyboard.releaseAll();
  }
  else if(y<150){
    mode=!mode;
  }
  else if (x > 190 ) {
    Serial.println("Head tilted to the right");
    if(mode){
      Keyboard.press(period);
    Keyboard.releaseAll();
    }
    else{
      Keyboard.press(A);
    Keyboard.releaseAll();
    }
  }
  
  else if (x< 170 ) {
    Serial.println("Head tilted to the left");
   if(mode){
      Keyboard.press(hyphen);
    Keyboard.releaseAll();
    }
    else{
      Keyboard.press(B);
    Keyboard.releaseAll();
    }
  }
 
  else {
    Serial.println("Head straight");
  }
delay(2000);

}
