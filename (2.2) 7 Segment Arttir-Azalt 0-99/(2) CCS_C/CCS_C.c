#include <16f877.h>                               
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use fast_io(a)
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
   
   set_tris_a(0x03);
   set_tris_b(0x00);    
   set_tris_c(0x00);
   output_b(0x00);
   output_c(0x00);
   
   
   const int a[] = {63,6,91,79,102,109,124,7,127,111};  // Display degerleri atandi
   int sayi = 0,onlar,birler; 
   
   while(1){
   
      if(input(pin_a0) == 1 && (sayi != 99)){
         
         sayi++;
         
         birler = sayi % 10;
         onlar = sayi / 10;
         
         output_high(pin_c0);
         output_b(a[birler]);
         delay_ms(50);
         output_low(pin_c0);
         
         output_high(pin_c1);
         output_b(a[onlar]);
         delay_ms(50);
         output_low(pin_c1);

      }
      
      if(input(pin_a1) == 1 && (sayi != 0)){
         
         sayi--;
         
         birler = sayi % 10;
         onlar = sayi / 10;
         
         output_high(pin_c0);
         output_b(a[birler]);
         delay_ms(50);
         output_low(pin_c0);
         
         output_high(pin_c1);
         output_b(a[onlar]);
         delay_ms(50);
         output_low(pin_c1);
         
      }
      
         output_high(pin_c0);
         output_b(a[birler]);
         delay_ms(50);
         output_low(pin_c0);
         
         output_high(pin_c1);
         output_b(a[onlar]);
         delay_ms(50);
         output_low(pin_c1);
   }
       
}
