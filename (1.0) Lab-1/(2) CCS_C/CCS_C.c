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
   
   set_tris_a(0x07);                             // A portunun ilk 2 pini giris olarak ayarlandi
   set_tris_b(0x00);                             // B portunun tumu cikis olarak ayarlandi   
   output_b(0x00);
   
   while(TRUE){
 
      if(input(pin_a0) == 1){                    // Yuruyen isik
      
         output_b(0x00);
         int x = 1,y=64;
   
         for(int i=0; i<8; i++){
         
            output_b(x);
            delay_ms(250);
            x = x * 2;
         }
      
         for(int j=0; j<7; j++){
         
            output_b(y);
            delay_ms(250);
            y = y / 2;
         }
      
         output_b(0x00);
      }
  
  
      else if(input(pin_a1) == 1){              // Kara simsek 
      
         output_b(0x00);
         int a = 3,b=96;
      
         for(int i=0; i<7; i++){
         
            output_b(a);
            delay_ms(250);
            a = a * 2;
         }
      
         for(int j=0; j<6; j++){
         
            output_b(b);
            delay_ms(250);
            b = b / 2;
         }
         
         output_b(0x00);
      }
   
   
      else if(input(pin_a2) == 1){              // Binary sayici
         
         output_b(0x00);
         int c = 1,d=127;
      
         for(int i=0; i<8; i++){
         
            output_b(c);
            delay_ms(250);
            c = (c * 2) + 1;
         }
      
         for(int j=0; j<7; j++){
         
            output_b(d);
            delay_ms(250);
            d = d / 2;
         }
         
      output_b(0x00);
      }
  }
  
}





