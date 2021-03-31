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

//Pin genomen, zijn globale waardes gekozen om niet de hele tijd parameters mee te geven.
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
    //De led pulse wordt hier aangeroepen. Door de verschillende golven kan je de snelheid aanpassen.
    //Je kunt het testen met een ledje.
    for (;;){
        digitalWrite (led, HIGH) ; delay (1) ;
        digitalWrite (led,  LOW) ; delay (low) ;
    }
}

void sturen() {
    //Dit is een grote functie die het sturen bekijkt en reageert op WASD.
    static int draaien = 1500;

    int ch = 0;
    
    //We gebruiken getch() om niet de hele tijd een Enter in te toetsen. Hiervoor moet een extra window komen en de onderstaande regels.
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);

    thread ledThread (led_pwm, ledpin);

    cout << "Press Q to quit\n";
    do {
        if ((ch = getch()) != ERR) {
            switch (ch) {
                    //Gaat harder, gaat niet vanzelf weer zachter.
                    case 'W':
                    case 'w':
                        if(0 < low){
                            low -= 2;
                        }else{
                            printw("Pepernoten kind dit is het limiet...\n");
                        }
                    break;
                    //stuurt naar links
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
                    //Gaat zachter, kan niet achteruit.
                    case 's':
                    case 'S':
                        if(low < 20){
                            low += 2;
                        }else{
                            printw("Pepernoten kind dit is het limiet...\n");
                        }
                    break;
                    //Gaat naar rechts
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
    //Als je stopt dan gaat alles weer naar een basis stand.
    draaien = 1500;
    servoPulse(servo, draaien);
    low = 20;
    ledThread.detach();
    endwin();
//    exit(0);
}
int main(){
    //Pinnen worden geset.
    wiringPiSetup ();
    pinMode (servo, OUTPUT);
    pinMode (ledpin, OUTPUT);

    while (true) {
        //Keuze menu als je het programma start. Kunnen extra's aan als bijvoorbeeld ledstrip regelen of leds.
        string invoer = "";
        cout << "Wat wil je doen?\n";
        getline(cin, invoer);
        if (invoer == "sturen") {
            cout << "Veel stuur plezier!\n";
            sturen();
        }
        else if (invoer == "quit"){
            //Als je klaar bent met de boot sturen.
            cout << "Bye bye babe ;)\n";
            break;
        }
        else {
            cout << "Heb nog geen functie hiervoor\n";
        }
    }
}
