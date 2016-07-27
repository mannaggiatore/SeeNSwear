// include the SD library:
#include <SPI.h>
#include <SD.h>

// change this to match your SD shield or module;
const int chipSelect = 10;

// include the PCM library:
#include <TMRpcm.h>
TMRpcm tmrpcm;   // create an object for use in this sketch


int commonPin1 = 3;
int commonPin2 = 2;

int btnPressed = 0;
int lastbtn = 0;
int fattore = 0;
int contacane = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("See 'n swear");

  pinMode(commonPin1, OUTPUT);      // sets the digital pin as output
  pinMode(commonPin2, OUTPUT);

  pinMode(4, INPUT);  // sets the digital pin as input
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed!");
    return;
  }
  tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
}

void loop()
{
  btnPressed = 0;

  digitalWrite(commonPin2, LOW);
  digitalWrite(commonPin1, HIGH);
  delay(50);

  if (digitalRead(4) == HIGH) btnPressed = 2;
  if (digitalRead(5) == HIGH) btnPressed = 3;
  if (digitalRead(6) == HIGH) btnPressed = 4;
  if (digitalRead(7) == HIGH) btnPressed = 5;
  if (digitalRead(8) == HIGH) btnPressed = 6;
  if (digitalRead(14) == HIGH) btnPressed = 7;
  if (digitalRead(15) == HIGH) btnPressed = 8;
  if (digitalRead(16) == HIGH) btnPressed = 9;


  digitalWrite(commonPin1, LOW);
  digitalWrite(commonPin2, HIGH);
  delay(50);

  if (digitalRead(16) == HIGH) btnPressed = 10;
  if (digitalRead(17) == HIGH) btnPressed = 1;


  if (btnPressed == 0 and (not lastbtn == 0)) {
    Serial.println(lastbtn);

    if (fattore == 0) {
      if (lastbtn == 1) {
        contacane = contacane + 1;
        Serial.print("contacane: ");
        Serial.println(contacane);
      } else {
        contacane = 0;
      }
    }

    if (contacane == 3) {
      fattore = 1;
      contacane = 0;
      Serial.println("Fattore mode on");
      tmrpcm.play("fattore.wav");
    } else {
      if (fattore == 0) {
        if (lastbtn == 1) tmrpcm.play("noswear/01.wav");
        if (lastbtn == 2) tmrpcm.play("noswear/02.wav");
        if (lastbtn == 3) tmrpcm.play("noswear/03.wav");
        if (lastbtn == 4) tmrpcm.play("noswear/04.wav");
        if (lastbtn == 5) tmrpcm.play("noswear/05.wav");
        if (lastbtn == 6) tmrpcm.play("noswear/06.wav");
        if (lastbtn == 7) tmrpcm.play("noswear/07.wav");
        if (lastbtn == 8) tmrpcm.play("noswear/08.wav");
        if (lastbtn == 9) tmrpcm.play("noswear/09.wav");
        if (lastbtn == 10) tmrpcm.play("noswear/10.wav");
      } else {
        if (lastbtn == 1) tmrpcm.play("swear/01.wav");
        if (lastbtn == 2) tmrpcm.play("swear/02.wav");
        if (lastbtn == 3) tmrpcm.play("swear/03.wav");
        if (lastbtn == 4) tmrpcm.play("swear/04.wav");
        if (lastbtn == 5) tmrpcm.play("swear/05.wav");
        if (lastbtn == 6) tmrpcm.play("swear/06.wav");
        if (lastbtn == 7) tmrpcm.play("swear/07.wav");
        if (lastbtn == 8) tmrpcm.play("swear/08.wav");
        if (lastbtn == 9) tmrpcm.play("swear/09.wav");
        if (lastbtn == 10) tmrpcm.play("swear/10.wav");
      }
      delay(100);
    }
  }
  lastbtn = btnPressed;
}

