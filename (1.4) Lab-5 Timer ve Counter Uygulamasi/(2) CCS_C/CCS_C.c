#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(a)
#use fast_io(b)

int sayici = 0;
int16 zamanlayici = 0;

#int_timer0 
void timer0_kesme() {   // SAYICI OLARAK KULLANILDI
   set_timer0(255);
   sayici++;
}

#int_timer1
void timer1_kesme() {   // ZAMANLAYICI OLARAK KULLANILDI

   set_timer1(63036);
   
   if(zamanlayici < 500){
   
      zamanlayici++;
      output_b(sayici);
      
      if(sayici == 3)
         sayici == 0;
         
      break;
   }
   
   if(zamanlayici >= 500){
   
      output_b(0x03);
      delay_ms(500);
      output_b(0x00);
      delay_ms(500);
      
      zamanlayici = 0;
      sayici = 0;
      
      break;
   }
}

void main(){

   setup_psp(PSP_DISABLED);
  // setup_timer_1(T1_DISABLED);       TIMER1 KULLANILDIGI ICIN BU KOD DEVRE DISI
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_a(0x10);
   set_tris_b(0x00);
   output_b(0x00);
 
   setup_timer_0(RTCC_EXT_L_TO_H | RTCC_DIV_1); // HER 1 BASMADA KESMEYE GIDER (1x1)
   set_timer0(255);
   
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);  // HER 0.02 SANIYEDE KESMEYE GIDER (8x2500x10^-6)
   set_timer1(63036);
   
   enable_interrupts(INT_timer0);
   enable_interrupts(INT_timer1);
   enable_interrupts(GLOBAL);
   
   while(1);
}
