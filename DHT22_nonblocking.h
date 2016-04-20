/*****************************************************
 *  DHT22 Non-blocking Library
 *  File:   DHT22_nonblocking.h
 *  Date:   2016_04_20
 *  Author: Stephen Minakian
 *  Version:0.0.1
 *****************************************************/

#ifndef _DHT22_NONBLOCKING_H
#define _DHT22_NONBLOCKING_H

#include "application.h"

class DHT22 {
    private:
        // Variables
        uint8_t _pin;
        unsigned long micTimeStart = 0;
        unsigned long duration[40];
        char position = 0;
        bool flag = false;
        uint16_t humidity;
        uint16_t tempC;
        uint8_t check;
        
        // Functions
        void readDHT22(void);
        float readTemp(void);
        float readHumidity(void);
        float convertCtoF(float);

    public:
        // Functions
        DHT22(uint8_t pin);
        void begin(void);
        void nextBit(void);
        float getRH(void);
        float getTemp(void);
        float getTemp(bool f);
        void completeData(void);
        bool getFlag(void);
        void setFlag(bool status);
};

#endif