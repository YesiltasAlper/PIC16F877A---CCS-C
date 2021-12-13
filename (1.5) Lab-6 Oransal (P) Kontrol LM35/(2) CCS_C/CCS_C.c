#include<16f877.h>
#device adc = 10
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use delay (clock=4000000)

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)

#define use_portb_lcd TRUE
#include <lcd.c>

unsigned int16 adc_pot,adc_lm35;
float sicaklik,hata,referans;
int kp = 2,duty = 0;

void main(){
   
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED);setup_CCP2(CCP_OFF); 
   
   set_tris_a(0x03);
   set_tris_c(0x00);
   
   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_16,100,1); 
   set_pwm1_duty(duty);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(ALL_ANALOG);
   
   lcd_init();
   
   while(1){
   
      set_adc_channel(0);
      delay_us(25);
      adc_pot = read_adc();
      referans = (adc_pot)/10.24;      // 0-100 arasinda degisen referans
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fSet:%.1f",referans);
      delay_ms(200);
      
      set_adc_channel(1);
      delay_us(25);
      adc_lm35 = read_adc();
      sicaklik = ((adc_lm35) * 0.4887585532746823); // Sicaklik
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Temp:%.1f",sicaklik);
      delay_ms(200);
      
      hata = referans-sicaklik;           // Hata
      lcd_gotoxy(9,1);
      printf(lcd_putc,"Err:%.1f",hata);
      delay_ms(200);
      
      duty = kp * hata;             // Duty
      
      if(hata > 0){
         duty = kp * hata;
         set_pwm1_duty(duty);
      }
      
      if(hata < 0){
         duty = 0;
         set_pwm1_duty(duty);
      }
      
      if(duty > 100){
         duty = 100;
         set_pwm1_duty(duty);
      }
      
      lcd_gotoxy(10,2);
      printf(lcd_putc,"Duty:%d",duty);
      delay_ms(200);
      
   }

}
