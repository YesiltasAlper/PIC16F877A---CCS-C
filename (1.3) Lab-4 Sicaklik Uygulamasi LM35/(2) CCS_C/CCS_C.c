#include<16f877.h>
#device adc = 10
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use delay (clock=4000000)
#use fast_io(a)
#use fast_io(b)
#use fast_io(c)


#define use_portb_lcd TRUE
#include <lcd.c>

unsigned int16 adc_okuma1,adc_okuma2;
float sicaklik_lm35,voltaj_lm35,sicaklik_pot;

void main(){
   
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF); 
  
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_AN1_AN3); // RA0-RA1-RA3 ANALOG
   
   set_tris_a(0x03);
   set_tris_c(0x00);
   output_c(0x00);
  
   lcd_init();
   
   while(1){
      
      set_adc_channel(0);
      delay_ms (10);
      adc_okuma1 = read_adc();
      sicaklik_pot = (adc_okuma1/25.575)+30;    // Max 70 derece
      printf(lcd_putc,"\fSp:%.1f",sicaklik_pot);
     
      set_adc_channel(1);
      delay_ms (10);
      adc_okuma2 = read_adc();
      voltaj_lm35 = (adc_okuma2 * 0.0048828125)*1000; // MV cinsinden gerilim degeri
      printf(lcd_putc,"\nVL:%.1fmV",voltaj_lm35);
      
      lcd_gotoxy(9,1);
      sicaklik_lm35 = (voltaj_lm35/10);
      printf(lcd_putc,"SL:%.1f",sicaklik_lm35);
      
     
      if(sicaklik_lm35 > sicaklik_pot){   
         output_high(pin_c0);
         lcd_gotoxy(11,2);
         printf(lcd_putc,"LED:1");
         delay_ms (10);
      }
   
      else{
         output_low(pin_c0);
         lcd_gotoxy(11,2);
         printf(lcd_putc,"LED:0");
         delay_ms (10);
      }
   }
}
