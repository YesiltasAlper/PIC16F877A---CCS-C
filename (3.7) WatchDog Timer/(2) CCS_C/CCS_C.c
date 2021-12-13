#include <16f877.h>                                
#use delay (clock = 4000000)                      
#fuses HS,WDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT      // NOWDT komutu WDT komutuna cevrildi.

#use fast_io(a)
#use fast_io(b)

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
   set_tris_b(0x00);
   output_b(0x00);
 
   setup_WDT(WDT_2304MS);           // WDT ayari yapiliyor (max 2304 ms)
      
   while(1){
      
      output_toggle(pin_b0);        // RBO cikis durumu tersleniyor
      
      while(input(pin_a0))          
         restart_wdt();             // WDT'i sifirla
         
      sleep();                      // Denetleyici uyku moduna aliniyor
   }
 
}

// Program basladiginda LED = 1 olur ve butona basildiginda denetleyici 2304 ms sonra uyku moduna gecer ve LED = 0 olur
// Ardindan tekrar butona basilirsa denetleyici 2304 ms sonra uyku modundan cikar ve LED = 1 olur
