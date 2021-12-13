#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses XT,HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 
#use fast_io(b)


#int_RB                
void B_degisiklik(){   
   
   if(input(pin_b4))
      output_high(pin_b0);
   if(input(pin_b5))
      output_high(pin_b1);
   if(input(pin_b6))
      output_high(pin_b2);
   if(input(pin_b7))
      output_high(pin_b3);
      
   delay_ms(1000);
   output_b(0x00);
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
   
   set_tris_b(0xF0);
   output_b(0x00);
   
   while(1){
   
      enable_interrupts(INT_RB);    // Kesmeyi aktif etmek icin
      enable_interrupts(GLOBAL);    // Aktif edilen kesmelere izin verilir
   }
  
}
