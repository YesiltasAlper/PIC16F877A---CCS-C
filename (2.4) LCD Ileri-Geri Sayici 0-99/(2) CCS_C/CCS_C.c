#include <16f877.h> 
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use delay (clock = 4M)        
#include <lcd.c>

int sayi1 = 0,sayi2 = 99;

void main(){

   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x01);
   set_tris_d(0x00);
   
   lcd_init();
   
   while(1){
   
      printf(lcd_putc,"\fSayici1 : %d",sayi1);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Sayici2 : %d",sayi2);
      delay_ms(100);
      sayi1++;
      sayi2--;
      
      if(sayi1 == 99 || sayi2 == 0){
         sayi1 = 0;
         sayi2 = 99;
      }
      
      else if(input(pin_a0) == 1){
         break;
      }
   }
   
   lcd_putc('\f');
   lcd_gotoxy(1,1);
   lcd_putc("Cikis");
   lcd_gotoxy(1,2);
   lcd_putc("Basarili...");
   delay_ms(1500);
   lcd_putc('\f');
   output_d(0x00);
}
