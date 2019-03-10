/*
 * CONTROLEUR GESTUEL version initiale
 * 
 * Breve descritpion : 
 * effectuer certaines commandes basiques sur son PC non pas à l'aide des touches du clavier 
 * mais en positionnant les mains à une certaine distance de 2 modules HC-SR04 
 * Dans la pratique, on va  pouvoir par exemple :
 *    mettre sur Play/Pause un film
 *    revenir en arriere ou aller plus loin dans sa lecture
 *    augmenter/diminuer le son
 *    
 * 
 * 
 * Auteurs : Léo Marache, Oualid Ben Mohamed
 */


#include <NewPing.h>

const int trigger1 = 2; 
const int echo1 = 3; 

const int trigger2 = 4; 
const int echo2 = 5; 

double distL,distR; 

NewPing sonar1(trigger1, echo1,200); // le module HC-SR04 de gauche
NewPing sonar2(trigger2, echo2,200); // et celui de droite




void setup() {
  Serial.begin(9600);  
}

void loop() { 
  
  distL = sonar1.ping_cm();
  distR = sonar2.ping_cm();
  
 
// PLAY/PAUSE
if ((distL >1 && distR>1) && (distL <10 && distR<10)) {   // dans cette version, pour ne pas mal interpreter un geste, on met tout simplement une plage de distance differente pour le geste PLAY/PAUSE
  Serial.println("PLAY/PAUSE"); 
  delay (1000); // on laisse le temps à l'utilisateur de retirer ses mains
  }
  


// Finalement , il est plus commode pour l'utilisateur de laisser sa main à une certaine distance plutot que de devoir l'approcher ou l'éloigner 
 
// SON--/SON++
if (distL>=15 && distL<=35){
  delay(500); 
  distL = sonar1.ping_cm();
  if (distL>=15 && distL<=35){
    Serial.println("main gauche OK"); // permet de verifier que le module fonctionne bien
    while(distL<=35){
      distL = sonar1.ping_cm();
      if (distL<20){
        Serial.println ("SON--");   
        }
      if (distL>20){
        Serial.println ("SON++"); 
        }
    }
  }
}

// REWIND/FORWARD
if (distR>=15 && distR<=35){
  delay(500); 
  distR = sonar2.ping_cm();
  if (distR>=15 && distR<=35){
    Serial.println("main droite OK"); 
    while(distR<=35){
      distR = sonar2.ping_cm();
      if (distR<20) {
        Serial.println ("Rewind"); 
        }
      if (distR>20){
        Serial.println ("Forward"); 
        }
    }
  }
}

}
