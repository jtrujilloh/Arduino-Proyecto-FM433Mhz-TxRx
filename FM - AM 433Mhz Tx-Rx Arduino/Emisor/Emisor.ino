/*
CÓDIGO PARA EL EMISOR/SERVIDOR:
Nombre proyecto:	Ejemplo de uso de dos módulos RF junto a dos Arduinos.
			Desde el monitor serial se escribe lo que se quiera (hasta 128bytes), el Arduino emisor
			lo envía por el modulo RF y el Arduino receptor lo recoge y muestra en el LCD que tiene conectado.
URL proyecto:		http://giltesa.com/?p=11606
Fecha:			19/07/2012
Licencia:		(CC) BY-NC-SA: giltesa.com	
*/


// Librerias:
#include <VirtualWire.h>
#define PIN_LED 2

// Variables globales
char cadena[100];
int i=0;


void setup()
{
        pinMode(PIN_LED, OUTPUT);
        digitalWrite(PIN_LED, LOW);
	Serial.begin(9600);	// Abre el puerto serie a 9600 bps
	vw_setup(2000);		// Abre el puerto RF a 200 bps
        vw_set_tx_pin(12);
	Serial.print("Finalice con \".\" cada envio de datos.");
}


void loop()
{
	// Indica cuantos caracteres hay en el buffer:
	if( Serial.available() > 0)
	{
	    // Cada vez que se lee un carácter se guarda en nuestro array 
            // y se descuenta del buffer.	
            cadena[i] = Serial.read();	
	    i++;
	}

	// Cuando escribamos un punto, se enviara todo el texto por el emisor RF:
	if( cadena[i-1] == '.')
	{
                digitalWrite(PIN_LED, HIGH);
		cadena[i] = '\0';						// Se añade fin de linea al array (string)
		i=0;
		vw_send((byte *)cadena, strlen(cadena));	// Se envía el texto.
                vw_wait_tx();	
                //delay(400);	
                digitalWrite(PIN_LED, LOW);
                
	}
}
