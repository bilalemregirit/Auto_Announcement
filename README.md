# OPEN SOURCE - WORK IN PROGRESS
Youtube Video of the Project: https://www.youtube.com/watch?v=9ex4jSiTSgA&t=38s

THE LATEST VERSION OF THE PROJECT
![Ekran görüntüsü 2023-10-05 132101](https://github.com/bilalemregirit/Auto_Announcement_system/assets/60060887/8d35b672-1630-455d-8e45-37a65f3aa210)



# HOW IT WORKS

This is a project that automizes the announcements of the public transportations with the GPS coordinates. 
And This is how it works: First i want to start with the hardware of the device.
![image](https://github.com/bilalemregirit/Auto_Announcement/assets/60060887/eaf463e3-062e-45a4-a03c-ce7876c2a655)
There are bunch of components in the device such as; Dfplayer Mini, this device helps to make announcements, it has 
sd card socket that keeps all the announcement audio files and it gives audio output to the Aux port when it recieves
spesific signal. Arduino Pro Micro keeps all the location data as longitude and latitude and if it recieves gps signals 
from the gps module. When the device is in the spesific area it transmits signal to the DfPlayer. There is a GPS module 
and the antenna, the model of this component is GPS Neo 6m. And There is a TouchScreen Display Nextion. This display 
got Windows application. You can customize it for you personal needs easily. And lastly there is a Dip switch between 
microcontroller and the display. Because you cannot upload your codes while the display is connected. My solution for 
this problem is cutting the connection with two components with switch when i want to upload a code to the micro controller.
![COMPONENTS (1)](https://github.com/bilalemregirit/Auto_Announcement/assets/60060887/4ab5dbb0-785c-4a87-b8b9-99125e0584c6)



There is a common GPS module inside of the device that indicates the estimated 
location. The GPS module is obtaioning and transmitting some values that it gets from sattelites like 
latitude, logitude. It transmits the value that it got to the micro controller. Inside of the microcontroller,
there are bunch of coordinate values that indicates spesific areas in the place that the vessel is going to work
(you can also reach all the coordinates that i used in bosphorus in the link: rb.gy/ims96)
![image](https://github.com/bilalemregirit/Auto_Announcement/assets/60060887/a27e065c-3d33-49e2-a315-e24402321df5)









The early beggining of this project includes a tiny OLED screen (SSD1306) with 
arduino nano and several basic buttons.(The menu demonstration of that device: 
https://www.youtube.com/watch?v=d2qRUfzXhB8&t=34s) 






















    
 Menu Demo (SSD1306): https://www.youtube.com/watch?v=d2qRUfzXhB8&t=34s
 
 Menu Demo (ST7735) : https://www.youtube.com/watch?v=dHNRrd75gP8
 
  This is a project that indicates which station that vessel approaches and makes the announcement automatically. This device get coordinates 
with UBLOX NEO6M gps module, and announcement sound files can uploaded to the any sd card and attached the DF player module. Speakers that make 
announcement are connecting the 3.5mm jack input.   

Schematic of the project:
![gps_anons](https://user-images.githubusercontent.com/60060887/175570052-f531bdab-98e3-444b-9662-8625886b9e28.png)

 Required Parts for this project:
      - UBLOX NEO6M
      - SSD1306 OLED
      - Arduino Nano / Mini(5v)
      - DF Player Mini
      - SD card (at least 2gb)
      - 3.5mm Jack input   
      
BASİC PCB DESİGN OF CARD:
![untitled2](https://user-images.githubusercontent.com/60060887/175928738-212f4597-2feb-4142-bfca-90d5eb1ed512.png)
