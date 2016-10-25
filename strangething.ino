#include <Adafruit_NeoPixel.h>

////////////////////////////////////////////////////////////////////////////////
//// Configuration /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Phrases
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
#define pixelsInStrip 50 // number of neopixels
#define controlPin 3 // signal control pin 
Adafruit_NeoPixel lightstrip = Adafruit_NeoPixel(pixelsInStrip, controlPin, NEO_GRB + NEO_KHZ800);

// Colors & Fading
#define softStepAmount 20 // How many `for` steps it takes to soft-light and soft-dim each LED (% of 255 to dim each `for` step)
int colorCount = 6;
uint32_t colors[] = {
  lightstrip.Color(255, 255, 255), // white
  lightstrip.Color(0, 0, 255), // blue
  lightstrip.Color(255, 0, 255), // pink
  lightstrip.Color(0, 255, 0), // green
  lightstrip.Color(255, 255, 0), // yellow
  lightstrip.Color(255, 0, 00) // red
};

// LED Letters
#define led_A 0
#define led_B 2
#define led_C 4
#define led_D 6
#define led_E 8
#define led_F 10
#define led_G 12
#define led_H 14
#define led_I 32
///
#define led_J 30
#define led_K 28
#define led_L 26
#define led_M 24
#define led_N 22
#define led_O 20
#define led_P 18
#define led_Q 16
///
#define led_R 34
#define led_S 36
#define led_T 38
#define led_U 40
#define led_V 42
#define led_W 44
#define led_X 46
#define led_Y 48
#define led_Z 49


////////////////////////////////////////////////////////////////////////////////
//// Functions /////////////////////////////////////////////////////////////////
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
  // Random pick an effect to display
  
  uint32_t color;
  switch (13/*random(0, 15)*/) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: 
    case 8:
    case 9:
    case 10:
      // Spell a word
      fx_LightPhrase(phrases[random(0, phraseCount)]);
      break;
    case 11:
      // Flash red
      fx_FlashColor(lightstrip.Color(255, 0, 00));
      softDarkenStrip(color);
      break;
    case 12:
      // Flash a random color
      color = colors[random(0, colorCount)];
      fx_FlashColor(color);
      softDarkenStrip(color);
      break;
    case 13:
      // Color line-walk
      color = colors[random(0, colorCount)];
      fx_LineWalk(color);
      softDarkenStrip(color);
      break;
    case 14:
      // Flash rando-color, then pop
      color = colors[random(0, colorCount)];
      fx_FlashColor(color);
      fx_LightPop(lightstrip.Color(255, 255, 255));
      break;
      
    //TODO: line-walk rando color (?)
    //TODO: 
  }

  // Wait between effects
  delayForRandom(7500, 2500);
}

void test_default() {
  delay(1000);

  Serial.println("Starting LED test...");
  fx_LineWalk(lightstrip.Color(255, 255, 255));
  softDarkenStrip(lightstrip.Color(255, 255, 255));
  Serial.println("Finished LED test!");
  
  fx_LightPhrase("wtf");
  delay(750);
}


////////////////////////////////////////////////////////////////////////////////
//// Effects ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void fx_LightPhrase(String phrase) {  
  // foreach letter in phrase
  for (int currentLetter = 0; currentLetter < phrase.length(); currentLetter++) {
    char letter = phrase.charAt(currentLetter);
    int ledNumber = letterToLed(letter);
    uint32_t color = colors[random(0, colorCount) % colorCount]; // was: colors[ledNumber%colorCount]
    
    _debug_color(ledNumber % colorCount);
    _debug_letter(letter);
    
    if (ledNumber >= 0) {
      // light LED for letter
      softLightLed(ledNumber, color);
      delayForRandom(1000, 250);
      softDarkenLed(ledNumber, color);
      delayForRandom(1000, 250);
    } else {
      // wait for "space"
      delayForRandom(500, 250);
      _debug_letter(' ');
      delayForRandom(1000, 125);
    }
  }

  // wait between words
  _debug_letter('-');
}

void fx_FlashColor(uint32_t color) {
  delay(1500);
  
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {  
    for (int currentLight = 0; currentLight < pixelsInStrip; currentLight++) {
      int r = color_clampVal(currentStep * (color_GetRVal(color) / softStepAmount));
      int g = color_clampVal(currentStep * (color_GetGVal(color) / softStepAmount));
      int b = color_clampVal(currentStep * (color_GetBVal(color) / softStepAmount));
      
      lightstrip.setPixelColor(
        currentLight,
        g,
        r,
        b
      );
    }
    
    lightstrip.show();
    delay((softStepAmount - currentStep) * 7);
  }

  delay(500);
}

void fx_LineWalk(uint32_t color) {
  for (int currentLed = 0; currentLed < pixelsInStrip; currentLed++) {
      hardLightLed(currentLed, color);
      delay(50);
  }
  delayForRandom(1000, 250);
}

void fx_LightPop(uint32_t color) {
  
}


////////////////////////////////////////////////////////////////////////////////
//// Utilitiy Functions ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

uint32_t softLightLed(int ledNumber, uint32_t toColor) {  
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {
    int r = color_clampVal(currentStep * (color_GetRVal(toColor) / softStepAmount));
    int g = color_clampVal(currentStep * (color_GetGVal(toColor) / softStepAmount));
    int b = color_clampVal(currentStep * (color_GetBVal(toColor) / softStepAmount));
    
    lightstrip.setPixelColor(ledNumber,
      (g < 10 ? 0 : g), // turn off early
      (r < 10 ? 0 : r),
      (b < 10 ? 0 : b)
    );
    lightstrip.show();
    
    //_debug_message(ledNumber, "soft-lit to", r, g, b);
    delay(25);
  }

  //lightstrip.setPixelColor(ledNumber, color_GetRVal(toColor), color_GetGVal(toColor), color_GetBVal(toColor));
  lightstrip.show();
  
  _debug_message(ledNumber, "soft-lit to", color_GetRVal(toColor), color_GetGVal(toColor), color_GetBVal(toColor));
  return toColor;
}

uint32_t hardLightLed(int ledNumber, uint32_t toColor) {
  lightstrip.setPixelColor(ledNumber, color_GetGVal(toColor), color_GetRVal(toColor), color_GetBVal(toColor));
    lightstrip.show();
    
    //_debug_message(ledNumber, "hard-lit to",color_GetRVal(toColor), color_GetGVal(toColor), color_GetBVal(toColor));
    return toColor;
}

uint32_t softDarkenLed(int ledNumber, uint32_t fromColor) {  
  for (int currentStep = 0; currentStep < softStepAmount; currentStep++) {  
    int r = color_clampVal(color_GetRVal(fromColor) - currentStep * (color_GetRVal(fromColor) / softStepAmount));
    int g = color_clampVal(color_GetGVal(fromColor) - currentStep * (color_GetGVal(fromColor) / softStepAmount));
    int b = color_clampVal(color_GetBVal(fromColor) - currentStep * (color_GetBVal(fromColor) / softStepAmount));
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
  
  _debug_message(ledNumber, "soft-dimmed to", 0, 0, 0);
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
    for (int currentLight = 0; currentLight < pixelsInStrip; currentLight++) {
      int r = color_clampVal(color_GetRVal(fromColor) - currentStep * (color_GetRVal(fromColor) / softStepAmount));
      int g = color_clampVal(color_GetGVal(fromColor) - currentStep * (color_GetGVal(fromColor) / softStepAmount));
      int b = color_clampVal(color_GetBVal(fromColor) - currentStep * (color_GetBVal(fromColor) / softStepAmount));
      lightstrip.setPixelColor(
        currentLight,
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
//// Debug Functions ///////////////////////////////////////////////////////////
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

void _debug_color(int colorNumber) {
  Serial.print("[");
  switch (colorNumber) {
    case 0: Serial.print("white"); break;
    case 1: Serial.print("blue"); break;
    case 2: Serial.print("pink"); break;
    case 3: Serial.print("green"); break;
    case 4: Serial.print("yellow"); break;
    case 5: Serial.print("red"); break;
  }
  Serial.println("]");
}


////////////////////////////////////////////////////////////////////////////////
//// Data //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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

