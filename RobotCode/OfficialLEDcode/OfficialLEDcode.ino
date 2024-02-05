/*
  THIS CODE HAS LIGHT DOCUMENTATION (not every line is documented) 
  ONLY MEANT FOR THE OFFICIAL ROBOT CODE
*/

// Library and Color Order
#define COLOR_ORDER GRB
#include <FastLED.h>

// LED Pin(s)
#define LED1 7

// Input Pin(s)
#define ALLIANCE 2
#define FOUNDNOTE 3
#define AIMED 4
#define NOTEINTAKE 5
#define NOTEOUTTAKE 6

// # of LEDs
#define NumberOfLEDs 21

// Create the LED Strip's variable (array)
CRGB led1[NumberOfLEDs];

// LED Priorities (Note > Alliance < Found Note)
int priorityN = 0;
int priorityF = 0;

// Setup
void setup() {
  pinMode(LED1, OUTPUT);  // Set pin 7 as as output

  // Define all pins below as Input pins CHANGE TO NORMAL INPUT FOR THE ACTUAL ROBOT CODE --------
  pinMode(ALLIANCE, INPUT_PULLUP);
  pinMode(FOUNDNOTE, INPUT_PULLUP);
  pinMode(AIMED, INPUT_PULLUP);
  pinMode(NOTEINTAKE, INPUT_PULLUP);
  pinMode(NOTEOUTTAKE, INPUT_PULLUP);

  FastLED.addLeds<WS2812, LED1, GRB>(led1, NumberOfLEDs);  // <Type of LED, Pin #, Color value type>(LED variable, # of LEDs)

  // Unique seed used for the random functions later in the code
  randomSeed(analogRead(0));

  // Begin Serial communication with Arduino
  Serial.begin(9600);
}

// Loop
void loop() {
  // Alliance Colors
  if (digitalRead(ALLIANCE) == HIGH && priorityN == 0 && priorityF == 0) {
    SetLEDs(255, 0, 0, NumberOfLEDs);  // Red
    FastLED.show();
  } else if (digitalRead(ALLIANCE) == LOW && priorityN == 0 && priorityF == 0) {
    SetLEDs(0, 0, 255, NumberOfLEDs);  // Blue
    FastLED.show();
  }

  // Note Colors
  if (digitalRead(FOUNDNOTE) == LOW) {
    priorityF = 1;                     // Set Priorities
    SetLEDs(75, 0, 75, NumberOfLEDs);  // Purple
    FastLED.show();
  } else {
    priorityF = 0;
  }

  // Shooter Colors
  if (digitalRead(AIMED) == LOW) {
    priorityN = 1;                     // Set Priority
    SetLEDs(0, 255, 0, NumberOfLEDs);  // Green
    FastLED.show();
  } else if (digitalRead(NOTEINTAKE) == LOW) {
    priorityN = 1;  // Set Priority
    ResetLEDs();    // Black/Nothing
  } else if (digitalRead(NOTEOUTTAKE) == LOW) {
    priorityN = 1;                     // Set Priority
    SetLEDs(75, 0, 75, NumberOfLEDs);  // Purple
    FastLED.show();
  } else {
    priorityN = 0;  // Set Priority
  }
}


// Function ResetLEDs
void ResetLEDs() {
  for (int i = 0; i < NumberOfLEDs; i++) {
    led1[i] = CRGB(0, 0, 0);
  }
}

// Function SetLEDs, Parameterers; RBG value, Number of LEDs
void SetLEDs(byte R, byte G, byte B, byte numberOfLEDs) {
  for (int i = 0; i < numberOfLEDs; i++) {
    led1[i] = CRGB(R, G, B);
  }
}
