#include <16f877.h>                                                   
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT      
#use delay (clock = 4000000)   

#use fast_io(a)
#use fast_io(c)

int i = 5;

void main(){

   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);      
   //setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
  // setup_CCP1(CCP_OFF);    
  // setup_CCP2(CCP_OFF);
   
   set_tris_a(0x03);
   set_tris_c(0x00);
   
   output_c(0x00);
   
   setup_ccp1(CCP_PWM);             // CCP1 birimi PWM cikisi icin ayarlandi
   setup_ccp2(CCP_PWM);             // CCP2 birimi PWM cikisi icin ayarlandi
   
   setup_timer_2(T2_DIV_BY_16,170,1);     // Timer 2 ayarlari
   
   enable_interrupts(INT_CCP1);
   enable_interrupts(INT_CCP2);
   enable_interrupts(GLOBAL);
   
   set_pwm1_duty(i);                // PWM1 cikisinin duty cycle belirleniyor
   set_pwm2_duty(i);                // PWM2 cikisinin duty cycle belirleniyor
   
   while(1){
      
      if(input(pin_a0)){
      
         delay_ms(20);
         while(input(pin_a0));
         i+=3;
         
         if(i >= 170)
            i = 170;
      }
      
      if(input(pin_a1)){
      
         delay_ms(20);
         while(input(pin_a1));
         i-=3;
         
         if(i < 5)
            i = 5;
            
      }
      
       set_pwm1_duty(i);
       set_pwm2_duty(i);
      
   }
 
}
