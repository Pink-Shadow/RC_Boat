# RC_Boat
RC_Boat voor een school project.

Om van ncurses gebruik te kunnen maken, moet je eerst 2 libraries installeren d.m.v.\
`sudo apt-get install libncurses5-dev libncursesw5-dev`

Om getch.cpp te compileren moet je het volgende commando gebruiken:\
`g++ -Wall -o [naam van executable] AAreboot.cpp AAafstandsencor.cpp AAmuziek.hpp AAmusic2.cpp -lwiringPi -lpthread -lncurses`

De motor gebruikt wiringPin:   1\
De servo gebruikt wiringPin:   26\
De speaker gebruikt wiringPin: 9
De linker SR04 gebruikt wiringPin: echo 4, trig 5
De rechter SR04 gebruikt wiringPin: echo 11, trig 10
De camera wordt in de camera klip gedaan van de RPI


## De besturing
De boot wordt bestuurd met de w,a,s,d toetsen.
```
De w toets zet de motor harder aan.
De s toets zet de motor zachter.
De a toets stuurt de boot naar links.
De d toets stuurt de boot naar rechst.
De q en Q toets schakel de besturing uit.
```
