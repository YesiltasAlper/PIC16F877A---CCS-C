#include <16f877.h>                                
#use delay (clock = 4000000)                      
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use fast_io(a)
#use fast_io(b)

#define     delay    delay_ms(20)

void main(){

   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x07);
   set_tris_b(0x00);    
   
   const int a[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};  // Display degerleri atandi
   int16 sayi = 5000,mod1000 = 0; 
   int binler = 0,onlar = 0,yuzler = 0,birler = 0,mod100 = 0,mod10 = 0;
   
   while(1){
     
     output_b(a[birler] | (0b00010000));
     delay;
     output_b(a[onlar]  | (0b00100000));
     delay;
     output_b(a[yuzler] | (0b01000000));
     delay;
     output_b(a[binler] | (0b10000000));
     delay;
     
     if(input(pin_a0)){
       
      sayi++;
      
      binler = sayi / 1000;
      mod1000 = sayi % 1000;
      yuzler = mod1000/100;
      mod100 = sayi % 100;
      onlar = mod100 / 10;
      mod10 = sayi % 10;
      birler = mod10 / 1;
       
       while(input(pin_a0)){
       
         output_b(a[birler] | (0b00010000));
         delay;
         output_b(a[onlar]  | (0b00100000));
         delay;
         output_b(a[yuzler] | (0b01000000));
         delay;
         output_b(a[binler] | (0b10000000));
         delay;
       }
       
     }
     
     if((input(pin_a1) == 1) && (sayi != 0)){
     
       sayi--;
      
       binler = sayi / 1000;
       mod1000 = sayi % 1000;
       yuzler = mod1000/100;
       mod100 = sayi % 100;
       onlar = mod100 / 10;
       mod10 = sayi % 10;
       birler = mod10 / 1;
         
         while(input(pin_a1)){
         
            output_b(a[birler] | (0b00010000));
            delay;
            output_b(a[onlar]  | (0b00100000));
            delay;
            output_b(a[yuzler] | (0b01000000));
            delay;
            output_b(a[binler] | (0b10000000));
            delay;
            
         }
     }
     
     if(input(pin_a2) == 1){
     
       sayi = 0;
       binler = 0;
       yuzler = 0;
       onlar = 0;
       birler = 0;
     }
           
   }
      
}
