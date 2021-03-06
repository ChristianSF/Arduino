#include <Ultrasonic.h>   //Carrega a biblioteca Ultrasonic  
#include <NewTone.h>   

#define tempo 500
int frequencia = 2000;
int PinoFalante = 2;

int atraso = 1000;

#define PINO_TRIGGER 13
#define PINO_ECHO 10

#define Led1 7
#define Led2 6

Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO);

void setup() {
  pinMode(PinoFalante, OUTPUT);

  pinMode(Led1, OUTPUT);

  pinMode(Led2, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {

  
  float cmMsec, inMsec;

  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  if (cmMsec > 80) {
    atraso = 2000;
  }

  else if (cmMsec > 50 && cmMsec < 80) {
    atraso = 1500;
  }

  else if (cmMsec > 30 && cmMsec<50) {
    atraso = 1200;
  }

  else if (cmMsec > 10 && cmMsec < 30) {
    atraso = 700;
  }

  else if (cmMsec < 10) {
    atraso = 300;
  }

  Serial.print("Cent: ");
  Serial.print(cmMsec);
  Serial.print(" atraso : ");
  Serial.println(atraso);

  NewTone(PinoFalante, frequencia, tempo);

  digitalWrite(Led1, HIGH);
  delay(atraso);
   digitalWrite(Led1, LOW);
  digitalWrite(Led2, HIGH);
  delay(atraso);
  digitalWrite(Led2, LOW);
}
