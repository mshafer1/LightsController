//http://www.youtube.com/channel/UC6mIxFTvXkWQVEHPsEdflzQ
//GreatScott!
#include <EEPROM.h>

#define default 1
#define dither 2
#define bound 3
#define beat 4
#define independent 5

#define cutoff 35
#define interested_regions 5
#define waste_pin 2
#define mode_addr 0

int analogPin = 0;
int strobePin = 4;
int resetPin = 5;

int spectrumValue[7];
int filter = 0;
int cutoff_val = cutoff;

const int numLights = 8;
const int regions = 4; // this affect spectrumValue mapping
const int lightsPerRegion = numLights / regions;
bool states[regions];
int onPins[regions];

unsigned long time;

const int baseLight = 6;

int mode = default;
int count = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(waste_pin, OUTPUT);

  //  pinMode(ledred, OUTPUT);
  //  pinMode(ledblue, OUTPUT);
  //  pinMode(ledyellow, OUTPUT);
  //  pinMode(ledgreen, OUTPUT);
  for (int i = 0; i < numLights; i++)
  {
    pinMode(baseLight + i, OUTPUT);
    digitalWrite(baseLight + i, LOW);

  }
  for (int i = 0; i < regions; i++)
  {
    states[i] = false;
  }

  randomSeed(analogRead(4));

  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
  mode = (int)EEPROM.read(mode_addr);
}

void loop()
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(strobePin, LOW);
    //    delay(30);
    delay(1);
    spectrumValue[i] = analogRead(analogPin);
    spectrumValue[i] = constrain(spectrumValue[i], filter, 1023);
    spectrumValue[i] = map(spectrumValue[i], filter, 1023, 0, 100);
    //  Serial.print(spectrumValue[i]);
    //  Serial.print(" ");
    digitalWrite(strobePin, HIGH);
  }
  //  Serial.println();
  //  analogWrite(ledred,spectrumValue[0]);
  //  analogWrite(ledred,spectrumValue[1]);
  //digitalWrite(ledblue, spectrumValue[0] > cutoff || spectrumValue[1] > cutoff);
  states[0] = spectrumValue[0] > cutoff_val || spectrumValue[1] > cutoff_val; // below middle C
  //  analogWrite(ledblue,spectrumValue[3]);
  //  analogWrite(ledblue,spectrumValue[4]);
  //digitalWrite(ledyellow, spectrumValue[2] > cutoff  );
  states[1] = spectrumValue[2] > cutoff_val; // near middle C
  //  analogWrite(ledgreen,spectrumValue[5]);
  //  analogWrite(ledgreen,spectrumValue[6]);
  //digitalWrite(ledred,spectrumValue[3] > cutoff ||  spectrumValue[4] > cutoff );
  states[2] = spectrumValue[3] > cutoff_val; // near high C
  //digitalWrite(ledgreen,spectrumValue[5] > cutoff);
  states[3] = spectrumValue[4] > cutoff_val || spectrumValue[5] > cutoff_val; // even higher
  update_display();
  check_serial();
}

void update_display()
{
  static bool previousStates[regions] = { false };
  ++count;
  if (mode == default)
  {
    //    if(count % 50 == 0)
    //    {
    //    Serial.println("Default");
    //    }

    for (int i = 0; i < regions; i++)
    {
      if (states[i])
      {
        //check if previously on
        if (previousStates[i])
        {
          // do nothing
        }
        else
        {
          // randomly select an output to turn on
          digitalWrite(baseLight + (i * lightsPerRegion) + random(lightsPerRegion), HIGH);
        }
      }
      else
      {
        // turn outputs off
        for (int j = 0; j < lightsPerRegion; j++)
        {
          digitalWrite(baseLight + (i * lightsPerRegion) + j, LOW);
        }
      }
      //chache this value
      previousStates[i] = states[i];
    }
  }
  else if (mode == dither)
  {
    bool value = false;
    for (int i = 0; i < regions; i++)
    {
      value = value || states[i];
    }
    if (value)
    {
      if (previousStates[0])
      { // NOOP
      }
      else
      {
        // randomly select an output to turn on
        digitalWrite(baseLight + random(numLights), value);

      }
    }
    else
    {
      all_off();
    }
    previousStates[0] = value;
  }
  else if (mode == bound)
  {
    bool value = false;
    for (int i = 0; i < regions; i++)
    {
      value = value || states[i];
    }
    for (int j = 0; j < numLights; j++)
    {
      digitalWrite(baseLight + j, value);
    }
  }
  else if (mode == beat)
  {
    bool any = false;
    for (int i = 0; i < regions; i++)
    {
      if (states[i])
      {

        //check if previously on
        if (previousStates[i])
        {
          // do nothing
        }
        else
        {
          // a beat - move lights
          any = true;
          // randomly select an output to turn on
          //          int light_to_turn_on = random(numLights);
          //          while(digitalReadOutputPin(baseLight + light_to_turn_on))
          //          {
          //            light_to_turn_on = random(numLights); // keep trying
          //
          //          }
          //          digitalWrite(baseLight + light_to_turn_on, HIGH);
          //          onPins[i] = baseLight + light_to_turn_on;
        }
      }
      else
      {
        // turn outputs off
        //        digitalWrite(onPins[i], LOW);
        //        onPins[i] = waste_pin;
      }
      //chache this value
      previousStates[i] = states[i];
    }
    if (any)
    {
      int num_lights_turn_on = random(3) + 1; // random number between 1 and 3
      //swith lights
      all_off();

      for (int i = 0; i < num_lights_turn_on; i++)
      {
        int light_to_turn_on = random(numLights);
        while (digitalReadOutputPin(baseLight + light_to_turn_on))
        {
          light_to_turn_on = random(numLights); // keep trying
        }
        digitalWrite(baseLight + light_to_turn_on, HIGH);
      }
      time = millis();
    }
    else
    {
      unsigned long new_time = millis();
      if (new_time - time > 500)
      {
        all_off();
      }
    }
  }
  else if (mode == independent)
  {
    unsigned long new_time = millis();
    if (new_time - time > 500)
    {
      all_off();
      for (int i = 0; i < regions; i++)
      {
        digitalWrite(baseLight + (i * lightsPerRegion) + random(lightsPerRegion), HIGH);
      }
      //chache this value
      time = millis();
    }
  }
}

void all_off()
{
  for (int i = 0; i < numLights; i++)
  {
    digitalWrite(baseLight + i, LOW);
  }
}

//from http://forum.arduino.cc/index.php?topic=41954.msg304419#msg304419
int digitalReadOutputPin(uint8_t pin)
{
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  if (port == NOT_A_PIN)
    return LOW;

  return (*portOutputRegister(port) & bit) ? HIGH : LOW;
}

void check_serial()
{
  if (Serial.available() > 0)
  {
    String result = "";
    int inChar = 0;
    while (Serial.peek() != '^')
    {
      Serial.read(); // flush extra chars
    }
    result = Serial.readString();
    result.trim();

    cutoff_val = cutoff;
    if (result == "^dither$")
    {
      mode = dither;
    }
    else if (result == "^bound$")
    {
      mode = bound;
    }
    else if (result == "^beat$")
    {
      mode = beat;
      //      cutoff_val = 40;
    }
    else if (result == "^musicless$")
    {
      mode = independent;
    }
    else
    {
      mode = default;
    }
    Serial.println("Received " + result);
    Serial.print("Set to ");
    Serial.println(mode);
    EEPROM.write(mode_addr, mode);
  }
  else
  {
    delay(35);
  }
}
