// Copyright 2019

#include <Servo.h> // On inclue la librairie pour le controle du servo
const char PWM_SERVO = 13; // On déclare dans la variable "PWM_SERVO" le pin du servomoteur
 Servo monServo; // On définit l'objet "monServo"
 
//Initialisation des variables relatives aux boutons
int valeurbp1;
int valeurbp2;
int valeurbp3;
int valeurbp4;
int valeurbp5;
int valeurbpverif;

bool bp1_Avant = 0;
bool bp2_Avant = 0;
bool bp3_Avant = 0;
bool bp4_Avant = 0;
bool bp5_Avant = 0;
bool bpverif_Avant = 0;

bool bp1_b = false;
bool bp2_b = false;
bool bp3_b = false;
bool bp4_b = false;
bool bp5_b = false;
bool bpverif_b = false;

//Initialisation des variables relatives aux DELs
bool etatLed1 = false;
bool etatLed2 = false;
bool etatLed3 = false;
bool etatLed4 = false;
bool etatLed5 = false;
bool etatLedverif = false;

//Assignation des broches aux boutons
#define bp1 11
#define bp2 A1
#define bp3 A2
#define bp4 A3
#define bp5 A4
#define bpverif A5

//Assignation des broches aux DELs
#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define led5 6
#define ledverif 12

//Assignation des broches au décodeur BCD
#define a 7
#define b 8
#define c 9
#define d 10

int chiffrebcd = 0; //Variable servant de mémoire pour le chiffre à afficher


void setup() {
  monServo.attach(13);  // On attache le pin 13 au servomoteur
  monServo.write(0); // On ferme la boite
  Serial.begin(9600); //On initialise la communication serie pour le débogage du système

//On déclare les broches I/O
  pinMode(bp1, INPUT);
  pinMode(bp2, INPUT);
  pinMode(bp3, INPUT);
  pinMode(bp4, INPUT);
  pinMode(bp5, INPUT);
  pinMode(bpverif, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(ledverif, OUTPUT);

  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(d,OUTPUT);

//On génère la combinaison aléatoirement par un randomSeed sur la broche A0
  randomSeed(analogRead(A0));
   valeurbp1 = random(0 ,2);
   valeurbp2 = random(0 ,2);
   valeurbp3 = random(0 ,2);
   valeurbp4 = random(0 ,2);
   valeurbp5 = random(0 ,2);
   
//Pour faciliter le débogage on envoit les réponses sur le port série
Serial.println(valeurbp1);
Serial.println(valeurbp2);
Serial.println(valeurbp3);
Serial.println(valeurbp4);
Serial.println(valeurbp5);
}

void loop() {
//On lit l'état de chaque bouton et on l'inscrit dans une variable puis on la traite
  bp1_b = digitalRead(bp1);
  bp2_b = digitalRead(bp2);
  bp3_b = digitalRead(bp3);
  bp4_b = digitalRead(bp4);
  bp5_b = digitalRead(bp5);
    valeurdesboutons();
    
//Inscription des etats DELs
  digitalWrite(led1,etatLed1); 
  digitalWrite(led2,etatLed2);
  digitalWrite(led3,etatLed3); 
  digitalWrite(led4,etatLed4);
  digitalWrite(led5,etatLed5); 
  delay(10);


// Si le bon code est trouvé et si le bouton de verification est pressé
if ((etatLed1 == valeurbp1) 
   && (etatLed2 == valeurbp2) 
   && (etatLed3 == valeurbp3) 
   && (etatLed4 == valeurbp4)
   && (etatLed5 == valeurbp5) 
   && (digitalRead(bpverif) == LOW)) { 

  cinq(); // On affiche le chiffre cinq

// On fait clignoter la DEL de vérification
    for ( int i = 0 ; i < 10 ; i++ ) {
    digitalWrite(ledverif, HIGH); // On allume la DEL de verif
    delay(100);
    digitalWrite(ledverif, LOW); // On eteind la DEL de verif
    delay(100);
} 
 // On eteint toutes les DELS
    poweroff_leds();
    delay(1000); //On attend une seconde
    monServo.write(170); //On ouvre la boite
    delay(1000); //On attends une seconde
    chiffrebcd = 0; // On remet à zéro la variable "chiffrebcd"  
   }   
   
// Si le bouton est appuyé mais que les codes ne sont pas bons       
else if ((digitalRead(bpverif) == LOW)){
  chiffrebcdvoid(); //On traite le nombre de bites justes
  bcd(); // Et on les affiches sur l'afficheur bcd
  delay(1000); //On attends une secondes
  poweroff_leds(); // On eteint toutes les DELs 
  chiffrebcd = 0; // On remet à zéro la variable "chiffrebcd"                        4
}
  bcd(); // On inscrit le bon chiffre sur l'afficheur correspondant à la variable "chiffrebcd"
}
void zero(){
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void un(){
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void deux(){
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void trois(){
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
}

void quatre(){
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,HIGH);
  digitalWrite(d,LOW);
}

void cinq(){
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  digitalWrite(c,HIGH);
  digitalWrite(d,LOW);
}


void bcd(){
  if (chiffrebcd == 0){
    zero();
  }
    if (chiffrebcd == 1){
    un();
  }
    if (chiffrebcd == 2){
    deux();
  }
    if (chiffrebcd == 3){
    trois();
  }
    if (chiffrebcd == 4){
    quatre();
  }
}


void valeurdesboutons(){
  // Valeur btn1
  if((!bp1_b == false) && (bp1_Avant == 1)){ 
    bp1_Avant = 0;
        etatLed1 = !etatLed1;
  }
    if((!bp1_b == true) && (bp1_Avant == 0)){
    bp1_Avant = 1;
    bp1_b = !bp1_b;
  }
  // Valeur btn2
   if((!bp2_b == false) && (bp2_Avant == 1)){
    bp2_Avant = 0;
        etatLed2 = !etatLed2;
  }
    if((!bp2_b == true) && (bp2_Avant == 0)){
    bp2_Avant = 1;
    bp2_b = !bp2_b;
  }

  if((!bp3_b == false) && (bp3_Avant == 1)){ 
    bp3_Avant = 0;
        etatLed3 = !etatLed3;
  }
    if((!bp3_b == true) && (bp3_Avant == 0)){
    bp3_Avant = 1;
    bp3_b = !bp3_b;
  }
  
  if((!bp4_b == false) && (bp4_Avant == 1)){ 
    bp4_Avant = 0;
        etatLed4 = !etatLed4;
  }
    if((!bp4_b == true) && (bp4_Avant == 0)){
    bp4_Avant = 1;
    bp4_b = !bp4_b;
  }

  if((!bp5_b == false) && (bp5_Avant == 1)){ 
    bp5_Avant = 0;
        etatLed5 = !etatLed5;
  }
    if((!bp5_b == true) && (bp5_Avant == 0)){
    bp5_Avant = 1;
    bp5_b = !bp5_b;
  }
}


void chiffrebcdvoid(){
   if (etatLed1 == valeurbp1){
   chiffrebcd++;
}  if (etatLed2 == valeurbp2){
   chiffrebcd++;
}  if (etatLed3 == valeurbp3){
   chiffrebcd++;
   }  if (etatLed4 == valeurbp4){
   chiffrebcd++;
}
if (etatLed5 == valeurbp5){
   chiffrebcd++;
}
}

void poweroff_leds(){
  etatLed1 = LOW;
  etatLed2 = LOW;
  etatLed3 = LOW;
  etatLed4 = LOW;
  etatLed5 = LOW;
}
