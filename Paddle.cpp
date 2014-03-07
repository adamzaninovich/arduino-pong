#import "Paddle.h"

Paddle::Paddle(int column, int spazziness) {
  _spazziness = spazziness;
  x = column;
  wins = 0;
  setup();
}

void Paddle::setup() {
  y = 0;
}

void Paddle::tick(int bmx, int by) {
  int lower = 0-_spazziness;
  int upper = _spazziness+1;
  if((bmx < 0 && x < 4) || (bmx > 0 && x > 3)) y = by + random(lower, upper);
  if(y < 0) y = 0;
  if(y > 6) y = 6;
}

