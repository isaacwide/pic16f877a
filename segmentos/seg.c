#include<16f877a.h>
#fuses xt,nowdt
#use delay(clock=4M)
#USE FAST_IO(C)
#USE FAST_IO(B)


void main(){
    set_tris_b(0x00); // Puerto b como salidas
    set_tris_c(0b00000010);// puerto co como salida
    
    output_b(0x00);  // Inicia apagado
    
    int hexa[10] ={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x1F,0x70,0x7F,0x7B}; // segmentos de el display
    int i =0 ;
    
    // cualquier declaracion debe ir fuera del while 
    
    while(1){
    
    // cuando presionamos un boton se incrementa el comtador 
    // interrupciones cunado se cambian de estados
      if(input(PIN_C1)){
             
           if(i<10){
           
              delay_ms(200);
              output_b(hexa[i]);  // Números 
              i++;
           
           }else{
              i=0;
           }
      }   
    }
}
