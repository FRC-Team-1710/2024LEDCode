// Import library and set color order
#define COLOR_ORDER GRB  // Green, Red, Blue
#include <FastLED.h>     // FastLED Library

// # of LEDs on the strip
#define NUM_LEDS 21  // 21 LEDs


// LED and Input ports
#define LED1 7      // LED
#define RGBCOMET 2  // Input

// Variables
CRGB led[NUM_LEDS];  // Create the led array

CRGBPalette16 rainbow = RainbowColors_p;  // Import the Rainbow color palette

int ledStart = 0;          // LED where the comet starts
int index = 0;             // Color on the color palette
const int cometSize = 5;   // Size of the comet (Has to be greater than 0)
const int cometSpeed = 2;  // 1 is the recommended min, 5 is the recommended max (You can go higher or lower)

CRGB nextColor;  // The next color in the color palette

// Setup
void setup() {
  pinMode(LED1, OUTPUT);  // Set pin 7 as output for LEDs

  pinMode(RGBCOMET, INPUT_PULLUP);  // Set pin 2 as input for has note; Sets to HIGH

  FastLED.addLeds<WS2812, LED1, GRB>(led, NUM_LEDS);  // <Type of LED, Pin #, Color value type>(LED variable, # of LEDs)

  Serial.begin(9600);  // Begin serial communication
}

// Loop
void loop() {
  // Initialize
  ResetLEDs();                                         // Reset all LEDs on strip
  nextColor = CRGB(ColorFromPalette(rainbow, index));  // Grab the next color in the palette

  for (int i = ledStart; i < cometSize + ledStart; i++) {  // Sets the comet
    if (i >= NUM_LEDS) {                                   // If the next LED index is not valid (greater than # of LEDs)
      led[i - NUM_LEDS] = nextColor;                       // Go back to the start to set the LED

    } else {
      led[i] = nextColor;  // Set the LED at index 'i'
    }
  }

  // Show
  FastLED.show();

  // Prepare
  index++;     // Increment the index on the color palette
  ledStart++;  // Increment the index on the LED strip

  if (ledStart == NUM_LEDS) {  // Checks if current LED index is higher than the # of LEDs
    ledStart = 0;              // Resets index to 0 if true
  }

  delay(50 / cometSpeed);  // Delay the time between iterations
}


void ResetLEDs() {                      // Function to reset LEDs on strip (without FastLED.show();)
  for (int x = 0; x < NUM_LEDS; x++) {  // Go through all LEDs
    led[x] = CRGB(0, 0, 0);             // Set color of LED to Black/Nothing
  }
}
