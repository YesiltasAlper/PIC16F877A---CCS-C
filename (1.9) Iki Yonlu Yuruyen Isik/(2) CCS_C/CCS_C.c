#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use fast_io(a)
#use fast_io(b)

void main(){

   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x03); 
   set_tris_b(0x00); 
   
   output_b(0x00);
   
   while(1){
   
      if(input(pin_a0) == 1){
      
         int x= 1;
      
         for(int i=0; i<8; i++){
      
            output_b(x);
            delay_ms(500);
            x=x<<1;
      
         if(input(pin_a0) == 1)
            break;
         
         if(input(pin_a1) == 1)
            break;
            
         }
         
      }
 
      else if(input(pin_a1) == 1){
      
         int y = 128;
         
         for(int i=0; i<8; i++){
         
            output_b(y);
            delay_ms(500);
            y = y>>1;
            
          if(input(pin_a1) == 1)
            break;
            
          if(input(pin_a0) == 1)
            break;
         }
          
      }
      
   }
   
}
