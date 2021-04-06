//
// Created by Isaak van Luijk on 01/04/2021.
//

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>

#include <chrono> // Voor de microsecconds

using namespace std;

//chrono instellingen.
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

//Kunnen gewoon aangepast worden.
const int trig_pin = 5;
const int echo_pin = 4;

float afstand(){
    digitalWrite(trig_pin, HIGH);
    usleep(10);
    digitalWrite(trig_pin, LOW);
    auto starttime = 0;
    auto stoptime = 0;

    while(digitalRead(echo_pin) == LOW){
        starttime = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    }
    while(digitalRead(echo_pin) == HIGH){
        stoptime = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    }
    float time_elapsed = stoptime - starttime;
    //krijg micrometers, daarom nog de gedeeld door hoog getal
    float distance = time_elapsed * 17150 / 1000000;

    return distance;

}

int main(){
    wiringPiSetup();
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);

    while(1) {
        cout << "Afstand =  " << afstand() << "cm" << endl;
        delay(600);
    }
    return 0;
}