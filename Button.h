/**
 * Have a button that triggers a callback when pressed
 */
class Button {
private:
 long _lastClicked;
 byte _pin;
 void (*_callback)();

public:
 Button(byte pin, void (*callback)());
 void setup();
 void loop();
};

Button::Button(byte pin, void (*callback)()) : _lastClicked(0), _pin(pin), _callback(callback)
{
}

void Button::setup() {
   pinMode(_pin, INPUT_PULLUP);
}

void Button::loop() {
  long now;

  if(digitalRead(_pin) == LOW) {
    now = millis();
    if(!_lastClicked || _lastClicked < now-50) {
      _lastClicked = now;
      _callback();
    }
  }
}

