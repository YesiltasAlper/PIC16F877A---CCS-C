#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use fast_io(a)
#use fast_io(b)

#define     delay    delay_ms(30);

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
   
   const int a[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};  // Display degerleri atandi
   int sayi = 0,onlar = 0,birler = 0; 
   
   while(1){
     
     output_b(a[birler] | (0b00010000));
     delay
     output_b(a[onlar]  | (0b00100000));
     delay
     
     if(input(pin_a0) == 1 && (sayi != 99)){
       
       sayi++;
       birler = sayi % 10;
       onlar = sayi / 10;
       
       while(input(pin_a0)){
       
         output_b(a[birler] | (0b00010000));
         delay
         output_b(a[onlar] | (0b00100000));
         delay
       }
       
     }
     
     if((input(pin_a1) == 1) && (sayi != 0)){
     
         sayi--;
         birler = sayi % 10;
         onlar = sayi / 10;
         
         while(input(pin_a1)){
         
            output_b(a[birler] | (0b00010000));
            delay
            output_b(a[onlar] | (0b00100000));
            delay
            
         }
     }
   
   } 
     
}
