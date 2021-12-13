#include<16f877.h>
#device adc = 10
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use delay (clock=4000000)
#use fast_io(a)

#define use_portb_lcd TRUE
#include <lcd.c>

void main(){
   
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF); 
   
   set_tris_a(0x01);
   set_tris_b(0x00);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0);
   
   lcd_init();
 
   while(1){
      
      set_adc_channel(0);
      delay_ms (10);
      int16 adc_oku = read_adc();
      
      float voltage = (0.0048828125*adc_oku)*1000;
      float sicaklik = (voltage/10)+2;
      
      printf(lcd_putc,"Sicaklik = ");
      lcd_gotoxy(11,1);
      printf(lcd_putc,"%5.1f'C",sicaklik);
   }

}
