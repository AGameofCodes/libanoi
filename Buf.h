/* 
 * File:   Buf.h
 * Author: alex
 *
 * Created on 14. Februar 2015, 09:53
 */

#ifndef BUF_H
#define	BUF_H

#include <string>
#include <cstdlib>

class Buf
{
public:
  Buf();
  Buf(size_t initialSize);

//write functions
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
  void write(Buf *b);

//read functions
  bool readBool();
  char readChar();
  short readShort();
  int readInt();
  long long readLong();
  float readFloat();
  double readDouble();
  std::string *readString();

//index funtions
  size_t readerIndex();
  size_t writerIndex();
  
  char* data();
private:
  Buf(const Buf& orig);
  virtual ~Buf();
  
  void checkWriteBound(size_t neededspace);
  void checkReadBound(size_t neededspace);

  char* bytes;
  size_t rIndex;
  size_t wIndex;
  size_t allocedSize;
};

#endif	/* BUF_H */

