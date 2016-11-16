//*******1*********2*********3*********4*********4*********5*********6*********7*********8
#ifndef KMPLAYER_H
#define KMPLAYER_H
#include "Arduino.h"
#include <SoftwareSerial.h>

class KmPlayer{
  public:
    KmPlayer(int rx, int tx, int busy, int io, int debug);
    void begin();
    void volume(int v);
    void play(int n);
    void next();
    void pause();
    void reset();
    void stop();
    void normal();
    void ioplay();
    bool silent();

  private:
    void send(char cmd, unsigned int op);
};

#endif
