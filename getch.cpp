#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include <ncurses.h>
#include <stdio.h>

int low=18;
const int ledpin = 1;


void led_pwm(const int led){
	for (;;){
        	digitalWrite (led, HIGH) ; delay (1) ;
        	digitalWrite (led,  LOW) ; delay (low) ;
    	}
}




int varen(){
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);

	std::thread led (led_pwm, ledpin);

	while(1)
	{
	
        if ((ch = getch()) != ERR){
		if (ch == 'q'){break;}
		if (ch == 'w' || ch == 's'){
			else if(0 < low && input == "w"){low -= 2;}
			else if(low < 18 && input == "s"){low += 2;}
			else {std::cout << "Je hebt het limiet berijkt!" << std::endl;}
		}
		else {std::cout << "deze optie bestaat niet" << std::endl;}
	}
	led.detach();
	endwin();
	return 0;

}

int main()
{
    wiringPiSetup ();
    int ch;
   
    std::string input = "";
    pinMode (ledpin, OUTPUT);
    std::cout << "whatcha wanna do?" << std::endl;
    while(1){
	if(getline(std::cin, input) == "varen"){
		varen();
	}
	else if(getline(std::cin, input) == "exit"){
		break;
	}
	else {std::cout << "verkeerde input bitch" << std::endl;}
    }
    return 0;
}
