/*****************************************************
 *  DHT22 Non-blocking Library
 *  File:   CDHT22_nonblocking.h
 *  Date:   2016_04_15
 *  Author: Stephen Minakian
 *  Version:0.0.1
 *****************************************************/

#include "DHT22_NONBLOCKING.h"

DHT22::DHT22(uint8_t pin) {
    Serial1.begin(115200);
    _pin = pin;
}

void DHT22::begin(void){
    readDHT22();
}

void DHT22::readDHT22(void){
    detachInterrupt(_pin);
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, 0);
    int low_time = micros();
    for(;;){
        if(micros() - low_time >= 1000)break;
    }
    pinMode(_pin, INPUT_PULLUP);
    attachInterrupt(_pin, &DHT22::nextBit, this, CHANGE, 1);
}

float DHT22::readTemp(void){
    return ((float)tempC)/10;
}

float DHT22::convertCtoF(float c){
    return c * 9 / 5 + 32;
}

float DHT22::readHumidity(void){
    return ((float)humidity)/10;
}

void DHT22::nextBit(void){
    char statePin = digitalRead(_pin);
    if(statePin){
        micTimeStart = micros();
    } else {
        duration[position] = micros() - micTimeStart;
        if(duration[position]<77){
            position++;
            if(position >= 40){
                position = 0;
                setFlag(true);
            }
        }
    }
}

float DHT22::getRH(void){
    return readHumidity();
}

float DHT22::getTemp(void){
    return readTemp();
}

float DHT22::getTemp(bool f){
    if(f){
        return convertCtoF(readTemp());
    } else {
        return readTemp();
    }
}

void DHT22::completeData(void){
    int i;
    for(i = 0; i < 40; i++){
        if(i < 16){
            humidity <<= 1;
            humidity |= duration[i]>40?1:0;
        } else if(i < 32){
            tempC <<= 1;
            tempC |= duration[i]>40?1:0;
        } else {
            check <<= 1;
            check |= duration[i]>40?1:0;
        }
    }
}

bool DHT22::getFlag(void){
    return flag;
}

void DHT22::setFlag(bool status){
    flag = status;
}