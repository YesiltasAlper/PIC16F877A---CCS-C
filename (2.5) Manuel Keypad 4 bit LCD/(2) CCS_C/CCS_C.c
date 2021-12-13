#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#define use_portb_lcd TRUE                         // Normalde D portuna ayarlanmis LCD B portundan kontrol edilecektir.
#include<lcd.c>

int tus = 0 , a = 0;

char tus_takimi(){

   output_high(pin_d4);
   if(input(pin_d0))  {delay_ms(20);  tus = 0;}
   if(input(pin_d1))  {delay_ms(20);  tus = 1;}
   if(input(pin_d2))  {delay_ms(20);  tus = 2;}
   if(input(pin_d3))  {delay_ms(20);  tus = 3;}
   output_low(pin_d4);
   
   output_high(pin_d5);
   if(input(pin_d0))  {delay_ms(20);  tus = 4;}
   if(input(pin_d1))  {delay_ms(20);  tus = 5;}
   if(input(pin_d2))  {delay_ms(20);  tus = 6;}
   if(input(pin_d3))  {delay_ms(20);  tus = 7;}
   output_low(pin_d5);
   
   output_high(pin_d6);
   if(input(pin_d0))  {delay_ms(20);  tus = 8;}
   if(input(pin_d1))  {delay_ms(20);  tus = 9;}
   if(input(pin_d2))  {delay_ms(20);  tus = 10;}
   if(input(pin_d3))  {delay_ms(20);  tus = 11;}
   output_low(pin_d6);
   
   output_high(pin_d7);
   if(input(pin_d0))  {delay_ms(20);  tus = 12;}
   if(input(pin_d1))  {delay_ms(20);  tus = 13;}
   if(input(pin_d2))  {delay_ms(20);  tus = 14;}
   if(input(pin_d3))  {delay_ms(20);  tus = 15;}
   output_low(pin_d7);
   
   return tus;

   }

void main(){

   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_adc_ports(NO_ANALOGS); setup_adc(ADC_OFF); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF);
   
   set_tris_b(0b00000000);
   set_tris_d(0b00001111); // D portunun ilk 4 biti (d0,d1,d2,d3) giris , son 4 biti (d4,d5d,d6,d7) cikis
   
   while(1){
      
     a = tus_takimi();
     output_b(a);
     delay_ms(20);
   }

}
