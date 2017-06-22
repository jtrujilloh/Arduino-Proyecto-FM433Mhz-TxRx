/*
CÓDIGO PARA EL RECEPTOR/CLIENTE:
Descripcion proyecto:	

Sistema capaz de recibir el caracter numérico escrito mediante el Monitor Serial
desde el transmisor/servidor.

Fecha:			15/07/2014
*/


// Librerías:
#include <VirtualWire.h>

// Variables globales:
char cad[100];
int pos = 0;
int vTimerDelay = 150;

// Declaraciones
#define PIN_LED 2

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);
    
    vw_set_rx_pin(3);
    vw_setup(2000);       // Se indica los bits por segundo (baudios) para la comunicacion.
    vw_rx_start();        // Se inicia la recepción.
}

void loop()
{
    byte buf[VW_MAX_MESSAGE_LEN];        // Se crea una array de tipo byte de 30 componentes (Es el valor que tiene la constante VW_MAX_MESSAGE_LEN en la libreria)
    byte buflen = VW_MAX_MESSAGE_LEN;    // Se indica que por defecto el tamaño sera de hasta 30 caracteres.

    // Si se recibe un mensaje desde el Arduino emisor, la función vw_get_message devolverá por valor un true y por referencia el mensaje y si tamaño.
    if( vw_get_message(buf, &buflen) )
    {
      switch(buf[0])
      {
        case '1':
          digitalWrite(PIN_LED, HIGH);
          //delay(vTimerDelay);
          //digitalWrite(PIN_LED, LOW);
        break;
        
        case '2':
          //digitalWrite(PIN_LED, HIGH);
          //delay(vTimerDelay);
          //digitalWrite(PIN_LED, LOW);
          //delay(vTimerDelay);
          //digitalWrite(PIN_LED, HIGH);
          //delay(vTimerDelay);
          digitalWrite(PIN_LED, LOW);
        break;
       
        case '3':
          digitalWrite(PIN_LED, HIGH);
          delay(vTimerDelay);
          digitalWrite(PIN_LED, LOW);
          delay(vTimerDelay);
          digitalWrite(PIN_LED, HIGH);
          delay(vTimerDelay);
          digitalWrite(PIN_LED, LOW);
          delay(vTimerDelay);
          digitalWrite(PIN_LED, HIGH);
          delay(vTimerDelay);
          digitalWrite(PIN_LED, LOW);
        break; 
      }  
    vw_wait_rx();	   
    }
}
