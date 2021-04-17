#include <RotaryEncoder.h>

const int NUM_SLIDERS = 1; //number of analog sliders
const int NUM_ROTARY = 4; //number of rotary encoders
const int NUM_BUTTONS = 4; //number of pushbuttons
const int analogInputs[NUM_SLIDERS] = {A0}; //analog input pins
int buttonState[NUM_BUTTONS] = { };
int analogValues[NUM_SLIDERS+NUM_ROTARY]; //array with analog values (0-1023)


RotaryEncoder encoder1(2,3);
RotaryEncoder encoder2(5,6);
RotaryEncoder encoder3(8,9);
RotaryEncoder encoder4(11,12);

const int button1=4;
const int button2=7;
const int button3=10;
const int button4=13;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 175;    // the debounce time; increase if the output flickers






void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogValues[i] = analogRead(analogInputs[i]);
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(analogValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
