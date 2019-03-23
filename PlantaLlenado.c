/*
    Created on : 23/03/2019
    Authores     :heberthardila@gmail.com
                  script-cat@outlook.com
                  uavlabs.org

    Programa para un micro controlador 18F4550 el cual se encarga del control de una
    planta de llenado
*/

#include <18F4550.h>
#fuses xt, nowdt, noprotect, put, CPUDIV1

// se define el uso del reloj interno a 8Mhz
#use delay(internal = 8000000)
//incluye laa libreria modificada para majear la lcd en por el puerto D
#include "Mi_LCD.c"

// se define la comunicacion serial a 9600 baudios, sin paridad y un bit de stop
#use rs232(baud = 9600, bits = 8, parity = N, xmit = PIN_C6, RCV = PIN_C7, stop=1, ERRORS)

// puertos que se van a utilizar
#use fast_io(d)// lcd
#use fast_io(b)
#use fast_io(a)
#use fast_io(c)


// ****************  Variables Globales  *******************
#define botonReset PIN_B7
#define botonStop PIN_B6
#define botonStart PIN_B5
#define valvula PIN_B4
#define banda PIN_B3
#define trigger PIN_B2
#define echo PIN_B1

// distancia retornada por el sonar
// Se inicia en 2 con el fin de no generar un 0 por desconexion del sensor.
int distancia = 2;

// seteo del timer para la distancia del sonar




//*****************Define los puertos de conexion*********
void define_puertos() {
    // se ponen todos los pines de la LCD como salida
    set_tris_d(0x00);

    /*
    Se definen todas las entradas y salidas del sistema sobre el puerto B
    bit 8 - Entrada Boton Reset en B7
    bit 7 - Entrada Boton Stop en B6
    bit 6 - Entrada Boton Start en B5
    bit 5 - Entrada Valvula en B4
    bit 4 - Salida Banda en B3
    bit 3 - Salida en Sonar (Trigger) B2
    bit 2 - Entrada en Sonar (Echo) B1
    bit 1 - Salida No Utilizada
    */
    set_tris_b(0b11110010);
    //output_low(PIN_B1);

}


// ************************* interupciones ************************

// iterupcion de cambio en el puerto b por flanco de subida
#int_rb
void int_rb_pulsadores(){
    //boton de rest b7
    if(input(PIN_B7)){

        lcd_putc("\f"); //limpia la lcd
        printf(lcd_putc,"Reset");
        printf("7.0000");
        cajasLivianas = 0;
        cajasPesadas = 0;
    }
    // stop b6
    if(input(PIN_B6)){
        lcd_putc("\f"); //limpia la lcd
        printf(lcd_putc,"Stop");
        //parar_planta();
    }

    // stop b5
    if(input(PIN_B5)){
        lcd_putc("\f"); //limpia la lcd
        printf(lcd_putc,"Start");
        //parar_planta();
    }
    // stop b4 sensor
    if(input(PIN_B4)){
        lcd_putc("\f"); //limpia la lcd
        printf(lcd_putc,"DatoSensor:");
        //parar_planta();
    }
}

//interrupcion de llegada de datos
#int_rda
void rb_isr() {
    // comprueba si hay llegada de datos
    if (kbhit()) {
        dato_recibido = getc();
        delay_ms(4);

        if(dato_recibido == '1'){
            parar_planta();
        }

        dato_recibido = '0';
    }
}

//**********Funciones de la panta*******************+
int sonar()
{
  output_high(trigger);                         // ping the sonar
  delay_us(20);                            // sending 20us pulse
  output_low(trigger);

  while(!input(echo))                       // wait for high state of echo pin
  {}

  set_timer1(0);                           // setting timer zero

  while(input(echo))                       // Wait for high state of echo pin
  {}

  time=get_timer1();                       // Getting the time

  distancia=time*0.028 + 1.093 ;          // Calulando la distancia

  return distancia;
}

void llenar()
{
  // TOdo el codigo aqui
}



void main(){
  //configuracion inicial del la lcd
  lcd_init();

  lcd_putc("\f"); //limpia la lcd
  printf(lcd_putc,"Wellcome ;)");

  //habilita las interrupciones por serial
  enable_interrupts(int_rda);
  //habilita las interrupciones puerto b
  enable_interrupts(int_rb);
  //habilita las interrupciones glovales
  enable_interrupts(global);

  //intrerrupcion por flanco de subida
  ext_int_edge(L_TO_H);

  // habilita el timer 1 para el calculo de distancia con Sonar
  setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);     // initiating timer
  // configura los puertos
  define_puertos();

  while (true) {
    // Toda la ejecucion aqui...

  }

}
