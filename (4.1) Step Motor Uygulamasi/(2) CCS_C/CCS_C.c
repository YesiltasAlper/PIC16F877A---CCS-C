#include <16f877.h> 
#use delay (clock = 4000000)    
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#define use_portb_lcd TRUE
#include <lcd.c>

#use fast_io(a)
#use fast_io(b)
#use fast_io(d)

#define buton_ileri  pin_a0
#define buton_geri   pin_a1

unsigned int adim = 1;
int durum;

void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);  
   setup_CCP2(CCP_OFF);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   
   set_tris_a(0x03);
   set_tris_b(0x00);
   set_tris_d(0x00);
   
   output_b(0x00);
   
   lcd_init();
   delay_ms(10);
   
   printf(lcd_putc,"\fSTEP KONTROL...");
   delay_ms(1000);
   
   while(1){
   
      switch(adim){
        
         case 1: output_d(0b00000001); break;
         case 2: output_d(0b00000011); break;
         case 3: output_d(0b00000010); break;
         case 4: output_d(0b00000110); break;
         case 5: output_d(0b00000100); break;
         case 6: output_d(0b00001100); break;
         case 7: output_d(0b00001000); break;
         case 8: output_d(0b00001001); break;
      }
      
      delay_ms(10);
      
      switch(durum){
         case 1: printf(lcd_putc,"\fAdim = %u \nDURUM  -->>",adim); break;
         case 2: printf(lcd_putc,"\fAdim = %u \nDURUM  <<--",adim); break;
         case 3: printf(lcd_putc,"\fAdim = %u \nDURUM  BOS",adim);  break;
         case 4: printf(lcd_putc,"\fAdim = %u \nDURUM  #HATA",adim);break;
      }
      
      delay_ms(10);
      
      if(input(buton_ileri)){
        delay_ms(500);
        adim++;
        durum =1;
        
        if(adim == 9){
           adim = 0;
           durum = 1;
        }
      }
      
      if(input(buton_geri)){
        delay_ms(500);
        adim--;
        durum =2;
        
        if(adim == 0){
           adim = 8;
           durum = 2;
        }
      }
      
      if(input(buton_ileri) == 0 && input(buton_geri) == 0)
      durum = 3;
      
      if(input(buton_ileri) == 1 && input(buton_geri) == 1)
      durum = 4;
     
     
   }

}
