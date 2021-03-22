//
// Created by Isaak van Luijk on 16/03/2021.
//
#include <ncurses.h> //Snellere invoer
#include <iostream> //Tekst
#include <wiringPi.h> //Voor de Pins, RPI
#include <unistd.h> //Voor de sleep en usleep

using namespace std;

void sturen(int pin,float slaap){
    cout << slaap << endl;
    for(int i = 0; i < 3; i++) {
        digitalWrite(pin, HIGH);
        usleep(slaap);
        digitalWrite(pin, LOW);
        delay(200);
//        delay(slaap);
    }
}

int main(){
    static float draaien = 1500;
//    wiringPiSetupGpio();
    wiringPiSetup ();
    pinMode (9, OUTPUT);
    pinMode (0,PWM_OUTPUT);
    char invoer = wgetch(); //Dit werkt nu niet/
    cout << "Druk q in om te stoppen.\n";
    bool status = true;
    string move = "";
    while(status == 1){
        cin >> invoer;
        if(invoer == 'a'){
            cout << "Naar links \n";
            if(draaien <= 500){
                cout <<"Kan niet verder\n";
            }
            else {
                sturen(0, draaien - 200);
                draaien -= 200;
            }
        }
        else if(invoer == 'd'){
            cout << "Naar rechts: \n";
            if(draaien >= 2500){
                cout <<"Kan niet verder\n";
            }
            else {
                sturen(0, draaien+200);
                draaien += 200;
            }
        }
        else if(invoer == 'q'){
            break;
        }
        cin.clear();
        cin.ignore(10000,'\n');
    }
}