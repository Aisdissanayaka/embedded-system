#include "Arduino.h"
#include "LEDon.h"

void blink(int pin) {
  
  digitalWrite(pin, HIGH);
}


/*
void Control(float Total_L) {
  if (Total_L < 4)  //Compare totoal litters
  {
    if ((Total_L > 2) && (Total_L < 4)) {  //Compare totoal litters
      int val = digitalRead(D1);
      if (val == 1) {
        digitalWrite(MOTER_2, HIGH);  //Start moter tow running
        blink(D6);                    //D6
      } else {
        digitalWrite(MOTER_2, LOW);
      }
    }
  } else {
    digitalWrite(MOTER_1, LOW);                                   //Stop moter one running
    digitalWrite(MOTER_2, LOW);                                   //stop moter tow running
    Blynk.virtualWrite(V0, LOW);                                  //set value switch
    blink(D7);                                                    //D7
    Blynk.notify("System turn off and Water supply is done..!");  //Display Warning message
  }
}

*/

