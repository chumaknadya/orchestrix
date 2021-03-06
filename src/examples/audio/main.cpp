//
// Created by zulus on 21.04.17.
//
#include <iostream>
#include <audio/AudioData.h>
#include <audio/AudioManager.h>
#include <audio/AudioPlayer.h>
#include <graphic/ConsoleEqualizer.h>

//#define _DEBUG
using namespace std;

void exampleSound() {
    string filename1 = "res/21pilots.wav";
    AudioData *sound1 = AudioData::load(filename1);
    AudioManager *manager = AudioManager::init(1, 8);
    AudioPlayer *player1 = new AudioPlayer(manager, sound1, 1);
    cout << player1->toString() << endl;
    player1->play();
    while (true) {
        char input;
        cin >> input;
        if (input == '1') {
            player1->play();
        } else if (input == '2') {
            player1->pause();
        } else if (input == '3') {
            player1->rewind();
        } else if (input == '4') {
            player1->stop();
        } else if (input == '5') {
            break;
        }
    }
    delete player1;
    delete manager;
    delete sound1;
}

void exampleEQ() {
    string filename1 = "res/ppl.wav";
    AudioData *sound1 = AudioData::load(filename1);
    cout << sound1->toString() << endl;
    ConsoleEqualizer eq(sound1, 20, 40);
    eq.exec();
}

int main(void) {
    exampleSound();

}
