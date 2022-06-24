#include "Arduino.h"
#include "TinyGPS.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "U8glib.h"

 
TinyGPS gps;
SoftwareSerial ssgps(4, 3); //rx tx
SoftwareSerial ssplayer(10, 11); // RX, TX
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);
DFRobotDFPlayerMini player;
  float flat, flon;
  int anons_sayac = 0;
  int ses_dosya;
  int button1 =0;
  int current_page =0;
  float Current_loc[2];
 
 float Uskudar_iskele[]= {41.027217994892446, 29.01372839057748,41.02895214760056, 29.0161689187923};
 float Besiktas_iskele[]={41.03866509266325, 29.00607231973659,41.04208892352286, 29.009748793486658};  
 float Kabatas_iskele[]={41.03215613616468, 28.993632499629786,41.03576978184062, 28.995824806783194};  
 float Kadikoy_iskele[]={40.99012455461286, 29.01862938022462,40.994610897993184, 29.02165491211252};
 float Bizim_ev_konum[]={41.01320994453465, 29.02247559580991,41.01378517610856, 29.023098102779393};    

 /*  ANONS NUMARALANDIRMASI 
      uskudar iskele  -- 1
      besiktas iskele -- 2
      kabatas iskele  -- 3
      kadikoy iskele  -- 4
 */    
void setup()
   { 
  //pinMode(5,INPUT);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
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
  player.volume(30);  
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

 void sefer_kad_bes()
   {
     if(InorOut(Kadikoy_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(4);}}      
      else
      {anons_sayac = 0;} 
       
    if(InorOut(Besiktas_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(2);}}      
      else
      {anons_sayac = 0;}        
    }

    
 void sefer_usk_bes()
   {
    if(InorOut(Uskudar_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(1);}}      
      else
      {anons_sayac = 0;} 
       
    if(InorOut(Besiktas_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(2);}}      
      else
      {anons_sayac = 0;}     
    }
 void sefer_kad_kab()
   {
   if(InorOut(Kadikoy_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(4);}}      
      else
      {anons_sayac = 0;} 
       
    if(InorOut(Kabatas_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(3);}}      
      else
      {anons_sayac = 0;}  
    }
 void sefer_usk_kab()
   {
   if(InorOut(Uskudar_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(1);}}      
      else
      {anons_sayac = 0;} 
       
    if(InorOut(Kabatas_iskele,Current_loc)==true)
     {if(anons_sayac < 3)
      {anons_yap(3);}}      
      else
      {anons_sayac = 0;} 
    }
    
  int anons_yap(int x)
  {
     static unsigned long timer1 = millis();
  if (millis() - timer1 > 5000) {
    timer1 = millis();
    player.play(x);
    anons_sayac ++; 
    Serial.println(anons_sayac);
  }
    }
void loop()
{
 
 
  //##############################  GPS  ######################################
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
   
    Current_loc[0] = flat, 6;
    Current_loc[1] = flon, 6;
    
    Serial.print(Current_loc[0],6);
    Serial.print(F(", "));
    Serial.println(Current_loc[1],6);
    
    smartdelay(100);
    //##############################  GPS  ######################################
    
    //##############################  OLED  ######################################

    if(digitalRead(7)==HIGH)
    {
    button1--;
    //delay(50);
    Serial.println("aaaaaaaaaaaaaaaaaaa");
    }

    if(digitalRead(6)==HIGH)
    {
    button1++;
    //delay(50);
    Serial.println("bbbbbbbbbbbbbbbbb");
    }
    
  
    current_page = button1 % 4;
    //Serial.println(current_page);

    
  if(current_page ==0){ //KADİKOY_BESİKTAS
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
     sefer_kad_bes();
  
  }
  while( u8g.nextPage() );
  }
  if(current_page ==1){ //USKUDAR_BESİKTAS
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
    // u8g.drawLine(1,48-u,128,48-u);
     u8g.drawStr( 1, 61-u, "Uskudar-Kabatas");
     //u8g.drawLine(1,64-u,128,64-u);
     sefer_usk_bes();
  } while( u8g.nextPage() );  
  }
  if(current_page ==2){ //KADIKOY_KABATAS
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
     sefer_kad_kab();
  } while( u8g.nextPage() );  
  }
  if(current_page ==3){//USKUDAR_KABATAS
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
     sefer_usk_kab();
  } while( u8g.nextPage() );  
  }
  //##############################OLED######################################

      
}
   static void smartdelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ssgps.available())
      gps.encode(ssgps.read());
  } while (millis() - start < ms);
}

  
