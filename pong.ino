#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "Ball.h"
#include "Paddle.h"

#define SPAZZINESS 1
#define FRAME_TIME 70

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
Ball ball = Ball();
Paddle left = Paddle(0, SPAZZINESS);
Paddle right = Paddle(7, SPAZZINESS);

void asplode() {
  for(int i=0; i < 12; ++i) {
    int color = LED_RED;
    if(i%2==0) color = LED_YELLOW;
    matrix.drawCircle(ball.x,ball.y,i, color);
    matrix.writeDisplay();
    delay(FRAME_TIME);
  }
  delay(FRAME_TIME*4);
}

void print_score() {
  int columns = (floor(log10(abs(left.wins))) + floor(log10(abs(right.wins))) + 3) * 6;
  columns = max(columns, 18);
  matrix.setTextWrap(false);
  matrix.setTextSize(1);
  matrix.setTextColor(LED_GREEN);
  for (int8_t x=7; x>=-columns; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print(left.wins);
    matrix.print("-");
    matrix.print(right.wins);
    matrix.writeDisplay();
    delay(FRAME_TIME);
  }
}

void draw_frame() {
  int l_color = LED_GREEN, r_color = LED_GREEN;
  if(left.wins < right.wins) l_color = LED_YELLOW;
  if(left.wins > right.wins) r_color = LED_YELLOW;
  matrix.drawPixel(ball.x, ball.y, LED_RED);
  matrix.drawPixel(0,left.y, l_color);
  matrix.drawPixel(0,left.y+1, l_color);
  matrix.drawPixel(7,right.y, r_color);
  matrix.drawPixel(7,right.y+1, r_color);
  matrix.writeDisplay();
}

void start() {
  print_score();
  ball.setup();
  left.setup();
  right.setup();
}

void setup() {
  analogReference(EXTERNAL);
  Serial.begin(9600);
  matrix.begin(0x70);
  matrix.setRotation(1);
  start();
}

//void serial_update() {
//  Serial.print(ball.x);
//  Serial.print(',');
//  Serial.print(ball.y);
//  Serial.print(' ');
//  if(ball.mx > 0) Serial.print('>');
//  if(ball.mx < 0) Serial.print('<');
//  if(ball.my > 0) Serial.print('v');
//  if(ball.my < 0) Serial.print('^');
//  Serial.println();
//}

void loop() {
  matrix.clear();
  randomSeed(analogRead(A7));

  ball.tick();
  left.tick(ball.mx, ball.y);
  right.tick(ball.mx, ball.y);
  ball.bounce(left);
  ball.bounce(right);
  ball.bounce();
  if(ball.in_abyss()) {
    if(ball.mx < 0) right.wins++;
    if(ball.mx > 0) left.wins++;
    asplode();
    start();
  }
  draw_frame();
  delay(FRAME_TIME);
}

