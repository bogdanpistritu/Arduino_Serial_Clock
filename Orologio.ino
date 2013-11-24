#include <Time.h>
/*----------------------------------------------------------------\
// La configurazione per il programma è la seguente:              |
// A0 Decine ore, A1 Unità ore, A2 Decine minuti, A3 Unità minuti |
// A4 Decine secondi, A5 Unità secondi                            |
//              2                                                 |
//           #######                                              |
//        7  #     #  3                                           |  
//           #  8  #                                              |
//           #######                                              |
//           #     #                                              |
//        6  #     #  4                                           | 
//           ####### # <- 9                                       |
//              5                                                 |   
\----------------------------------------------------------------*/
int SEG[8] = {2, 3, 4, 5, 6, 7, 8, 9}; 
int Vp[6] = {A0, A1, A2, A3, A4, A5};
boolean NMatrix[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0},  //0
  {0, 1, 1, 0, 0, 0, 0, 0},  //1
  {1, 1, 0, 1, 1, 0, 1, 0},  //2
  {1, 1, 1, 1, 0, 0, 1, 0},  //3
  {0, 1, 1, 0, 0, 1, 1, 0},  //4 
  {1, 0, 1, 1, 0, 1, 1, 0},  //5
  {0, 0, 1, 1, 1, 1, 1, 0},  //6
  {1, 1, 1, 0, 0, 0, 0, 0},  //7
  {1, 1, 1, 1, 1, 1, 1, 0},  //8
  {1, 1, 1, 1, 0, 1, 1, 0}}; //9
void setup() 
{
  byte hh = 0, mm = 0, ss = 0;
  
  pinMode(13, OUTPUT);
  
  Serial.begin(9600); 
   
  while(Serial.available() == 0) 
  { 
    tone(13, 2000, 10);   
    Serial.write('h'); 
    delay(1000);
  }
  tone(13, 1000, 50);  
  hh = Serial.read();  
  delay(100);
    
  while(Serial.available() == 0) 
  {    
    tone(13, 2000, 10);   
    Serial.write('m'); 
    delay(1000);
  }
  tone(13, 1000, 50); 
  mm = Serial.read();
  delay(100);
    
  while(Serial.available() == 0) 
  {    
    tone(13, 2000, 10);   
    Serial.write('s'); 
    delay(1000);
  }
  tone(13, 1000, 50); 
  ss = Serial.read();
  
  setTime(hh, mm, ss, 00, 00, 00);
  
  for (int i = 0; i < 8; i++)
  {    
    pinMode(SEG[i], OUTPUT);  
    digitalWrite(SEG[i], HIGH); 
  }
  for (int i = 0; i < 6; i++)
  {
    pinMode(Vp[i], OUTPUT);
    digitalWrite(Vp[i], LOW);
  } 
}

void loop() 
{
  update(); 
}

void update()  
{  
  byte timeFigures[6] = {hour() / 10, hour() % 10, minute() / 10, minute() % 10, second() / 10, second() % 10};   
  for(int i = 0; i < 6; i++)
  {
    digitalWrite (Vp[i], HIGH);     
    for(int j = 0; j < 8; j++)
    {
      if(NMatrix[timeFigures[i]][j])      
        digitalWrite(SEG[j], LOW);           
      else
        digitalWrite(SEG[j], HIGH);
    } 
    if(i == 3 && second() % 2 == 0)
    {
      digitalWrite(SEG[7], LOW);
    }    
    delay(1);
    digitalWrite (Vp[i], LOW);
  }
}
