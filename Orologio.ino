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
  {1, 1, 1, 1, 1, 0, 0, 0},  //0
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
  setTime(00, 00, 00, 00, 00, 00);
  
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
        digitalWrite(SEG[j], HIGH);
      else
        digitalWrite(SEG[j], LOW);
    }  
    digitalWrite (Vp[i], LOW);
  }
}