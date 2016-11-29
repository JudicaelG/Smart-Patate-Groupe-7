int r1= 2;  //-Led 1 rouge
int b1 = 3; //-Led 1 bleu

int r2= 4;  //-Led 2 (milieu)
int b2 = 5; //-+

int r3= 6;  //-Led 3
int b3 = 7; //-+

// 1=rouge  2=bleu

int i=0;         //-Utilisé pour les boucles
int f=1000;      //-Fréquences buzzer
int x=-10;       //-Incrément freq buzzer ou drapeaux
int o=0;         //-2e boucles
int buzzer = 11; //-Pin buzzer
int mode=1;      //-Mode en fonction du capteur
                 //-La variable mode réagira au retour du programme capacitatif

void led(int couleur, int led){ //-Fonction pour les couleurs et position leds
  if (led==1){
    if (couleur==1){digitalWrite(r1, HIGH);}
    else if (couleur==2){digitalWrite(b1, HIGH);}
  }
  else if (led==2){
   if (couleur==1){digitalWrite(r2, HIGH);}
   else if (couleur==2){digitalWrite(b2, HIGH);}
  }
  else if (led==3){
    if (couleur==1){digitalWrite(r3, HIGH);}
    else if (couleur==2){digitalWrite(b3, HIGH);}
  }
}


void off(){ //-Fonction pour éteindre les leds
  digitalWrite(r1, LOW);
  digitalWrite(b1, LOW);
  //digitalWrite(r2, LOW); //-retiré pour modification avancée
  //digitalWrite(b2, LOW); //-+
  digitalWrite(r3, LOW);
  digitalWrite(b3, LOW);
}

void action(int mode) {

  // -----mode 1 -----
  if(mode==1){
    
    for(i=4;i>0;i--){     //-Défini les led 1 et 2 en rouge
      led(1,1);           // |
      led(1,3);           // |
      delay(50);          // |
      off();              //-+
    }
    if(x=5){
      for(i=4;i>0;i--){   //-Défini les les 1 et 2 en bleu
        led(2,1);         // |
        led(2,3);         // |
        delay(50);        // |
        off();            //-+
      }
    }
    /*while(1){  //-Alarme incendie
        delay(100);
        tone(buzzer,440);
        delay(400);
        tone(buzzer,554);}*/
  }
  

  // ----- mode 2 -----
  else if (mode==2){
    if(f<0 | f>2){f=0;}
    f=f+1;                  //-Incrémentation

    if(f==1){
      (buzzer, 415);      //-Buzzer 415Hz
      led(1,1);               //-Led 1 couleur rouge(1)
      delay(600);             //-Délai 0.65 secondes
      off();                  //-Led éteintes
    }
    else if(f==2){
      led(2,3);               //-Led 3 couleur bleu(1)
      tone(buzzer, 545);
      delay(600);
      off();
      }
    }


  // ----- mode 3 -----
  else if(mode==3){
    if(f<=600){x=7;f=600;} //Si f est proche de 500 on remonte
    if (f>=1200){x=-7;} // Si f est proche de 1000 on descent
    f+=x;
    tone(buzzer, f);
    led(2,2);
    
    for(i=6;i>0;i--){ // I
      f+=x;
      tone(buzzer, f);
      led(1,1);
      delay(50);
      f+=x;
      tone(buzzer, f);
      off();
      delay(50);
      f+=x;
      tone(buzzer, f);
    }
    digitalWrite(b2, LOW);
    led(1,2);

    for(i=6;i>0;i--){ //II
      f+=x;
      tone(buzzer, f);
      led(2,3); 
      delay(50);
      f+=x;
      tone(buzzer, f);
      off();
      delay(50);
      f+=x;
      tone(buzzer, f);
    }
    digitalWrite(r2, LOW);
  }

  // ----- mode 4 -----  //-Mode lorsque patate non-reliée
  else if(mode==4){
    if(x==-10 | x>4){x=0;}
    for(i=2;i>=1;i--){
      for(o=3; o>=1; o--){
        if(o==3 && i==1 && x==1){tone(buzzer, 1000);}
        led(i,o);
        delay(404);
        if(o==3 && i==1 && x==1){tone(buzzer, 400);}
        off();
        digitalWrite(b2, LOW); //-Eteint la led 2(milieu) couleur bleue
        digitalWrite(r2, LOW); //-Eteint led 2 Rouge
        delay(50);
        if(o==3 && i==1 && x==1){tone(buzzer,777);x=0;}
        delay(50);
        noTone(buzzer);
      }      
      if(i==2){f=1;}
      x++;
    }
  }
}



