#include "Arduino.h"
#include "TinyGPS.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SPI.h>
#include <TFT_ST7735.h>
#include "_fonts/orbitron14.c"
#include "_icons/sesduzey.c"
#include "_icons/smoke.c"

#define BLACK   0x0000
#define RED     0x001F
#define BLUE    0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF
/*
 SES DOSYALARI
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
SoftwareSerial ssplayer(3, 2); // RX, TX
DFRobotDFPlayerMini player;
TFT_ST7735 tft = TFT_ST7735(10,8,9);


  float flat, flon;
  uint8_t anons_sayac ;
  uint8_t ses_dosya;
  uint8_t button_sayac3;
  uint8_t button_sayac2 =0;
  uint8_t button_sayac1 =1;
  uint8_t current_page1 =0;
  uint8_t current_page2 =0;
  uint8_t menu_swap = 1;
  uint8_t sefer_no=0;
  uint8_t sigara_anons_no=0 ; 
  uint8_t volume=25;
  float current_loc[2];
  uint8_t sigara_anons_freq;
  uint8_t ekran_koruyucu;
  unsigned long timer1=5000;
  uint8_t ok_durum;   
 
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



    
   void setup()
    { 
   Serial.begin(9600);
   ssplayer.begin(9600);   
   ssgps.begin(9600);
   tft.begin();
   tft.setRotation(2);
   tft.clearScreen();
   tft.setFont(&orbitron14);
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
     //Serial.println(anons_sayac);
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
     //Serial.println("SİGARA ANONSU YAPLIYOR");
     }
   }

   int sefer_kayit()
   {   
    tft.clearScreen();
    tft.drawLine(0,60,130,60,0xF400);
    tft.drawLine(0,61,130,61,0xF400);
    tft.drawLine(0,120,130,120,0xF400);
    tft.drawLine(0,121,130,121,0xF400);
    tft.setTextColor(0xFFFF);
    tft.setCursor(35,70);
    tft.print(F("SEFER"));
    tft.setCursor(30,90);
    tft.print(F("SECILDI"));
    delay(3000);
    tft.clearScreen();
    tft.setTextColor(0xFFFF);    
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
         }}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         }}  
         else
         {anons_sayac = 0;} 
    }
    
    if(sefer_nu ==2) // ÜSKÜDAR BESİKTAS NO. 2
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(2);
         }}            
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
         }}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(3);
         }}      
         else
         {anons_sayac = 0;}    
     } 
     if(sefer_nu ==4) // ÜSKÜDAR KABATAŞ NO. 4
     {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(2);
         }}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(3);
         }}      
         else
         {anons_sayac = 0;}    
     } 
      if(sefer_nu ==5) // ADALAR NO. 5
    {
         if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         }}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(3);
         }}
         else if(InorOut(Eminonu_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(5);
         }}
         else if(InorOut(Burgazada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(6);
         }}
         else if(InorOut(Kinaliada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(7);
         }}
         else if(InorOut(Heybeliada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(8);
         }}
         else if(InorOut(Buyukada_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(9);
         }}
         else if(InorOut(Kadikoy_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(4);
         }}  
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
    
    Serial.print(current_loc[0],6);
    Serial.print(F(", "));
    Serial.println(current_loc[1],6);
   /*  Serial.print(F(",   "));
    Serial.print(F(sefer_no));
    Serial.print(F(",   "));
    Serial.print(current_page1);
    Serial.print(",   ");
    Serial.print(current_page2);
    Serial.print(",   ");
    Serial.print(menu_swap);
    Serial.print(",   "); 
    Serial.println(volume);*/
   
   //##############################  SERİAL PORT  ##########################################################
    
   //#############################  BUTTON  ###################################################### 
    //ORTA TUS  A5
    if(analogRead(A6)==LOW) 
    {  
    button_sayac1++;
    ekran_koruyucu = millis();
    tft.clearScreen();
    }

    if(analogRead(A2)==LOW)
    {
    button_sayac2++;
    ekran_koruyucu=millis();
       if(current_page1==1&&menu_swap==1)
       {tft.clearScreen();}

    }
    if(analogRead(A4)==LOW)
    {
    button_sayac2--;
    ekran_koruyucu=millis();
       if(current_page1==1&&menu_swap==1)
       {tft.clearScreen();}
    }
    if(analogRead(A3)==LOW)
    { 
    button_sayac1--;
    ekran_koruyucu=millis();
    tft.clearScreen();
    }
    if(analogRead(A5)==LOW)
    {
    button_sayac3++;  
      }
    
    static unsigned long ekran_koruyucu = millis(); 
    if (millis() - ekran_koruyucu > 300000) 
     {
     button_sayac1++; 
     current_page1=0;
     menu_swap=1;
     //tft.clearScreen();
      if(analogRead(A2)==LOW||
         analogRead(A3)==LOW||
         analogRead(A4)==LOW||
         analogRead(A5)==LOW||
         analogRead(A6)==LOW)
       {ekran_koruyucu=millis();}
     }
     
     else
     {
    menu_swap = button_sayac1 % 2;
    
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
    ok_durum= button_sayac3%2;
  
    //#############################  BUTTON  ###################################################### 
    timer1=millis()%15000;
         
   
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
                                   sigara_anons_freq = 5;
                                   break;
                               case 2:
                                   oto_anons_yap(600000);
                                   sigara_anons_freq = 10;
                                   break;
                               case 3:
                                   oto_anons_yap(900000);
                                   sigara_anons_freq = 15;
                                   break;
                               case 4:
                                   oto_anons_yap(1200000);
                                   sigara_anons_freq = 20;
                                   break;
                               case 5:
                                   oto_anons_yap(1800000);
                                   sigara_anons_freq = 30;
                                   break;                              
                               case 6:
                                   oto_anons_yap(3600000);
                                   sigara_anons_freq = 60;
                                   break;
                             }
          
          }
      
      
      //########### OTO ANONSLAR #################
    
    
    //##############################  OLED  #######################################################

   
    
     switch (current_page1) 
     {
     
     
         
 
 
            
                 case 0:
                      
                   
                      if(menu_swap==0)
                      {    
                           timer1=5000;
                           tft.setCursor(22,32);
                           tft.setTextColor(0xFFFF);
                           tft.print(F("Ana Menu"));
                           tft.drawLine(0,50,130,50,0xF400);
                           tft.setCursor(5,50);
                           tft.setTextColor(0xF800);
                           tft.print(F("Bilgi Ekrani"));
                           tft.setCursor(5,65);
                           tft.setTextColor(0xFFFF);
                           tft.print(F("Sefer Secimi")); 
                           tft.setCursor(5,80);
                           tft.print(F("Ses Ayari")); 
                           tft.setCursor(5,97);
                           tft.print(F("Oto Anons")); 
                           tft.setCursor(5,114);                           
                           tft.print(F("Tek Anons"));
                           
                       }             
                                                                                                  
                                if(menu_swap==1)
                                {     
                                      if (analogRead(A2==LOW)&&
                                          analogRead(A3== LOW))
                                          {timer1=timer1+4500;}
                                        
                                      if((timer1)%5000<250){
                                        tft.clearScreen();
                                        tft.drawLine(0,50,130,50,0xF400);
                                        tft.drawLine(0,51,130,51,0xF400);
                                        tft.drawLine(0,140,130,140,0xF400);
                                        tft.drawLine(0,139,130,139,0xF400);}
                                      if((timer1)%15000<250){
                                        tft.drawIcon(30, 55, &sesduzey, 1, 0xFFFF, BLACK,true);
                                        tft.setCursor(6,113);
                                        tft.setTextColor(0xFFFF);
                                        tft.print(F("Ses Duzeyi"));
                                        tft.setCursor(100,113);
                                        tft.print(volume);
                                        
                                        }
                                      if ((timer1+10000)%15000<250)
                                      {
                                        tft.setCursor(19,55);
                                        tft.setTextColor(0xFFFF);
                                        tft.print(F("Secili Sefer"));
                                        tft.setCursor(30,75); 
                                        tft.setCursor(13,109);
                                                      if(int(current_loc[0])==1000 && int(current_loc[1])==1000)
                                                      {tft.setTextColor(0x001F);
                                                      tft.print(F("SINYAL YOK"));}
                                                      //sinyal yok
                                                      if(int(current_loc[0])!=1000 && int(current_loc[1])!=1000)
                                                      {tft.setTextColor(0x07E0);
                                                      tft.print(F("SINYAL VAR"));}
                                                                     
                                        
                                        tft.setTextColor(0xFFFF);                                                   
                                        switch (sefer_no) 
                                        {
                                         case 0:
                                         tft.setCursor(33,75);
                                         tft.print(F("SEFER"));
                                         tft.setCursor(18,90);
                                         tft.print(F("SECILMEDI"));
                                             break;
                                         case 1:
                                         tft.setCursor(28,75);
                                         tft.print(F("KADIKOY"));
                                         tft.setCursor(20,90);
                                         tft.print(F("BESIKTAS"));
                                             break;
                                             
                                         case 2:
                                         tft.setCursor(23,75);
                                         tft.print(F("USKUDAR"));
                                         tft.setCursor(23,90);
                                         tft.print(F("BESIKTAS"));
                                              break;
                                              
                                         case 3:
                                         tft.setCursor(27,75);
                                         tft.print(F("KADIKOY"));
                                         tft.setCursor(22,90);
                                         tft.print(F("KABATAS"));
                                              break;
                                         
                                         case 4:
                                         tft.setCursor(23,75);
                                         tft.print(F("USKUDAR"));
                                         tft.setCursor(23,90);
                                         tft.print(F("KABATAS"));                                               
                                              break;    
                                         case 5:
                                         tft.setCursor(29,75);
                                         tft.print(F("DENTUR"));
                                         tft.setCursor(28,90);
                                         tft.print(F("ADALAR"));
                                               break;                                                                       
                                         case 6:
                                         tft.setCursor(0,75);
                                         tft.print(F("SEHIRHATLARI"));
                                         tft.setCursor(28,90);
                                         tft.print(F("ADALAR"));
                                               break;
                                         case 7:
                                         tft.setCursor(19,75);
                                         tft.print(F("3 NUMARA"));
                                         tft.setCursor(38,90);
                                         tft.print(F("HISAR"));
                                               break;
                                         case 8:
                                         tft.setCursor(19,75);
                                         tft.print(F("6 NUMARA"));
                                         tft.setCursor(10,90);
                                         tft.print(F("ORTABOGAZ"));
                                               break;
                                         case 9:
                                         tft.setCursor(19,75);
                                         tft.print(F("7 NUMARA"));
                                         tft.setCursor(23,90);
                                         tft.print(F("KUCUKSU"));
                                               break;
                                         case 10:
                                         tft.setCursor(19,75);
                                         tft.print(F("8 NUMARA"));
                                         tft.setCursor(25,90);
                                         tft.print(F("SARIYER"));
                                               break;
                                         case 11:
                                         tft.setCursor(19,75);
                                         tft.print(F("9 NUMARA"));
                                         tft.setCursor(29,90);
                                         tft.print(F("BEYKOZ"));
                                               break;
                                         case 12:
                                         tft.setCursor(16,75);
                                         tft.print(F("14 NUMARA"));
                                         tft.setCursor(29,90);
                                         tft.print(F("ADALAR"));
                                               break;
                                         case 13:
                                         tft.setCursor(14,75);
                                         tft.print(F("20 NUMARA"));
                                         tft.setCursor(29,90);
                                         tft.print(F("BEYKOZ"));
                                               break;
                                         case 14:
                                         tft.setCursor(15,75);
                                         tft.print(F("21 NUMARA"));
                                         tft.setCursor(32,90);
                                         tft.print(F("KAVAK"));
                                               break;
                                         case 15:
                                         tft.setCursor(14,75);
                                         tft.print(F("23 NUMARA"));
                                         tft.setCursor(29,90);
                                         tft.print(F("BEYKOZ"));
                                               break;
                                         case 16:
                                         tft.setCursor(14,75);
                                         tft.print(F("24 NUMARA"));
                                         tft.setCursor(25,90);
                                         tft.print(F("SARIYER"));
                                               break;
                                         case 17:
                                         tft.setCursor(25,75);
                                         tft.print(F("YALOVA"));
                                         tft.setCursor(27,90);
                                         tft.print(F("ADALAR"));
                                               break;
                                         case 18:
                                         tft.setCursor(24,75);
                                         tft.print(F("AVCILAR"));
                                         tft.setCursor(28,90);
                                         tft.print(F("ADALAR"));
                                               break;
                                         case 19:
                                         tft.setCursor(28,75);
                                         tft.print(F("HOP ON"));
                                         tft.setCursor(24,90);
                                         tft.print(F("HOP OFF"));
                                               break;      
                                                  
                                        }
                                        }
                                        if ((timer1+5000)%15000<250)
                                       {  
                                         tft.drawIcon(30, 55, &smoke, 1, 0xFFFF, BLACK,true);
                                         tft.setCursor(8,113);
                                         tft.setTextColor(0xFFFF);
                                         tft.print("Sigara");
                                         tft.setCursor(63,113);
                                         tft.print(sigara_anons_freq);
                                         tft.setCursor(88,113);
                                         tft.print("dak.");
                                        
                                       }
                                       
                                      
                                                  
                                                                         
                                                  
                                    }                                       
                    break;         
                 

                 case 1:
                      if(menu_swap==0)
                      {
                           tft.setCursor(22,32);
                           tft.setTextColor(0xFFFF);
                           tft.print("Ana Menu");
                           tft.drawLine(0,50,130,50,0xF400);
                            tft.setCursor(5,50);
                           tft.print("Bilgi Ekrani");
                           tft.setCursor(5,65);
                           tft.setTextColor(0xF800);
                           tft.print("Sefer Secimi"); 
                           tft.setCursor(5,80);
                           tft.setTextColor(0xFFFF);;
                           tft.print("Ses Ayari"); 
                           tft.setCursor(5,97);
                           tft.print("Oto Anons"); 
                           tft.setCursor(5,114);                           
                           tft.print("Tek Anons"); 
                      }             
                                                                                                  
                                   if(menu_swap==1)
                                 {
                                                                   
                                     current_page1 = 1;
                                     current_page2 = button_sayac2 % 19;
                                     tft.fillTriangle(60,40,30,50,90,50,0xF400);
                                     tft.fillTriangle(60,150,30,140,90,140,0xF400);


                                      switch (current_page2) 
                                        {
                                         case 0:
                                         tft.setCursor(30,70);
                                         tft.print("Kadikoy");
                                         tft.setCursor(27,85);
                                         tft.print("Besiktas");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=1;
                                          sefer_kayit();}  
                                             break;
                                         case 1:
                                         tft.setCursor(30,70);
                                         tft.print("Uskudar");
                                         tft.setCursor(28,85);
                                         tft.print("Besiktas");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=2;
                                          sefer_kayit();}  
                                             break;
                                             
                                         case 2:
                                         tft.setCursor(30,70);
                                         tft.print("Kadikoy");
                                         tft.setCursor(28,85);
                                         tft.print("Kabatas");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=3;
                                           sefer_kayit();} 
                                              break;
                                              
                                         case 3:
                                         tft.setCursor(28,70);
                                         tft.print("Uskudar");
                                         tft.setCursor(28,85);
                                         tft.print("Kabatas");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=4;
                                          sefer_kayit();}  
                                              break;
                                         
                                         case 4:
                                         tft.setCursor(32,70);
                                         tft.print("Dentur");
                                         tft.setCursor(33,85);
                                         tft.print("Adalar");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=5;
                                          sefer_kayit();}  
                                               break;
                                         
                                         case 5:
                                         tft.setCursor(15,70);
                                         tft.print("SehirHatlari");
                                         tft.setCursor(35,85);
                                         tft.print("Adalar");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=6;
                                          sefer_kayit();}  
                                               break;                              
                                         
                                         case 6:
                                         tft.setCursor(24,70);
                                         tft.print("3 Numara");
                                         tft.setCursor(37,85);
                                         tft.print("Hisar");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=7;
                                          sefer_kayit();}  
                                               break;
                                         case 7:
                                         tft.setCursor(24,70);
                                         tft.print("6 Numara");
                                         tft.setCursor(22,85);
                                         tft.print("Ortabogaz");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=8;
                                          sefer_kayit();}  
                                               break;
                                         case 8:
                                         tft.setCursor(24,70);
                                         tft.print("7 Numara");
                                         tft.setCursor(28,85);
                                         tft.print("Kucuksu");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=9;
                                          sefer_kayit();}  
                                               break;
                                         case 9:
                                         tft.setCursor(24,70);
                                         tft.print("8 Numara");
                                         tft.setCursor(31,85);
                                         tft.print("Sariyer");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=10;
                                          sefer_kayit();}  
                                               break;
                                         case 10:
                                         tft.setCursor(24,70);
                                         tft.print("9 Numara ");
                                         tft.setCursor(31,85);
                                         tft.print("Beykoz");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=11;
                                          sefer_kayit();}  
                                               break;
                                         case 11:
                                         tft.setCursor(22,70);
                                         tft.print("14 Numara");
                                         tft.setCursor(33,85);
                                         tft.print("Adalar");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=12;
                                          sefer_kayit();}  
                                               break;
                                         case 12:
                                         tft.setCursor(22,70);
                                         tft.print("20 Numara");
                                         tft.setCursor(33,85);
                                         tft.print("Beykoz");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=13;
                                          sefer_kayit();}  
                                               break;
                                         case 13:
                                         tft.setCursor(22,70);
                                         tft.print("21 Numara");
                                         tft.setCursor(35,85);
                                         tft.print("Kavak");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=14;
                                          sefer_kayit();}  
                                               break;
                                         case 14:
                                         tft.setCursor(22,70);
                                         tft.print("23 Numara");
                                         tft.setCursor(33,85);
                                         tft.print("Beykoz");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=15;
                                          sefer_kayit();}  
                                               break;
                                         case 15:
                                         tft.setCursor(22,70);
                                         tft.print("24 Numara");
                                         tft.setCursor(31,85);
                                         tft.print("Sariyer");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=16;
                                          sefer_kayit();}  
                                               break;

                                         case 16:
                                         tft.setCursor(33,70);
                                         tft.print("Avcilar");
                                         tft.setCursor(34,85);
                                         tft.print("Adalar");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=17;
                                          sefer_kayit();}  
                                               break;
                                         case 17:
                                         tft.setCursor(33,70);
                                         tft.print("Yalova");
                                         tft.setCursor(34,85);
                                         tft.print("Adalar");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=18;
                                          sefer_kayit();}  
                                               break;
                                         case 18:
                                         tft.setCursor(9,70);
                                         tft.print("HopOnHopOff");
                                         tft.setCursor(18,85);
                                         tft.print("BogazTuru");
                                         if(analogRead(A5)==LOW)
                                          {sefer_no=19;
                                          sefer_kayit();}  
                                               break;
                                        }
                                    
                                        
                                 
                                              
                                  }
                   break;

                 case 2:
                  
                      if(menu_swap==0)
                      {     
                           tft.setCursor(22,32);
                           tft.setTextColor(0xFFFF);
                           tft.print("Ana Menu");
                           tft.drawLine(0,50,130,50,0xF400);
                           tft.setCursor(5,50);
                           tft.setTextColor(0xFFFF);
                           tft.print("Bilgi Ekrani");
                           tft.setCursor(5,65);
                           tft.print("Sefer Secimi"); 
                           tft.setCursor(5,80);
                           tft.setTextColor(0xF800);;
                           tft.print("Ses Ayari"); 
                           tft.setCursor(5,97);
                           tft.setTextColor(0xFFFF);
                           tft.print("Oto Anons"); 
                           tft.setCursor(5,114);                         
                           tft.print("Tek Anons"); 
                      }           

                                             if(menu_swap==1)
                                             {  
                                               
                                               current_page1=2;
                                               current_page2 = abs((button_sayac2 % 31)-30);
                                               volume = current_page2;
                                               int volume_g = current_page2*3.5;
                                               tft.setCursor(17,32);
                                               tft.setTextColor(0xFFFF);
                                               tft.print("Ses Duzeyi");
                                               tft.drawLine(0,50,130,50,0xF400); 
                                               tft.drawRect(10,60,110,20,0xFFFF);
                                               tft.drawRect(11,61,108,18,0xFFFF);
                                               tft.fillRect(12,62,volume_g,16,0xF100);
                                               tft.fillRect(12+volume_g,62,106-volume_g,16,0x0000);
                                               if(analogRead(A2)==LOW){tft.fillTriangle(33,125,13,105,53,105,0xF100);}
                                               else{tft.fillTriangle(33,125,13,105,53,105,0xFFFF);}
                                               if(analogRead(A4)==LOW){tft.fillTriangle(93,105,73,125,113,125,0xF100);}
                                               else{tft.fillTriangle(93,105,73,125,113,125,0xFFFF);}
                                               tft.setCursor(6,80);
                                               tft.setTextColor(0xFFFF);
                                               tft.print("0-5-15-25-30");
                                             
                                                } 
                  break;
                
                   
                 case 3:
                    if(menu_swap==0)
                      {     current_page2 =0;
                           tft.setCursor(22,32);
                           tft.setTextColor(0xFFFF);
                           tft.print("Ana Menu");
                           tft.drawLine(0,50,130,50,0xF400);
                           tft.setCursor(5,50);
                           tft.print("Bilgi Ekrani");
                           tft.setCursor(5,65);
                           tft.print("Sefer Secimi"); 
                           tft.setCursor(5,80);
                           tft.print("Ses Ayari"); 
                           tft.setCursor(5,97);
                           tft.setTextColor(0xF800);
                           tft.print("Oto Anons"); 
                           tft.setCursor(5,114);
                           tft.setTextColor(0xFFFF);                           
                           tft.print("Tek Anons");
                      }     

                                                             if(menu_swap==1)
                                                             {
                                                              current_page1 = 3;
                                                              current_page2 = button_sayac2 % 6;
                                                             tft.setCursor(3,32);
                                                             tft.setTextColor(0xFFFF);
                                                             tft.print("Sigara Anonsu");
                                                             tft.drawLine(0,50,130,50,0xF400);
                                                             tft.setCursor(5,50);
                                                             tft.setTextColor(0xFFFF);
                                                             tft.print("Hangi Siklikta?");
                                                             tft.setCursor(5,65);
                                                             if(current_page2==0){tft.setTextColor(0xF800);
                                                             sigara_anons_no=1;}
                                                             //else if (sigara_anons_no==1){tft.setTextColor(0x001F);}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("5   dakika"); 
                                                             tft.setCursor(5,80);
                                                             if(current_page2==1){tft.setTextColor(0xF800);
                                                             sigara_anons_no=2;}
                                                             //else if (sigara_anons_no==2){tft.setTextColor(0x001F);}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("10   dakika");
                                                             tft.setCursor(5,95);
                                                             if(current_page2==2){tft.setTextColor(0xF800);
                                                             sigara_anons_no=3;}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("15  dakika"); 
                                                             tft.setCursor(5,110);
                                                             if(current_page2==3){tft.setTextColor(0xF800);
                                                             sigara_anons_no=4;}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("20  dakika"); 
                                                             tft.setCursor(5,125);
                                                             if(current_page2==4){tft.setTextColor(0xF800);
                                                             sigara_anons_no=5;}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("30 dakika"); 
                                                             tft.setCursor(5,140);
                                                             if(current_page2==5){tft.setTextColor(0xF800);
                                                             sigara_anons_no=6;}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("60  dakika");  
                                                              
                                                             }                                                                              
                 break;     
                  


                  
                case 4:
                   if(menu_swap==0)
                      {    
                        current_page2=0;
                           tft.setCursor(22,32);
                           tft.setTextColor(0xFFFF);
                           tft.print("Ana Menu");
                           tft.drawLine(0,50,130,50,0xF400);
                           tft.setCursor(5,50);
                           tft.print("Bilgi Ekrani");
                           tft.setCursor(5,65);
                           tft.print("Sefer Secimi"); 
                           tft.setCursor(5,80);
                           tft.print("Ses Ayari"); 
                           tft.setCursor(5,97);
                           tft.print("Oto Anons"); 
                           tft.setCursor(5,114);
                           tft.setTextColor(0xF800);                           
                           tft.print("Tek Anons");  
                       }
                                  if(menu_swap==1)
                                  {  current_page1 = 4;
                                     current_page2 = button_sayac2 % 4;

                                                             tft.setCursor(9,32);
                                                             tft.setTextColor(0xFFFF);
                                                             tft.print("Tek Anonslar");
                                                             tft.drawLine(0,50,130,50,0xF400);
                                                             tft.setCursor(5,50);
                                                             if(current_page2==0){tft.setTextColor(0xF800);
                                                             if(analogRead(A5)==LOW){tft.setTextColor(0x001F);}}
                                                             else{tft.setTextColor(0xFFFF);}      
                                                             tft.print("Sigara ");
                                                             tft.setCursor(5,65);
                                                             if(current_page2==1){tft.setTextColor(0xF800);
                                                             if(analogRead(A5)==LOW){tft.setTextColor(0x001F);}}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("Yolcu Tahliye"); 
                                                             tft.setCursor(5,80);
                                                             if(current_page2==2){tft.setTextColor(0xF800);
                                                             if(analogRead(A5)==LOW){tft.setTextColor(0x001F);}}
                                                             else{tft.setTextColor(0xFFFF);}
                                                             tft.print("Kayip Esya"); 
                                   }
                                         
                 break;
         }
  //##############################OLED######################################

  sefer_secimi(sefer_no);    
}
