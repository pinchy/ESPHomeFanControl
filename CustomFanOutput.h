#include "esphome.h"
using namespace esphome;

#define PIN_FAN_OFF 33
#define PIN_FAN_LOW 15
#define PIN_FAN_MED 26
#define PIN_FAN_HIGH 25
#define PIN_LED 23
#define PIN_ADDR0 32
#define PIN_SW0 36


#define PIN_HOLD_TIME 250

class CustomFanOutput : public Component, public FloatOutput 
{
    public:
    	void setup() override 
    	{
    		pinMode(PIN_FAN_OFF, OUTPUT);
    		pinMode(PIN_FAN_LOW, OUTPUT);
    		pinMode(PIN_FAN_MED, OUTPUT);
    		pinMode(PIN_FAN_HIGH, OUTPUT);
            pinMode(PIN_LED, OUTPUT);
            pinMode(PIN_ADDR0, OUTPUT);
            pinMode(PIN_SW0, INPUT);

    		digitalWrite(PIN_FAN_OFF, HIGH);
    		digitalWrite(PIN_FAN_LOW, HIGH);
    		digitalWrite(PIN_FAN_MED, HIGH);
    		digitalWrite(PIN_FAN_HIGH, HIGH);
            digitalWrite(PIN_ADDR0, HIGH);
    	}

    	void write_state(float state) override
    	{
    		if(state == 0) pulse_pin(PIN_FAN_OFF);
    		else if((int) (state * 100) == 33) pulse_pin(PIN_FAN_LOW);
    		else if((int) (state * 100) == 66) pulse_pin(PIN_FAN_MED);
    		else if(state == 1) pulse_pin(PIN_FAN_HIGH);

    	}

    	void pulse_pin(int pin)
    	{
    		digitalWrite(PIN_LED, HIGH);
    		digitalWrite(pin, LOW);  // fan is active low
    		delay(PIN_HOLD_TIME);
    		digitalWrite(pin, HIGH);
    		digitalWrite(PIN_LED, LOW);
    	}
};

