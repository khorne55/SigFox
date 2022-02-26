
#include <Wire.h>
#include <SmeSFX.h>
#include <Arduino.h>



char helloMsg[5]= {'H','e', 'l', 'l', 'o'};
bool messageSent;

// the setup function runs once when you press reset or power the board
void setup() {
    delay(6000);
    SerialUSB.begin(115200);
    sfxAntenna.begin(115200);
    int initFinish=1;

    SerialUSB.println("SFX in Command mode");
    sfxAntenna.setSfxConfigurationMode(); // enter in configuration Mode
}

void loop() {
    do {
        uint8_t answerReady = sfxAntenna.hasSfxAnswer();
        if (answerReady){
            switch (initFinish){
            case 1:                                
                SerialUSB.println("SFX in Data mode");
                sfxAntenna.setSfxDataMode();
                initFinish++;
                break;

            case 2:
                initFinish++; // exit
                break;
            }
        }
    } while (initFinish!=3);

    SerialUSB.println("sending Hello over the network");
    // send Hello on the air
    sfxAntenna.sfxSendData(helloMsg, strlen((char*)helloMsg));
}
