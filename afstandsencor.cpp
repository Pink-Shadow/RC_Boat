//

// Created by Isaak van Luijk on 01/04/2021.

//



#include <iostream>

#include <wiringPi.h>

#include <unistd.h>

#include "muziek.hpp"

#include <chrono> // Voor de microsecconds



using namespace std;



//chrono instellingen.

using std::chrono::duration_cast;

using std::chrono::microseconds;

using std::chrono::seconds;

using std::chrono::system_clock;



//Kunnen gewoon aangepast worden.

const int trig_pin1 = 5;

const int echo_pin1 = 4;



float afstand(int echo_pin, int trig_pin){

    digitalWrite(trig_pin1, HIGH);

    usleep(10);

    digitalWrite(trig_pin1, LOW);

    auto starttime = 0;

    auto stoptime = 0;



    while(digitalRead(echo_pin1) == LOW){

        starttime = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

    }

    while(digitalRead(echo_pin1) == HIGH){

        stoptime = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

    }

    float time_elapsed = stoptime - starttime;

    //krijg micrometers, daarom nog de gedeeld door hoog getal

    float distance = time_elapsed * 17150 / 1000000;



    return distance;



}



//int sr04_output(){

//    wiringPiSetup();

//    pinMode(trig_pin1, OUTPUT);

//    pinMode(echo_pin1, INPUT);



//    while(1) {

//        cout << "Afstand =  " << afstand(trig_pin1, echo_pin1) << "cm" << endl;

//        delay(600);

//    }

//    return 0;

//}



