//
//

#include <wiringPi.h>
#include <iostream>
#include <string>
#include <thread>
#include <ncurses.h>
#include <stdio.h>
int low=18;

void led_pwm(const int led){
	for (;;){
        	digitalWrite (led, HIGH) ; delay (1) ;
        	digitalWrite (led,  LOW) ; delay (low) ;
    	}
}


int main (void)
{
    const int ledpin = 1;
    std::string input = "";
    //char invoer;
    wiringPiSetup ();
    pinMode (ledpin, OUTPUT);
    std::thread led (led_pwm, ledpin);
    
    //while(getch() == -1){ invoer = getch(); cbreak(); std::cout << invoer << std::endl;}
    while(getline(std::cin, input)){
	if (0 < low && input == "w"){
		low -= 2;
	}
	else if(low < 18 && input == "s"){
		low += 2;
	}
	else{std::cout << "Je hebt het limiet berijkt!" << std::endl;}
    }
    
    
    return 0 ;
}
