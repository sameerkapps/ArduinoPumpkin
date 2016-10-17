// Sameer Khandekar
// Code to detect using sensor taken from
// https://github.com/mrichardson23/PimpYourPumpkin/blob/master/PimpYourPumpkin.pde

#define CANDLELED 11
#define BUZZER 4
#define SENSOR A0
#define PROXIMITY_THRESHOLD 100
#define PROXIMITY_CONSECUTIVE_READINGS 3
#define BUZZER_FREQUENCY 3000
#define FLICKER_INTERVAL 50

long previousMillis = 0;
long closeReadings = 0;
int lastLEDState = LOW;

void setup() 
{ 
  // initialize Buzzer and LED pin as output pins  
  pinMode(CANDLELED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // initialize sensor as input pin
  pinMode(SENSOR, INPUT);
  delay(1000); // Allow the proximity sensor to initialize
}

void loop() 
{
  // If sensor detects something close
  if (analogRead(0) > PROXIMITY_THRESHOLD) 
  {
    // Ensure consecutive "close" readings before going into detected mode. 
    // This prevents little blips of the buzzer.
    closeReadings++;
    if (closeReadings >= PROXIMITY_CONSECUTIVE_READINGS) 
    {
      // blink LEDs
      BlinkLED(); 
      // Start the buzzer
      tone(BUZZER, BUZZER_FREQUENCY);
    }
  }
  else
  { 
    // stop the buzzer
    noTone(BUZZER);
    // reset prox readings
    closeReadings = 0;
    // turn off the blinking eyes
    digitalWrite(CANDLELED, LOW);
  }
}

// blinks LED
void BlinkLED()
{
  // check current milliSec
  unsigned long currentMillis = millis();
  // if it exceeds interval
  if(currentMillis - previousMillis > FLICKER_INTERVAL)
  {
    // toggle the state of LED (on/off)
    if(lastLEDState == HIGH)
    {
      lastLEDState = LOW;
    }
    else
    {
      lastLEDState = HIGH;
    }

    // reset interval
    previousMillis = currentMillis;
    // write the state
    digitalWrite(CANDLELED, lastLEDState);
  }
}

