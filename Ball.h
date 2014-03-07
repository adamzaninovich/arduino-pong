#ifndef _hBall
#define _hBall

#import "Arduino.h"
#include "Paddle.h"
  
class Ball {
  public:
    int x, y, mx, my;
    Ball();
    void setup();
    void tick();
    void bounce();
    void bounce(Paddle paddle);
    bool in_abyss();
  private:
    bool _in_abyss;
};

#endif
