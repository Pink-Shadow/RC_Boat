//
// Created by Isaak van Luijk on 22/03/2021.
//
#include <wiringPi.h> //Voor de RPI pinnen
#include <iostream> // Voor de cout
#include <thread> // Voor de PWM moter, processen naast elkaar draaien

#include <ncurses.h> // is voor Linux getch()
#include <stdlib.h> // De de WASD
//#include <signal.h> // De de WASD

#include <unistd.h> //Voor de sleep en usleep

using namespace std;

int low=20;
const int ledpin = 1;
int servo = 0;

void servoPulse(int pin,float slaap){
    //Dit is de de pulse voor de Servo aan te sturen.
    for(int i = 0; i < 3; i++) {
        digitalWrite(pin, HIGH);
        usleep(slaap);
        digitalWrite(pin, LOW);
        delay(200);
    }
}

void led_pwm(const int led){
    for (;;){
        digitalWrite (led, HIGH) ; delay (1) ;
        digitalWrite (led,  LOW) ; delay (low) ;
    }
}

void sturen() {
    static int draaien = 1500;

    int ch = 0;

    initscr();
    cbreak();
    nodelay(stdscr, TRUE);

    thread ledThread (led_pwm, ledpin);

    cout << "Press Q to quit\n";
    do {
        if ((ch = getch()) != ERR) {
            switch (ch) {
                    case 'W':
                    case 'w':
                        if(0 < low){
                            low -= 2;
                        }else{
                            printw("Pepernoten kind dit is het limiet...\n");
                        }
                    break;
                    case 'A':
                    case 'a':
                        if(draaien <= 500){
                            printw("Kan niet verder oen\n");
                        }
                        else {
                            servoPulse(servo, draaien - 200);
                            draaien -= 200;
                        }
                    break;
                    case 's':
                    case 'S':
                        if(low < 20){
                            low += 2;
                        }else{
                            printw("Pepernoten kind dit is het limiet...\n");
                        }
                    break;
                    case 'D':
                    case 'd':
                        if(draaien >= 2500){
                            printw("Denk is aan het limiet dwerg\n");
                        }
                        else {
                            servoPulse(servo, draaien+200);
                            draaien += 200;
                        }
                    break;
                }
        }
    }
    while (ch != 'Q' && ch != 'q');
    draaien = 1500;
    servoPulse(servo, draaien);
    low = 20;
    ledThread.detach();
    endwin();
//    exit(0);
}
int main(){
    wiringPiSetup ();
    pinMode (servo, OUTPUT);
    pinMode (ledpin, OUTPUT);

    while (true) {
        string invoer = "";
        cout << "Wat wil je doen?\n";
        getline(cin, invoer);
        if (invoer == "sturen") {
            cout << "Veel stuur plezier!\n";
            sturen();
        }
        else if (invoer == "quit"){
            cout << "Bye bye babe ;)\n";
            break;
        }
        else {
            cout << "Heb nog geen functie hiervoor\n";
        }
    }
}