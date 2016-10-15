// Mike Joseph - michaelpjoseph@gmail.com
// 2016.Oct.13
// Iron Man inspired gesture triggered glove
//  My HW Setup:
//    Arduino Uno
//    LED array and reflector from cheap dollar store type flashlights
//    12 LED NeoPixel Ring
//    5v 5mW Laser diode
//    2x NPN transistors and various resistors for power managemnt to harvested flashlight LED array and laser blaster


#include <Adafruit_NeoPixel.h>

#define NUMBER_PIXELS 12  // pixels on the NeoPixel ring
#define BLASTER   9  // harvested flashlight array for central blaster base
#define LEDPIN    3  // NeoPixel ring
#define LASERPIN  6  // FRICKIN LASER BEAMS

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(BLASTER, OUTPUT);
  pinMode(LASERPIN, OUTPUT);
  strip.begin();
}

int pos = 0, dir = 1; // Position, direction of "eye"
int flexposition;
bool laseralt=1;  //flash laser on and off

void loop() {
  int j;

  flexposition = analogRead(0);
  Serial.println(flexposition);
  //flexposition=540;
  
  if (flexposition >= 520) {   //initiate palm blaster at finger extension
    strip.setPixelColor(pos - 2, 5, 5, 5);
    strip.setPixelColor(pos - 1, 25, 25, 100);
    strip.setPixelColor(pos    , 0, 0, 255);
    strip.setPixelColor(pos + 1, 25, 25, 100);
    strip.setPixelColor(pos + 2, 5, 5, 5);
  
    strip.show();
    delay(20);
  
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
  } else if (flexposition <= 455) {  // initate FRICKIN LASER BEAM
    if (laseralt) {   // flicker laser on and off to appear unstable
      digitalWrite(LASERPIN, HIGH);
    } else {
      digitalWrite(LASERPIN, LOW);
    }
    laseralt=!laseralt;
    delay(40);  // laser flicker rate
  } else {
    pos = 0;
    digitalWrite(LASERPIN, LOW);
    strip.setBrightness(0);
    strip.show();
    strip.setBrightness(255);
  }
}

void lightningcrash() {  // flash sequence for palm blaster
  //-- inital blast start
  for (int i = 0; i <= strip.numPixels(); i++) {
    strip.setPixelColor(i    , 0, 0, 255);
  }
  strip.show();
  delay(15);
  strip.setBrightness(0);
  strip.show();
  strip.setBrightness(255);
  delay(250);
  //-- inital blast end
  //-- rapid blast start
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
  //-- rapid blast end
  //-- random color and decay sequence
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
  strip.setBrightness(255);
  digitalWrite(BLASTER, LOW);
}
