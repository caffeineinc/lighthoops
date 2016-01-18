/**
 * PIR sensor handler that triggers on-movement and off-movement
 */
class PIRSensor {
private:
 long _lastHigh;
 unsigned int _timeout;
 byte _pin;
 bool _status;
 void (*_onCallback)();
 void (*_offCallback)();

public:
 PIRSensor(byte pin, unsigned int timeout, void (*onCallback)(), void (*offCallback)());
 void setup();
 void loop();
};

PIRSensor::PIRSensor(byte pin, unsigned int timeout, void (*onCallback)(), void (*offCallback)()) :
  _lastHigh(0),
  _status(false),
  _pin(pin),
  _timeout(timeout),
  _onCallback(onCallback),
  _offCallback(offCallback)
{
}

void PIRSensor::setup()
{
   pinMode(_pin, INPUT);
}

void PIRSensor::loop()
{
  long now;
  now = millis();

  // On, just keep track of how recently the signal has been on
  if(digitalRead(_pin) == HIGH) {
    _lastHigh = now;

    // On the for the first time, then trigger the on callback
    if(!_status) {
      _status = true;
      _onCallback();
    }


  // Off for the timeout period, trigger the off callback
  } else if((now - _lastHigh > _timeout*1000) && _status) {
    _status = false;
    _offCallback();
  }
}

