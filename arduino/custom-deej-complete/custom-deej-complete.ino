#include <RotaryEncoder.h>

const int NUM_SLIDERS = 1; //number of analog sliders
const int NUM_ROTARY = 4; //number of rotary encoders
const int NUM_BUTTONS = 4; //number of pushbuttons
const int analogInputs[NUM_SLIDERS] = {A0}; //analog input pins
int buttonState[NUM_BUTTONS] = { };  //initialize with 0
int muteState[NUM_BUTTONS] = { };
int analogValues[NUM_SLIDERS + NUM_ROTARY]; //array with analog values created from rotary encoders (0-1023)


//initialize rotary encoders and set pins
RotaryEncoder encoder1(2,3);
RotaryEncoder encoder2(5,6);
RotaryEncoder encoder3(8,9);
RotaryEncoder encoder4(11,12);

// encoder button pins
const int button1=4;
const int button2=7;
const int button3=10;
const int button4=13;

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

for (int i = 0; i < NUM_ROTARY; i++){
  analogValues[i+NUM_SLIDERS] = 512;
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
  checkEncoders();


  sendSliderValues(); // Actually send data (all the time)


}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogValues[i] = analogRead(analogInputs[i]);
  }
}

void updateRotaryValues() {

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


void checkButtons(){

}

void checkEncoders(){
  
}