#include<16f877.h>
#device ADC = 10        // 10 bit ADC

#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use delay (clock=4000000)
#use fast_io(b)
#use fast_io(e)

#define use_portb_lcd TRUE    // LCD varsayilan olarak D portuna baglidir.Baska bir porta baglamak icin bu kod kullanilir
#include <lcd.c>

unsigned int16 adc_oku;
float voltaj;

void main(){
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF); 
  
   set_tris_e(0x0F); 
   set_tris_b(0x00);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(AN0_AN1_AN4_AN5_AN6_AN7_VREF_VREF);
   
   lcd_init();
   
   while(1){
      
      set_adc_channel(5);
      delay_us(20);
      adc_oku = read_adc();
      voltaj = 1 + (0.001955034213*adc_oku);
      printf(lcd_putc,"\fDigit:%lu",adc_oku);
      printf(lcd_putc,"\nVoltaj:%.3fV",voltaj);
      delay_ms(500);
   }

}
