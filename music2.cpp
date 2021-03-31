//
// Created by Isaak van Luijk on 24/03/2021.
//
#include <iostream>
#include <wiringPi.h>
#include <vector>
#include "muziek.hpp"
#include <string>
using namespace std;

int speakerPin = 9;


void playTone(int tone, int duration){
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

void playNote(string note, int duration){
    vector<string> names = {"c","c#","d","d#","e","f","f#","g","g#","a","a#","b","C"};
    int tones[] = {1915, 1800, 1700, 1600, 1519, 1432, 1350, 1275, 1200,1136, 1075, 1014, 956};

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}

void loop(vector<string> notes, int beats[], int tempo,int length){
    for (int i = 0; i < length; i++) {
        if (notes[i] == " ") {
            delay(beats[i] * tempo); // rest
        } else {
            playNote(notes[i], beats[i] * tempo);
        }
        // pause between notes
        delay(tempo / 2);
    }
}

void play(string song){
    //char notes[] = "ccggaagffeeddc "; // a space represents a rest
    //int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };

//    char notesStarwars[] = "cgfedcg"
//                           "fedcg"
//                           "fefd";
//    int beatsStarwars[] = {2,2,1,1,1,2,2,1,1,1,2,2,1,1,1,4};
    int tempo = 200; //300 orginale

    //Bron: https://mypianonotes.com/my-heart-will-go-on/
    vector<string> titanicNotes = {"e","f#","f#","g#","g#","f#","e","f#","b", // intro
                                   "a","g#","e","c#","b",// intro
                                   "e","f#","f#","g#","a","g#","f#","e","g#","f#","g#","f#","b",//intro
                                   "g#","b","b","c#","b","f#", // intro

                                   "e","e","e","e","d#","e", // every night in my dreams
                                   "e","d#","e","f#","g#","f#", // I see you, I feel you
                                   "e","e","e","e","d#","e","e","b", // That is how I know you go on
                                   "e","e","e","d#","e", // Far across the distance
                                   "e","d#","e","f#","g#","f#", //And the spaces between us
                                   "e","e","e","e","d#","e","e","b", // You have come to show you go on
                                   "e","f#","b","b","a","g#","f#", // Near far wherever you are
                                   "g#","a","g#","f#","e","d#","e","d#","c#", // I believe that the heart does go on
                                   "e","f#","b","b","a","g#","f#", // One more you open the door
                                   "g#","a","g#","f#","e","d#", // And you're here in my heart
                                   "e","d#","d#","e","f#","g#","f#", // And my heat will go on and on

                                   "g#","a","g#","f#","e","g#","f#","g#","f#","b", // tussenstuk
                                   "g#","b","b","c#","b","f#", // tussenstuk

                                   "e","e","e","e","d#","e", // Love can touch us one time
                                   "c#","c#","e","f#","g#","f#", // And last for a lifetime
                                   "e","e","e","e","d#","e","e","b", // and never let go til were gone
                                   "e","e","e","e","d#","e", // Love was when I loved you
                                   "e","d#","e","f#","g#","f#", // one true time I hold to
                                   "e","e","e","e","d#","e","f#","b",//In my life well always go on
                                   "e","f#","b","b","a","g#","f#", // near, farm wherever you are
                                   "g#","a","g#","f#","e","d#","e","d#","c#", // I believe that the heart does go on
                                   "e","f#","b","b","a","g#","f#", // One more you open the door
                                   "g#","a","g#","f#","e","d#", // And youre here in my heart
                                   "e","d#","d#","e","f#","g#","f#", // And my heart will go on and on

                                   "e","f#","f#","g#","f#","g#","f#","e","f#","b",// tussenstuk
                                   "a","g#","e","c#", //tussenstuk
                                   "e","f#","f#","g#","a","g#","f#","e","g#","f#","b", //tussenstuk
                                   "g#","b","c#","d#","e","f#",// tussenstuk

                                   "g#","a#","d#","d#","c#","c","a#",//Youre here, there nothing i fear
                                   "c","c#","c","a#","g#","g","g#","g","f",// And I know that my heart will go on
                                   "g#","a#","d#","d#","c#","c","a#", //Well stay forever this way
                                   "c","c#","c","a#","g#","g", // You are safe in my heart
                                   "g#","g","g","g#","a#","c","a#","g#" // And my heart will go on and on
    };
    int titanicBeats[] = {2,2,2,8,1,1,2,2,6,// 9 notes intro
                          2,1,2,8,6,// 5 notes intro
                          2,2,2,5,1,1,1,1,1,1,1,2,6,// 13 notes intro
                          2,2,2,6,3,8,// 6 notes intro

                          3,1,2,2,2,3,//6 notes every night in my dreams
                          2,2,3,2,3,3,//6 notes I see you, I feel you
                          3,1,2,2,2,3,2,8, //8 notes That is how I know you go on
                          3,2,2,2,3,//5 notes Far across the distance
                          1,2,3,2,3,3,//6 notes And the spaces between us
                          3,1,2,2,2,3,1,8,//8 notes You have come to show you go on
                          4,4,2,3,2,1,3,//7 notes Near far wherever you are
                          2,2,3,1,1,2,2,1,6,//9 notes I believe that the heart does go on
                          4,4,2,3,2,1,3,//7 notes One more you open the door
                          2,2,4,2,2,2, //6 notes And you're here in my heart
                          3,2,2,3,2,3,3,//7 notes And my heat will go on and on

                          7,1,1,1,1,1,1,1,1,4,//10 notes tussenstuk
                          1,1,2,4,2,8,//6 notes tussenstuk

                          3,1,2,2,2,3, //6 notes Love can touch us one time
                          1,2,3,2,4,4,// 6 notes And last for a lifetime
                          3,1,2,2,2,3,1,6,//8 notes and never let go til were gone
                          3,1,2,2,2,3,//6 notes Love was when I loved you
                          1,2,3,2,3,3,//6 notes one true time I hold to
                          3,1,2,2,2,3,2,6,//8 notes In my life well always go on
                          6,5,2,4,2,1,4,//7 notes near, farm wherever you are
                          3,1,4,1,1,2,4,1,8,//9 notes I believe that the heart does go on
                          6,5,2,3,2,1,4, //7 notes One more you open the door
                          2,2,4,2,2,2,//6 notes And youre here in my heart
                          3,2,2,3,2,4,3,//7 notes And my heart will go on and on

                          2,2,2,4,1,1,1,2,1,5,//10 notes tussenstuk
                          1,2,2,6,//4 notes tussenstuk
                          2,2,2,4,1,1,1,1,1,1,4,//11 notes tussenstuk
                          2,1,5,3,4,4,//6 notes tussenstuk

                          8,6,3,4,3,1,5,//7 notes Youre here, there nothing i fear
                          2,1,5,3,1,4,3,1,5,//9 notes And I know that my heart will go on
                          8,5,3,5,3,2,5,//7 notes Well stay forever this way
                          3,3,5,3,3,3,//6 notes You are safe in my heart
                          4,3,3,5,1,5,3,7}; //8 notes And my heart will go on and on
    // lengte = the number of notes
//    vector<string> toonLader = {"c","c#","d","d#","e","f","f#","g","g#","a","a#","b","C"};
//    int toonLaderBeats[] = {20,20,20,20,20,20,20,20,20,20,20,20,20};
    wiringPiSetup();
    pinMode(speakerPin, OUTPUT);
//    loop(toonLader,toonLaderBeats,tempo,toonLader.size());
    if (song == "Titanic"){
        loop(titanicNotes,titanicBeats,tempo,titanicNotes.size());
    }
    else{
        cout << "Heb die song niet\n";
    }
    cout << "En finito!\n";
}