#include <16f877.h>                                
#use delay (clock = 4000000)                   
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(b)
#use fast_io(c)

int i = 0;

#int_timer1
void timer1_kesme(){       // [Timer1 Eger sayici       Kesme olusma suresi = (Bolme orani) * (65536 - Timer1 degeri)
                           //  olarak kullanilirsa]     Kesme olusma suresi = (2) * (65536 - 65535) = 2

   set_timer1(65535);
   i++;                    // RC0 butonu her lojik 1 oldugunda timer1 kesmesi olusur ve her iki kesme olustugunda kod              
                           // timer1_kesme() fonksiyonuna gelir ve i degisken degeri artar.
   if(i%2 == 1)
      output_b(0x01);
   
   if(i%2 == 0)
      output_b(0x02);
      
   if(i == 2)
      i = 0;
}

void main()
{
   setup_psp(PSP_DISABLED);
 //setup_timer_1(T1_DISABLED);      	Timer 1 kullaniliyor.
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   set_tris_c(0x01);
   output_b(0x00);
  
   setup_timer_1(T1_EXTERNAL | T1_DIV_BY_2);
   set_timer1(65535);
   
   enable_interrupts(INT_timer1);
   enable_interrupts(GLOBAL);
   
   while(1);
   
}
