#ifndef _hPaddle
#define _hPaddle

#import "Arduino.h"

class Paddle {
  public:
    int x, y, wins;
    Paddle(int column, int spazziness);
    void setup();
    void tick(int bmx, int by);
  private:
    int _spazziness;
};

#endif
