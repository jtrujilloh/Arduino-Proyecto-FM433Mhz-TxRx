/*
    CÓDIGO PARA EL RECEPTOR/CLIENTE:

    Nombre proyecto:    Ejemplo de uso de dos módulos RF junto a dos Arduinos.
                            Desde el monitor serial se escribe lo que se quiera (hasta 128bytes), el Arduino emisor
                            lo envía por el modulo RF y el Arduino receptor lo recoge y muestra en el LCD que tiene conectado.
    URL proyecto:        http://giltesa.com/?p=11606
    Fecha:                19/07/2012
    Licencia:            (CC) BY-NC-SA: giltesa.com    
*/


// Librerías:
    #include <LiquidCrystal.h>
    #include <VirtualWire.h>

// Instanciacion del LCD:
    LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Variables globales:
    char cad[100];
    int pos = 0;

#define PIN_LED 2

void setup()
{
    lcd.begin(20, 4);     // Configuración del LCD, 4 líneas de 20 caracteres cada una.
    lcd.setCursor(0, 0);  // Se pone el cursor en la primera posición de la pantalla.

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);
    
    vw_setup(2000);       // Se indica los bits por segundo (baudios) para la comunicacion.
    vw_set_rx_pin(11);
    vw_rx_start();        // Se inicia la recepción.
}


void loop()
{
    byte buf[VW_MAX_MESSAGE_LEN];        // Se crea una array de tipo byte de 30 componentes (Es el valor que tiene la constante VW_MAX_MESSAGE_LEN en la libreria)
    byte buflen = VW_MAX_MESSAGE_LEN;    // Se indica que por defecto el tamaño sera de hasta 30 caracteres.
    int i;

    // Si se recibe un mensaje desde el Arduino emisor, la función vw_get_message devolverá por valor un true y por referencia el mensaje y si tamaño.
    if( vw_get_message(buf, &buflen) )
    {
      digitalWrite(PIN_LED, HIGH);
      
      delay(500);
      
      digitalWrite(PIN_LED, LOW);
        if(pos < 4)
            lcd.setCursor(0, pos);
        else
        {
            pos=0;
            lcd.clear();
        }

        // Se imprime por pantalla componente a componente del array hasta que se llegue al final.
        for (i = 0; i < buflen; i++)
        {
            lcd.print(buf[i]);
            // Otras formas de imprimir:
            // lcd.write(buf[i]);
            // lcd.print(buf[i], BYTE);
            // lcd.print((char)buf[i]);
            pos++;
        }
    }
}
