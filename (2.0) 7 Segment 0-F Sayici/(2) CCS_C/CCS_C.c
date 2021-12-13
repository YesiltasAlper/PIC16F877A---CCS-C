#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use fast_io(b)

 void segment(int x){
   
      switch(x){

   case 0:
               output_b(63);       // 0x3F          0 0 1 1 1 1 1 1         0
               delay_ms(250);
               break;
   case 1:
               output_b(6);        // 0x06          0 0 0 0 0 1 1 0         1
               delay_ms(250);
               break;
   case 2:
               output_b(91);       // 0x5B          0 1 0 1 1 0 1 1         2
               delay_ms(250);
               break;
   case 3:
               output_b(79);       // 0x4F          0 1 0 0 1 1 1 1         3   
               delay_ms(250);
               break;
   case 4:
               output_b(102);      // 0x66          0 1 1 0 0 1 1 0         4
               delay_ms(250);
               break;
   case 5:
               output_b(109);      // 0x6D          0 1 1 0 1 1 0 1         5
               delay_ms(250);
               break;
   case 6:
               output_b(124);      // 0x7C          0 1 1 1 1 1 0 0         6
               delay_ms(250);
               break;
   case 7:
               output_b(7);        // 0x07          0 0 0 0 0 1 1 1         7
               delay_ms(250);
               break;
   case 8:
               output_b(127);      // 0x7F          0 1 1 1 1 1 1 1         8
               delay_ms(250);
   case 9:
               output_b(111);      // 0x6F          0 1 1 0 1 1 1 1         9
               delay_ms(250);
               break;
   case 10:
               output_b(119);      // 0x77          0 1 1 1 0 1 1 1         A 
               delay_ms(250);
               break;
   case 11:
               output_b(124);      // 0x7C          0 1 1 1 1 1 0 0         B    
               delay_ms(250);
               break;
   case 12:
               output_b(57);       // 0x39          0 0 1 1 1 0 0 1         C
               delay_ms(250);
               break;
   case 13:
               output_b(94);       // 0x5E          0 1 0 1 1 1 1 0         D 
               delay_ms(250);
               break;
   case 14:
               output_b(121);      // 0x79          0 1 1 1 1 0 0 1         E
               delay_ms(250);
               break;
   case 15:
               output_b(113);      // 0x71          0 1 1 1 0 0 0 1         F
               delay_ms(250);
               break;
      }
   }
   
void main(){

   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x01);
   set_tris_b(0x00);
   
    int y = 0;
    
    int1 flag = 1;
    
    while(1){
      
      for(int i=0; i<=15; i++){
         
         segment(y);
         y++; 
         
         if(input(pin_a0) == 1){
            flag = 0;
            break;
         }
           
      }
      
      if(flag == 0)
         break;
    }
    
    output_b(0x3F);
    delay_ms(250);
    output_b(0x00);    
}
