#include <Adafruit_NeoPixel.h>

////// Letter LEDs //////
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

////// Phrases //////
int phraseCount = 23;
String phrases[] = {
  "run",
  "hide"
  "murder",
  "redrum",
  "help",
  "undead",
  "help me",
  "trapped"
  "it escaped",
  "its  here",
  "did you hear that",
  "i see you",
  "hi",
  "beer me",
  "get drunk",
  "fuck trump",
  "fyeah",
  "boo",
  "then who was phone",
  "boo",
  "spoopy",
  "skinwalkers",
  "i want to believe",
};

////// Light Strip //////
#define pixelsInStrip 50   // number of neopixels
#define controlPin 3 // signal control pin 
Adafruit_NeoPixel lightstrip = Adafruit_NeoPixel(pixelsInStrip, controlPin, NEO_GRB + NEO_KHZ800);

////// Configuration //////
#define softStepAmount 10 // How fast the bulbs soft-light and -dim
int colorCount = 6;
uint32_t colors[] = {
  lightstrip.Color(255, 255, 255), // white
  lightstrip.Color(0, 0, 255), // blue
  lightstrip.Color(255, 130, 0), // orange
  lightstrip.Color(0, 255, 0), // green
  lightstrip.Color(255, 180, 0), // yellow
  lightstrip.Color(255, 0, 00) // red
};


////// Functions //////
void setup() {
  // Initialization
  // open the serial port at 9600 bps
  Serial.begin(9600);

  // seed rng with noise from pin 0
  randomSeed(analogRead(0));
  
  // init lightstrip
  lightstrip.begin();
  lightstrip.show(); // Initialize all pixels to 'off'

  // call debug function
  //test();
}

void loop() {
  // pick a random phrase
  int currentPhrase = random(0, phraseCount);
  
  // foreach letter in phrase
  for (int currentLetter = 0; currentLetter < phrases[currentPhrase].length(); currentLetter++) {
    char letter = phrases[currentPhrase].charAt(currentLetter);
    int ledNumber = letterToLed(letter);
    uint32_t color = colors[ledNumber % colorCount];
    
    _debug_letter(letter);
    
    if (ledNumber >= 0) {
      // light LED for letter
      uint32_t brightness = softLightLed(ledNumber, 200);
      delayForRandom(1000, 250);
      softDarkenLed(ledNumber, brightness);
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
  delayForRandom(7500, 2500);
}

void test() {
  delay(2000);

  Serial.println("Starting LED test");
  for (char currentLetter = 0; currentLetter < pixelsInStrip; currentLetter++) {
    hardLightLed(currentLetter, 200);
    delay(150);
    hardDarkenLed(currentLetter);
    delay(50);
  }
  Serial.println("Finished LED test");
}

int softLightLed(int ledNumber, uint32_t toColor) {
  int currentBrightness = 0;
  
  for (; currentBrightness < toBrightness; currentBrightness += softStepAmount)
  {    
    lightstrip.setPixelColor(ledNumber, currentBrightness, currentBrightness, currentBrightness);
    lightstrip.show();
    delay(25);
  }

  lightstrip.setPixelColor(ledNumber, currentBrightness, currentBrightness, currentBrightness);
  lightstrip.show();
  
  //_debug_message(ledNumber, "soft-lit to", currentBrightness, currentBrightness, currentBrightness);
  return currentBrightness;
}

int hardLightLed(int ledNumber, int brightness) {
    lightstrip.setPixelColor(ledNumber, brightness, brightness, brightness);
    lightstrip.show();
    
    //_debug_message(ledNumber, "hard-lit to", brightness, brightness, brightness);
    return brightness;
}

int softDarkenLed(int ledNumber, int startingBrightness) {
  int currentBrightness = startingBrightness;
  
  for (; currentBrightness > 0; currentBrightness -= softStepAmount) {
    lightstrip.setPixelColor(ledNumber, currentBrightness, currentBrightness, currentBrightness);
    lightstrip.show();
    delay(10); // Arbitrary wait-a-bit, dimming seems "faster" than lighting
  }

  currentBrightness = 0;
  lightstrip.setPixelColor(ledNumber, 0, 0, 0);
  lightstrip.show();
  
  //_debug_message(ledNumber, "soft-dimmed to", currentBrightness, currentBrightness, currentBrightness);
  return currentBrightness;
}

int hardDarkenLed(int ledNumber) {
  int brightness = 0;
  lightstrip.setPixelColor(ledNumber, brightness, brightness, brightness);
  lightstrip.show();
  
  //_debug_message(ledNumber, "hard-dimmed to", brightness, brightness, brightness);
  return brightness;
}

//// Debug ////
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

//// Utility ////
int delayForRandom(int median, int spread) {
  delay(random(median - spread > 0 ? median - spread : 0, median + spread));
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




