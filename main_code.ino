##include "Arduino.h"
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
 */
TinyGPS gps;
SoftwareSerial ssgps(4, 3); //rx tx
SoftwareSerial ssplayer(10, 11); // RX, TX
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
DFRobotDFPlayerMini player;
  float flat, flon;
  int anons_sayac = 0;
  int ses_dosya;
  int button_sayac2 =0;
  int button_sayac1 =0;
  int current_page1 =0;
  int current_page2 =0;
  int menu_swap = 0;
  int sefer_no;
  int volume=16;
  float current_loc[2];
  int goruntu_sayac =1;
  long ekran_koruyucu;
  
 
 float Uskudar_iskele[]= {41.027217994892446, 29.01372839057748,41.02895214760056, 29.0161689187923};
 float Besiktas_iskele[]={41.03548691051261, 29.002465570306633,41.04208892352286, 29.009748793486658};  
 float Kabatas_iskele[]={41.03163795571091, 28.9910089244191,41.03854037283602, 28.999265559997532};  
 float Kadikoy_iskele[]={40.988788863418215, 29.01305777796483,40.995898991450574, 29.025116990081813};
 float Bizim_ev_konum[]={41.01320994453465, 29.02247559580991,41.01378517610856, 29.023098102779393};    
 float denemekonum_1 [] ={ 41.04095345646132, 29.008002022589267, 41.04142246629378, 29.008764837850528 };
 float denemekonum_2 [] ={ 41.04107877925389, 29.009353942705765 , 41.04181172292837, 29.01049187174237 };
 float sigarakonum_1 [] ={ 41.01731327139809, 28.995139641802037 , 41.02522248918977, 29.00730858292561 };
const uint8_t dentur_logo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x01, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x3f, 0xf8, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x1f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x01, 0xf0, 0xfc, 0xe3, 0x3f, 0xb9, 0xcf, 0xc0, 0x1f, 0x31, 0xcf, 0xc3, 0xf3, 0xf7, 0x78, 0xfc, 
  0x03, 0xf8, 0xe9, 0xe7, 0x1c, 0x73, 0xdd, 0xe0, 0x3e, 0x33, 0x9e, 0xc7, 0xf3, 0xf3, 0xf1, 0xfc, 
  0x07, 0x39, 0xf3, 0xee, 0x3c, 0xe7, 0x99, 0x80, 0x76, 0x37, 0x1d, 0xce, 0x67, 0xc3, 0xe1, 0x98, 
  0x0e, 0x33, 0xf3, 0xbc, 0x78, 0xef, 0x3f, 0x00, 0xfc, 0x3e, 0x3f, 0x9f, 0xe7, 0xe1, 0xc3, 0xf8, 
  0x1f, 0xf3, 0x87, 0x38, 0xf1, 0xde, 0x73, 0x01, 0xfc, 0x3c, 0x73, 0x9f, 0xe7, 0xe3, 0x87, 0x38, 
  0x1f, 0xe7, 0xee, 0x31, 0xe3, 0xf8, 0xe7, 0x03, 0x8c, 0x38, 0xe3, 0x38, 0xc7, 0xc7, 0x0e, 0x30, 
  0x3f, 0xc7, 0xfe, 0x31, 0xc3, 0xf1, 0xc7, 0x47, 0x0c, 0x30, 0xc3, 0x70, 0xcf, 0xce, 0x1c, 0x30, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
    
void setup()
   { 

  Serial.begin(9600);
  ssplayer.begin(9600);  
  if (!player.begin(ssplayer)) { 
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    } /*while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }  Serial.println(F("DFPlayer Mini online."));*/
  Serial.println(F("DFPlayer Mini online."));
  ssgps.begin(9600);
  player.volume(16); 
    
  
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
         Serial.println("kadikoydeyiz");}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         Serial.println("besiktasayız");}}  
         else
         {anons_sayac = 0;} 
    }
    
    if(sefer_nu ==2) // ÜSKÜDAR BESİKTAS NO. 2
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(2);
         Serial.println("uskudardayız");}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         Serial.println("besiktasayız");}}      
         else
         {anons_sayac = 0;}     
     }  
     if(sefer_nu ==3) // KADIKÖY KABATAŞ NO. 3
     {
         if(InorOut(Kadikoy_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(5);
         Serial.println("kadikoydeyiz");}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(4);
         Serial.println("kabatastayız");}}      
         else
         {anons_sayac = 0;}    
     } 
     if(sefer_nu ==4) // ÜSKÜDAR KABATAŞ NO. 3
     {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(3);
         Serial.println("uskudardayız");}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {if(anons_sayac < 2)
         {anons_yap(4);
         Serial.println("kabatastayız");}}      
         else
         {anons_sayac = 0;}    
     } 
  }  
    

 void loop()
 {
  
  //##############################  GPS  ##########################################################
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
   
    current_loc[0] = flat, 6;
    current_loc[1] = flon, 6;
  //##############################  GPS  ##########################################################

    Serial.print(current_loc[0],6);
    Serial.print(F(", "));
    Serial.print(current_loc[1],6);
    Serial.print((",   "));
    Serial.print(sefer_no);
    Serial.print((",   "));
    Serial.print(current_page1);
    Serial.print((",   "));
    Serial.print(current_page2);
    Serial.print((",   "));
    Serial.println(menu_swap);
    smartdelay(100);

   //##############################  SERİAL PORT  ##########################################################
   
    
   //#############################  BUTTON  ###################################################### 
    if(digitalRead(5)==HIGH)
    {  
    Serial.println("aaaaaaaaaaaaaaaaaaa");
    button_sayac1++;
    ekran_koruyucu = 0;
    delay(20);
    }

    if(digitalRead(6)==HIGH)
    {
    button_sayac2--;
    Serial.println("bbbbbbbbbbbbbbbbb");
    ekran_koruyucu = 0;
    }
    if(digitalRead(8)==HIGH)
    {
    button_sayac2++;
    //delay(50);
    Serial.println("ccccccccccccccccc");
    ekran_koruyucu = 0;
    }
    if(digitalRead(7)==HIGH)
    {
    //delay(50);
    button_sayac1--;
    Serial.println("eeeeeeeeeeeeeeeeee");
    ekran_koruyucu = 0;
    }
    
    
    menu_swap = button_sayac1 % 2;
    if(menu_swap==0)
    {
    current_page1 = button_sayac2 % 4;
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
    //#############################  BUTTON  ###################################################### 


    
    //##############################  OLED  ####################################################### 
    
    
 if(goruntu_sayac==0)
   {
   u8g.firstPage();  
   do {
    u8g.setFont(u8g_font_courB14);
    u8g.drawStr( 35, 25, "NESET");
    u8g.drawStr( 2, 43, "GIRITLIOGLU");
    goruntu_sayac = 1;
   } while( u8g.nextPage() );
   delay(3000);
   
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
                                                                                                  
                                    if(menu_swap==1)
                                    {
                                    current_page1 = 0;
                                    current_page2 = button_sayac2 % 5;
                                    u8g.firstPage();  
                                    do {         
                                    u8g.setFont(u8g_font_unifont);  
                                    u8g.drawStr( 1, 13, "Ana Ekran"); 
                                    u8g.setFont(u8g_font_unifont);  
                                    u8g.drawStr( 5, 23, "YAPILACAK");   
                                    }
                                    while( u8g.nextPage() );                                          
                                    }         
                 }

                  if(current_page1 ==1)      //SEFER SECİMİ
                 { 
                      if(menu_swap==0)
                      {
                            u8g.firstPage();  
                            do {
                            int u = 0;
                            u8g.setFont(u8g_font_unifont);
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
                                     current_page2 = button_sayac2 % 5;
    // KADIKÖY BESİKTAS                                  
                                         if(current_page2==0)  
                                        {
                                               u8g.firstPage();  
                                               do {
                                               int u = 0;
                                               u8g.setFont(u8g_font_unifont);
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
                                                                          if(digitalRead(5)==HIGH)
                                                                          {
                                                                             sefer_no=1;
                                                                             u8g.firstPage();  
                                                                             do {
                                                                             u8g.setFont(u8g_font_courB14);
                                                                             u8g.drawStr( 33, 25, "SEFER");
                                                                             u8g.drawStr( 24, 43, "KAD-BES");
                                                                             } 
                                                                             while( u8g.nextPage() );  
                                                                             delay(3000);
                                                                          }
                                                                                  
                                        }
      // USKUDAR-BESİKTAS                                    
                                         if(current_page2==1)
                                        {
                                               u8g.firstPage();  
                                               do {
                                               int u = 0;
                                               u8g.setFont(u8g_font_unifont);
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
                                                                           if(digitalRead(5)==HIGH)
                                                                          {
                                                                            sefer_no=2;
                                                                            u8g.firstPage();  
                                                                             do {
                                                                             u8g.setFont(u8g_font_courB14);
                                                                             u8g.drawStr( 33, 25, "SEFER");
                                                                             u8g.drawStr( 24, 43, "USK-BES");
                                                                             } 
                                                                             while( u8g.nextPage() );  
                                                                             delay(3000);  
                                                                          }                                    
                                        } 
       // KADIKOY-KABATAS 
                                          if(current_page2==2)
                                        {
                                               u8g.firstPage();  
                                               do {
                                               int u = 0;
                                               u8g.setFont(u8g_font_unifont);
                                               //u8g.drawLine(1,0-u,128,0-u);
                                               u8g.drawStr( 1, 13-u, "Kadikoy-Besiktas");
                                               //u8g.drawLine(1,16-u,128,16-u);
                                               u8g.drawStr( 1, 29-u, "Uskudar-Besiktas");
                                               u8g.drawLine(1,32-u,128,32-u);
                                               u8g.drawStr( 1, 45-u, "Kadikoy-Kabatas");
                                               u8g.drawLine(1,48-u,128,48-u);
                                               u8g.drawStr( 1, 61-u, "Uskudar-Kabatas");
                                               //u8g.drawLine(1,64-u,128,64-u);
                                               }
                                               while( u8g.nextPage() );  
                                                                           if(digitalRead(5)==HIGH)
                                                                          {
                                                                            sefer_no=3;
                                                                            u8g.firstPage();  
                                                                             do {
                                                                             u8g.setFont(u8g_font_courB14);
                                                                             u8g.drawStr( 33, 25, "SEFER");
                                                                             u8g.drawStr( 24, 43, "KAD-KAB");
                                                                             } 
                                                                             while( u8g.nextPage() );  
                                                                             delay(3000);    
                                                                          }                                    
                                        }
      // USKUDAR-KABATAS
                                          if(current_page2==3)
                                        {
                                               u8g.firstPage();  
                                               do {
                                                int u = 14;
                                                u8g.setFont(u8g_font_unifont);
                                                //u8g.drawLine(1,0-u,128,0-u);
                                                u8g.drawStr( 1, 13-u, "Kadikoy-Besiktas");
                                                //u8g.drawLine(1,16-u,128,16-u);
                                                u8g.drawStr( 1, 29-u, "Uskudar-Besiktas");
                                                //u8g.drawLine(1,32-u,128,32-u);
                                                u8g.drawStr( 1, 45-u, "Kadikoy-Kabatas");
                                                u8g.drawLine(1,48-u,128,48-u);
                                                u8g.drawStr( 1, 61-u, "Uskudar-Kabatas");
                                                u8g.drawLine(1,64-u,128,64-u);
                                                }
                                                while( u8g.nextPage() );  
                                                                           if(digitalRead(5)==HIGH)
                                                                          {
                                                                            sefer_no=4;
                                                                            u8g.firstPage();  
                                                                             do {
                                                                             u8g.setFont(u8g_font_courB14);
                                                                             u8g.drawStr( 33, 25, "SEFER");
                                                                             u8g.drawStr( 24, 43, "USK-KAB");
                                                                             } 
                                                                             while( u8g.nextPage() );  
                                                                             delay(3000);      
                                                                          }                                    
                                        } 
                                              
                                  }
                  }

                    if(current_page1 ==2)      //SES AYARI
                 { 
                  
                      if(menu_swap==0)
                      {
                            u8g.firstPage();  
                            do {
                            int u = 0;
                            u8g.setFont(u8g_font_unifont);
                            //u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            //u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            //u8g.drawLine(1,64-u,128,64-u);
                            }                 
                            while( u8g.nextPage() );
                      }           

                                             if(menu_swap==1)
                                             {
                        
                        
                                             }
                 }
                   
                    if(current_page1 ==3)      //OTOMATİK ANONSLAR
                 { 
                    if(menu_swap==0)
                      {
                            u8g.firstPage();  
                            do {
                            int u = 0;
                            u8g.setFont(u8g_font_unifont);
                            //u8g.drawLine(1,0-u,128,0-u);
                            u8g.drawStr( 1, 13-u, "Ana Ekran");
                            //u8g.drawLine(1,16-u,128,16-u);
                            u8g.drawStr( 1, 29-u, "Sefer Secimi");
                            //u8g.drawLine(1,32-u,128,32-u);
                            u8g.drawStr( 1, 45-u, "Ses Ayari");
                            u8g.drawLine(1,48-u,128,48-u);
                            u8g.drawStr( 1, 61-u, "OtomatikAnonslar");
                            u8g.drawLine(1,63-u,128,63-u);
                            }                 
                            while( u8g.nextPage() );
                      }           
                  }
            
        }
 
  
  //##############################OLED######################################

  sefer_secimi(sefer_no);    
}
