#include "Arduino.h"
#include "TinyGPS.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "U8glib.h"
/* SES DOSYALARI
 * 0001.mp3 -   1  - BESIKTAS
 * 0002.mp3 -   2  - ÜSKÜDAR
 * 0003.mp3 -   3  - KABATAS 
 * 0004.mp3 -   4  - KADIKOY 
 * 0005.mp3 -   5  - EMİNONU
 * 0006.mp3 -   6  - BURGAZADA
 * 0007.mp3 -   7  - KINALIADA
 * 0008.mp3 -   8  - HEYBELİADA
 * 0009.mp3 -   9  - BÜYÜKADA
 * 0010.mp3 -  10  - SİGARA 
 * 0011.mp3 -  10  - SİGARA 
 * 0012.mp3 -  10  - SİGARA 
 * 0013.mp3 -  10  - SİGARA 
 * 0014.mp3 -  10  - SİGARA 
 * 0015.mp3 -  10  - SİGARA 
 * 0016.mp3 -  10  - SİGARA 
 * 0017.mp3 -  10  - SİGARA 
 * 0018.mp3 -  10  - SİGARA 
 * 0019.mp3 -  10  - SİGARA 
 * 0020.mp3 -  10  - SİGARA 
 */
TinyGPS gps;
SoftwareSerial ssgps(4, 3); //rx tx
SoftwareSerial ssplayer(10, 11); // RX, TX
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
DFRobotDFPlayerMini player;
  float flat, flon;
  uint8_t anons_sayac = 0;
  uint8_t ses_dosya;
  uint8_t button_sayac2 =0;
  uint8_t button_sayac1 =1;
  uint8_t current_page1 =0;
  uint8_t current_page2 =0;
  uint8_t menu_swap = 1;
  uint8_t sefer_no;
  uint8_t sigara_anons_no; 
  uint8_t volume=25;
  uint8_t ekran_koruyucu_sure;
  float current_loc[2];
  uint8_t goruntu_sayac =1;
  long ekran_koruyucu;
  long kayan_yazi;
  long timer1;
  uint8_t konum_no;
  
 
 float Uskudar_iskele[]= {41.027217994892446, 29.01372839057748,41.02895214760056, 29.0161689187923};
 float Besiktas_iskele[]={41.03548691051261, 29.002465570306633,41.04208892352286, 29.009748793486658};  
 float Kabatas_iskele[]={41.03163795571091, 28.9910089244191,41.03854037283602, 28.999265559997532};  
 float Kadikoy_iskele[]={40.98950422380814, 29.014312701382195,40.99434691574612, 29.0241617732726};
 float Eminonu_iskele[] = {41.01648010295696, 28.97366558469026,41.020463971063556, 28.983527946406113};
 float Bizim_ev_konum[]={41.01320994453465, 29.02247559580991,41.01378517610856, 29.023098102779393};    
 float Kinaliada_iskele[]={40.907163934878525, 29.051784355259848,40.91913462942703, 29.062101904181475};    
 float Burgazada_iskele[]={40.87927305179468, 29.067910566555568,40.887283177645905, 29.074210306836868};    
 float Heybeliada_iskele[]={40.8743194408761, 29.09723371727601,40.88442693823291, 29.10566658170427};    
 float Buyukada_iskele[]={40.87148983581885, 29.1215669068439,40.879321174647124, 29.129542212535682};    


const uint8_t wifi_on [] PROGMEM = {
  0x00, 0x3c, 0x42, 0xbd, 0x42, 0x18, 0x18, 0x00
};
const uint8_t ses_on [] PROGMEM = {
  0x02, 0x09, 0x65, 0xe5, 0xe5, 0x65, 0x09, 0x02
};
const uint8_t asagi [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x7f, 0xfc, 0x3f, 0xf8, 0x1f, 0xf0, 
  0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t yukari [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x80, 0x07, 0xc0, 0x0f, 0xe0, 
  0x1f, 0xf0, 0x3f, 0xf8, 0x7f, 0xfc, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const uint8_t dentur_logo [] PROGMEM = {

};
    
void setup()
   { 
  Serial.begin(9600);
  ssplayer.begin(9600);   
  ssgps.begin(9600);
   }

 
  static void smartdelay(unsigned long ms)
  {
  unsigned long start = millis();
  do {
      while (ssgps.available())
      gps.encode(ssgps.read());
     }  
     while (millis() - start < ms);
  }


  float InorOut(float x[],float y[])
   { 
      if(x[0]< y[0] &&
         x[2]> y[0] &&
         x[1]< y[1] &&
         x[3]> y[1] ) 
      {return true;}
      else
      {return false;}    
   }


   int anons_yap(int x)
   {
     static unsigned long timer1 = millis();
     if (millis() - timer1 > 40000) 
     {
     timer1 = millis();
     player.volume(volume); 
     player.play(x);
     anons_sayac ++; 
     Serial.println(anons_sayac);
     }
   }

    int oto_anons_yap(long y)
   {
     static unsigned long timer1 = millis();
     if (millis() - timer1 > y) 
     {
     timer1 = millis();
     player.volume(volume); 
     player.play(10);
     Serial.println("SİGARA ANONSU YAPLIYOR");
     }
   }


  int sefer_secimi(int sefer_nu)
  {
    if(sefer_nu ==0) // SEFER YOK
    {
     
    }
    
    if(sefer_nu ==1) // KADIKÖY BESİKTAS NO. 1
    {
         if(InorOut(Kadikoy_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(4);
         konum_no=4;}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         konum_no=1;}}  
         else
         {anons_sayac = 0;} 
    }
    
    if(sefer_nu ==2) // ÜSKÜDAR BESİKTAS NO. 2
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(2);
         Serial.println("aaaasa");
         konum_no=2;}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);}}      
         else
         {anons_sayac = 0;}     
     }  
     if(sefer_nu ==3) // KADIKÖY KABATAŞ NO. 3
     {
         if(InorOut(Kadikoy_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(4);
         konum_no=4;}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(3);
         konum_no=3;}}      
         else
         {anons_sayac = 0;}    
     } 
     if(sefer_nu ==4) // ÜSKÜDAR KABATAŞ NO. 4
     {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(2);
         konum_no=2;}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(3);
         konum_no=3;}}      
         else
         {anons_sayac = 0;}    
     } 
      if(sefer_nu ==5) // ADALAR NO. 5
    {
         if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         konum_no=1;}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(3);
         konum_no=1;}}
         else if(InorOut(Eminonu_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(5);
         konum_no=1;}}
         else if(InorOut(Burgazada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(6);
         konum_no=1;}}
         else if(InorOut(Kinaliada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(7);
         konum_no=1;}}
         else if(InorOut(Heybeliada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(8);
         konum_no=1;}}
         else if(InorOut(Buyukada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(9);
         konum_no=1;}}
         else if(InorOut(Kadikoy_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(4);
         konum_no=1;}}  
         else
         {anons_sayac = 0;} 
    }
  
  }  
    

 void loop()
 {
  
  //##############################  GPS  ##########################################################
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age2;
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);
    int bagli_uydu = gps.satellites();
    
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
   
    current_loc[0] = flat, 6;
    current_loc[1] = flon, 6;
  //##############################  GPS  ##########################################################

    
    smartdelay(100);
    /*
    Serial.print(current_loc[0],6);
    Serial.print(F(", "));
    Serial.print(current_loc[1],6);
    Serial.print(F(",   "));
    Serial.print(F(sefer_no));
    Serial.print(F(",   "));
    Serial.print(F(current_page1));
    Serial.print(F(",   "));
    Serial.print(F(current_page1));
    Serial.print(F(",   "));
    Serial.print(F(menu_swap));
    Serial.print(F(",   "));
    Serial.println(F(bagli_uydu));
    */
   //##############################  SERİAL PORT  ##########################################################
    
   //#############################  BUTTON  ###################################################### 
    if(digitalRead(5)==HIGH)
    {  
    button_sayac1++;
    delay(100);
    ekran_koruyucu = millis();
    }

    if(digitalRead(6)==HIGH)
    {
    delay(50);
    button_sayac2--;
    ekran_koruyucu=millis();
    }
    if(digitalRead(8)==HIGH)
    {
    button_sayac2++;
    delay(50);
    ekran_koruyucu=millis();
    }
    if(digitalRead(7)==HIGH)
    { 
    button_sayac1--;
    ekran_koruyucu=millis();
    delay(100);
    }
    
    static unsigned long ekran_koruyucu = millis(); 
    if (millis() - ekran_koruyucu > 300000) 
     {
     current_page1=0;
     menu_swap=1;
      if(digitalRead(5)==HIGH||
         digitalRead(6)==HIGH||
         digitalRead(7)==HIGH||
         digitalRead(8)==HIGH)
       {ekran_koruyucu=millis();}
     }
     
     else
     {
    menu_swap = button_sayac1 % 3;
    if(menu_swap==0)
    {
    current_page1 = button_sayac2 % 5;
    current_page2 = 0;
    }
    if(menu_swap==1)
    {
    //current_page1 = 0;
    current_page2 = button_sayac2 % 4;
    }
    if(button_sayac1<0)
    {button_sayac1=0;}
    if(button_sayac2<0)
    {button_sayac2=0;}
     }
     
    //#############################  BUTTON  ###################################################### 
    timer1=millis();
    kayan_yazi = 10000000-(timer1 / 100);     
    //##############################  ANONSLAR  #######################################################

          if(current_page1==1 &&
             current_page2==0 &&
             menu_swap==2)
           {
               sefer_no=1;
               u8g.firstPage();  
               do {
               //u8g.setFont(u8g_font_courB14);
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAD-BES");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);
               button_sayac1=button_sayac1+2;         
           }

           
          if(current_page1==1 &&
             current_page2==1 &&
             menu_swap==2)
           {
               sefer_no=2;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "USK-BES");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000); 
               button_sayac1=button_sayac1+2;             
           }

           
          if(current_page1==1 &&
             current_page2==2 &&
             menu_swap==2)
           {
               sefer_no=3;
               u8g.firstPage();  
               do {
                u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAD-KAB");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000); 
               button_sayac1=button_sayac1+2;              
           }

           
           if(current_page1==1 &&
             current_page2==3 &&
             menu_swap==2)
           {
               sefer_no=4;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "USK-KAB");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==4 &&
             menu_swap==2)
           {
               sefer_no=5;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "HISAR");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==5 &&
             menu_swap==2)
           {
               sefer_no=6;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "ORTABOGAZ");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==6 &&
             menu_swap==2)
           {
               sefer_no=7;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KUCUKSU");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==7 &&
             menu_swap==2)
           {
               sefer_no=8;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "SARIYER");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==8 &&
             menu_swap==2)
           {
               sefer_no=9;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "BEYKOZ");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==9 &&
             menu_swap==2)
           {
               sefer_no=10;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "ADALAR");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==10 &&
             menu_swap==2)
           {
               sefer_no=11;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "BEYKOZ");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==11 &&
             menu_swap==2)
           {
               sefer_no=12;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAVAK");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==12 &&
             menu_swap==2)
           {
               sefer_no=13;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "BEYKOZ");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==13 &&
             menu_swap==2)
           {
               sefer_no=14;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "SARIYER");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==14 &&
             menu_swap==2)
           {
               sefer_no=15;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAD-BES");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==15 &&
             menu_swap==2)
           {
               sefer_no=16;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAD-BES");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==1 &&
             current_page2==16 &&
             menu_swap==2)
           {
               sefer_no=17;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAD-BES");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           
           if(current_page1==1 &&
             current_page2==17 &&
             menu_swap==2)
           {
               sefer_no=18;
               u8g.firstPage();  
               do {
               u8g.drawStr( 45, 15, "SEFER");
               u8g.drawStr( 35, 35, "KAD-BES");
               u8g.drawStr( 25, 55, "AYARLANDI");
               } 
               while( u8g.nextPage() );  
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }

           if(current_page1==4 &&
             current_page2==0 &&
             menu_swap==2)
           {
               u8g.firstPage();  
               do {
               //u8g.setFont(u8g_font_courB14);
               u8g.drawStr( 45, 15, "SIGARA");
               u8g.drawStr( 35, 35, "ANONSU");
               u8g.drawStr( 25, 55, "YAPILIYOR");
               } 
               while( u8g.nextPage() );  
               player.volume(volume); 
               player.play(10);
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
           if(current_page1==4 &&
             current_page2==1 &&
             menu_swap==2)
           {
               u8g.firstPage();  
               do {
               //u8g.setFont(u8g_font_courB14);
               u8g.drawStr( 45, 15, "TAHLIYE");
               u8g.drawStr( 35, 35, "ANONSU");
               u8g.drawStr( 25, 55, "YAPILIYOR");
               } 
               while( u8g.nextPage() );  
               player.volume(volume); 
               player.play(6);
               delay(3000);       
               button_sayac1=button_sayac1+2;        
           }
     //##############################  ANONSLAR  #######################################################

      //########### OTO ANONSLAR #################
      if(
         InorOut(Kadikoy_iskele,current_loc)==false &&
         InorOut(Besiktas_iskele,current_loc)==false &&
         InorOut(Uskudar_iskele,current_loc)==false &&
         InorOut(Kabatas_iskele,current_loc)==false ||
         anons_sayac>=2  
        )
         {
                             switch (sigara_anons_no) 
                             {
                               case 1:
                                   oto_anons_yap(300000);
                                   break;
                               case 2:
                                   oto_anons_yap(600000);
                                   break;
                               case 3:
                                   oto_anons_yap(900000);
                                   break;
                               case 4:
                                   oto_anons_yap(1200000);
                                   break;
                               case 5:
                                   oto_anons_yap(1800000);
                                   break;
                               case 6:
                                   oto_anons_yap(2700000);
                                   break;
                               case 7:
                                   oto_anons_yap(3600000);
                                   break;
                             }
          
          }
      
      
      //########### OTO ANONSLAR #################
    
    
    //##############################  OLED  #######################################################
    
 if(goruntu_sayac==0)
   {
   u8g.firstPage();  
   do {


    goruntu_sayac = 1;
   } while( u8g.nextPage() );
   
   
   }
   
 if(goruntu_sayac==1)
   {
   u8g.firstPage();  
   do {
    u8g.drawBitmapP( 0, 0, 16, 64, dentur_logo); 
    goruntu_sayac = 2;
   } while( u8g.nextPage() );
   delay(3000);
   }
   
        if (goruntu_sayac ==2)
        {  
        
        current_page2=0;
            
                 if(current_page1 ==0)      //ANAEKRAN
                 {  
                  
                  
                   
                      if(menu_swap==0)
                      {
                            u8g.firstPage();  
                            do {
                            int u = 0;
                            u8g.setFont(u8g_font_unifont);
                            u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            //u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            //u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            //u8g.drawLine(1,64-u,128,64-u);
                            }                 
                            while( u8g.nextPage() );
                       }             
                                                                                                  
                                if(menu_swap==1 || menu_swap==2)
                                {   


                                    
                                                  current_page1 = 0;
                                                  current_page2 = button_sayac2 % 5;
                                                  u8g.firstPage();  
                                                  do {
                                                      if(int(current_loc[0])==1000 && int(current_loc[1])==1000)
                                                      {
                                                      u8g.drawLine(1,5,128,5);
                                                      u8g.drawStr(25,22,"! DIKKAT !");
                                                     // u8g.setFont(u8g_font_courB14);
                                                      u8g.drawStr(kayan_yazi, 45, "SINYAL YOK SINYAL YOK ");
                                                      u8g.drawLine(1,53,128,53);
                                                      u8g.setFont(u8g_font_unifont);                                                      
                                                      }
                                                      else
                                                      {      
                                                             u8g.drawLine(1,13,128,13);
                                                             u8g.setPrintPos(1, 10);
                                                             u8g.print(hour+3);
                                                             u8g.setPrintPos(22, 10);
                                                             u8g.print(minute);
                                                             u8g.drawStr(16,10,":");
                                                             u8g.drawBitmapP( 105, 1, 1, 8, wifi_on);
                                                             u8g.setPrintPos(115,10);                                                            
                                                             u8g.print(gps.satellites());
                                                             u8g.drawBitmapP( 72, 1, 1, 8, ses_on);
                                                             u8g.setPrintPos(84,10);
                                                             u8g.print(volume);
                                                             u8g.setFont(u8g_font_unifont);
                                                             if(sefer_no==0)
                                                             {
                                                             u8g.drawStr(kayan_yazi,35,"Aktif Sefer Yok Aktif Sefer Yok ");           
                                                             }
                                                             if(sefer_no==1)
                                                             {
                                                             u8g.drawStr(kayan_yazi,35,"Secili Sefer: KADIKOY-BESIKTAS ");           
                                                             }
                                                             if(sefer_no==2)
                                                             {
                                                             u8g.drawStr(kayan_yazi,35,"Secili Sefer: USKUDAR-BESIKTAS ");           
                                                             }
                                                             if(sefer_no==3)
                                                             {
                                                             u8g.drawStr(kayan_yazi,35,"Secili Sefer: KADIKOY-KABATAS ");           
                                                             }
                                                             if(sefer_no==4)
                                                             {
                                                             u8g.drawStr(kayan_yazi,35,"Secili Sefer: USKUDAR-KABATAS ");           
                                                             }
                                                             if(sefer_no==5)
                                                             {
                                                             u8g.drawStr(kayan_yazi,35,"Secili Sefer: DENTUR-ADALAR ");           
                                                             }
                                                            

                                                              switch (sigara_anons_no) 
                                                              {
                                                              case 0:
                                                                 u8g.drawStr(kayan_yazi+80,55," Otomatik Anons Yok");
                                                                 break;
                                                              case 1:
                                                                 u8g.drawStr(kayan_yazi+80,55," 5 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              case 2:
                                                                 u8g.drawStr(kayan_yazi+80,55,"10 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              case 3:
                                                                 u8g.drawStr(kayan_yazi+80,55,"15 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              case 4:
                                                                 u8g.drawStr(kayan_yazi+80,55,"20 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              case 5:
                                                                 u8g.drawStr(kayan_yazi+80,55,"30 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              case 6:
                                                                 u8g.drawStr(kayan_yazi+80,55,"45 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              case 7:
                                                                 u8g.drawStr(kayan_yazi+80,55,"60 Dakikada Bir Sigara Anonsu");
                                                                 break;
                                                              }
                                                             
                                                                         
                                                     }                     
                                                  } while( u8g.nextPage() );  
                                    }                                       
                                }         
                 }

                  if(current_page1 ==1)      //SEFER SECİMİ
                 { 
                      if(menu_swap==0)
                      {
                            u8g.firstPage();  
                            do {
                            int u = 0;
                            //u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            //u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            //u8g.drawLine(1,64-u,128,64-u);
                            }                 
                            while( u8g.nextPage() );
                      }             
                                                                                                  
                                   if(menu_swap==1)
                                 {
                                     current_page1 = 1;
                                     current_page2 = button_sayac2 % 18;
    // KADIKÖY BESİKTAS                                  
                                         if(current_page2==0)  
                                        {
                                               u8g.firstPage();  
                                               do {
                                               int u = 0;
                                              
                                               u8g.drawLine(1,0-u,128,0-u);
                                               u8g.drawStr( 1, 13-u, "Kadikoy-Besiktas");
                                               u8g.drawLine(1,16-u,128,16-u);
                                               u8g.drawStr( 1, 29-u, "Uskudar-Besiktas");
                                               //u8g.drawLine(1,32-u,128,32-u);
                                               u8g.drawStr( 1, 45-u, "Kadikoy-Kabatas");
                                               //u8g.drawLine(1,48-u,128,48-u);
                                               u8g.drawStr( 1, 61-u, "Uskudar-Kabatas");
                                               //u8g.drawLine(1,64-u,128,64-u);
                                               }
                                               while( u8g.nextPage() );   
               
                                        }
      // USKUDAR-BESİKTAS                                    
                                         if(current_page2==1)
                                        {
                                               u8g.firstPage();  
                                               do {
                                               int u = 0;
                                              
                                               //u8g.drawLine(1,0-u,128,0-u);
                                               u8g.drawStr( 1, 13-u, "Kadikoy-Besiktas");
                                               u8g.drawLine(1,16-u,128,16-u);
                                               u8g.drawStr( 1, 29-u, "Uskudar-Besiktas");
                                               u8g.drawLine(1,32-u,128,32-u);
                                               u8g.drawStr( 1, 45-u, "Kadikoy-Kabatas");
                                               //u8g.drawLine(1,48-u,128,48-u);
                                               u8g.drawStr( 1, 61-u, "Uskudar-Kabatas");
                                               //u8g.drawLine(1,64-u,128,64-u);
                                               }
                                               while( u8g.nextPage() );  
                                                                                                              
                                        } 
       // KADIKOY-KABATAS 
                                          if(current_page2==2)
                                        {
                                               u8g.firstPage();  
                                               do {
                                               int u = 0;
                                               //u8g.drawLine(1,0-u,128,0-u);
                                               u8g.drawStr( 1, 13-0, "Kadikoy-Besiktas");
                                               //u8g.drawLine(1,16-u,128,16-u);
                                               u8g.drawStr( 1, 29-0, "Uskudar-Besiktas");
                                               u8g.drawLine(1,32-0,128,32-0);
                                               u8g.drawStr( 1, 45-0, "Kadikoy-Kabatas");
                                               u8g.drawLine(1,48-0,128,48-0);
                                               u8g.drawStr( 1, 61-0, "Uskudar-Kabatas");
                                               //u8g.drawLine(1,64-u,128,64-u);
                                               }
                                               while( u8g.nextPage() );  
                                                                                                             
                                        }
      // USKUDAR-KABATAS
                                          if(current_page2==3)
                                        {
                                               u8g.firstPage();  
                                               do {

                                              
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-14, "Kadikoy-Besiktas");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-14, "Uskudar-Besiktas");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-14, "Kadikoy-Kabatas");
                                                u8g.drawLine(1,48-14,128,48-14);
                                                u8g.drawStr( 1, 61-14, "Uskudar-Kabatas");
                                                u8g.drawLine(1,63-14,128,63-14);
                                                u8g.drawStr( 1, 76-14, "Dentur Adalar");
                                                //u8g.drawLine(1,77-u,128,77-u);
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
     //DENTUR ADALAR
                                            if(current_page2==4)
                                        {
                                               u8g.firstPage();  
                                               do {

                                                
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "Kadikoy-Besiktas");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "Uskudar-Besiktas");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "Kadikoy-Kabatas");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "Uskudar-Kabatas");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "Dentur Adalar");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "3 No. Hisar");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        } 
                                           if(current_page2==5)
                                        {
       //3no Hisar
                                               u8g.firstPage();  
                                               do {

                                               
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "Uskudar-Besiktas");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "Kadikoy-Kabatas");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "Uskudar-Kabatas");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "Dentur Adalar");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "3 No. Hisar");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "6 No. Ortabogaz");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                           if(current_page2==6)
                                        {
          //6no Ortabogaz                                 
                                               u8g.firstPage();  
                                               do {

                                               
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "Kadikoy-Kabatas");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "Uskudar-Kabatas");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "Dentur Adalar");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "3 No. Hisar");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "6 No. Ortabogaz");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "7 No. Kucuksu");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                           if(current_page2==7)
                                        {
           //7no Kucuksu                               
                                               u8g.firstPage();  
                                               do {

                                      
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr(1, 13-28, "Uskudar-Kabatas");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "Dentur Adalar");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "3 No. Hisar");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "6 No. Ortabogaz");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "7 No. Kucuksu");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "8 No. Sariyer");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                           if(current_page2==8)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {

                                               
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "Dentur Adalar");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "3 No. Hisar");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "6 No. Ortabogaz");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "7 No. Kucuksu");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "8 No. Sariyer");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "9 No. Beykoz");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                           if(current_page2==9)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {

                                              
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "3 No. Hisar");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "6 No. Ortabogaz");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "7 No. Kucuksu");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "8 No. Sariyer");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "9 No. Beykoz");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "14 No. Adalar");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==10)
                                        {
                                          
                                               
                                                u8g.firstPage();  
                                               do {

                                               
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "6 No. Ortabogaz");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "7 No. Kucuksu");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "8 No. Sariyer");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "9 No. Beykoz");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "14 No. Adalar");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "20 No. Beykoz");
                                                }
                                                while( u8g.nextPage() );  
                                                                               
                                        }
                                        if(current_page2==11)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                        
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "7 No. Kucuksu");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "8 No. Sariyer");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "9 No. Beykoz");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "14 No. Adalar");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "20 No. Beykoz");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "21 No. Kavak");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==12)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                                
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "8 No. Sariyer");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "9 No. Beykoz");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "14 No. Adalar");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "20 No. Beykoz");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "21 No. Kavak");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "23 No. Beykoz");
                                                
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==13)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                              
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "8 No. Sariyer");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "9 No. Beykoz");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "14 No. Adalar");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "20 No. Beykoz");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "21 No. Kavak");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "23 No. Beykoz");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==14)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                              
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "9 No. Beykoz");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "14 No. Adalar");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "20 No. Beykoz");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "21 No. Kavak");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "23 No. Beykoz");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "24 No. Sariyer");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==15)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                        
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "14 No. Adalar");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "20 No. Beykoz");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "21 No. Kavak");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "23 No. Beykoz");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "24 No. Sariyer");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "Avcılar-Adalar");
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==16)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                             
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "20 No. Beykoz");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "21 No. Kavak");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "23 No. Beykoz");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "24 No. Sariyer");
                                                u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "Avcilar-Adalar");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "Yalova-Adalar");
                                               
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        if(current_page2==17)
                                        {
                                          
                                               u8g.firstPage();  
                                               do {
                                                
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-28, "20 No. Beykoz");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-28, "21 No. Kavak");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-28, "23 No. Beykoz");
                                                //u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-28, "24 No. Sariyer");
                                                //u8g.drawLine(1,63-28,128,63-28);
                                                u8g.drawStr( 1, 76-28, "Avcilar-Adalar");
                                                u8g.drawLine(1,77-28,128,77-28);
                                                u8g.drawStr( 1, 91-28, "Yalova-Adalar");
                                                u8g.drawLine(1,91-28,128,91-28);
                                                }
                                                while( u8g.nextPage() );  
                                                                                                            
                                        }
                                        
                                        
                                 
                                              
                                  }
                  }

                    if(current_page1 ==2)      //SES AYARI
                 { 
                  
                      if(menu_swap==0)
                      {
                            u8g.firstPage();  
                            do {
                            int u = 14;
                     
                            //u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            //u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            //u8g.drawLine(1,64-u,128,64-u);
                            u8g.drawStr( 1, 76-u, "Anlik Anonslar");
                            //u8g.drawLine(1,80-u,128,80-u);
                            
                            }                 
                            while( u8g.nextPage() );
                      }           

                                             if(menu_swap==1 || menu_swap==2)
                                             { current_page1=2;
                                               current_page2 = button_sayac2 % 31;
                                               volume = current_page2;
                                               int volume_screen = current_page2*4;
                                                 u8g.firstPage();  
                                                 do {         
                                                 
                                                 u8g.drawStr( 26, 18, "SES AYARI");
                                                 u8g.drawStr(2,53,"0");
                                                 u8g.drawStr(108,53,"30");
                                                 u8g.setPrintPos(55, 53);
                                                 u8g.print(volume);
                                                 u8g.drawFrame(1,20,124,20); 
                                                 u8g.drawBox(3,23,volume_screen,14 );
                                                 }
                                                 while( u8g.nextPage() );
                        
                                             }
                 }
                   
                    if(current_page1 ==3)      //OTOMATİK ANONSLAR
                 { 
                    if(menu_swap==0)
                      {     current_page2 =0;
                            u8g.firstPage();  
                            do {
                            int u = 14;
                 
                            //u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            //u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            //u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            u8g.drawLine(1,63-u,128,63-u);
                            u8g.drawStr( 1, 76-u, "Anlik Anonslar");
                            //u8g.drawLine(1,77-u,128,77-u);
                            }                 
                            while( u8g.nextPage() );
                      }     

                                                             if(menu_swap==1)
                                                             {
                                                              current_page1 = 3;
                                                              current_page2 = button_sayac2 % 8;
                                                             u8g.firstPage();  
                                                             do {
                                                             u8g.drawStr( 10, 13, "SIGARA ANONSU");
                                                             u8g.drawLine(1,16,128,16);
                                                             u8g.drawBitmapP( 5, 20, 2, 16, yukari); 
                                                             u8g.drawBitmapP( 5, 50, 2, 16, asagi);
                                                                                 if(current_page2 ==0)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "Anons Yok");
                                                                                   sigara_anons_no=0;
                                                                                  }
                                                                                  if(current_page2 ==1)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "5  Dakikada Bir");
                                                                                   sigara_anons_no=1;
                                                                                  } 
                                                                                  if(current_page2 ==2)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "10 Dakikada Bir");
                                                                                   sigara_anons_no=2;
                                                                                  }
                                                                                  if(current_page2 ==3)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "15 Dakikada Bir");
                                                                                   sigara_anons_no=3;
                                                                                  }
                                                                                  if(current_page2 ==4)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "20 Dakikada Bir");
                                                                                   sigara_anons_no=4;
                                                                                  }
                                                                                  if(current_page2 ==5)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "30 Dakikada Bir");
                                                                                   sigara_anons_no=5;
                                                                                  }  
                                                                                  if(current_page2 ==6)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "45 Dakikada Bir");
                                                                                   sigara_anons_no=6;
                                                                                  }  
                                                                                  if(current_page2 ==7)
                                                                                 {
                                                                                   u8g.drawStr( 5, 48, "60 Dakikada Bir");
                                                                                   sigara_anons_no=7;
                                                                                  }         
                                                             
                                                             }                 
                                                             while( u8g.nextPage() );
                                                             }     
                  }


                  
                    if(current_page1 ==4)      //ANLIK ANONSLAR
                 { 
                   if(menu_swap==0)
                      {     current_page2=0;
                            u8g.firstPage();  
                            do {
                            int u = 14;
                            
                            //u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            //u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            //u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            //u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            u8g.drawLine(1,63-u,128,63-u);
                            u8g.drawStr( 1, 76-u, "Anlik Anonslar");
                            u8g.drawLine(1,77-u,128,77-u);
                            }                 
                            while( u8g.nextPage() );
                       }
                                  if(menu_swap==1)
                                  {  current_page1 = 4;
                                     current_page2 = button_sayac2 % 4;

                                       if (current_page2==0)
                                       {  
                                          u8g.firstPage();  
                                          do {
                                          int u = 0;
                                         
                                          u8g.drawLine(1,0-u,128,0-u);
                                          u8g.drawStr( 1, 13-u, "Sigara");
                                          u8g.drawLine(1,16-u,128,16-u);
                                          u8g.drawStr( 1, 29-u, "Yolcu Tahliye");
                                          //u8g.drawLine(1,32-u,128,32-u);
                                          u8g.drawStr( 1, 45-u, "Kayip Esya");
                                          //u8g.drawLine(1,48-u,128,48-u);
                                          }                 
                                          while( u8g.nextPage() );
                                        }
                                        if (current_page2==1)
                                       {  
                                          u8g.firstPage();  
                                          do {
                                          int u = 0;
                                         
                                          //u8g.drawLine(1,0-u,128,0-u);
                                          u8g.drawStr( 1, 13-u, "Sigara");
                                          u8g.drawLine(1,16-u,128,16-u);
                                          u8g.drawStr( 1, 29-u, "Yolcu Tahliye");
                                          u8g.drawLine(1,32-u,128,32-u);
                                          u8g.drawStr( 1, 45-u, "Kayip Esya");
                                          //u8g.drawLine(1,48-u,128,48-u);
                                          }                 
                                          while( u8g.nextPage() );
                                        }
                                        if (current_page2==2)
                                       {  
                                          u8g.firstPage();  
                                          do {
                                          int u = 0;
                                          
                                          //u8g.drawLine(1,0-u,128,0-u);
                                          u8g.drawStr( 1, 13-u, "Sigara");
                                          //u8g.drawLine(1,16-u,128,16-u);
                                          u8g.drawStr( 1, 29-u, "Yolcu Tahliye");
                                          u8g.drawLine(1,32-u,128,32-u);
                                          u8g.drawStr( 1, 45-u, "Kayip Esya");
                                          u8g.drawLine(1,48-u,128,48-u);
                                          }                 
                                          while( u8g.nextPage() );
                                        }
                                   }
                                         
                 }
         
  //##############################OLED######################################

  sefer_secimi(sefer_no);    
}
