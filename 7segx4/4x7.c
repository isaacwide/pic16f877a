#include<16f877a.h>
#fuses xt,nowdt
#use delay(clock=4M)
#USE FAST_IO(A)
#USE FAST_IO(B)
#USE FAST_IO(C)

void show(int unidad,int decenas ,int centenas , int millares);

int hexa[10] ={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x1F,0x70,0x7F,0x7B};

void main(){
    set_tris_a(0b00000010); // entrada ra1 
    set_tris_b(0x00); // b como salidas
    set_tris_c(0b11111000); // rc0 rc1 rc2 
    
    output_b(0x00);
    
    
    int flag = 1; // vandera para cambiar de estado 
    
    int millares = 0;
    int centenas = 0;
    int decenas = 0;
    int unidad = 0;
    
    while(1){
       for(millares = 0; millares < 10; millares++){
          for(centenas = 0; centenas < 10; centenas++){
             for(decenas = 0; decenas < 10; decenas++){
               for(unidad = 0; unidad < 10; unidad++){
                   if(input(PIN_A1)){  // si pulsa el boton inicia el pause  
                      delay_ms(50);   // evitamos rebote 
                      flag = 0;
                      
                      while(flag == 0){ // ejegutara esto hasta que se vuelva a presionar el boton 
                         if(input(PIN_A1)){  // acabar la mini interrupcion 
                            delay_ms(50);
                            flag = 1;
                         }
                         show(unidad,decenas,centenas,millares);
                      }
                   }
                   show(unidad,decenas,centenas,millares);
               }
             }
          }
       }
       
        millares = 0;
        centenas = 0;
        decenas = 0;
        unidad = 0;
    }
}

void show(int unidad,int decenas ,int centenas , int millares){
    output_c(0b11111000);
    output_b(hexa[millares]);
    delay_ms(1);
    
    output_c(0b11111001);
    output_b(hexa[centenas]);
    delay_ms(1);
    
    output_c(0b11111010);
    output_b(hexa[decenas]);
    delay_ms(1);
    
    output_c(0b11111011);
    output_b(hexa[unidad]);
    delay_ms(1);  // Dentro de la función ahora
}
