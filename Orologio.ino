#include <Time.h>
/*----------------------------------------------------------------\
// La configurazione per il programma è la seguente:              |
// A0 Decine ore, A1 Unità ore, A2 Decine minuti, A3 Unità minuti |
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
int Vp[4] = {A0, A1, A2, A3};
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
  Serial.begin(9600); 
   
  while(Serial.available() == 0) 
  {    
    Serial.write('h'); 
    delay(1000);
  }
  hh = Serial.read();  
  delay(100);
    
  while(Serial.available() == 0) 
  {    
    Serial.write('m'); 
    delay(1000);
  }
  mm = Serial.read();
  delay(100);
    
  while(Serial.available() == 0) 
  {    
    Serial.write('s'); 
    delay(1000);
  }
  ss = Serial.read();
  
  setTime(hh, mm, ss, 00, 00, 00);
  
  for (int i = 0; i < 8; i++)
  {    
    pinMode(SEG[i], OUTPUT);  
    digitalWrite(SEG[i], HIGH); 
  }
  for (int i = 0; i < 4; i++)
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
  byte timeFigures[4] = {hour() / 10, hour() % 10, minute() / 10, minute() % 10};   
  for(int i = 0; i < 4; i++)
  {  
    digitalWrite (Vp[i], HIGH);
    for(int j = 0; j < 8; j++)
    {
      if(NMatrix[timeFigures[i]][j])
        digitalWrite(SEG[j], LOW);
      else
        digitalWrite(SEG[j], HIGH);
    }  
    delay(5);
    digitalWrite (Vp[i], LOW);
  }
}
