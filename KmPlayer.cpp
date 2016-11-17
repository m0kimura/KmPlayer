//*******1*********2*********3*********4*********4*********5*********6*********7*********8
#include "KmPlayer.h"

SoftwareSerial Mp3(1, 2);
int Prx, Ptx, Pbusy, Pio, Debug;
char Buf[10];


KmPlayer::KmPlayer(int rx, int tx, int busy, int io, int debug){
  Debug=debug; Prx=rx; Ptx=tx; Pbusy=busy; Pio=io;
}


void KmPlayer::begin(){

  if(Debug){Serial.begin(115200);}

  pinMode(Prx, INPUT); pinMode(Ptx, OUTPUT);
  Mp3=SoftwareSerial(Prx, Ptx);
  Mp3.begin(9600);

  if(Pbusy>0){pinMode(Pbusy, INPUT);}
  if(Pio>0){pinMode(Pio, OUTPUT); digitalWrite(Pio, LOW);}

  delay(100);

}


void KmPlayer::volume(int v){KmPlayer::send(0x06, v);}
void KmPlayer::play(int n){KmPlayer::send(0x0D, n);}
void KmPlayer::next(){KmPlayer::send(0x01, 0);}
void KmPlayer::pause(){KmPlayer::send(0x0E, 0);}
void KmPlayer::reset(){KmPlayer::send(0x0C, 0);}
void KmPlayer::stop(){KmPlayer::send(0x16, 0);}
void KmPlayer::normal(){KmPlayer::send(0x0B, 0);}
void KmPlayer::ioplay(){
  if(Pio>0){
    delay(300); digitalWrite(Pio, HIGH); delay(300); digitalWrite(Pio, LOW);
  }
}
bool KmPlayer::silent(){
  if(Pbusy>0){if(digitalRead(Pbusy)){
    return false;
  }}
  return true;
}

void KmPlayer::send(char cmd, unsigned int op){

  Buf[0]=0x7E; Buf[1]=0xFF; Buf[2]=0x06; Buf[9]=0xEF;
  Buf[3]=cmd; Buf[4]=0x00;
  Buf[5]=(uint8_t)(op>>8); Buf[6]=(uint8_t)op;

  unsigned int sum = 0; int x;

  for(int i=2; i<7; i++){sum+=(int)Buf[i];} sum=~sum+1;

  Buf[7]=(uint8_t)(sum>>8); Buf[8]=(uint8_t)sum;


  for (int i=0; i<10; i++) {Mp3.write(Buf[i]);}
  if(Debug){
    Serial.print("\nCMD:");
    for (int i=0; i<10; i++) {x=Buf[i]; Serial.print(String(x)+" ");}
  }

}

