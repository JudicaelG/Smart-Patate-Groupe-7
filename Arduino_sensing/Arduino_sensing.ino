//****************************************************************************************
// Illutron take on Disney style capacitive touch sensor using only passives and Arduino
// Dzl 2012
//****************************************************************************************


//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))				        //-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+



#define N 130  //How many frequencies

float results[N];            //-Filtered result buffer
float freq[N];               //-Filtered result buffer
int sizeOfArray = N;

 
   
   

void setup()
{
  
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+
  ICR1=110;
  OCR1A=55;

  pinMode(9,OUTPUT);        //-Signal generator pin
  pinMode(8,OUTPUT);        //-Sync (test) pin

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(11, OUTPUT);

  Serial.begin(115200);

  for(int i=0;i<N;i++)      //-Preset results
    results[i]=0;           //-+
}

void loop()
{
  unsigned int d;

  int counter = 0;
  for(unsigned int d=0;d<N;d++)
  {
    int v=analogRead(0);    //-Read response signal
    CLR(TCCR1B,0);          //-Stop generator
    TCNT1=0;                //-Reload new frequency
    ICR1=d;                 // |
    OCR1A=d/2;              //-+
    SET(TCCR1B,0);          //-Restart generator

    results[d]=results[d]*0.5+(float)(v)*0.5; //Filter results
   
    freq[d] = d;

 //   plot(v,0);              //-Display
 //   plot(results[d],1);
  // delayMicroseconds(1);
  }


 //   plot(v,0);              //-Display
 //   plot(results[d],1);
  // delayMicroseconds(1);*


    // no touch  57
    // 1touch  82/83
    // 2 touchs  104
    // hand  120

    
    /*Serial.println(" ");
    Serial.println("120:");
    Serial.println(results[120]);
    Serial.println("97:");
    Serial.println(results[97]);
    Serial.println("58:");
    Serial.println(results[58]);*/


    noTone(11);
    if(results[58]>600){off();}
    else if(results[58]<280 && results[97]<270 && results[127]<220){action(1);}
    else if(results[58]<400 && results[97]>270  && results[120]< 250){action(2);}
    else if(results[58]<130 && results[120]>= 250){action(3);}
    else if(results[53]>444){action(4);}

//PlottArray(1,freq,results);
 

  TOG(PORTB,0);            //-Toggle pin 8 after each sweep (good for scope)
}
   
