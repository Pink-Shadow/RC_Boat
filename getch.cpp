#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include <ncurses.h>
//#include <stdio.h>
//#include <signal.h>
#include <unistd.h>


int power = 100;
const int ledpin = 1;
const int servo = 26;
static int draaien = 1500;


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
		
				else {printw( "Je hebt het limiet berijkt!\n");}
			}
			else {
				printw("Dit karakter doet niks.\n"); 
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
   
    std::string input = "";
    std::cout << "whatcha wanna do?" << std::endl;
    while(getline(std::cin, input)){
	if(input == "varen"){
		varen();
	}
	else if(input == "exit"){
		break;
	}
	else {std::cout << "verkeerde input" << std::endl;}
    }
    return 0;
}
