// progrma de un contador de 2 digitos 
#include<16f877a.h>
#fuses xt,nowdt
#use delay(clock=4M)
#USE FAST_IO(B)
#USE FAST_IO(D)

void show(int unidad,int decenas);


// vamos a tener que cmabiar los hezas 
// a b c d e f g dp
// 0 1 2 3 4 5 6 7 

int hexa[10] = {
  0x3F,  // 0 = 0011 1111 = abcdef   (segmentos: a,b,c,d,e,f)
  0x06,  // 1 = 0000 0110 = bc       (segmentos: b,c)
  0x5B,  // 2 = 0101 1011 = abdeg    (segmentos: a,b,d,e,g)
  0x4F,  // 3 = 0100 1111 = abcdg    (segmentos: a,b,c,d,g)
  0x66,  // 4 = 0110 0110 = bcfg     (segmentos: b,c,f,g)
  0x6D,  // 5 = 0110 1101 = acdfg    (segmentos: a,c,d,f,g)
  0x7D,  // 6 = 0111 1101 = acdefg   (segmentos: a,c,d,e,f,g)
  0x07,  // 7 = 0000 0111 = abc      (segmentos: a,b,c)
  0x7F,  // 8 = 0111 1111 = abcdefg  (segmentos: todos)
  0x6F   // 9 = 0110 1111 = abcdfg   (segmentos: a,b,c,d,f,g)
};

void main(){
    // configuramos el adc
    int16 valor_adc;
    
    unsigned int v ;
    
    //mas configuraciones 
    
    setup_adc_ports(AN0);        
   
    setup_adc(ADC_CLOCK_DIV_8);  // Configura el reloj del ADC en este caso como es de 4 mg hrs 
    
    set_adc_channel(0);          // Selecciona el canal 0 (AN0)
    
    delay_us(20);
    
    set_tris_d(0b00000000); // todos seran salidas por la multiplexion
    set_tris_b(0x00); // b como salidas  
    output_b(0x00);
    
    int decenas = 0;
    int unidad = 0;
    int i ;
    
    while(true){
        
       valor_adc= read_adc();
       v = (valor_adc * 99)/1023 ; 
       
       decenas = v / 10;            
       unidad = v % 10;
      
       for(i = 0 ; i<100 ; i++ ){
         show(unidad,decenas);
            
       }
        
        decenas = 0;
        unidad = 0;
    }
}

void show(int unidad, int decenas){
   
    output_d(0b00000000);          // Apagar todo
    output_b(hexa[decenas]);       
    output_d(0b10000000);          
    delay_ms(1);
    
    output_d(0b00000000);          // Apagar todo primero
    output_b(hexa[unidad]);        
    output_d(0b01000000);          
    delay_ms(1);
}
