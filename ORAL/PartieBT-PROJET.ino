/*
 * PARTIE BLUETOOTH VERSION FINALE 
 * 
 * Breve descritpion : 
 * On controle l'ordi à partir de son smartphone (via Bluetooth) 
 * On a les memes fonctionnalités que dans la partie gestuelle du projet, mais en plus, on peut déplacer la souris à l'aide 
 * du PAD de l'appli Bluetooth Electronics et cliquer.
 *    
 * 
 * 
 * Auteurs : Léo Marache, Oualid Ben Mohamed
 */

#include<SoftwareSerial.h> 

#define RX 2
#define TX 3

SoftwareSerial BlueT(RX,TX);

String Data;
int X, Y ;

void setup() {
  
  Serial.begin(9600); 
  BlueT.begin(9600);

  delay(500);
}

void loop() {
  
  
  if (BlueT.available()){
    
    Data = BlueT.readString(); // on lit la chaine de caractere qui est dans le buffer
 
    // BOUTONS -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if (Data=="T") { 
      Serial.println("PLAY/PAUSE");
      delay(1000);
    }
    
    if(Data=="F"){
      Serial.println("FORWARD"); 
    }
    
    if(Data=="R"){
      Serial.println("REWIND"); 
    }
    
    if(Data=="U"){
      Serial.println("VOLUME++"); 
    }
    
    if(Data=="D"){
      Serial.println("VOLUME--"); 
    }
    
    if(Data=="C"){
      Serial.println("CLICK");
    }

    
    // PAD -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    if (Data.length() > 1) {
      Serial.println(Data); 
    }
    
  }
}
