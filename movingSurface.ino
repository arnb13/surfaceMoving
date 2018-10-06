#include <Servo.h>
#include<Wire.h>

int pos = 0;
const int MPU_addr=0x68;
int16_t GyX,GyY;
Servo myservo1;
Servo myservo2;

void setup() {
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  myservo1.attach(12);
  myservo2.attach(13);  
  myservo1.write(90);
  myservo2.write(100);
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)

  if(GyX >= -100 && GyX <= 400 && GyY >= 900 && GyY <= 1300) {
    myservo1.write(90);
    myservo2.write(100);
  } 
  if (GyY > 1300) {
      if(GyY > 1300  && GyY < 5500) {
        myservo2.write(95);
        
      } if(GyY >= 5500 && GyY < 11000) {
        myservo2.write(90);
      } if(GyY >= 11000) {
        myservo2.write(80);
      }
          
  } else if (GyY < 900) {
      if(GyY > -2450 && GyY < 900) {
        myservo2.write(105);
        
      } if(GyY > -5500 && GyY <= -2450) {
        myservo2.write(110);
      } if(GyY <= -9000) {
        myservo2.write(120);
      }
          
  }

    if (GyX > 400) {
      if(GyX > 400  && GyX < 4400) {
        myservo1.write(95);
        
      } if(GyX >= 4400 && GyX < 8800) {
        myservo1.write(100);
      } if(GyX >= 8000) {
        myservo1.write(110);
      }
          
  } else if (GyX < -100) {
      if(GyX > -3000 && GyX < -100) {
        myservo1.write(85);
        
      } if(GyX > -6000 && GyX <= -3000) {
        myservo1.write(80);
      } if(GyX <= -6000) {
        myservo1.write(70);
      }
          
  }





  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.println(GyY);
  delay(50);

  
  
}
