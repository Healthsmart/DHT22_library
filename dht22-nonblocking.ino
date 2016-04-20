/*****************************************************
 *  DHT22 Non-blocking demo application
 *  File:   dht22-nonblocking.ino
 *  Date:   2016_04_20
 *  Author: Stephen Minakian
 *  Version:0.0.1
 *
 *  Description:
 *    Simple non-blocking demonstartion app that
 *	  reads the DHT22 and outputs the RH, TempC, 
 *	  and TempF.
 *****************************************************/

#include "DHT22_NONBLOCKING.h"

#define DHT22_PIN D1

DHT22 rhTempSensor(DHT22_PIN);

void setup() {
    rhTempSensor.begin();
}

void loop() {
    if(rhTempSensor.getFlag() == true){
        rhTempSensor.setFlag(false);
        rhTempSensor.completeData();
        Serial1.println("Relative Humidity: " + String(rhTempSensor.getRH()) + "%");
        Serial1.println("Temperature:       " + String(rhTempSensor.getTemp()) + "C");
        Serial1.println("Temperature:       " + String(rhTempSensor.getTemp(true)) + "F");
    }
}