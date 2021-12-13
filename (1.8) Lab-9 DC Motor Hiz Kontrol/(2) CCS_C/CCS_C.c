#include <16f877.h> 
#device adc=8
#use delay (clock = 4000000)    
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)

#define use_portb_lcd TRUE
#include <lcd.c>

unsigned int deger;
float voltaj;

void main(){
	
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);  
   setup_CCP2(CCP_OFF);
   //setup_timer_2(T2_DISABLED,0,1);
   //setup_adc_ports(NO_ANALOGS);
   //setup_adc(ADC_OFF);
   //setup_CCP1(CCP_OFF);
   
   setup_timer_2(T2_DIV_BY_4,255,1);
   setup_CCP1(CCP_PWM);
   
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(ALL_ANALOG);
   set_adc_channel(4);
   
   set_tris_a(0x20);
   set_tris_b(0x00);
   set_tris_c(0x00);
   
   output_a(0x00);
   output_b(0x00);
   output_c(0x00);
   
   lcd_init();
   printf(lcd_putc,"\fDC MOTOR\nHIZ KONTROLU");
   delay_ms(1000);
   
   set_pwm1_duty(0);    // 5V * %0 = 0 Volt 
   
   while(1){
      
      deger = read_adc();
      voltaj = deger/51.0;
      
      output_high(pin_c3);
      output_low(pin_c4);
      
      set_pwm1_duty(deger);
      
      printf(lcd_putc,"\fVoltaj:%.2fV",voltaj);
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Deger:%u",deger);
      delay_ms(1000);
   }

}
