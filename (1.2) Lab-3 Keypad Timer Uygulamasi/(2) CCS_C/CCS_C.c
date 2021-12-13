#include <16f877.h>   
#fuses HS,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT    
#use delay (clock = 4000000)

#use fast_io(b)
#use fast_io(c)
#use fast_io(d)

#define use_portb_lcd TRUE
#include<lcd.c>


int16 hedef = 0,binler = 0,yuzler = 0,onlar = 0, birler = 0,tus_degeri = 20, t = 0, x=0,sayac = 0;


int tus_oku();
void calis();
void temizle();
void surehesap();
void yaz();


void main(){
   setup_psp(PSP_DISABLED); setup_timer_1(T1_DISABLED); setup_timer_2(T2_DISABLED,0,1); setup_adc_ports(NO_ANALOGS); setup_adc(ADC_OFF); setup_CCP1(CCP_OFF); setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   set_tris_c(0x00);
   set_tris_d(0x0F);
   
   output_c(0x00);
   
   lcd_init();
   lcd_putc("\fHEDEF:");
   lcd_gotoxy(11,1);
   lcd_putc("S:");
   lcd_gotoxy(1,2);
   lcd_putc("DURUM:");
   lcd_gotoxy(7,2);
   lcd_putc("LCD_AKTIF");
 
   while(1){
   
   t = tus_oku();
   
   if(t != 20){
         
      if(t == 10){      // 4 basamakli sayi girildikten sonra tamam icin '*' tusuna basilir
         calis();
      }
         
      if(t == 11){      // Temizle icin islem bittikten sonra '#' tusuna basilir
         temizle();
      }
         
      if(t < 10){
         surehesap();
      }
        
      if(x > 0){
         yaz();
      }
      delay_ms(500);
   }
   
   }
}


int tus_oku(){

   tus_degeri = 20;
   
   output_high(pin_d4);
   if(input(pin_d0))  {delay_ms(20);  tus_degeri = 1;  x++; while(input(pin_d0));}
   if(input(pin_d1))  {delay_ms(20);  tus_degeri = 4;  x++; while(input(pin_d1));}
   if(input(pin_d2))  {delay_ms(20);  tus_degeri = 7;  x++; while(input(pin_d2));}
   if(input(pin_d3))  {delay_ms(20);  tus_degeri = 10;     while(input(pin_d3));}
   output_low(pin_d4);
   
   output_high(pin_d5);
   if(input(pin_d0))  {delay_ms(20);  tus_degeri = 2;  x++; while(input(pin_d0));}
   if(input(pin_d1))  {delay_ms(20);  tus_degeri = 5;  x++; while(input(pin_d1));}
   if(input(pin_d2))  {delay_ms(20);  tus_degeri = 8;  x++; while(input(pin_d2));}
   if(input(pin_d3))  {delay_ms(20);  tus_degeri = 0;  x++; while(input(pin_d3));}
   output_low(pin_d5);
   
   output_high(pin_d6);
   if(input(pin_d0))  {delay_ms(20);  tus_degeri = 3;  x++; while(input(pin_d0));}
   if(input(pin_d1))  {delay_ms(20);  tus_degeri = 6;  x++; while(input(pin_d1));}
   if(input(pin_d2))  {delay_ms(20);  tus_degeri = 9;  x++; while(input(pin_d2));}
   if(input(pin_d3))  {delay_ms(20);  tus_degeri = 11;      while(input(pin_d3));}
   output_low(pin_d6);
   
   return tus_degeri;
}


void calis(){
   
   lcd_gotoxy(7,2);
   lcd_putc(" SAYIYOR.");
   output_high(pin_c0);
   
      for(sayac = 0; sayac <= hedef; sayac++){
      
         lcd_gotoxy(13,1);
         printf(lcd_putc,"%lu",sayac);
         delay_ms(1);
      }
      
      output_low(pin_c0);
      lcd_gotoxy(7,2);
      lcd_putc("SAYIM_OK.");
}


void temizle(){

   x = 0;
   t = 0;
   sayac = 0;
   hedef = 0;
   binler = 0;
   yuzler = 0;
   onlar = 0;
   birler = 0;
   lcd_gotoxy(1,1);
   lcd_putc("\fHEDEF:");
   lcd_gotoxy(11,1);
   lcd_putc("S:");
   lcd_gotoxy(1,2);
   lcd_putc("DURUM:");
   lcd_gotoxy(7,2);
   lcd_putc("RESET_OK.");
   delay_ms(1000);
   lcd_gotoxy(7,2);
   lcd_putc("LCD_AKTIF");
}


void surehesap(){
   
    if(x == 1){
    binler = t * 1000;
    }
               
    if(x == 2){
    yuzler = t * 100;
    }
                 
    if(x == 3){
    onlar = t * 10;
    }
              
    if(x == 4){
    birler = t * 1;
    }
    
    hedef = binler + yuzler + onlar + birler;
 
}



void yaz(){
      
     lcd_gotoxy(7,1);
     printf(lcd_putc,"%lu",hedef);
     delay_ms(50);
}





