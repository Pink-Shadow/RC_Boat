//JE MOET DE VOLGENDE FILES ERBIJ HEBBEN!!!!
//muziek.hpp
//music2.cpp

#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include <ncurses.h>
#include <unistd.h>
#include "muziek.hpp"

using namespace std;

// waardes voor de servo en motor
int power = 100;
int draaien = 1500;

// pin definitie
const int motorpin = 1;
const int servo = 26;

//sr04 pins
const int trig_pin1 = 5;
const int echo_pin1 = 4;

const int trig_pin2 = 10;
const int echo_pin2 = 11;

//Dit is de pulse functie om de Servo aan te sturen.
void servoPulse(int pin,float slaap){
    digitalWrite(pin, HIGH);
    usleep(slaap);
    digitalWrite(pin, LOW);
    delay(200);
}
//Dit zijn de functies voor de sensoren de afstand te meten.
void sensor_links(){
    while (true){
	if (afstand(echo_pin1,trig_pin1) <= 25){
	printw("begin de boot te sturen"); }
	else if(afstand(echo_pin1,trig_pin1) <= 50){ printw("ga eens ff uitwijken");
	}
    }
}


void sensor_rechts(){
    while (true){

	if (afstand(echo_pin2, trig_pin2) <= 25){
	printw("begin de boot te sturen");}
	else if(afstand(echo_pin2,trig_pin2) <= 50) {printw("ga eens ff uitwijken");
	}
    }
}

// De functie om de boot te besturen met "wasd" 
void varen(){
    int ch = 0;
   
    pinMode (motorpin, PWM_OUTPUT);	// pin setup
    pinMode (trig_pin1, OUTPUT);
    pinMode (echo_pin1, INPUT);
    pinMode (trig_pin2, OUTPUT);
    pinMode (echo_pin2, INPUT);
     
    thread links(sensor_links);
    thread rechts(sensor_rechts);
    
    initscr();				// start screen
    cbreak();
    nodelay(stdscr, TRUE);

    do{
        if ((ch = getch()) != ERR){
            if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd'){
		
		// commando's voor de bijbehorende letters
                if(power < 1020 && ch == 'w') pwmWrite(motorpin, power+=40);
                else if(100 <= power && ch == 's') pwmWrite(motorpin, power-=40);

                else if(draaien >= 500 && ch == 'a') servoPulse(servo, draaien-=200);
                else if(draaien <= 2500 && ch == 'd') servoPulse(servo, draaien+=200);

                else {printw("Dit is het limiet\n");} // error als je aan het limiet zit van de snelheid of angle
            }
            else {
                printw("Deze toets doet niks :(\n"); // error als je een verkeerde toest indrukt
            }
        }
    }

    // Om de besturing uit te schakelen
    while(ch != 'Q' && ch != 'q');
    
    // reset alles
    draaien = 1500;
    rechts.detach();
    links.detach();
    
    servoPulse(servo, draaien);
    pinMode (motorpin, OUTPUT);
    pinMode (servo, OUTPUT);
    endwin(); // sluit de window
}



// Start de boot
int main(){
    wiringPiSetup ();
    pinMode(9, OUTPUT);
    string input = "";

    thread* music = nullptr;

    // vraag om invoer
    cout << "Wat wil je doen met Reboot?\n" << endl;
    cout << "1)\tvaren" << endl;
    cout << "2)\tzinken" << endl;
    cout << "3)\texit\n" << endl;
   
    while(getline(cin, input)){

	// verwerk de invoer
	if (input == "varen" || input == "1"){
	    
	}
        if(input == "varen" || input == "1"){
            cout << "Veel stuur plezier!\n" << endl;
 	    varen();
        }
        else if(input == "zinken" || input == "2"){
	    cout << "Owhjeeej\n" << endl;    
	    music = new thread(play, "Titanic");
        }
        else if(input == "exit" || input == "3"){
	    break;
	}
        else {cout << "Er is geen input met die naam" << endl;}
        cout << "Wat wil je doen met Reboot?" << endl;
	cout << "1)\tvaren" << endl;
    	cout << "2)\tzinken" << endl;
    	cout << "3)\texit\n" << endl;
    }
    music->detach();
    digitalWrite(9, LOW);
    cout << "Done!" << endl;

    return 0;
}
