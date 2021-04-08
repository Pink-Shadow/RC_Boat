//
// Created by Isaak van Luijk on 08/04/2021.
//

#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include "AAmuziek.hpp"
#include <chrono> // Voor de microsecconds
using namespace std;

//chrono instellingen.
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

float afstand(int echo_pin, int trig_pin){
    wiringPiSetup();
    pinMode(echo_pin, INPUT);
    pinMode(trig_pin,OUTPUT);

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