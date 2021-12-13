#include <16f877.h>
#use delay(clock=4000000)
#fuses XT,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(b)
#use fast_io(c)


#INT_CCP2
void compare_interrupt(){
   set_timer1(0);
   output_toggle(pin_b0);
}


void main(){

   setup_psp(PSP_DISABLED);
   // Timer1 kullanildigi icin buradaki kod devre disi birakildi
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   // CCP2 kullanildigi icin buradaki kod devre disi birakildi
  
   set_tris_b(0x00); 
   set_tris_c(0x01);
   
   output_b(0x00);
   
   enable_interrupts(INT_CCP2);
   enable_interrupts(GLOBAL);
   
   setup_ccp2(CCP_COMPARE_INT);     // CCP2 birimi compare moduna ayarlandi
   
   setup_timer_1(T1_EXTERNAL_SYNC | T1_DIV_BY_1);  
   
   CCP_2_HIGH = 0x00;      // CCPR2H kaydedicisi sifirlaniyor
   CCP_2_LOW = 0x05;       // CCPR2L kaydedicisine 5 degeri atanir
   
   set_timer1(0);          // timer1 icerigi clear edildi.
   
   while(true);
}
