#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "TinyGPS.h"

float flat, flon;
float current_loc[2];
uint8_t volume=25;
uint8_t anons_sayac;
uint8_t anons_sayac1;
uint8_t geri_tus=0;
uint8_t sefer_no;
uint8_t ekran_no;
uint8_t vol_no;
uint8_t oto_no1;
uint8_t oto_no2;
uint8_t oto_no3;
uint8_t oto_sw=0;
uint8_t ta_no;
uint8_t tsa_no;
int dak = 60000;
uint8_t iskele_txt_no=0;

String saat;
String dakika;


TinyGPS gps;
SoftwareSerial ssgps(4, 3);
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini player;


 byte besiktas_anons=1;
 byte uskudar_anons =2;
 byte kabatas_anons =3;
 byte kadikoy_anons =4;
 byte eminonu_anons =5;
 byte kinaliada_anons =6;
 byte burgazada_anons =7;
 byte heybeliada_anons =8;
 byte buyukada_anons =9;
 byte ahisari_anons=11;
 byte kandilli_anons=12;
 byte kuzguncuk_anons=13;
 byte beylerbeyi_anons=14;
 byte cengelkoy_anons=15;
 byte kucuksu_anons=16;
 byte ortakoy_anons=17;
 byte emirgan_anons= 18;
 byte istinye_anons= 19;
 byte sariyer_anons=20;
 byte kanlica_anons=21;
 byte pasabahce_anons=22;
 byte beykoz_anons=23;
 byte cubuklu_anons=24;
 byte akavagi_anons=25;
 byte arnavutkoy_anons=26;
 byte buyukdere_anons=27;
 byte rkavagi_anons=28;
 byte bebek_anons=29;
 byte bos_anons=30;

  
 byte dolmabahcecamii_bt_anons=31;
 byte dolmabahce_bt_anons=32;
 byte ciragan_bt_anons=33;
 byte feriye_bt_anons=34;
 byte ortakoy_bt_anons=35;
 byte ortakoycamii_bt_anons=36;
 byte bogazicikoprusu_bt_anons=37;
 byte galatasarayadasi_bt_anons=38;
 byte arnavutkoy_bt_anons=39;
 byte akoysirayalilar_bt_anons=40;
 byte akintiburnu_bt_anons=41;
 byte misirkonsolosluk_bt_anons=42;
 byte bebek_bt_anons=43;
 byte rumelihisari_bt_anons=44;
 byte yusufpasakosku_bt_anons=45;
 byte baltalimanihastanesi_bt_anons=46;
 byte emirgan_bt_anons=47;
 byte sakipsabancimuzesi_bt_anons=48;
 byte kanlica_bt_anons=49;
 byte fsmkoprusu_bt_anons=50;
 byte anadoluhisari_bt_anons=51;
 byte kucuksukasri_bt_anons=52;
 byte kandilli_bt_anons=53;
 byte vanikoy_bt_anons=54;
 byte vanikoycamii_bt_anons=55;
 byte kuleliaskerilisesi_bt_anons=56;
 byte sumahan_bt_anons=57;
 byte cengelkoy_bt_anons=58;
 byte beylerbeyi_bt_anons=59;
 byte beylerbeyisarayi_bt_anons=60;
 byte kuzguncuk_bt_anons=61;
 
 float Uskudar_iskele[]= {41.0278426, 29.012778,41.03078, 29.020130};
 float Besiktas_iskele[]={41.03882, 29.00544,41.04266, 29.01091};  
 float Kabatas_iskele[]={41.03291, 28.9926,41.03619, 28.9958};  
 float Kadikoy_iskele[]={40.98950422, 29.014312,40.994346, 29.02416177};
 float Eminonu_iskele[]={41.0164801, 28.9736655,41.020463, 28.98352794}; 
 float Kinaliada_iskele[]={40.90838, 29.05284,40.915, 29.05916};    
 float Burgazada_iskele[]={40.87904, 29.0669,40.88674, 29.07481};    
 float Heybeliada_iskele[]={40.87324, 29.09428,40.88226, 29.1069};    
 float Buyukada_iskele[]={40.87284, 29.1188,40.87894, 29.13074};    
 float Kuzguncuk_iskele[]={41.03409, 29.02859,41.03783, 29.03535};
 float Beylerbeyi_iskele[]={41.04273, 29.04316,41.04607, 29.05026};
 float Cengelkoy_iskele[]={41.0497, 29.04969,41.05224, 29.05351};
 float Kandilli_iskele[]={41.07305, 29.05702,41.0751, 29.06042};
 float Ahisari_iskele[]={41.08226, 29.06475,41.08426, 29.06796};
 float Arnavutkoy_iskele[]={41.06601, 29.04229,41.0676, 29.04454};
 float Bebek_iskele[]={41.07464, 29.04223,41.0777, 29.04616};
 float Emirgan_iskele[]={41.10212, 29.0547,41.10413, 29.05744};
 float Istinye_iskele[]={41.11165, 29.05955,41.11411, 29.06307};
 float Kanlica_iskele[]={41.09931, 29.06432,41.10102, 29.06667};
 float Kucuksu_iskele[]={41.07818, 29.06375,41.08025, 29.06724};
 float Ortakoy_iskele[]={41.04626, 29.02211,41.049, 29.02709};
 float Sariyer_iskele[]={41.16483, 29.056,41.16734, 29.05975}; 
 float Pasabahce_iskele[]={41.11609, 29.08988,41.11878, 29.09513};
 float Beykoz_iskele[]={41.13285, 29.08706,41.13629, 29.09313};
 float Cubuklu_iskele[]={41.10709, 29.07817,41.10937, 29.08202};
 float Akavagi_iskele[]={41.17128, 29.08492,41.1753, 29.092};
 float Rkavagi_iskele[]={41.17958, 29.07215,41.18378, 29.07884};
 float Buyukdere_iskele[]={41.15838, 29.04275,41.16324, 29.05007};
 float dolmabahcecamii_bturu[] ={41.03501, 28.99718,41.03744, 28.99928};
 float dolmabahce_bturu[] ={41.03648, 29.00055,41.03894, 29.00458};
 float ciragan_bturu[] ={41.04036, 29.01353,41.04242, 29.01556};
 float feriye_bturu[] ={41.04156, 29.0173,41.04543, 29.02053};
 float ortakoy_bturu[] ={41.0429, 29.02223,41.04666, 29.02496};
 float ortakoycamii_bturu[] ={41.04417, 29.02566,41.04682, 29.02836};
 float bogazicikoprusu_bturu[] ={41.04591, 29.02985,41.04878, 29.03271};
 float galatasarayadasi_bturu[] ={41.05834, 29.03789,41.06057, 29.04191};
 float arnavutkoy_bturu[] ={41.06102, 29.04083,41.06301, 29.04503};
 float akoysirayalilar_bturu[] ={41.06446, 29.04339,41.06634, 29.04751};
 float akintiburnu_bturu[] ={41.06766, 29.04631,41.06983, 29.04915};
 float misirkonsolosluk_bturu[] ={41.07277, 29.04508,41.0747, 29.04875};
 float bebek_bturu[] ={41.07649, 29.04431,41.07908, 29.05085};
 float rumelihisari_bturu[] ={41.08268, 29.05594,41.08476, 29.05979};
 float yusufpasakosku_bturu[] ={41.08826, 29.05719,41.09003, 29.05992};
 float baltalimanihastanesi_bturu[] ={41.09462, 29.05383,41.09626, 29.05802};
 float emirgan_bturu[] ={41.09768, 29.05452,41.0989, 29.05795};
 float sakipsabancimuzesi_bturu[] ={41.10014, 29.05477,41.10122, 29.05789};
 float kanlica_bturu[] ={41.09937, 29.06297,41.10105, 29.06596};
 float fsmkoprusu_bturu[] ={41.09182, 29.0626,41.09412, 29.06646};
 float anadoluhisari_bturu[] ={41.08431, 29.06452,41.08589, 29.0674};
 float kucuksukasri_bturu[] ={41.07972, 29.06239,41.08144, 29.06596};
 float kandilli_bturu[] ={41.07463, 29.05766,41.07638, 29.06094};
 float vanikoy_bturu[] ={41.06831, 29.05337,41.06973, 29.05741};
 float vanikoycamii_bturu[] ={41.06456, 29.05351,41.06635, 29.05661};
 float kuleliaskerilisesi_bturu[] ={41.05843, 29.04998,41.06055, 29.05334};
 float sumahan_bturu[] ={41.05549, 29.04961,41.05665, 29.05294};
 float cengelkoy_bturu[] ={41.05047, 29.04821,41.05242, 29.05193};
 float beylerbeyi_bturu[] ={41.04672, 29.04516,41.04819, 29.04844};
 float beylerbeyisarayi_bturu[] ={41.04233, 29.03664,41.04439, 29.04049};
 float kuzguncuk_bturu[] ={41.038, 29.02937,41.04054, 29.03351};
 

/* 
 float Kanlica_iskele[]={,};
 float Kanlica_iskele[]={,};
 */
 
 
 

 
void setup() 
{
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  if(!player.begin(mySoftwareSerial)) 
   {  
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));   
   }
   Serial.println(F("DFPlayer Mini online."));
   delay(0);
   
   ssgps.begin(9600);
   
} 

  static void smartdelay(unsigned long ms)
  {
    unsigned long start = millis();
    do  
    {while (ssgps.available())
     gps.encode(ssgps.read());}
     while (millis() - start < ms);
  }

    int anons_yap(int x)
  {   
     static unsigned long timer1 = millis();
     if (millis() - timer1 > 15500) 
     {
     timer1 = millis();    
     player.volume(volume); 
     player.play(x);
     anons_sayac ++; 
     anons_sayac1++; 
     }
  }

  int oto_anons_yap(long y,long x)
   {
     static unsigned long timer1 = millis();
     if (millis() - timer1 > y) 
     {
     timer1 = millis();
     player.volume(volume); 
     player.play(x);
     }
     
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

   int sefer_secimi(int sefer_nu)
  { 
    /*
    if(sefer_nu ==0) // SEFER DENEME
    {
         if(InorOut(Bizim_ev_konum,current_loc)==true)
         {if(anons_sayac < 3)
         {anons_yap(1);
         }}              
         else
         {anons_sayac = 0;} 
    }
    */
    if(sefer_nu ==1) // KADIKÖY BESİKTAS 
    {
         if(InorOut(Kadikoy_iskele,current_loc)==true)
         {
          iskele_txt_no=4;
          if(anons_sayac < 2)
         {anons_yap(4);
         
         }}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {
          iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(1);
         }}  
         else
         {iskele_txt_no=0;
          anons_sayac = 0;} 
    }
    
    if(sefer_nu ==2) // ÜSKÜDAR BESİKTAS 
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {
          iskele_txt_no=1;
          if(anons_sayac < 2)
         {anons_yap(2);
         }}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {
          iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(1);}}      
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  

     if(sefer_nu ==3) // ÜSKÜDAR KABATAS
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {iskele_txt_no=1;
          if(anons_sayac < 2)
         {anons_yap(2);
         }}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(3);}}      
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  

     if(sefer_nu ==4) // KADIKÖY KABATAŞ
    {
         if(InorOut(Kadikoy_iskele,current_loc)==true)
         {iskele_txt_no=4;
          if(anons_sayac < 2)
         {anons_yap(4);
         }}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(3);}}      
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  

     
    if(sefer_nu ==5) // 3No Hisar SABAH TARİFESİ
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
          if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
          if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Kandilli_iskele,current_loc)==true)
         {iskele_txt_no=13;
          if(anons_sayac < 2)
         {anons_yap(kandilli_anons);}}
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
          if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  
     
      if(sefer_nu ==6) // 3No Hisar AKSAM TARİFESİ
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
          if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Kuzguncuk_iskele,current_loc)==true)
         {iskele_txt_no=10;
          if(anons_sayac < 2)
         {anons_yap(kuzguncuk_anons);}} 
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
          if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
          if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
          if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else
         {anons_sayac = 0;
         iskele_txt_no=0;}     
     }  
     if(sefer_nu ==7) // 6No Ortaboğaz NORMAL TARİFE
    {
         if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
          if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}}            
         else if(InorOut(Arnavutkoy_iskele,current_loc)==true)
         {iskele_txt_no=15;
          if(anons_sayac < 2)
         {anons_yap(arnavutkoy_anons);}} 
         else if(InorOut(Bebek_iskele,current_loc)==true)
         {iskele_txt_no=16;
          if(anons_sayac < 2)
         {anons_yap(bebek_anons);}} 
         else if(InorOut(Kandilli_iskele,current_loc)==true)
         {iskele_txt_no=13;
          if(anons_sayac < 2)
         {anons_yap(kandilli_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
          if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
          if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
          if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}}
         else if(InorOut(Istinye_iskele,current_loc)==true)
         {iskele_txt_no=18;
          if(anons_sayac < 2)
         {anons_yap(istinye_anons);}} 
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  
      if(sefer_nu ==8) // 6No Ortaboğaz PAZAR TARİFESİ
    {
         if(InorOut(Bebek_iskele,current_loc)==true)
         {iskele_txt_no=16;
          if(anons_sayac < 2)
         {anons_yap(bebek_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
          if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
          if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
          if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}}
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  
    if(sefer_nu ==9) // 7No Küçüksu SABAH
    {
           
         if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Kucuksu_iskele,current_loc)==true)
         {iskele_txt_no=20;
          if(anons_sayac < 2)
         {anons_yap(kucuksu_anons);}}
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
          if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  
      if(sefer_nu ==10) // 7No Küçüksu AKSAM
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
          if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
          if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
          if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Kucuksu_iskele,current_loc)==true)
         {iskele_txt_no=20;
          if(anons_sayac < 2)
         {anons_yap(kucuksu_anons);}}
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  

      if(sefer_nu ==11) // 8No Sariyer HAFTAICI SABAH
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
          if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
          if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Kuzguncuk_iskele,current_loc)==true)
         {iskele_txt_no=10;
          if(anons_sayac < 2)
         {anons_yap(kuzguncuk_anons);}}
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
          if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}} 
         else if(InorOut(Istinye_iskele,current_loc)==true)
         {iskele_txt_no=18;
          if(anons_sayac < 2)
         {anons_yap(istinye_anons);}} 
         else if(InorOut(Sariyer_iskele,current_loc)==true)
         {iskele_txt_no=22;
          if(anons_sayac < 2)
         {anons_yap(sariyer_anons);}} 
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  

     if(sefer_nu ==12) // 8No Sariyer HAFTAICI AKSAM
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
          if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Ortakoy_iskele,current_loc)==true)
         {iskele_txt_no=21;
          if(anons_sayac < 2)
         {anons_yap(ortakoy_anons);}} 
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
          if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}} 
         else if(InorOut(Istinye_iskele,current_loc)==true)
         {iskele_txt_no=18;
          if(anons_sayac < 2)
         {anons_yap(istinye_anons);}} 
         else if(InorOut(Sariyer_iskele,current_loc)==true)
         {iskele_txt_no=22;
          if(anons_sayac < 2)
         {anons_yap(sariyer_anons);}} 
         else
         {anons_sayac = 0;}     
     }  
     if(sefer_nu ==13) // 8No Sariyer CTS SABAH
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
          if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
          if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
          if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
          if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}} 
         else if(InorOut(Istinye_iskele,current_loc)==true)
         {iskele_txt_no=18;
          if(anons_sayac < 2)
         {anons_yap(istinye_anons);}} 
         else if(InorOut(Sariyer_iskele,current_loc)==true)
         {iskele_txt_no=22;
          if(anons_sayac < 2)
         {anons_yap(sariyer_anons);}} 
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  
     if(sefer_nu ==14) // 8No Sariyer CTS AKSAM
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
         if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
          if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
         if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Ortakoy_iskele,current_loc)==true)
         {iskele_txt_no=21;
          if(anons_sayac < 2)
         {anons_yap(ortakoy_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
         if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
         if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}} 
         else if(InorOut(Istinye_iskele,current_loc)==true)
         {iskele_txt_no=18;
         if(anons_sayac < 2)
         {anons_yap(istinye_anons);}} 
         else if(InorOut(Sariyer_iskele,current_loc)==true)
         {iskele_txt_no=22;
         if(anons_sayac < 2)
         {anons_yap(sariyer_anons);}} 
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }  
     if(sefer_nu ==15) // 8No Sariyer PAZAR
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
         if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
         if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
          if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else if(InorOut(Sariyer_iskele,current_loc)==true)
         {iskele_txt_no=22;
         if(anons_sayac < 2)
         {anons_yap(sariyer_anons);}} 
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }  
    if(sefer_nu ==16) // 9No Beykoz SABAH
    {
         if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
         if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}}            
         else if(InorOut(Uskudar_iskele,current_loc)==true)
         {iskele_txt_no=1;
         if(anons_sayac < 2)
         {anons_yap(uskudar_anons);}} 
         else if(InorOut(Kucuksu_iskele,current_loc)==true)
         {iskele_txt_no=20;
         if(anons_sayac < 2)
         {anons_yap(kucuksu_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
         if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
         if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}}
         else if(InorOut(Pasabahce_iskele,current_loc)==true)
         {iskele_txt_no=23;
         if(anons_sayac < 2)
         {anons_yap(pasabahce_anons);}} 
         else if(InorOut(Beykoz_iskele,current_loc)==true)
         {iskele_txt_no=24;
         if(anons_sayac < 2)
         {anons_yap(beykoz_anons);}} 
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }  
      if(sefer_nu ==17) // 9No Beykoz AKSAM
    {
         if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
         if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}}            
         else if(InorOut(Uskudar_iskele,current_loc)==true)
         {iskele_txt_no=1;
         if(anons_sayac < 2)
         {anons_yap(uskudar_anons);}} 
         else if(InorOut(Kuzguncuk_iskele,current_loc)==true)
         {iskele_txt_no=10;
         if(anons_sayac < 2)
         {anons_yap(kuzguncuk_anons);}} 
         else if(InorOut(Kucuksu_iskele,current_loc)==true)
         {iskele_txt_no=20;
         if(anons_sayac < 2)
         {anons_yap(kucuksu_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
         if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
         if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}}
         else if(InorOut(Pasabahce_iskele,current_loc)==true)
         {iskele_txt_no=23;
         if(anons_sayac < 2)
         {anons_yap(pasabahce_anons);}} 
         else if(InorOut(Beykoz_iskele,current_loc)==true)
         {iskele_txt_no=24;
         if(anons_sayac < 2)
         {anons_yap(beykoz_anons);}} 
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     } 
      if(sefer_nu ==18) // 14No Adalar
    {
         if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
         if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}}            
         else if(InorOut(Kadikoy_iskele,current_loc)==true)
         {iskele_txt_no=4;
          if(anons_sayac < 2)
         {anons_yap(kadikoy_anons);}} 
         else if(InorOut(Kinaliada_iskele,current_loc)==true)
         {iskele_txt_no=6;
         if(anons_sayac < 2)
         {anons_yap(kinaliada_anons);}} 
         else if(InorOut(Burgazada_iskele,current_loc)==true)
         {iskele_txt_no=7;
         if(anons_sayac < 2)
         {anons_yap(burgazada_anons);}} 
         else if(InorOut(Heybeliada_iskele,current_loc)==true)
         {iskele_txt_no=8;
         if(anons_sayac < 2)
         {anons_yap(heybeliada_anons);}} 
         else if(InorOut(Buyukada_iskele,current_loc)==true)
         {iskele_txt_no=9;
         if(anons_sayac < 2)
         {anons_yap(buyukada_anons);}}
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }
       
      if(sefer_nu ==19) // 20No Beykoz
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {iskele_txt_no=1;
         if(anons_sayac < 2)
         {anons_yap(uskudar_anons);}}            
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
         if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
         if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
         if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
         if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else if(InorOut(Pasabahce_iskele,current_loc)==true)
         {iskele_txt_no=23;
         if(anons_sayac < 2)
         {anons_yap(pasabahce_anons);}}
         else if(InorOut(Cubuklu_iskele,current_loc)==true)
         {iskele_txt_no=25;
         if(anons_sayac < 2)
         {anons_yap(cubuklu_anons);}}
         else if(InorOut(Beykoz_iskele,current_loc)==true)
         {iskele_txt_no=24;
         if(anons_sayac < 2)
         {anons_yap(beykoz_anons);}}
         else
         {iskele_txt_no=0;
          anons_sayac = 0;}     
     }  
      if(sefer_nu ==20) // 21No Kavak
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {iskele_txt_no=1;
         if(anons_sayac < 2)
         {anons_yap(uskudar_anons);}}            
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
         if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
         if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
         if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=19;
         if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else if(InorOut(Pasabahce_iskele,current_loc)==true)
         {iskele_txt_no=23;
         if(anons_sayac < 2)
         {anons_yap(pasabahce_anons);}}
         else if(InorOut(Cubuklu_iskele,current_loc)==true)
         {iskele_txt_no=25;
          if(anons_sayac < 2)
         {anons_yap(cubuklu_anons);}}
         else if(InorOut(Beykoz_iskele,current_loc)==true)
         {iskele_txt_no=24;
         if(anons_sayac < 2)
         {anons_yap(beykoz_anons);}}
         else if(InorOut(Akavagi_iskele,current_loc)==true)
         {iskele_txt_no=26;
         if(anons_sayac < 2)
         {anons_yap(akavagi_anons);}}
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }  
      if(sefer_nu ==21) // 23No Beykoz
    {
         if(InorOut(Uskudar_iskele,current_loc)==true)
         {iskele_txt_no=1;
         if(anons_sayac < 2)
         {anons_yap(uskudar_anons);}}            
         else if(InorOut(Beylerbeyi_iskele,current_loc)==true)
         {iskele_txt_no=11;
         if(anons_sayac < 2)
         {anons_yap(beylerbeyi_anons);}} 
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
         if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}} 
         else if(InorOut(Ahisari_iskele,current_loc)==true)
         {iskele_txt_no=14;
         if(anons_sayac < 2)
         {anons_yap(ahisari_anons);}} 
         else if(InorOut(Kanlica_iskele,current_loc)==true)
         {iskele_txt_no=13;
         if(anons_sayac < 2)
         {anons_yap(kanlica_anons);}} 
         else if(InorOut(Pasabahce_iskele,current_loc)==true)
         {iskele_txt_no=23;
          if(anons_sayac < 2)
         {anons_yap(pasabahce_anons);}}
         else if(InorOut(Cubuklu_iskele,current_loc)==true)
         {iskele_txt_no=25;
         if(anons_sayac < 2)
         {anons_yap(cubuklu_anons);}}
         else if(InorOut(Beykoz_iskele,current_loc)==true)
         {iskele_txt_no=24;
         if(anons_sayac < 2)
         {anons_yap(beykoz_anons);}}
         else if(InorOut(Akavagi_iskele,current_loc)==true)
         {iskele_txt_no=26;
          if(anons_sayac < 2)
         {anons_yap(akavagi_anons);}}
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }  
      if(sefer_nu ==22) // 24No Sariyer
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
         if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
         if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Arnavutkoy_iskele,current_loc)==true)
         {iskele_txt_no=15;
         if(anons_sayac < 2)
         {anons_yap(arnavutkoy_anons);}} 
         else if(InorOut(Emirgan_iskele,current_loc)==true)
         {iskele_txt_no=17;
         if(anons_sayac < 2)
         {anons_yap(emirgan_anons);}} 
         else if(InorOut(Istinye_iskele,current_loc)==true)
         {iskele_txt_no=18;
         if(anons_sayac < 2)
         {anons_yap(istinye_anons);}} 
         else if(InorOut(Buyukdere_iskele,current_loc)==true)
         {iskele_txt_no=28;
         if(anons_sayac < 2)
         {anons_yap(buyukdere_anons);}}
         else if(InorOut(Sariyer_iskele,current_loc)==true)
         {iskele_txt_no=22;
         if(anons_sayac < 2)
         {anons_yap(sariyer_anons);}}
         else if(InorOut(Rkavagi_iskele,current_loc)==true)
         {iskele_txt_no=27;
         if(anons_sayac < 2)
         {anons_yap(rkavagi_anons);}}
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }  
       if(sefer_nu ==23) // Dentur Adalar
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
         if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
         if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}} 
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
         if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Burgazada_iskele,current_loc)==true)
         {iskele_txt_no=7;
         if(anons_sayac < 2)
         {anons_yap(burgazada_anons);}} 
         else if(InorOut(Kinaliada_iskele,current_loc)==true)
         {iskele_txt_no=6;
         if(anons_sayac < 2)
         {anons_yap(kinaliada_anons);}} 
         else if(InorOut(Heybeliada_iskele,current_loc)==true)
         {iskele_txt_no=8;
         if(anons_sayac < 2)
         {anons_yap(heybeliada_anons);}}
         else if(InorOut(Buyukada_iskele,current_loc)==true)
         {iskele_txt_no=9;
         if(anons_sayac < 2)
         {anons_yap(buyukada_anons);}}
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}  
     } 
      if(sefer_nu ==24) // BOGAZ TURU
    {
         if(InorOut(dolmabahcecamii_bturu,current_loc)==true)
         {iskele_txt_no=29;
          if(anons_sayac < 1)
         {oto_anons_yap(5*60000,dolmabahcecamii_bt_anons);}}
         else if(InorOut(dolmabahce_bturu,current_loc)==true)
         {iskele_txt_no=30;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,dolmabahce_bt_anons);}}   
         else if(InorOut(ciragan_bturu,current_loc)==true)
         {iskele_txt_no=31;
          if(anons_sayac < 1)
         {oto_anons_yap(5*60000,ciragan_bt_anons);}}            
         else if(InorOut(feriye_bturu,current_loc)==true)
         {iskele_txt_no=32;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,feriye_bt_anons);}}
         else if(InorOut(ortakoy_bturu,current_loc)==true)
         {iskele_txt_no=33;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,ortakoy_bt_anons);}}   
         else if(InorOut(ortakoycamii_bturu,current_loc)==true)
         {iskele_txt_no=34;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,ortakoycamii_bt_anons);}}  
         else if(InorOut(bogazicikoprusu_bturu,current_loc)==true)
         {iskele_txt_no=35;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,bogazicikoprusu_bt_anons);}}  
         else if(InorOut(galatasarayadasi_bturu,current_loc)==true)
         {iskele_txt_no=36;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,galatasarayadasi_bt_anons);}}  
         else if(InorOut(arnavutkoy_bturu,current_loc)==true)
         {iskele_txt_no=37;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,arnavutkoy_bt_anons);}}  
         else if(InorOut(akoysirayalilar_bturu,current_loc)==true)
         {iskele_txt_no=38;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,akoysirayalilar_bt_anons);}}  
         else if(InorOut(akintiburnu_bturu,current_loc)==true)
         {iskele_txt_no=39;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,akintiburnu_bt_anons);}}  
         else if(InorOut(misirkonsolosluk_bturu,current_loc)==true)
         {iskele_txt_no=40;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,misirkonsolosluk_bt_anons);}}  
         else if(InorOut(bebek_bturu,current_loc)==true)
         {iskele_txt_no=41;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,bebek_bt_anons);}} 
         else if(InorOut(rumelihisari_bturu,current_loc)==true)
         {iskele_txt_no=42;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,rumelihisari_bt_anons);}}
         else if(InorOut(yusufpasakosku_bturu,current_loc)==true)
         {iskele_txt_no=43;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,yusufpasakosku_bt_anons);}}
         else if(InorOut(baltalimanihastanesi_bturu,current_loc)==true)
         {iskele_txt_no=44;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,baltalimanihastanesi_bt_anons);}}
         else if(InorOut(emirgan_bturu,current_loc)==true)
         {iskele_txt_no=45;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,emirgan_bt_anons);}}
         else if(InorOut(sakipsabancimuzesi_bturu,current_loc)==true)
         {iskele_txt_no=46;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,sakipsabancimuzesi_bt_anons);}}           
         else if(InorOut(kanlica_bturu,current_loc)==true)
         {iskele_txt_no=47;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,kanlica_bt_anons);}} 
         else if(InorOut(fsmkoprusu_bturu,current_loc)==true)
         {iskele_txt_no=48;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,fsmkoprusu_bt_anons);}}
         else if(InorOut(anadoluhisari_bturu,current_loc)==true)
         {iskele_txt_no=49;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,anadoluhisari_bt_anons);}}
         else if(InorOut(kucuksukasri_bturu,current_loc)==true)
         {iskele_txt_no=50;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,kucuksukasri_bt_anons);}}
         else if(InorOut(kandilli_bturu,current_loc)==true)
         {iskele_txt_no=51;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,kandilli_bt_anons);}}
         else if(InorOut(vanikoy_bturu,current_loc)==true)
         {iskele_txt_no=52;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,vanikoy_bt_anons);}}
         else if(InorOut(vanikoycamii_bturu,current_loc)==true)
         {iskele_txt_no=53;
          if(anons_sayac < 1)
         {oto_anons_yap(5*60000,vanikoycamii_bt_anons);}}             
         else if(InorOut(kuleliaskerilisesi_bturu,current_loc)==true)
         {iskele_txt_no=54;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,kuleliaskerilisesi_bt_anons);}}
         else if(InorOut(sumahan_bturu,current_loc)==true)
         {iskele_txt_no=55;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,sumahan_bt_anons);}}
         else if(InorOut(cengelkoy_bturu,current_loc)==true)
         {iskele_txt_no=56;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,cengelkoy_bt_anons);}}
         else if(InorOut(beylerbeyi_bturu,current_loc)==true)
         {iskele_txt_no=57;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,beylerbeyi_bt_anons);}}
         else if(InorOut(beylerbeyisarayi_bturu,current_loc)==true)
         {iskele_txt_no=58;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,beylerbeyisarayi_bt_anons);}}
         else if(InorOut(kuzguncuk_bturu,current_loc)==true)
         {iskele_txt_no=59;
         if(anons_sayac < 1)
         {oto_anons_yap(5*60000,kuzguncuk_bt_anons);}}            
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}  
     }
       if(sefer_nu ==25) // EMN BES ORT
    {
         if(InorOut(Eminonu_iskele,current_loc)==true)
         {iskele_txt_no=5;
         if(anons_sayac < 2)
         {anons_yap(eminonu_anons);}}            
         else if(InorOut(Besiktas_iskele,current_loc)==true)
         {iskele_txt_no=2;
         if(anons_sayac < 2)
         {anons_yap(besiktas_anons);}} 
         else if(InorOut(Ortakoy_iskele,current_loc)==true)
         {iskele_txt_no=21;
         if(anons_sayac < 2)
         {anons_yap(ortakoy_anons);}}    
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }
           if(sefer_nu ==26) // KABATAS-CENGEL
    {
         if(InorOut(Kabatas_iskele,current_loc)==true)
         {iskele_txt_no=3;
         if(anons_sayac < 2)
         {anons_yap(kabatas_anons);}}            
         else if(InorOut(Cengelkoy_iskele,current_loc)==true)
         {iskele_txt_no=12;
         if(anons_sayac < 2)
         {anons_yap(cengelkoy_anons);}}    
         else
         {iskele_txt_no=0;
         anons_sayac = 0;}     
     }   
  }  
   
void loop() {

  //--------------------------------ANONS_AYARLARI-----------------------------------
   
  
   sefer_secimi(sefer_no);
 
 if(oto_sw==1)
 {
   switch (oto_no1) 
  {
   case 1: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
   
   case 2: 
      oto_anons_yap(oto_no1*60000,10);
      break;  
   
   case 3: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
      
   case 4: 
      oto_anons_yap(oto_no1*60000,10);
      break; 

   case 5: 
      oto_anons_yap(oto_no1*60000,10);
      break; 

   case 10: 
      oto_anons_yap(oto_no1*60000,10);
      break; 

   case 15: 
      oto_anons_yap(oto_no1*60000,10);
      break; 

   case 20: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
      
   case 25: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
      
   case 30: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
   
   case 45: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
  
   case 60: 
      oto_anons_yap(oto_no1*60000,10);
      break; 
  }
 }
 else if(oto_sw==0)
 {}
  //--------------------------------ANONS_AYARLARI-----------------------------------
   
  //--------------------------------GPS-----------------------------------
    int year;
    byte month, day, hour, minute, second, hundredths;
    unsigned long age2;
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);
    int bagli_uydu = gps.satellites();
    
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
   
    current_loc[0] = flat, 6;
    current_loc[1] = flon, 6;
   /*
    current_loc[0] = 41.03779;
    current_loc[1] = 29.00259;
    */ 
    smartdelay(100);
    
    int deger1=flat;
    int deger2=flon;
 
    
   
   //--------------------------------GPS-----------------------------------
   
   //--------------------------------NEXTİON_SERIAL-----------------------------------
  if(Serial.available())
  { 
    String data = "";
    while(Serial.available())
    {
      data += char(Serial.read());
    }
   
    if(data.substring(0,8)=="B.BPAGE0")
    {
     ekran_no=0;  
    }
    if(data.substring(0,8)=="B.BPAGE1")
    {
      Serial.println(iskele_txt_no);
     ekran_no=1;
          if(data.substring(7,9)=="12")
          {  
          ekran_no=12;  
          Serial.print("f4.val=");
          Serial.print(iskele_txt_no);
          Serial.write(0xff);
          Serial.write(0xff);
          Serial.write(0xff);
          }
          if(data.substring(8,10)=="SS")
          {    
          player.volume(volume); 
          player.play(30);
          }
    }
    if(data.substring(0,8)=="B.BPAGE2")
    {
     ekran_no=2;
     vol_no = data.substring(8,10).toInt();
     
    }
    if(data.substring(0,8)=="B.BPAGE3")
    {
     ekran_no=3;
    // Serial.println(data);
    // Serial.println(data.substring(8,10).toInt());
     sefer_no = data.substring(8,10).toInt();
     
     Serial.print("n53.val=");
     Serial.print(sefer_no);
     Serial.write(0xff);
     Serial.write(0xff);
     Serial.write(0xff);

    }
    if(data.substring(0,8)=="B.BPAGE4")
    {
         ekran_no=4;
         //Serial.println(oto_no1);
         if(data.substring(10,11)=="M")
         { 
         oto_sw=1;
         oto_no1 = data.substring(8,10).toInt();
         oto_no2 = data.substring(11,13).toInt();  
         //Serial.println(oto_no1*60000);   
         }
         if(data.substring(10,11)=="W")
         {
         oto_no2 = data.substring(8,10).toInt();
         oto_no3 = data.substring(11,13).toInt();
         oto_no1 = data.substring(14,16).toInt();
         if(saat==oto_no2 && dakika==oto_no3)
         {
         oto_sw=1;
         }    
         }        
    }
         if(data.substring(0,8)=="B.BPAGE5")
     { 
         ekran_no=5;
         
         ta_no=data.substring(9,11).toInt();
         /*
         Serial.print(anons_sayac1);
         Serial.print("   ");
         Serial.println(ta_no);
         */
         static unsigned long timer2 = millis();
         if (millis() - timer2 > 10000) 
         {
         timer2 = millis();    
         anons_sayac1=0;
         }   
         if(ta_no>0 && ta_no<30)
         {if(anons_sayac1 < 1)
         {player.volume(volume); 
          player.play(ta_no);
          anons_sayac1++;}
         else if(anons_sayac1==1)
         {ta_no = 0;} }
             
        
     }
    if(data.substring(0,8)=="B.BPAGE7")
     { 
             ekran_no=7;
             tsa_no=data.substring(8,10).toInt();
             //Serial.println(tsa_no);

             
              static unsigned long timer3 = millis();
              if (millis() - timer3 > 15000) 
              {
              timer3 = millis();    
              anons_sayac1=0;
              } 
                
              if(tsa_no>0 && tsa_no<30)
              {if(anons_sayac1 < 1)
              {player.volume(volume); 
              player.play(tsa_no);
              anons_sayac1++;}
              else if(anons_sayac1==1)
              {ta_no = 0;} }   

         
     }
   
      if(data.substring(0,8)=="B.BPAGE6")
    {
     ekran_no=6;
    }
    }

     /*
         static unsigned long timer4 = millis();     //ANA MENU
         if (millis() - timer4 > 60000) 
         {
         timer4 = millis();    
         Serial.print("page ");
         Serial.print("page1");
         Serial.write(0xff);
         Serial.write(0xff);
         Serial.write(0xff);
         }   
     */
  
  uint8_t gps_logo;
  uint8_t saat_durum;
  long saat0_renk;
  long saat1_renk;
  String saat_text;
  saat= String(hour+3);
  if(minute<=9)
  {dakika= "0"+String(minute);}
  else 
  {dakika= String(minute);}
  saat_text= saat+ dakika;

if(ekran_no==4)
   {
  Serial.print("n4.val=");
  Serial.print(saat);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("n5.val=");
  Serial.print(dakika);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  }
  
 
  if(
     ekran_no==1||
     ekran_no==2||
     ekran_no==4||
     ekran_no==6||
     ekran_no==7)
  {
 if(flat==1000 && flon==1000 )
  {
  Serial.print("t12.pco=");
  Serial.print(59392);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("x12.pco=");
  Serial.print(397);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  }
  else
  {
  Serial.print("t12.pco=");
  Serial.print(397);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("x12.pco=");
  Serial.print(64512);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("x12.val=");
  Serial.print(saat_text.toInt());
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  }  
  }
  else
  {}
 

 if(ekran_no==6)
   {
  Serial.print("x0.val=");
  Serial.print(deger1);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("x1.val=");
  Serial.print(deger2);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("x2.val=");
  Serial.print(sefer_no);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("x3.val=");
  Serial.print(oto_no1);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  Serial.print("x4.val=");
  Serial.print(vol_no);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  
  Serial.print("x5.val=");
  Serial.print(iskele_txt_no);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  }
  
  if(ekran_no==1)
   {
    
   

    Serial.print("n0.val=");
    Serial.print(iskele_txt_no);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
   
    Serial.print("n2.val=");
    Serial.print(sefer_no);
    Serial.write(0xff);
    Serial.write(0xff);
    Serial.write(0xff);
    
    }
    }
   //--------------------------------NEXTİON_SERIAL-----------------------------------
  
  
  
