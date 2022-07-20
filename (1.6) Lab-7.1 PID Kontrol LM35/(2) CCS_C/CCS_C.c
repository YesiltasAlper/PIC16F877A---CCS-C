#include<16f877.h>
#device adc = 10
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use delay (clock=4000000)

#use fast_io(a)
#use fast_io(c)

unsigned int16 adc_pot,adc_lm35;
float sicaklik,hata,Ehata,referans,integral,t_integral = 0,Ki = 0.1;

float turev;   	
float Kd = 2.5;      

int Kp = 1;
float DGM = 0;

void main(){
   
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED);setup_CCP2(CCP_OFF); 
   
   set_tris_a(0x03);
   set_tris_c(0x00);
   
   setup_ccp1(CCP_PWM);
   setup_timer_2(T2_DIV_BY_16,100,1);
   set_pwm1_duty(DGM);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(ALL_ANALOG);
   
   while(1){
   
      set_adc_channel(0);
      delay_us(25);
      adc_pot = read_adc();
      referans = (adc_pot)/10.24;             // 0-100 arasinda degisen pot ayarli referans
      delay_ms(200);
      
      set_adc_channel(1);
      delay_us(25);
      adc_lm35 = read_adc();
      sicaklik = ((adc_lm35) * 0.4887585532746823); // Sicaklik
      delay_ms(200);
      
      Ehata = hata;
      hata = referans-sicaklik;              // Hata
      delay_ms(200);

      turev = (hata - Ehata);	             // turev hesabı

      integral = (hata + Ehata)*0.5/2;       // integral hesabi
      t_integral = t_integral + integral;    // toplam integral 

      
      DGM = (Kp * hata) + (Ki * t_integral) + (Kd * turev);  // Duty hesabi 


      if(DGM > 0){
         DGM = DGM;
      }
      
      if(DGM < 0){
         DGM = 0;
      }
      
      if(DGM > 100){
         DGM = 100;
      }
     
      delay_ms(200);
      set_pwm1_duty(DGM);
   }

}