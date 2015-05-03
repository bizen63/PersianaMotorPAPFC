//http://www.prometec.net/infrarrojos/

#include "IRLremote.h"
const int interruptIR = 0;                 // Arduino interrupcion 0: Pin 2, Pin 3 para Leonardo

uint8_t IRProtocol = 0;  // Variables para recibir los datos
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

void setup()
   {     Serial.begin(115200);  // Fijate en la velocidad
         Serial.println("Startup");
         IRLbegin<IR_ALL>(interruptIR);
   }
void loop()
   { 
         uint8_t oldSREG = SREG;  // Parar las interrupciones
         cli();
         if (IRProtocol)          // Si reconoce el protocolo
            {
                 Serial.print("Protocol:");
                 Serial.println(IRProtocol);
                 Serial.print("Address:");
                 Serial.println(IRAddress, HEX);
                 Serial.print("Command:");
                 Serial.println(IRCommand, HEX);
                 IRProtocol = 0;
            }
         SREG = oldSREG;
    }

void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
    {
        IRProtocol = protocol;  // Recogemos los valores y nos volvemos
        IRAddress = address;
        IRCommand = command;
    }
