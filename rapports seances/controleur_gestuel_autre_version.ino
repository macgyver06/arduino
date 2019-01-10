/*
 * CONTROLEUR GESTUEL autre version
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

double dist1,dist2,distL,distR,diff; 

NewPing sonar1(trigger1, echo1,200); // le module HC-SR04 de gauche
NewPing sonar2(trigger2, echo2,200); // et celui de droite



void setup() {
  Serial.begin(9600); 

}

void loop() {
  /*
   * on mesure la distance du plus proche obstacle pour les deux modules
   */
  distL = sonar1.ping_cm();
  distR = sonar2.ping_cm();


  /*
   * detection des 3 gestes possibles :
   *    PLAY/PAUSE : les deux mains devant les modules à une distance inferiure à 40 cm
   *    REWIND/FORWARD : la main droite devant le module de droite (<40cm): si on l'avance la video "rewind" et "forward" si on la recule
   *    SON--/SON++ : la main gauche devant le module de gauche (40cm) : si on l'avance on baisse le son et on l'augmente si on la recule
   */
  if ((distL > 1 && distL < 40) || (distR > 1 && distR < 40)) {  
    /*
     * on veut éviter de mal interpreter le geste, sans cela on repère les gestes R/F ou S--/S++ alors qu'on voulait mettre sur Play/Pause
     * 
     * 
     */
    
    delay(300); // on s'assure que le geste est réelement volontaire
    dist1 = sonar1.ping_cm();
    distL = dist1 ;
    dist1 = sonar2.ping_cm();
    distR = dist1 ;

    //PLAY/PAUSE
    if ((distL > 1 && distL < 40) && (distR > 1 && distR < 40)) { // repère le geste PLAY/PAUSE
      Serial.println("PLAY/PAUSE");  // ce message est alors lu par le programme python qui tourne simultanement 
      delay(1000); // necessaire car autrement on aurait pas le temps d'abaisser ses mains (ainsi on relancerait la lecture)
      
    }

    //REWIND/FORWARD
    if((distR > 1 && distR < 40) && (distL > 40)){

      
      while(dist1 >= 1 && dist1 <= 40){
        dist1 =sonar2.ping_cm();
        delay(100);
        dist2 =sonar2.ping_cm();  
        diff = dist2-dist1 ;
        if(diff >= 1) {
         Serial.println ("FORWARD"); delay (100); 
        }
        else if(diff <= -1) {
         Serial.println ("REWIND"); delay (100);
        }
  

      }
  
    }

    //SON--/SON++
    if((distL > 1 && distL < 40) && (distR > 40)){
      
      while(dist1 >= 1 && dist1 <= 40){
        dist1 =sonar2.ping_cm();
        delay(100);
        dist2 =sonar2.ping_cm();  
        diff = dist2-dist1 ;
        if(diff >= 1) {
         Serial.println ("SON++"); delay (100); 
        }
        else if(diff <= -1) {
         Serial.println ("SON--"); delay (100);
        }
  

      }
    }

  }
  delay(100);
}
