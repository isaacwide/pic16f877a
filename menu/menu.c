#include <16f877a.h>
#fuses XT,NOWDT
#use delay(clock=4M)
#use fast_io(B)
#use fast_io(C)

#define lcd_rs_pin     pin_d0
#define lcd_rw_pin     pin_d1
#define lcd_enable_pin pin_d2
#define lcd_data4      pin_d4
#define lcd_data5      pin_d5
#define lcd_data6      pin_d6
#define lcd_data7      pin_d7
#include <lcd.c>

const char TECLAS[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// c5 azul
// c6 rosado 
// c7 blanco

//con A abanzaremos con B retrocederemos  
// beep para acpetar 
void beep_corto(){
    output_high(PIN_C4);
    delay_ms(50);
    output_low(PIN_C4);
}

//sonido para atrad
void beep_doble(){
    output_high(PIN_C4);
    delay_ms(50);
    output_low(PIN_C4);
    delay_ms(30);
    output_high(PIN_C4);
    delay_ms(50);
    output_low(PIN_C4);
}
// Sonido para avanzar 

void beep_triple(){
     int i ;
    for( i = 0; i < 3; i++){
        output_high(PIN_C4);
        delay_ms(30);
        output_low(PIN_C4);
        delay_ms(20);
    }
}

// vamos a prender el led que este estipilado

void encender(int numero){
    // Apagar todos los LEDs (C5, C6, C7) pero mantener C4 intacto
    output_low(PIN_C5);
    output_low(PIN_C6);
    output_low(PIN_C7);
    
    // Encender el LED correspondiente
    if(numero == 0x20) output_high(PIN_C5);  // Azul
    if(numero == 0x40) output_high(PIN_C6);  // Rosado
    if(numero == 0x80) output_high(PIN_C7);  // Blanco
}

char digito(){
    int i;
    for(i = 0; i < 4; i++){
        // Primero ponemos TODAS las filas en HIGH opcional
        
        // Luego ponemos UNA fila en LOW
        if (i == 0) output_b(0b00001110); // B0=0, resto=1
        if (i == 1) output_b(0b00001101); // B1=0, resto=1
        if (i == 2) output_b(0b00001011); // B2=0, resto=1
        if (i == 3) output_b(0b00000111); // B3=0, resto=1
        
        delay_us(100); // Tiempo de estabilización
        
        // Leemos las columnas
        if(!input(PIN_B4)){
            while(!input(PIN_B4)); // Espera a que suelte
            delay_ms(50);          // Anti-rebote
            return TECLAS[i][0];
        }
        
        if(!input(PIN_B5)){
            while(!input(PIN_B5));
            delay_ms(50);
            return TECLAS[i][1];
        }
        
        if(!input(PIN_B6)){
            while(!input(PIN_B6));
            delay_ms(50);
            return TECLAS[i][2];
        }
        
        if(!input(PIN_B7)){
            while(!input(PIN_B7));
            delay_ms(50);
            return TECLAS[i][3];
        }
    }
    
    return 0; //  FUERA del for
}

void main(){
    set_tris_b(0b11110000); // B0-B3 salidad , B4-B7 entradas 
    set_tris_c(0b00000000);
    port_b_pullups(true);
    lcd_init();
    int pin = 0 ;// pin que encenderemoa
    unsigned  int estado = 0 ; // estados con los que nos estaremos moviendo 
    boolean flag = true ; // bandera pra el boton 
    boolean anterior = false ; // revisamos si el anteriro ya canvio
   
    while(true){
    
       
        lcd_gotoxy(1,1);
        printf(lcd_putc, "Menu de LE's");
        
        char k = digito();
        
        if(k != 0){
            
            if(k == 'A' && estado<=3){
                beep_triple();
                estado ++;
            }
            if(k == 'B' && estado >=1){
               beep_doble();
               estado --;
            }
            if(k == '#'){
               flag = false;
               anterior = true;
            }
            if (estado > 3 ){
               estado = 1;
            }
            if (estado ==0){
               estado = 3;
            }
            
            lcd_putc('\f');
            pin = 0 ;
            switch (estado) {  
                  case 1:
                     lcd_gotoxy(1,2);
                     printf(lcd_putc, "LED AZUL");
                     pin = 1;
                  break;
                  case 2:
                     lcd_gotoxy(1,2);
                     printf(lcd_putc, "LED ROSADO");
                     pin = 2;
                  break;
                  case 3:
                     lcd_gotoxy(1,2);
                     printf(lcd_putc, "LED BLANCO");
                     pin = 3;
                  break;
                  default:
                  break;
                }
                
               if(flag == false && anterior == true){
                beep_corto();
                switch(pin){
                     case 1:
                        encender(0x20);
                     break;
                     case 2:
                        encender(0x40);
                     break;
                     case 3:
                        encender(0x80);
                     break;
                     default:
                     break;
                }
                anterior = false ;
                    
                }
        }
    }
}
