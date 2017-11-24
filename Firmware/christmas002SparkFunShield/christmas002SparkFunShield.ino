//http://www.youtube.com/channel/UC6mIxFTvXkWQVEHPsEdflzQ
//GreatScott!
int analogPin=0;
int strobePin=4;
int resetPin=5;

int spectrumValue[7];
int filter=0;
int cutoff = 35;

const int numLights = 8;
const int regions = 4; // this affect spectrumValue mapping
const int lightsPerRegion = numLights / regions;
bool states[regions];

const int baseLight = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
//  pinMode(ledred, OUTPUT);
//  pinMode(ledblue, OUTPUT);
//  pinMode(ledyellow, OUTPUT);
//  pinMode(ledgreen, OUTPUT);
  for(int i = 0; i < numLights; i++)
  {
    pinMode(baseLight + i, OUTPUT);
    digitalWrite(baseLight + i, LOW);
    
  }
  for(int i=0; i < regions; i++)
  {
    states[i] = false;
  }

  randomSeed(analogRead(4));

  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop()
{
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  for (int i=0;i<7;i++)
  {
    digitalWrite(strobePin, LOW);
//    delay(30);
    delay(1);
    spectrumValue[i]=analogRead(analogPin);
    spectrumValue[i]=constrain(spectrumValue[i], filter, 1023);
    spectrumValue[i]=map(spectrumValue[i], filter,1023,0,100);
    Serial.print(spectrumValue[i]);
    Serial.print(" ");
    digitalWrite(strobePin, HIGH);
  }
  Serial.println();
//  analogWrite(ledred,spectrumValue[0]);
//  analogWrite(ledred,spectrumValue[1]);
  //digitalWrite(ledblue, spectrumValue[0] > cutoff || spectrumValue[1] > cutoff);
  states[0] = spectrumValue[0] > cutoff || spectrumValue[1] > cutoff;
//  analogWrite(ledblue,spectrumValue[3]);
//  analogWrite(ledblue,spectrumValue[4]);
  //digitalWrite(ledyellow, spectrumValue[2] > cutoff  );
  states[1] = spectrumValue[2] > cutoff;
//  analogWrite(ledgreen,spectrumValue[5]);
//  analogWrite(ledgreen,spectrumValue[6]);
  //digitalWrite(ledred,spectrumValue[3] > cutoff ||  spectrumValue[4] > cutoff );
  states[2] = spectrumValue[3] > cutoff;
  //digitalWrite(ledgreen,spectrumValue[5] > cutoff);
  states[3] = spectrumValue[4] > cutoff || spectrumValue[5] > cutoff;
  update_display();
  delay(25);
}

void update_display()
{
  static bool previousStates[regions] = {false};
  for(int i = 0; i < regions; i ++)
  {
    if(states[i])
    {
      //check if previously on
      if(previousStates[i])
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
      for(int j = 0; j < lightsPerRegion; j++)
      {
        digitalWrite(baseLight + (i * lightsPerRegion) + j, LOW);
      }
    }
    //chache this value
    previousStates[i] = states[i];    
  }
}

