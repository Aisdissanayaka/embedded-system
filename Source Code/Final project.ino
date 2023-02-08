#define BLYNK_TEMPLATE_ID "TMPLwzWs0PPW"
#define BLYNK_DEVICE_NAME "Nodemcu"
#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"
#include "LEDon.h"

int MOTER_1 = D1;
int MOTER_2 = D5;

#define SENSOR D4

BLYNK_WRITE(V0) {
  int systemTurnOn = param.asInt();
  digitalWrite(MOTER_1, systemTurnOn);
}

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

long currentMillis = 0;
long previousMillis = 0;

int interval = 1000;

boolean ledState = LOW;

float calibrationFactor = 5.8;
volatile byte pulseCount;
byte pulse1Sec = 0;

float flowRate;

unsigned long flowMilliLitres;
unsigned int totalMilliLitres;

float flowLitres;
float totalLitres;
float estiateTime;
float volume = 4;

void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Serial.begin(115200);
  delay(100);
  //pinMode(D1,OUTPUT);
  pinMode(MOTER_1, OUTPUT);
  pinMode(MOTER_2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSOR, INPUT_PULLUP);

  //Add value for declaed variable
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(SENSOR), pulseCounter, FALLING);

  BlynkEdgent.begin();
}

void loop() {
  //Calculate waterflow rate and total water flow
  currentMillis = millis();  //add milis function
  if (currentMillis - previousMillis > interval) {

    pulse1Sec = pulseCount;
    pulseCount = 0;

    //Calculate flowrate
    flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
    previousMillis = millis();


    flowMilliLitres = (flowRate / 60) * 1000;
    flowLitres = (flowRate / 60);


    totalMilliLitres += flowMilliLitres;
    //Total litters
    totalLitres += flowLitres;

    //Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(float(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");  // Print tab space

    Control(totalLitres);

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);  // Print the integer part of the variable
    Serial.print("mL / ");
    Serial.print(totalLitres);  // Print the integer part of the variable
    Serial.println("L");

    //Calculate estimate time
    estiateTime = volume / flowRate;

    //add data to virtual data stream
    Blynk.virtualWrite(V1, totalLitres);
    Blynk.virtualWrite(V2, flowRate);
    Blynk.virtualWrite(V3, estiateTime);
  }
  BlynkEdgent.run();
}


