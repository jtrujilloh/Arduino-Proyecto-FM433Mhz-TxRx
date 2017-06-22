/*
CÓDIGO PARA EL EMISOR/SERVIDOR:
Descripcion proyecto:	

Sistema capaz de enviar el caracter numérico escrito mediante el Monitor Serial.

Fecha:			15/07/2014
*/


// Librerias:
#include <VirtualWire.h>

// Declaraciones
#define PIN_ON 13
#define PIN_ACTIVACION_BOTONES 12

#define PIN_BTN_1 9 //digital 9 
#define PIN_BTN_2 8 //digital 8
#define PIN_BTN_3 7 //digital 7

boolean vBtn_State1 = false;
boolean vBtn_State2 = false;
boolean vBtn_State3 = false;

#define PIN_LED 2

// Variables globales
char vDatos[100];
int i=0;

void setup()
{
  pinMode(PIN_ACTIVACION_BOTONES, OUTPUT);
  digitalWrite(PIN_ACTIVACION_BOTONES, HIGH);
  
  pinMode(PIN_BTN_1, INPUT);
  pinMode(PIN_BTN_2, INPUT);
  pinMode(PIN_BTN_3, INPUT);
  digitalWrite(PIN_BTN_1, LOW);
  digitalWrite(PIN_BTN_2, LOW);
  digitalWrite(PIN_BTN_3, LOW);
  
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  Serial.begin(9600);	// Abre el puerto serie a 9600 bps

  vw_set_tx_pin(3);
  vw_setup(2000);	// Abre el puerto RF a 2000 bps
  
  Serial.println("Finalice con \"ENTER\" cada envio de datos.");
  
  pinMode(PIN_ON, OUTPUT);
  digitalWrite(PIN_ON, HIGH);
}

void loop()
{
  /*
  // Indica cuantos caracteres hay en el buffer:
  if( Serial.available() > 0)
  {
    // Cada vez que se lee un carácter se guarda en nuestro array 
    // y se descuenta del buffer.	
    //cadena[i] = Serial.read();
    //i++;
    vDatos[i] = Serial.read();	
    i++;
  }
  
  switch(vDatos[0])
  {
   case '1':
      EnviarDatos();
   break;
   
   case '2':
     EnviarDatos();
   break;
   
   case '3':
     EnviarDatos();
   break;
   
   default:
     i = 0;
   break;
   
  }
  */
  
  delay(100);
  
  vBtn_State1 = digitalRead(PIN_BTN_1);
  vBtn_State2 = digitalRead(PIN_BTN_2);
  vBtn_State3 = digitalRead(PIN_BTN_3);
  
  if (vBtn_State1 == true)
  {
    Serial.println("Botón 1: [PRESIONADO]");
    vDatos[0] = '1';
    vDatos[1] = '\0';
    EnviarDatos();
  }
  
  if (vBtn_State2 == true)
  {
    Serial.println("Botón 2: [PRESIONADO]");
    vDatos[0] = '2';
    vDatos[1] = '\0';
    EnviarDatos();
  }
  
  if (vBtn_State3 == true)
  {    
    Serial.println("Botón 3: [PRESIONADO]");
    vDatos[0] = '3';
    vDatos[1] = '\0';
    EnviarDatos();
  }
  
}

void EnviarDatos()
{
  digitalWrite(PIN_LED, HIGH);
  
  //cadena[i] = '\0';	// Se añade fin de linea al array (string)
  //vDatos[i] = '\0';
  i = 0;
  vw_send((byte *)vDatos, strlen(vDatos)); // Se envía el texto.
  vw_wait_tx();	
  digitalWrite(PIN_LED, LOW);
}

