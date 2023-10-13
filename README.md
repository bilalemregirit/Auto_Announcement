# OPEN SOURCE - WORK IN PROGRESS
Youtube Video of the Project: https://www.youtube.com/watch?v=9ex4jSiTSgA&t=38s

THE LATEST VERSION OF THE PROJECT
![Ekran görüntüsü 2023-10-05 132101](https://github.com/bilalemregirit/Auto_Announcement_system/assets/60060887/8d35b672-1630-455d-8e45-37a65f3aa210)


# HOW IT WORKS

    This is a project that automizes the announcements of the public transportations with the GPS coordinates. 
And This is how it works: First i want to start with the hardware of the device.
![image](https://github.com/bilalemregirit/Auto_Announcement/assets/60060887/eaf463e3-062e-45a4-a03c-ce7876c2a655)
The device consists of several components. The Dfplayer Mini is used for making announcements. It has an SD card socket to store audio files and provides audio output to the Aux port upon receiving a specific signal. The Arduino Pro Micro stores location data such as longitude and latitude, and it receives GPS signals from the GPS module. When the device is in a specific area, it transmits a signal to the DfPlayer. The GPS module used is the GPS Neo 6m, which includes an antenna. The device also includes a TouchScreen Display called Nextion, which comes with a Windows application for easy customization. Lastly, there is a Dip switch between the microcontroller and the display. This switch allows you to disconnect the display when uploading code to the microcontroller.
![beyas](https://github.com/bilalemregirit/Auto_Announcement/assets/60060887/d082c807-aecf-4676-84d3-80e717586295)


    The device contains a common GPS module that provides an estimated location. Firstly, the device waits for user input regarding the intended voyage. Once the user confirms the voyage, the device starts to determine its own location. During this process, the GPS module receives and transmits values from satellites, such as latitude and longitude, to the microcontroller. The microcontroller contains a set of coordinate values that represent specific areas in the work location of the vessel.(you can also reach all the coordinates that i used in bosphorus in the link: rb.gy/ims96) ![image](https://github.com/bilalemregirit/Auto_Announcement/assets/60060887/a27e065c-3d33-49e2-a315-e24402321df5) When the microcontroller detects that the device is within the designated area, it sends a signal to the Df player mini with the specific media file number. The player then starts to play the corresponding media file this is how this device works. Additionally the device is capable of handling announcements that loop at specific intervals. For example, it can play "no smoking" announcements every 30 minutes.


The early beggining of this project includes a tiny OLED screen (SSD1306) with arduino nano and several basic buttons. Older versions: 
Menu Demo (SSD1306): https://www.youtube.com/watch?v=d2qRUfzXhB8&t=34s 
Menu Demo (ST7735) : https://www.youtube.com/watch?v=dHNRrd75gP8


Schematic of the project:
![gps_anons](https://user-images.githubusercontent.com/60060887/175570052-f531bdab-98e3-444b-9662-8625886b9e28.png)

BASİC PCB DESİGN OF CARD:
![untitled2](https://user-images.githubusercontent.com/60060887/175928738-212f4597-2feb-4142-bfca-90d5eb1ed512.png)
