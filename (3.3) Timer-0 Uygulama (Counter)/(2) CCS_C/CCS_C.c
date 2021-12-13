#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(a)
#use fast_io(b)

int i = 0;

#int_timer0
void timer0_kesme(){       // [Timer0 Eger sayici       Kesme olusma suresi = (Bolme orani) * (256 - Timer0 degeri)
                           //  olarak kullanilirsa]     Kesme olusma suresi = (1) * (256 - 254) = 2
   set_timer0(254);
   
   i++;
   output_b(i);
  
   if(i == 15)             // RA4 butonu her lojik 1 oldugunda timer0 kesmesi olusur ve her iki kesme olustugunda kod bu fonksiyona 
      i = 0;               // kod timer_0 kesme fonksiyonuna gelir ve islemleri yapar.
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
   
   set_tris_a(0x10);
   set_tris_b(0x00);
   output_b(0x00);
  
   setup_timer_0(RTCC_EXT_L_TO_H | RTCC_DIV_1);
   set_timer0(254);
   enable_interrupts(INT_timer0);
   enable_interrupts(GLOBAL);
   
   while(1);
   
}
