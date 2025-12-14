/* mi primer codigo en micro*/
#include <16f877a.h>
#fuses xt,nowdt
#use delay(clock=4M)

#byte TRISC=0x87
#byte PORTC=0x07

void main()
{
  TRISC=0x00;
  PORTC=0x00;
  
  while(1){
  
    PORTC=0b00000001;
    delay_ms(100);
    PORTC=0b00000000;
    delay_ms(100);
    
    
    PORTC=0b00000010;
    delay_ms(100);
    PORTC=0b00000000;
    delay_ms(100);
    
    
    PORTC=0b00000011;
    delay_ms(100);
    PORTC=0b00000000;
    delay_ms(100);
    
    PORTC=0b00000011;
    delay_ms(100);
    PORTC=0b00000000;
    delay_ms(100);
  }
}
