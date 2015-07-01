/*  ----------------------------------------------------------------
   CONTROL DOMÓTICO DE UNA PERSIANA MEDIANTE MANDO A DISTANCIA IR Y MOTOR PAP
    Pin 2 (salida de sensor IR), 3 PARA ARDUINO LEONARDO
    Felcha Arriba:629D
    Felcha Abajo:A857
    Botón OK:2FD (STOP)
    
    Encendiendo y apagando 4 LEDs desde un mando a distancia de infrarroj0
-------------------------------------------------------------------- */
#include "IRLremote.h"
/* Motor paso a paso 5VDC+ controladora UNL2003 */

 int motorPin1 = 8;                              
 int motorPin2 = 9;
 int motorPin3 = 10;
 int motorPin4 = 11;
 int delayTime = 15;      // delay que determina el tiempo cada vez que cambia de paso                 
 int FcArriba = 6;        // Final de carrera arriba
 int FcAbajo = 7;         // Final de carrera abajo
 int estado = 0;


const int interruptIR = 0;
uint8_t IRProtocol = 0;  // Variables para recibir los datos
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

void setup() {
  Serial.begin(115200);  // Fijate en la velocidad
  
  pinMode(motorPin1, OUTPUT);                   
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(FcArriba, INPUT);
  pinMode(FcAbajo, INPUT); 
    
  IRLbegin<IR_ALL>(interruptIR);
}

void loop() 
{   
  uint8_t oldSREG = SREG;  // Parar las interrupciones
  cli();
  if (IRProtocol) 
      {
        switch (IRCommand)
        {
            case 0x629D:
                Serial.println("Arriba");
                estado=1;
                         break;
            case 0xA857:
                Serial.println("Abajo");
                 estado=2;
                  
                break;
           
            case 0x2FD:
                Serial.println("STOP");
                estado=3;
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
                break;                
        }
        IRProtocol = 0;
      }
  SREG = oldSREG;
 if(estado==1 && digitalRead(FcArriba)==HIGH){
    digitalWrite(motorPin1, LOW);                 // sentido anti-horario (arriba)
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    delay(delayTime);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    delay(delayTime);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    delay(delayTime);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    delay(delayTime);
    }
  if(estado==2 && digitalRead(FcAbajo)==HIGH){
    digitalWrite(motorPin1, HIGH);                 // sentido agujas del reloj (abajo)
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    delay(delayTime);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    delay(delayTime);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    delay(delayTime);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    delay(delayTime); 

} 
}

void IREvent(uint8_t protocol, uint16_t address, uint32_t command) 
{
  IRProtocol = protocol;  // Recogemos los valores
  IRAddress = address;
  IRCommand = command;
       
}
