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

const char* messages[] = {
  "Don't forget to solve programming problems and Duolingo",
  "Please do Time Management to avoid getting late and do multiple things",
  "Learn everyday and act fast",
  "Sleep is an important part of learning",
  "Beep Boop :)"
};

const int messageCount = sizeof(messages) / sizeof(messages[0]);

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

  int randomIndex = random(messageCount);
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(messages[randomIndex], 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, 30);
  display.println(messages[randomIndex]);

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

  int randomNumber = random(1, 7);
  if (randomNumber == 1) {
    displayMessage();
    delay(5000);
  }

  drawEyes(eyeHeight);
  delay(2000);

}