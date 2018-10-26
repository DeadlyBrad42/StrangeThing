#include <Adafruit_NeoPixel.h>

////////////////////////////////////////////////////////////////////////////////
//// Configuration /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Phrases
// (?) Phrases to be displayed
int phraseCount = 27;
String phrases[] = {
  "run",
  "hide",
  "murder",
  "redrum",
  "help",
  "undead",
  "help me",
  "trapped"
  "it escaped",
  "its here",
  "did you hear that",
  "i see you",
  "kill",
  "hi",
  "beer me",
  "get drunk",
  "fuck trump",
  "fyeah",
  "godamnit jason",
  "boo",
  "hail satan",
  "halloweiners",
  "who was phone",
  "boo",
  "spoopy",
  "skinwalkers",
  "i want to believe",
};

// Light Strip
#define pixelsInStrip 100 // number of neopixels (?) Adjust this
#define controlPin 3 // signal control pin (?) Adjust this
Adafruit_NeoPixel lightstrip = Adafruit_NeoPixel(pixelsInStrip, controlPin, NEO_GRB + NEO_KHZ800);

// Colors
// (?) Add new colors here to reference in code, and in the `colorCount` array to appear in the random display
uint32_t white = lightstrip.Color(255, 255, 255);
uint32_t blue = lightstrip.Color(0, 0, 255);
uint32_t pink = lightstrip.Color(255, 0, 255);
uint32_t green = lightstrip.Color(0, 255, 0);
uint32_t yellow = lightstrip.Color(255, 255, 0);
uint32_t red = lightstrip.Color(255, 0, 0);

// Marker variable representing times when you want bulbs lit with their
//  "assigned" color, taken from the `colors` list belows
uint32_t assignedColor = lightstrip.Color(0, 0, 0, 255);

// (?) Array of colors used for `assignedColor`, as well as the list for random colors
int colorCount = 6;
uint32_t colors[] = {
  white,
  blue,
  pink,
  green,
  yellow,
  red
};

// Fading
#define softStepAmount 20 // How many `for` steps it takes to soft-light and soft-dim each LED

// LED Letters
// (?) You may need to adjust this for your display
/////
#define led_A 5
#define led_B 8
#define led_C 13
#define led_D 17
#define led_E 21
#define led_F 24
#define led_G 27
#define led_H 30
/////
#define led_I 66
#define led_J 62
#define led_K 59
#define led_L 56
#define led_M 52
#define led_N 48
#define led_O 45
#define led_P 42
#define led_Q 38
/////
#define led_R 74
#define led_S 77
#define led_T 81
#define led_U 85
#define led_V 88
#define led_W 91
#define led_X 95
#define led_Y 98
#define led_Z 0
/////


////////////////////////////////////////////////////////////////////////////////
//// Arduino Functions /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void setup() {
  // Initialization
  // open the serial port at 9600 bps
  Serial.begin(9600);

  // seed RNG with noise from pin 0
  randomSeed(analogRead(0));

  // init lightstrip
  lightstrip.begin();
  lightstrip.show(); // Initialize all pixels to 'off'
  lightstrip.setBrightness(180); // Set max brightness

  // call startup test function
  test_default();
}

void loop() {
  // CHOOSE MODE:

  // Shuffle through various effects
  //effects_shuffle();

  // -or-

  // "Curated", ordered display
  effects_curated();

  // -or

  // Just call functions to do whatever you want
  //fx_LightPhrase("wow v spoopy");
}


////////////////////////////////////////////////////////////////////////////////
//// Functions /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void test_default() {
  delay(1000);

  Serial.println("Starting LED test...");
  fx_LineWalk(white);
  softDarkenStrip(white);
  Serial.println("Finished LED test!");

  // fx_LightPhrase("abcdefghijklmnopqrstuvwxy");
  fx_LightPhrase("wtf");
  delay(750);
}

void effects_shuffle() {
  // Randomly pick an effect|text to display
  uint32_t color;
  switch (random(0, 7)) {
    case 0:
      // Spell a word
      fx_LightPhrase(phrases[random(0, phraseCount)]);
      break;
    case 1:
      // Red Flash
      fx_FlashColor(red);
      delay(500);
      softDarkenStrip(red);
      break;
    case 2:
      // Random-colored flash
      delay(500);
      color = colors[random(0, colorCount)];
      fx_FlashColor(color);
      softDarkenStrip(color);
      break;
    case 3:
      // Random-color line-walk
      color = colors[random(0, colorCount)];
      fx_LineWalk(color);
      delay(500);
      softDarkenStrip(color);
      break;
    case 4:
      // Assigned-color line-walk
      fx_LineWalk(assignedColor);
      delay(500);
      softDarkenStrip(assignedColor);
      break;
    case 5:
      // Random-color flash, then pop
      color = colors[random(0, colorCount)];
      fx_FlashColor(color);
      delay(500);
      fx_LightPop(white);
      break;
    case 6:
      // Assigned-color flash, then pop
      fx_FlashColor(assignedColor);
      delay(500);
      fx_LightPop(assignedColor);
      break;
  }

  // Wait between effects
  delayForRandom(7500, 2500);
}

void effects_curated() {
  uint32_t color;

  // Play random effect
  switch (random(0, 4)) {
    case 0:
      // Red Flash
      fx_FlashColor(red);
      softDarkenStrip(red);
      break;
    case 1:
      // Random-colored flash
      color = colors[random(0, colorCount)];
      fx_FlashColor(color);
      softDarkenStrip(color);
      break;
    case 2:
      // Random-color line-walk
      color = colors[random(0, colorCount)];
      fx_LineWalk(color);
      softDarkenStrip(color);
      break;
    case 3:
      // Assigned-color line-walk
      fx_LineWalk(assignedColor);
      softDarkenStrip(assignedColor);
      break;
  }

  // Fade to assignedColor
  fx_FlashColor(assignedColor);

  // Wait for ~3 minutes
  delayForRandom(3 * 6000, 3000);

  // Flicker for ~30 seconds
  fx_Flicker(assignedColor, 500);

  // Wait for 10-30 seconds
  delayForRandom(1000 + 2000, 1000);

  // Flicker for ~2 minutes
  fx_Flicker(assignedColor, 2000);

  // Pop to Black
  fx_LightPop(assignedColor);

  // blink red 3 times
  for (int count = 0; count < 3; count++) {
    fx_FlashColor(red);
    softDarkenStrip(red);
  }

  // Light up a phrase
  fx_LightPhrase(phrases[random(0, phraseCount)]);

  // Wait for ~2 minutes
  delayForRandom(2 * 6000, 3000);
}


////////////////////////////////////////////////////////////////////////////////
//// Effects ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void fx_LightPhrase(String phrase) {
  // foreach letter in phrase
  for (int currentLetter = 0; currentLetter < phrase.length(); currentLetter++) {
    char letter = phrase.charAt(currentLetter);
    int ledNumber = letterToLed(letter);
    uint32_t color = colors[ledNumber % colorCount];

    //_debug_color(ledNumber % colorCount);

    if (ledNumber >= 0) {
      // light LED for letter
      _debug_letter(letter);
      softLightLed(ledNumber, color);
      delayForRandom(1000, 250);
      softDarkenLed(ledNumber, color);
      delayForRandom(1000, 250);
    } else {
      // wait for "space"
      _debug_letter(' ');
      delayForRandom(1500, 750);
    }
  }

  // wait between words
  _debug_letter('-');
}

void fx_FlashColor(uint32_t color) {
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {
    for (int currentLed = 0; currentLed < pixelsInStrip; currentLed++) {
      uint32_t bulbColor = (color == assignedColor ? colors[currentLed % colorCount] : color);
      int r = color_clampVal(currentStep * (color_GetRVal(bulbColor) / softStepAmount));
      int g = color_clampVal(currentStep * (color_GetGVal(bulbColor) / softStepAmount));
      int b = color_clampVal(currentStep * (color_GetBVal(bulbColor) / softStepAmount));

      lightstrip.setPixelColor(
        currentLed,
        g,
        r,
        b
      );
    }

    lightstrip.show();
    delay((softStepAmount - currentStep) * 7);
  }
}

void fx_LineWalk(uint32_t color) {
  for (int currentLed = 0; currentLed < pixelsInStrip; currentLed++) {
      uint32_t bulbColor = (color == assignedColor ? colors[currentLed % colorCount] : color);
      hardLightLed(currentLed, bulbColor);
      delay(50);
  }
  delayForRandom(1000, 250);
}

void fx_LightPop(uint32_t color) {
  // Keep track of popped bulbs
  boolean popped[pixelsInStrip];
  for (int count = 0; count < pixelsInStrip; count++) {
    popped[count] = false;
  }

  int lightsLeft = pixelsInStrip;
  while (lightsLeft > 0) {
    int lightToPop = random(0, pixelsInStrip);
    if(!popped[lightToPop]) {
      hardLightLed(lightToPop, white);
      softDarkenLed(lightToPop, white);
      popped[lightToPop] = true;
      lightsLeft--;
    }
  }
}

void fx_Flicker(uint32_t color) {
    // Flicker for default amount of cycles. I've found that 5000 = ~2mins
    fx_Flicker(color, 5000);
}

void fx_Flicker(uint32_t color, int cycles) {
  for (int timer = 0; timer < cycles; timer++) {
    for (int currentLed = 0; currentLed < pixelsInStrip; currentLed++) {
      // Get bulb color
      uint32_t bulbColor = (color == assignedColor ? colors[currentLed % colorCount] : color);
      // Dim by random amount
      uint32_t bulbColorDimValue = random(165, 256);
      int r = color_clampVal((int)(color_GetRVal(bulbColor) * (float)(bulbColorDimValue / (float)(255))));
      int g = color_clampVal((int)(color_GetGVal(bulbColor) * (float)(bulbColorDimValue / (float)(255))));
      int b = color_clampVal((int)(color_GetBVal(bulbColor) * (float)(bulbColorDimValue / (float)(255))));

      lightstrip.setPixelColor(
        currentLed,
        g,
        r,
        b
      );
    }

    lightstrip.show();
  }
}


////////////////////////////////////////////////////////////////////////////////
//// Utility Functions /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

uint32_t softLightLed(int ledNumber, uint32_t toColor) {
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {
    uint32_t bulbColor = (toColor == assignedColor ? colors[ledNumber % colorCount] : toColor);
    int r = color_clampVal(currentStep * (color_GetRVal(bulbColor) / softStepAmount));
    int g = color_clampVal(currentStep * (color_GetGVal(bulbColor) / softStepAmount));
    int b = color_clampVal(currentStep * (color_GetBVal(bulbColor) / softStepAmount));

    Serial.print(r); Serial.print(",");
    Serial.print(g); Serial.print(",");
    Serial.println(b);

    lightstrip.setPixelColor(ledNumber,
      (g < 10 ? 0 : g), // turn off early
      (r < 10 ? 0 : r),
      (b < 10 ? 0 : b)
    );
    lightstrip.show();

    //_debug_message(ledNumber, "soft-lit to", r, g, b);
    delay(25);
  }

  lightstrip.setPixelColor(ledNumber, color_GetGVal(toColor), color_GetRVal(toColor), color_GetBVal(toColor));
  lightstrip.show();

  //_debug_message(ledNumber, "soft-lit to", color_GetRVal(toColor), color_GetGVal(toColor), color_GetBVal(toColor));
  return toColor;
}

uint32_t hardLightLed(int ledNumber, uint32_t toColor) {
  uint32_t bulbColor = (toColor == assignedColor ? colors[ledNumber % colorCount] : toColor);

  lightstrip.setPixelColor(ledNumber, color_GetGVal(bulbColor), color_GetRVal(bulbColor), color_GetBVal(bulbColor));
  lightstrip.show();

  //_debug_message(ledNumber, "hard-lit to", color_GetRVal(bulbColor), color_GetGVal(bulbColor), color_GetBVal(bulbColor));
  return toColor;
}

uint32_t softDarkenLed(int ledNumber, uint32_t fromColor) {
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {
    uint32_t bulbColor = (fromColor == assignedColor ? colors[ledNumber % colorCount] : fromColor);
    int r = color_clampVal(color_GetRVal(bulbColor) - currentStep * (color_GetRVal(bulbColor) / softStepAmount));
    int g = color_clampVal(color_GetGVal(bulbColor) - currentStep * (color_GetGVal(bulbColor) / softStepAmount));
    int b = color_clampVal(color_GetBVal(bulbColor) - currentStep * (color_GetBVal(bulbColor) / softStepAmount));

    Serial.print(r); Serial.print(",");
    Serial.print(g); Serial.print(",");
    Serial.println(b);

    lightstrip.setPixelColor(
      ledNumber,
      (g < 10 ? 0 : g), // turn off early
      (r < 10 ? 0 : r),
      (b < 10 ? 0 : b)
    );

    lightstrip.show();
    delay(25); // Arbitrary wait-a-bit, dimming seems "faster" than lighting
  }

  lightstrip.setPixelColor(ledNumber, 0, 0, 0);
  lightstrip.show();

  //_debug_message(ledNumber, "soft-dimmed to", 0, 0, 0);
  return lightstrip.Color(0, 0, 0);
}

uint32_t hardDarkenLed(int ledNumber) {
  lightstrip.setPixelColor(ledNumber, 0, 0, 0);
  lightstrip.show();

  //_debug_message(ledNumber, "hard-dimmed to", 0, 0, 0);
  return lightstrip.Color(0, 0, 0);
}

uint32_t softDarkenStrip(uint32_t fromColor) {
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {
    for (int currentLed = 0; currentLed < pixelsInStrip; currentLed++) {
      uint32_t bulbColor = (fromColor == assignedColor ? colors[currentLed % colorCount] : fromColor);
      int r = color_clampVal(color_GetRVal(bulbColor) - currentStep * (color_GetRVal(bulbColor) / softStepAmount));
      int g = color_clampVal(color_GetGVal(bulbColor) - currentStep * (color_GetGVal(bulbColor) / softStepAmount));
      int b = color_clampVal(color_GetBVal(bulbColor) - currentStep * (color_GetBVal(bulbColor) / softStepAmount));
      lightstrip.setPixelColor(
        currentLed,
        (g < 30 ? 0 : g), // turn off early
        (r < 30 ? 0 : r),
        (b < 30 ? 0 : b)
      );
    }

    lightstrip.show();
    delay(25); // Arbitrary wait-a-bit, dimming seems "faster" than lighting
  }

  //_debug_message(-1, "strip soft-dimmed to", 0, 0, 0);
  return lightstrip.Color(0, 0, 0);
}

uint32_t hardDarkenStrip() {
  for (int currentLight = 0; currentLight < pixelsInStrip; currentLight++) {
      lightstrip.setPixelColor(currentLight, 0, 0, 0);
    }
  lightstrip.show();

  //_debug_message(-1, "strip hard-dimmed to", 0, 0, 0);
  return lightstrip.Color(0, 0, 0);
}

int delayForRandom(int median, int spread) {
  delay(random(median - spread > 0 ? median - spread : 0, median + spread));
}

int color_GetRVal(uint32_t color) {
  return (color >> 16) & B11111111;
}

int color_GetGVal(uint32_t color) {
  return (color >> 8) & B11111111;
}

int color_GetBVal(uint32_t color) {
  return color & B11111111;
}

int color_clampVal(int colorValue) {
  colorValue = max(colorValue, 0);
  return min(colorValue, 255);
}


////////////////////////////////////////////////////////////////////////////////
//// Debug Functions & Data ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void _debug_message(int ledNumber, String message, int r, int g, int b) {
  Serial.print("LED #");
  Serial.print(ledNumber);
  Serial.print(" ");
  Serial.print(message);
  Serial.print("(");
  Serial.print(r);
  Serial.print(", ");
  Serial.print(g);
  Serial.print(", ");
  Serial.print(b);
  Serial.print(")");
  Serial.println("");
}

void _debug_letter(char letter) {
  Serial.print("{");
  Serial.print(letter);
  Serial.println("}");
}

void _debug_color(uint32_t color) {
  Serial.print("[");
  if (color == white) Serial.print("white");
  if (color == blue) Serial.print("blue");
  if (color == pink) Serial.print("pink");
  if (color == green) Serial.print("green");
  if (color == yellow) Serial.print("yellow");
  if (color == red) Serial.print("red");
  Serial.println("]");
}

int letterToLed(char letter) {
  switch (letter) {
    case ' ': return -1;
    case 'a': return led_A;
    case 'b': return led_B;
    case 'c': return led_C;
    case 'd': return led_D;
    case 'e': return led_E;
    case 'f': return led_F;
    case 'g': return led_G;
    case 'h': return led_H;
    case 'i': return led_I;
    case 'j': return led_J;
    case 'k': return led_K;
    case 'l': return led_L;
    case 'm': return led_M;
    case 'n': return led_N;
    case 'o': return led_O;
    case 'p': return led_P;
    case 'q': return led_Q;
    case 'r': return led_R;
    case 's': return led_S;
    case 't': return led_T;
    case 'u': return led_U;
    case 'v': return led_V;
    case 'w': return led_W;
    case 'x': return led_X;
    case 'y': return led_Y;
    case 'z': return led_Z;
    default:  return 0;
  }
}
