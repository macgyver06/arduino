/*
 * PARTIE GESTUELLE VERSION FINALE 
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

const int trigger1 = 12; 
const int echo1 = 13; 

const int trigger2 = 6; 
const int echo2 = 7; 

double distL,distR; 

NewPing sonar1(trigger1, echo1,200); // le module HC-SR04 de droite
NewPing sonar2(trigger2, echo2,200); // et celui de gauche




void setup() {
  Serial.begin(9600); 
  delay(500); 
}

void loop() { 
  
  distR = sonar1.ping_cm();
  distL = sonar2.ping_cm();
  
 
// PLAY/PAUSE
if ((distL > 1 && distR > 1) && (distL < 15 && distR < 15 )) {   // pour ne pas mal interpreter un geste, la plage de distance differente pour le geste PLAY/PAUSE
  Serial.println("PLAY/PAUSE");  // cette chaine de caractere va etre lue par le script python qui tourne parallelement
  delay (1000);  // on laisse le temps à l'utilisateur de retirer ses mains               
  }
  


 
 
// SON--/SON++ ___________________________________________________________________________________________________________________________________________________________________________________

 
  if (distR >= 15 && distR <= 35){
    
    Serial.println("main droite OK");  // permet de vérifier que le module fonctionne bien
    delay(500);                       // on s'assure que le geste est bien volontaire
    distR = sonar1.ping_cm();
   
    while(distR > 1 && distR <=35){ 
      
      distR = sonar1.ping_cm();
     
      if (distR < 25){
        Serial.println("VOLUME--"); 
        delay (500);                    // on laisse le temps à l'utilisateur de constater le changement (autrement le son diminue trop rapidement)
        }
        
      if (distR > 25){
        Serial.println("VOLUME++"); 
        delay (500);
      }  
    
    }
  
  }


// REWIND/FORWARD ___________________________________________________________________________________________________________________________________________________________________________________
// code identique que pour augmenter/diminuer le volume sonore
  
  if (distL >= 15 && distL <= 35){
    
    Serial.println("main gauche OK"); 
    delay(500);
    distL = sonar2.ping_cm();
    
    while(distL > 1 && distL <= 35){
      distL = sonar2.ping_cm(); 
      
      
      if (distL < 25) {
        Serial.println("REWIND"); 
        delay (500);
        }
   
      if (distL > 25){
        Serial.println("FORWARD"); 
        delay (500);
        }
    }
  
  }

}
