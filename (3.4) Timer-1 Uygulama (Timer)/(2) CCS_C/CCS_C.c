#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(b)

int i = 0;

#int_timer1
void timer1_kesme(){       // [Timer1 Eger timer        Kesme olusma suresi = Tkomut * (Bolme orani) * (65536 - Timer1 degeri)
                           //  olarak kullanilirsa]     Kesme olusma suresi = (10^-6 sn) * (4) * (65536- 60536) = 0.02 sn = 20 msn 
   set_timer1(60536);
   i++;
   
   if(i == 100)            // (0.02 sn) * (100) = 2 sn
      output_high(pin_b0);
   
   if(i == 200){           // (0.02 sn) * (200 - 100) = 2 sn
      output_low(pin_b0);
      i = 0;
   }
      
}

void main()
{
   setup_psp(PSP_DISABLED);
 //setup_timer_1(T1_DISABLED);         		Timer 1 kullaniliyor.
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   output_b(0x00);
  
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_4);
   set_timer1(60536);
   
   enable_interrupts(INT_timer1);
   enable_interrupts(GLOBAL);
   
   while(1);
}
