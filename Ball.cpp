#import "Ball.h"

Ball::Ball() {
  setup();
}

void Ball::setup() {
  x = random(3, 5);
  y = random(1, 7);
  my = random(-1, 1);
  mx = random(-1, 1);
  _in_abyss = false;
  if(mx==0) setup();
}

void Ball::bounce(Paddle paddle) {
  // bounce off left
  if(paddle.x == 0 && x == 1) {
    if(y == paddle.y-1 && my >= 0) {
      mx = 1;
      my -= 2;
    }
    if(y == paddle.y) {
      mx = 1;
      my -= 1;
    }
    if(y == paddle.y+1) {
     mx = 1;
     my += 1;
    }
    if(y == paddle.y+2 && my <= 0) {
     mx = 1;
     my += 2;
    }
  }
  // bounce off right
  if(paddle.x == 7 && x == 6) {
    if(y == paddle.y-1 && my >= 0) {
      mx = -1;
      my -= 2;
    }
    if(y == paddle.y) {
      mx = -1;
      my -= 1;
    }
    if(y == paddle.y+1) {
     mx = -1;
     my += 1;
    }
    if(y == paddle.y+2 && my <= 0) {
     mx = -1;
     my += 2;
    }
  }
}

void Ball::bounce() {
  // bounce off floor/ceiling
  if(y <= 0) {
    y = 0;
    my = 1;
  }
  if(y >= 7) {
    y = 7;
    my = -1;
  }
}

void Ball::tick() {
  // lose
  if(x == 0 || x == 7) _in_abyss = true;
  // move
  x += mx;
  y += my;

}
bool Ball::in_abyss() { return _in_abyss; }

