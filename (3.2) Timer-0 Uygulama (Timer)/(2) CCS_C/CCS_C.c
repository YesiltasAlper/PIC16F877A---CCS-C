#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use fast_io(b)

int i = 0;

#int_timer0
void timer0_kesme(){       // [Timer0 Eger timer        Kesme olusma suresi = Tkomut * (Bolme orani) * (256 - Timer0 degeri)
                           //  olarak kullanilirsa]     Kesme olusma suresi = (10^-6 sn) * (256) * (256 - 60) = 0.0501 sn = 0.05 sn
   set_timer0(60);
   i++;
   
   if(i == 10)                // (0.05 sn) * (10) = 0.5 sn
      output_high(pin_b0);
   
   if(i == 20){               // (0.05 sn) * (20 - 10) = 0.5 sn
      output_low(pin_b0);
      i = 0;
   }
}

void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   output_b(0x00);
  
    
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);
   set_timer0(60);
   enable_interrupts(INT_timer0);
   enable_interrupts(GLOBAL);
   
   while(1);
   
}
