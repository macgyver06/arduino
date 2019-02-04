
#include<SoftwareSerial.h> 

#define RX 3
#define TX 4

SoftwareSerial BlueT(RX,TX);

char Data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  BlueT.begin(9600);

  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (BlueT.available()){
    Data=BlueT.read(); 
    if (Data=='T') { 
      Serial.println("PLAY/PAUSE");
      delay(1000);
    
    }
    if(Data=='F'){
      Serial.println("FORWARD"); delay (300);
    }
    if(Data=='R'){
      Serial.println("REWIND"); delay (300);
    }
    if(Data=='U'){
      Serial.println("VOLUME++"); delay (300);
    }
    if(Data=='D'){
      Serial.println("VOLUME--"); delay (300);
    }
    if(Data=='Q'){
      Serial.println("QUIT"); delay (300);
    }
  }
}
