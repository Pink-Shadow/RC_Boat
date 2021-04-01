//JE MOET DE VOLGENDE FILES ERBIJ HEBBEN!!!!
//muziek.hpp
//music2.cpp

#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include <ncurses.h>
//#include <stdio.h>
//#include <signal.h>
#include <unistd.h>
#include "muziek.hpp"

using namespace std;

//Om execudeble van te maken:
//g++ -Wall -o <naamIets> <bestandNaam>.cpp muziek.hpp music2.cpp -lwiringPi -lpthread -lncurses

int power = 100;
const int ledpin = 1;
const int servo = 26;
static int draaien = 1500;
//speaker gebruikt wiringPin 9!!!

void servoPulse(int pin,float slaap){
    //Dit is de de pulse voor de Servo aan te sturen.
    digitalWrite(pin, HIGH);
    usleep(slaap);
    digitalWrite(pin, LOW);
    delay(200);
}


int varen(){
    int ch = 0;

    pinMode (ledpin, PWM_OUTPUT);
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);

    do{
        if ((ch = getch()) != ERR){
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd'){

                if(power < 1020 && ch == 'w') pwmWrite(ledpin, power+=40);

                else if(100 <= power && ch == 's') pwmWrite(ledpin, power-=40);

                else if(draaien >= 500 && ch == 'a') servoPulse(servo, draaien-=200);

                else if(draaien <= 2500 && ch == 'd') servoPulse(servo, draaien+=200);

                else {printw( "Pepernoten kind dit is het limiet...\n");}
            }
            else {
                printw("Dit karaktertje doet niks :(\n");
            }
        }
    }

    while(ch != 'Q' && ch != 'q');

    draaien = 1500;
    servoPulse(servo, draaien);
    pinMode (ledpin, OUTPUT);
    pinMode (servo, OUTPUT);
    endwin();
    return 0;
}

int main(){
    wiringPiSetup ();
    string input = "";
    cout << "Whatcha wanna do?" << endl;
    while(getline(cin, input)){
        if(input == "varen"){
            cout << "Veel stuur plezier!\n";
            play("Dark Father Theme");
            varen();
        }
        else if(input == "zinken"){
            cout << "Owhjeeej\n";
            play("Titanic");
        }
        else if(input == "exit"){
            cout << "Bye bye babe ;)\n";
            break;
        }
        else {cout << "Verkeerde input Dwerg!!" << endl;}
        cout << "Whatcha wanna do?" << endl;
    }
    return 0;
}
