#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include <ncurses.h>
#include <stdio.h>
#include <signal.h>
int low=18;
const int ledpin = 1;


void led_pwm(){
	for (;;){
        	digitalWrite (ledpin, HIGH) ; delay (1) ;
        	digitalWrite (ledpin,  LOW) ; delay (low) ;
    	}
}


int varen(){
	int ch = 0;
	//signal(SIGINT, quit);

	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	std::thread led (led_pwm);

	do
	{
	
        if ((ch = getch()) != ERR){
		if (ch == 'w' || ch == 's'){
			if(0 < low && ch == 'w'){low -= 2;}
			else if(low < 18 && ch == 's'){low += 2;}
			else {printw( "Je hebt het limiet berijkt!\n");}
		}
		else {printw("Dit karakter doet niks.\n"); }
	}
	}
	while(ch != 'Q' && ch != 'q');
	
	led.detach();
		
	
	endwin();
	digitalWrite(ledpin, LOW);

	return 0;

}

int main()
{
    wiringPiSetup ();
   
    std::string input = "";
    pinMode (ledpin, OUTPUT);
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
