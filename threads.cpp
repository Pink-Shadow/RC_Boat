#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <thread>
using namespace std;

void servo(){
	int pin = 9;
	pinMode(pin, OUTPUT);
	int slaap = rand()%(2500 - 500 + 1) + 500;
	for(int i = 0; i < 3; i++){
		digitalWrite(pin, HIGH);
		usleep(slaap);
		digitalWrite(pin, LOW);
		delay(200);
	}
}

int main(){
	wiringPiSetup();
	
	
	const int input_pin = 29;
	
	while(true){
		delay(5);
		if(digitalRead(input_pin) == HIGH){
			cout << "Ik ben ingedrukt" << endl;
			thread moter(servo);
			moter.join();
			}
		}
}
