/* 
 * File:   Buf.h
 * Author: alex
 *
 * Created on 14. Februar 2015, 09:53
 */

#ifndef BUF_H
#define	BUF_H

//#define uint unsigned int
#include <string>
#include <stdlib.h>

class Buf
{
public:
  Buf();
  Buf(size_t initialSize);

  void write(bool b);
  void write(char c);
  void write(short s);
  void write(int i);
  void write(long long l);
  void write(float f);
  void write(double d);
  void write(char* s);
  void write(char* s, size_t length);
  void write(std::string s);
  
  bool readBool();
  char readChar();
  short readShort();
  int readInt();
  long long readLong();
  float readFloat();
  double readDouble();
  std::string *readString();
  
  void checkWriteBound(size_t neededspace);
  void checkReadBound(size_t neededspace);
private:
  Buf(const Buf& orig);
  virtual ~Buf();

  char* data;
  size_t readerIndex;
  size_t writerIndex;
  size_t allocedSize;
};

#endif	/* BUF_H */

