# RC_Boat
RC_Boat for a school project.

Om ncurses te installen moet je de volgende command doen:
sudo apt-get install libncurses5-dev libncursesw5-dev

Om executable van getch te maken:
g++ -Wall -o <naam van executable> getch.cpp muziek.hpp music2.cpp -lwiringPi -lpthread -lncurses

De speaker gebruikt wiringPin 9


## De besturing
De boot wordt bestuurd met de w,a,s,d toetsen.
```
De w toets zet de motor harder aan.
De s toets zet de motor zachter.
De a toets stuurt de boot naar links.
De d toets stuurt de boot naar rechst.
De q en Q toets schakel de besturing uit.
```
