#include <RotaryEncoder.h>

const int NUM_SLIDERS = 1; //number of analog sliders
const int NUM_ROTARY = 4; //number of rotary encoders
const int NUM_BUTTONS = 4; //number of pushbuttons
const int analogInputs[NUM_SLIDERS] = {A0}; //analog input pins
int buttonState[NUM_BUTTONS] = { };  //initialize with 0
int muteState[NUM_BUTTONS] = { };
int analogValues_slider[NUM_SLIDERS] = { }; //array with analog values read from analog input (0-1023)
int analogValues_rotary[NUM_ROTARY] = { }; //array with analog values created from rotary encoders (0-1023)
int digitalValues_rotary[NUM_ROTARY] = { };

//initialize rotary encoders and set pins
RotaryEncoder encoder1(2, 3);
RotaryEncoder encoder2(5, 6);
RotaryEncoder encoder3(8, 9);
RotaryEncoder encoder4(11, 12);

// encoder button pins
const int button1 = 4;
const int button2 = 7;
const int button3 = 10;
const int button4 = 15; //A1 als digitalen Pin benutzt

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 175;    // the debounce time; increase if the output flickers


void setup() {
  // set pinMode for analog sliders
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  // set pinMode for buttons
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);


  // set start values for rotary encoders between 0-1023

  for (int i = 0; i < NUM_ROTARY; i++) {
    analogValues_rotary[i] = 512;
  }


  //set initial encoder position
  encoder1.setPosition(51);
  encoder2.setPosition(51);
  encoder3.setPosition(51);
  encoder4.setPosition(51);

  Serial.begin(9600);
}

void loop() {

  //analog input
  updateSliderValues();
  // printSliderValues(); // For debug

  //digital input
  checkButtons();
  // printButtonValues();
  checkEncoders();
  sendAllValues(); // Actually send data (all the time)
  // sendSliderValues(); 
}


void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    analogValues_slider[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogValues_slider[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogValues_slider[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}

void printButtonValues() {

  for (int i = 0; i < NUM_BUTTONS; i++) {
    String printedString = String("buttonState ") + String(i) + String(": ") + String(buttonState[i]) + "; ";
    Serial.print(printedString);
  }
    Serial.write("\n");
}


void printRotaryValues() {

  for (int i = 0; i < NUM_ROTARY; i++) {
    String printedString = String("Rotary encoder ") +String( i) + String("; digital: ") + String(digitalValues_rotary[i])
                           + String("; analog: ") + analogValues_rotary[i];
    Serial.write(printedString.c_str());
  }
}


void sendAllValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogValues_slider[i]);

    if (i < (NUM_ROTARY + NUM_SLIDERS) - 1) {
      builtString += String("|");
    }
  }
  for (int i = 0; i < NUM_ROTARY; i++) {
    builtString += String((int)analogValues_rotary[i]);

    if (i < (NUM_ROTARY + NUM_SLIDERS) - 1) {
      builtString += String("|");
    }
  }

  Serial.println(builtString);
}


void checkButtons() {

  buttonState[0] = digitalRead(button1);
  buttonState[1] = digitalRead(button2);
  buttonState[2] = digitalRead(button3);
  buttonState[3] = digitalRead(button4);

}

void checkEncoders() {

  digitalValues_rotary[0] = encoder1.getPosition();
  digitalValues_rotary[1] = encoder2.getPosition();
  digitalValues_rotary[2] = encoder3.getPosition();
  digitalValues_rotary[3] = encoder4.getPosition();


  for (int i = 0; i < NUM_ROTARY; i++) {

    if (digitalValues_rotary[i] > 0 && digitalValues_rotary[i] < 102 && muteState[i] == 0) {
      analogValues_rotary[i] = digitalValues_rotary[i] * 10;
    }

    else if (muteState[i] == 0 && digitalValues_rotary[i] > 101) {
      analogValues_rotary[i] = 102 * 10;
      digitalValues_rotary[i] = 102;
    }

    else if (muteState[i] == 1) {
      analogValues_rotary[i] = 0;
    }

    else {
      analogValues_rotary[i] = 0;
      digitalValues_rotary[i] = 0;
    }

  }

  encoder1.setPosition(digitalValues_rotary[0]);
  encoder2.setPosition(digitalValues_rotary[1]);
  encoder3.setPosition(digitalValues_rotary[2]);
  encoder4.setPosition(digitalValues_rotary[3]);

}
