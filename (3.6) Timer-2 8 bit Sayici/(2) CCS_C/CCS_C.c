#include <16f877.h>                                
#use delay (clock = 4000000)                      
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(a)
#use fast_io(b)

unsigned int i = 0;

#int_timer2 
void timer2_kesme(){       // Kesme olusma suresi = Tkomut * (Bolme orani) * (PR2 Degeri + 1) * (Postscaler degeri)
                           // Kesme olusma suresi = (1^10-6 sn) * (16) * (250 + 1) * (16) = 0.64 sn
   i++;
   
   output_high(pin_b0);
   output_low(pin_b0);
}

void main(){
	
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);      
  // setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x01);
   set_tris_b(0x00);
   
   output_b(0x00);
 
   setup_timer_2(T2_DIV_BY_16,250,16); 
   set_timer2(5);
   
   enable_interrupts(INT_timer2);
   enable_interrupts(GLOBAL);
   
   while(1){
      
      if(input(pin_a0))
      output_b(i);
   }
 
}
