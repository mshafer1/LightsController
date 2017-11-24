//http://www.youtube.com/channel/UC6mIxFTvXkWQVEHPsEdflzQ
//GreatScott!
int analogPin=0;
int strobePin=2;
int resetPin=3;
int ledred=9;
int ledyellow=10;
int ledblue=11;
int ledgreen=12;
int spectrumValue[7];
int filter=0;
int cutoff = 45;
int brightness = 100;

void setup(){
  
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  pinMode(strobePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(ledred, OUTPUT);
  pinMode(ledblue, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  digitalWrite(resetPin, LOW);
  digitalWrite(strobePin, HIGH);
}

void loop(){
  
  digitalWrite(resetPin, HIGH);
  digitalWrite(resetPin, LOW);
  for (int i=0;i<7;i++){
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
  digitalWrite(ledblue, spectrumValue[0] > cutoff || spectrumValue[1] > cutoff);
//  analogWrite(ledblue,spectrumValue[3]);
//  analogWrite(ledblue,spectrumValue[4]);
  digitalWrite(ledyellow, spectrumValue[2] > cutoff  );
//  analogWrite(ledgreen,spectrumValue[5]);
//  analogWrite(ledgreen,spectrumValue[6]);
  digitalWrite(ledred,spectrumValue[3] > cutoff );
  digitalWrite(ledgreen, spectrumValue[4] > cutoff || spectrumValue[5] > cutoff);
  delay(30);
}

