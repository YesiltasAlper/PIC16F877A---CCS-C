#include<16f877.h>
#device adc = 10     // 10 bit ADC

#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT
#use delay (clock=4000000)

#use fast_io(a)
#use fast_io(b)

#define use_portb_lcd TRUE
#include <lcd.c>

unsigned int16 adc_okuma;
float gerilim;

void main(){
   
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(ALL_ANALOG);
   set_adc_channel(0);
   delay_us(25);
   
   lcd_init();
   
   while(1){
      
      adc_okuma = read_adc();
      gerilim = adc_okuma * 0.004887585533;
      
      printf(lcd_putc,"\fADC:%lu",adc_okuma);
      printf(lcd_putc,"\nGerilim:%.2fV",gerilim);
      delay_ms(200);
   }

}
