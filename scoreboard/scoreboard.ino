#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 132
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Eye parameters
int eyeWidth = 32;
int eyeHeight = 32;
int cornerRadius = 8;
int leftEyeX = 20;
int rightEyeX = 80;
int eyeY = 16;

// Smile parameters
int smileX = 65;
int smileY = 50;
int smileRadius = 5;

void drawEyes(int h) {
  display.clearDisplay();

  // Draw left eye
  display.fillRoundRect(leftEyeX, eyeY + (eyeHeight - h)/2, eyeWidth, h, cornerRadius, SH110X_WHITE);
  // Draw right eye

  display.fillRoundRect(rightEyeX, eyeY + (eyeHeight - h)/2, eyeWidth, h, cornerRadius, SH110X_WHITE);

  // Draw smile (using pixels to simulate arc)
  for (int angle = 20; angle <= 160; angle += 2) { // angles in degrees
    float rad = angle * 3.14159 / 180; // convert to radians
    int x = smileX + smileRadius * cos(rad);
    int y = smileY + smileRadius * sin(rad);
    display.drawPixel(x, y, SH110X_WHITE);
  }
  
  display.display();
}

void blinkEyes() {
  // Close eyes (squash)
  for (int h = eyeHeight; h >= 2; h -= 2) {
    drawEyes(h);
    delay(5); // speed of closing
  }

  // Open eyes
  for (int h = 2; h <= eyeHeight; h += 2) {
    drawEyes(h);
    delay(5); // speed of opening
  }
}

void displayMessage() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 30);
  display.println("Hello World");
  display.display();
}

void setup() {
  Wire.begin(21, 22);

  if (!display.begin(0x3C, true)) {
    while (1);
  }

  randomSeed(analogRead(0));
  
  drawEyes(eyeHeight);
}

void loop() {
  blinkEyes();
  delay(5000);

  drawEyes(eyeHeight);
  delay(10000);

  int chance = random(1, 7);
  if (chance == 1) {
    displayMessage();
    delay(5000);
  }

  drawEyes(eyeHeight);
  delay(2000);

}