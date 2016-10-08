
#include <Adafruit_NeoPixel.h>

#define NUMBER_PIEXEL 12
#define BLASTER   8  // harvested flashlight array for central blaster base
#define LEDPIN    3  // NeoPixel ring

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIEXEL, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(BLASTER, OUTPUT);
  strip.begin();
}

int pos = 0, dir = 1; // Position, direction of "eye"
int flexposition;

void loop() {
  int j;

  //flexposition = analogRead(0);
  //Serial.println(flexposition);
  
  flexposition = 500;
  
  if (flexposition >= 490) {
    strip.setPixelColor(pos - 2, 5, 5, 5);
    strip.setPixelColor(pos - 1, 25, 25, 100);
    strip.setPixelColor(pos    , 0, 0, 255);
    strip.setPixelColor(pos + 1, 25, 25, 100);
    strip.setPixelColor(pos + 2, 5, 5, 5);
  
    strip.show();
    delay(20);
  
    // Rather than being sneaky and erasing just the tail pixel,
    // it's easier to erase it all and draw a new one next time.
    for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);
  
    // Bounce off ends of strip
    pos += dir;
    if(pos < 0) {
      //flash(pos);
      lightningcrash();
      pos = 1;
      dir = -dir;
    } else if (pos >= strip.numPixels()) {
      //flash(pos);
      pos = strip.numPixels() - 2;
      dir = -dir;
    }
  } else {
    pos = 0;
    strip.setBrightness(0);
    strip.show();
    strip.setBrightness(255);
  }
}

void flash(int pos) {
  for (int i = 0; i <= 4; i++) {
    strip.setPixelColor(pos - 2, 255, 255, 255); // Dark red
    strip.setPixelColor(pos - 1, 255, 255, 255); // Medium red
    strip.setPixelColor(pos    , 255, 255, 255); // Center pixel is brightest
    strip.setPixelColor(pos + 1, 255, 255, 255); // Medium red
    strip.setPixelColor(pos + 2, 255, 255, 255); // Dark red
    strip.show();
    delay(75);
    for(int j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);
    strip.show();
    delay(75);
  }
}

void lightningcrash() {
  for (int i = 0; i <= strip.numPixels(); i++) {
    strip.setPixelColor(i    , 0, 0, 255);
  }
  strip.show();
  delay(15);
  strip.setBrightness(0);
  strip.show();
  strip.setBrightness(255);
  delay(250);
  for (int times = 0; times < 4; times++) {
    for (int i = 0; i <= strip.numPixels(); i++) {
      strip.setPixelColor(i    , 255, 255, 255);
    }
    digitalWrite(BLASTER, HIGH);
    strip.show();
    delay(50);
    digitalWrite(BLASTER, LOW);
    strip.setBrightness(0);
    strip.show();
    strip.setBrightness(255);
    delay(50);
  }
  bool alt=true;
  for (int i = 0; i <= strip.numPixels(); i++) {
    int red=rand() % 255;
    int gre=rand() % 255;
    int blu=rand() % 255;
    strip.setPixelColor(i, strip.Color(red, gre, blu));
  }
  strip.show();
  for (int i = 255; i >= 0; i-- ) {
    strip.setBrightness(i);
    strip.show();
    delay(2);
  }
  delay(10);
  //delay(10000);
  strip.setBrightness(255);
  digitalWrite(BLASTER, LOW);
}
    
