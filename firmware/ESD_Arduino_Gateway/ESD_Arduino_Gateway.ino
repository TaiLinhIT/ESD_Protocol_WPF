#include <Arduino.h>
const byte SOF1=0xAA,SOF2=0x55,EOF1=0x0D,EOF2=0x0A; uint32_t lastSeq=0;
uint16_t be16(byte*p){return ((uint16_t)p[0]<<8)|p[1];}uint32_t be32(byte*p){return ((uint32_t)p[0]<<24)|((uint32_t)p[1]<<16)|((uint32_t)p[2]<<8)|p[3];}
void put32(byte*p,uint32_t v){p[0]=v>>24;p[1]=v>>16;p[2]=v>>8;p[3]=v;}
void TestTag(byte*d,uint16_t n,byte*t){uint32_t h=2166136261UL;for(uint16_t i=0;i<n;i++){h^=d[i];h*=16777619UL;}for(byte i=0;i<16;i++){h^=i*31;h*=16777619UL;t[i]=(h>>((i%4)*8))&255;}}
void Ack(uint32_t id,uint32_t seq){byte b[64],tag[16];uint16_t p=0;b[p++]=SOF1;b[p++]=SOF2;b[p++]=1;b[p++]=0;put32(&b[p],id);p+=4;b[p++]=0;b[p++]=0xF0;put32(&b[p],seq);p+=4;put32(&b[p],millis()/1000);p+=4;b[p++]=0;b[p++]=1;b[p++]=0;TestTag(&b[2],p-2,tag);memcpy(&b[p],tag,16);p+=16;b[p++]=EOF1;b[p++]=EOF2;Serial.write(b,p);}
void setup(){Serial.begin(115200);}void loop(){static byte b[300];static uint16_t n=0;while(Serial.available()){byte c=Serial.read();if(n==0&&c!=SOF1)continue;if(n==1&&c!=SOF2){n=0;continue;}b[n++]=c;if(n>=20){uint16_t len=be16(&b[18]);if(len>256){n=0;continue;}uint16_t total=38+len;if(n==total){if(b[n-2]==EOF1&&b[n-1]==EOF2){uint32_t id=be32(&b[4]),seq=be32(&b[10]);if(seq>lastSeq){lastSeq=seq;Ack(id,seq);}}n=0;}else if(n>total)n=0;}if(n>=sizeof(b))n=0;}}
