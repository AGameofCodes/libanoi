/* 
 * File:   Buf.cpp
 * Author: alex
 * 
 * Created on 14. Februar 2015, 09:53
 */

#include "Buf.h"
#include "exceptions/IndexOutOfBoundsException.h"
#include <cstdlib>
#include <cstring>

#define MEMBLOCK 256

using std::string;
using std::bad_alloc;

Buf::Buf() : Buf(MEMBLOCK)
{
}

Buf::Buf(size_t capacity) : bytes((char*) malloc(capacity)), rIndex(0), wIndex(0), cap(capacity)
{
}

Buf::~Buf()
{
  free(bytes);
}

//write functions

void Buf::write(bool b)
{
  write((char) b);
}

void Buf::write(char c)
{
  checkWriteBound(sizeof (c));

  bytes[wIndex++] = c;
}

void Buf::write(short s)
{
  checkWriteBound(sizeof (s));

  bytes[wIndex++] = (char) (s >> 8);
  bytes[wIndex++] = (char) (s & 255);
}

void Buf::write(int i)
{
  checkWriteBound(sizeof (i));

  bytes[wIndex++] = (char) (i >> 24);
  bytes[wIndex++] = (char) ((i >> 16) & 255);
  bytes[wIndex++] = (char) ((i >> 8) & 255);
  bytes[wIndex++] = (char) (i & 255);
}

void Buf::write(long long l)
{
  checkWriteBound(sizeof (l));

  bytes[wIndex++] = (char) ((l >> 56));
  bytes[wIndex++] = (char) ((l >> 48) & 255);
  bytes[wIndex++] = (char) ((l >> 40) & 255);
  bytes[wIndex++] = (char) ((l >> 32) & 255);
  bytes[wIndex++] = (char) ((l >> 24) & 255);
  bytes[wIndex++] = (char) ((l >> 16) & 255);
  bytes[wIndex++] = (char) ((l >> 8) & 255);
  bytes[wIndex++] = (char) (l & 255);
}

void Buf::write(float f)
{
  checkWriteBound(sizeof (f));

  char* cs = reinterpret_cast<char*> (&f);
  memcpy(bytes + wIndex, cs, sizeof (f));
  wIndex += sizeof (f);
}

void Buf::write(double d)
{
  checkWriteBound(sizeof (d));

  char* cs = reinterpret_cast<char*> (&d);
  memcpy(bytes + wIndex, cs, sizeof (d));
  wIndex += sizeof (d);
}

void Buf::write(char* s)
{
  write(s, strlen(s));
}

void Buf::write(char* s, size_t length)
{
  checkWriteBound(sizeof (int) +length);

  write((int) length);
  memcpy(bytes + wIndex, s, length);
  wIndex += length;
}

void Buf::write(std::string s)
{
  write((char*) s.c_str(), s.length());
}

void Buf::write(Buf *b)
{
  write(b->data(), b->writerIndex());
}

//read functions

bool Buf::readBool()
{
  return (bool)readChar();
}

char Buf::readChar()
{
  checkReadBound(sizeof (char));
  return bytes[rIndex++];
}

short Buf::readShort()
{
  checkReadBound(sizeof (short));

  return bytes[rIndex++] << 8 |
          bytes[rIndex++];
}

int Buf::readInt()
{
  checkReadBound(sizeof (int));

  return bytes[rIndex++] << 24 |
          bytes[rIndex++] << 16 |
          bytes[rIndex++] << 8 |
          bytes[rIndex++];
}

long long Buf::readLong()
{
  checkReadBound(sizeof (long long));

  return ((long) bytes[rIndex++]) << 56 |
          ((long) bytes[rIndex++]) << 48 |
          ((long) bytes[rIndex++]) << 40 |
          ((long) bytes[rIndex++]) << 32 |
          ((long) bytes[rIndex++]) << 24 |
          ((long) bytes[rIndex++]) << 16 |
          ((long) bytes[rIndex++]) << 8 |
          ((long) bytes[rIndex++]);
}

float Buf::readFloat()
{
  checkReadBound(sizeof (float));

  char cs[sizeof (float)];
  memcpy(cs, bytes + rIndex, sizeof (float));
  rIndex += sizeof (float);
  return *reinterpret_cast<float*> (cs);
}

double Buf::readDouble()
{
  checkReadBound(sizeof (double));

  char cs[sizeof (double)];
  memcpy(cs, bytes + rIndex, sizeof (double));
  rIndex += sizeof (double);
  return *reinterpret_cast<double*> (cs);
}

string *Buf::readString()
{
  size_t len = readInt();
  checkReadBound(len);

  char str[len + 1];
  str[len] = '\0';
  memcpy(str, bytes + rIndex, len);
  rIndex += len;
  return new string(str);
}

//index functions

size_t Buf::readerIndex()
{
  return rIndex;
}

size_t Buf::writerIndex()
{
  return wIndex;
}

size_t Buf::capacity()
{
  return cap;
}

void Buf::capacity(size_t newcapacity)
{
  if (wIndex >= newcapacity)
  {
    throw IndexOutOfBoundsException(wIndex, newcapacity);
  }

  bytes = (char*) realloc(bytes, newcapacity);
  if (bytes == NULL)
  {
    throw bad_alloc();
  }
}

size_t Buf::markReaderIndex()
{
  mrIndex = rIndex;
  return mrIndex;
}

size_t Buf::markWriterIndex()
{
  mwIndex = wIndex;
  return mwIndex;
}

size_t Buf::resetReaderIndex()
{
  rIndex = mrIndex;
}

size_t Buf::resetWriterIndex()
{
  wIndex = mwIndex;
}

size_t Buf::discardableBytes()
{
  return rIndex;
}

size_t Buf::readableBytes()
{
  return wIndex - rIndex;
}

size_t Buf::writableBytes()
{
  return cap - wIndex;
}

size_t Buf::discardReadBytes()
{
  size_t discarded = discardableBytes();
  memmove(bytes, bytes + rIndex, rIndex);
  rIndex -= discarded;
  wIndex -= discarded;
  return discarded;
}

char *Buf::data()
{
  return bytes;
}

//bounds check functions

void Buf::checkWriteBound(size_t neededspace)
{
  if (wIndex + neededspace >= cap)
  {
    throw IndexOutOfBoundsException(wIndex + neededspace, cap);
  }
}

void Buf::checkReadBound(size_t neededspace)
{
  if (rIndex + neededspace > wIndex)
  {
    throw IndexOutOfBoundsException(rIndex + neededspace, wIndex);
  }
}
