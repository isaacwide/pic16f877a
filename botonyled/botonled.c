/* mi primer codigo en micro*/
#include <16f877a.h> // direccion del pic 
#fuses xt,nowdt  //mandamos a la mirda al perro guardian y usamos el ocilador
#use delay(clock=4M)//usamos el osolador de 4m


// estas seran las salidas 
#byte TRISB=0x86
#byte PORTB=0x06

//ahora usaremos bit un bit del puerto c en este casi el rc 

#bit TRISC_RC2 = 0x87.2
#bit PORTC_RC2 = 0x07.2

void main()
{
  TRISB=0x00;  // configurtamos todo b como salidas 
  PORTB=0x00; // iniciamos en low 
  
  // configuramos entrada en este caso con 1 
   TRISC_RC2 = 1;

  while(1){
  
  if(TRISC_RC2=1){
     PORTB = 0b00001111;
  }else{
      PORTB = 0b0000000;
  }
 
  }
}
