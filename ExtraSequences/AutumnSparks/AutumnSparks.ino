// Import library and set color order
#define COLOR_ORDER GRB  // Green, Red, Blue
#include <FastLED.h>     // FastLED Library

// # of LEDs on the strip
#define NUM_LEDS 21  // 21 LEDs


// LED and Input ports
#define LED1 7      // LED
#define SPARKLE 2  // Input

CRGB led[NUM_LEDS];  // Create the led array

const int density = 3; // The visual amount of LEDs on the Strip (lower density = more LEDs on strip lit up)
const int speed = 10; // The speed the LEDs appear and disappear (higher = faster, vice versa)



void setup() {
  pinMode(LED1, OUTPUT);  // Set pin 7 as output for LEDs

  pinMode(SPARKLE, INPUT_PULLUP);  // Set pin 2 as input for has note; Sets to HIGH

  FastLED.addLeds<WS2812, LED1, GRB>(led, NUM_LEDS);  // <Type of LED, Pin #, Color value type>(LED variable, # of LEDs)

  Serial.begin(9600);  // Begin serial communication

}

void loop() {
  int index = random(0, NUM_LEDS); // Find a random LED on the strip
  led[index] = CRGB(random(190, 255), random(0, 60), 0); // Set that LED to be between Red and light Orange
  for (int i = 0; i < 5 - density; i++) { // Provide a gap between the LEDs being turned on (also dim them)
    fadeall(); // Dim the LEDs
    FastLED.show(); // Show the LEDs
    delay(50/speed); // Delay
  }
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { led[i].nscale8(245); } } // Dims all of the LEDs