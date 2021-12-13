#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use fast_io(b)
#use fast_io(c)
   
void main(){

   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   set_tris_c(0x00);
   
   char segment[] = {63,6,91,79,102,109,124,7,127,111};
   
   output_b(0x00);
   output_c(0x00);
   
   int1 flag = 1;
   
   while(1){

      for(int j = 0; j < 10; j++){
      
            for(int k = 0; k < 10; k++){
               output_c(segment[j]);
               output_b(segment[k]);
               delay_ms(50);
               
               if(input(pin_a0) == 1){
                 flag = 0;
                 break;
               }
            }
      }
      
      if(flag == 0)
         break;
   }
   
    output_c(segment[0]);
    output_b(segment[0]);
    delay_ms(250);
    output_b(0x00);    
}
