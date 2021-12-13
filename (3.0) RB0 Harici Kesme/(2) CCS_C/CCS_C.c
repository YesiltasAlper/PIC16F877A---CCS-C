#include <16f877.h>                                
#use delay (clock = 4000000)                       
#fuses XT,HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT 

#use fast_io(b)

#int_ext                // Harici kesme bildirme syntax
void dis_kesme(){       // Kesmede ne yapýlacaksa o fonksiyon
  
  while(1){
   
      output_high(pin_b1);
      delay_us(1000);
      output_low(pin_b1);
      delay_us(1000);
      
      if(input(pin_a0) == 1)
         break;
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
   
   set_tris_a(0x01);
   set_tris_b(0x01);
   output_b(0x00);
   
   while(1){
   
      ext_int_edge(H_TO_L);         // High to Low dusen kenarda demektir
      enable_interrupts(INT_EXT);   // Kesmeyi aktif etmek icin
      enable_interrupts(GLOBAL);    // Aktif edilen kesmelere izin verilir
   }
  
}
