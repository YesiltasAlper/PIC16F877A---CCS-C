#include<16f877.h>
#device adc = 10
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use delay (clock=4000000)
#use fast_io(a)

#define use_portb_lcd TRUE
#include <lcd.c>

void main(){
   
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF); 
   
   set_tris_a(0x03);
   set_tris_b(0x00);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_AN1_AN3);    // RA0-RA1-RA3 ANALOG
   
   lcd_init();
   
   while(1){
   
      set_adc_channel(0);
      delay_ms (10);
      int16 adc_oku1 = read_adc();
      
      set_adc_channel(1);
      delay_ms (10);
      int16 adc_oku2 = read_adc();
      
      signed int16 sicaklik = adc_oku1 - adc_oku2;
      
      lcd_gotoxy(1,1);
      printf(lcd_putc,"temp= %2.1f",sicaklik*5.*100./1023.); 
      printf(lcd_putc,"C   ");
      
      signed int16 voltage = adc_oku1 - adc_oku2;
      
      lcd_gotoxy(1,2);
      printf(lcd_putc,"voltage= %2.1f",voltage*5.*10./1023.); 
      printf(lcd_putc,"V   ");
   }

}
