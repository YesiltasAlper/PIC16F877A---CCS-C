#include <16f877.h>                                                   
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT      
#use delay (clock = 4000000)   

#use fast_io(b)
#use fast_io(c)

int i = 0;

#INT_CCP1
void yakala1_kesmesi(){             // CCP1 kesmesi her 4 yukselen kenarda 1 yakalama yapar
   i++;                             // RC2 butonu 4 kez lojik 1 oldugunda i = i+1;
   output_b(i);   
}

#INT_CCP2
void yakala2_kesmesi(){             // CCP2 kesmesi her 1 yukselen kenarda 1 yakalama yapar
   if(i == 0)                       // RC1 butonu her lojik 1 oldugunda i = i-1;
      i = 1;
      
   i--;
   output_b(i);
}

void main()
{
   setup_psp(PSP_DISABLED);
  // setup_timer_1(T1_DISABLED);      Capture modu timer1'i kullanir
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
  // setup_CCP1(CCP_OFF);    
  // setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   set_tris_c(0x06);
   output_b(0x00);
   output_c(0x00);
   
   enable_interrupts(INT_CCP1);
   enable_interrupts(INT_CCP2);
   enable_interrupts(GLOBAL);
   
   setup_ccp1(CCP_CAPTURE_DIV_4);   // CCP1 kesmesi her 4 yukselen kenarda 1 yakalama yapar
   setup_ccp2(CCP_CAPTURE_RE);      // CCP2 kesmesi her 1 yukselen kenarda 1 yakalama yapar
   
   CCP_1_HIGH = 0x00;               // CCPR1H kaydedicisi sifirlaniyor (Yuksek 8 biti)
   CCP_1_LOW = 0x00;                // CCPR1H kaydedicisi sifirlaniyor (Dusuk 8 biti)
   
   CCP_2_HIGH = 0x00;               // CCPR2H kaydedicisi sifirlaniyor (Yuksek 8 biti)
   CCP_2_LOW = 0x00;                // CCPR2H kaydedicisi sifirlaniyor (Dusuk 8 biti)
      
   while(1);
}
