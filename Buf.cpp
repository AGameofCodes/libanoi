/* 
 * File:   Buf.cpp
 * Author: alex
 * 
 * Created on 14. Februar 2015, 09:53
 */

#include "Buf.h"
#include <cstdlib>
#include <cstring>

#define MEMBLOCK 256

using std::string;
using std::bad_alloc;

Buf::Buf() : Buf(256)
{
}

Buf::Buf(size_t initialSize) : data((char*) malloc(initialSize)), readerIndex(0), writerIndex(0), allocedSize(initialSize)
{
}

Buf::Buf(const Buf& orig)
{
}

Buf::~Buf()
{
  free(data);
}

void Buf::write(bool b)
{
  write((char) b);
}

void Buf::write(char c)
{
  checkWriteBound(sizeof (c));

  data[writerIndex] = c;
  writerIndex++;
}

void Buf::write(short s)
{
  checkWriteBound(sizeof (s));

  data[writerIndex++] = (char) (s >> 8);
  data[writerIndex++] = (char) (s & 255);
}

void Buf::write(int i)
{
  checkWriteBound(sizeof (i));

  data[writerIndex++] = (char) (i >> 24);
  data[writerIndex++] = (char) ((i >> 16) & 255);
  data[writerIndex++] = (char) ((i >> 8) & 255);
  data[writerIndex++] = (char) (i & 255);
}

void Buf::write(long long l)
{
  checkWriteBound(sizeof (l));

  data[writerIndex++] = (char) ((l >> 56));
  data[writerIndex++] = (char) ((l >> 48) & 255);
  data[writerIndex++] = (char) ((l >> 40) & 255);
  data[writerIndex++] = (char) ((l >> 32) & 255);
  data[writerIndex++] = (char) ((l >> 24) & 255);
  data[writerIndex++] = (char) ((l >> 16) & 255);
  data[writerIndex++] = (char) ((l >> 8) & 255);
  data[writerIndex++] = (char) (l & 255);
}

void Buf::write(float f)
{
  checkWriteBound(sizeof (f));

  char* cs = reinterpret_cast<char*> (&f);
  memcpy(data + writerIndex, cs, sizeof (f));
  writerIndex += sizeof (f);
}

void Buf::write(double d)
{
  checkWriteBound(sizeof (d));

  char* cs = reinterpret_cast<char*> (&d);
  memcpy(data + writerIndex, cs, sizeof (d));
  writerIndex += sizeof (d);
}

void Buf::write(char* s)
{
  write(s, strlen(s));
}

void Buf::write(char* s, size_t length)
{
  checkWriteBound(sizeof (int) +length);

  write((int) length);
  memcpy(data + writerIndex, s, length);
}

void Buf::write(std::string s)
{
  write((char*) s.c_str(), s.length());
}

bool Buf::readBool()
{
  return (bool)readChar();
}

char Buf::readChar()
{
  checkReadBound(sizeof (char));
  return data[readerIndex++];
}

short Buf::readShort()
{
  checkReadBound(sizeof (short));

  return data[readerIndex++] << 8 |
          data[readerIndex++];
}

int Buf::readInt()
{
  checkReadBound(sizeof (int));

  return data[readerIndex++] << 24 |
          data[readerIndex++] << 16 |
          data[readerIndex++] << 8 |
          data[readerIndex++];
}

long long Buf::readLong()
{
  checkReadBound(sizeof (long long));

  return ((long)data[readerIndex++]) << 56 |
          ((long)data[readerIndex++]) << 48 |
          ((long)data[readerIndex++]) << 40 |
          ((long)data[readerIndex++]) << 32 |
          ((long)data[readerIndex++]) << 24 |
          ((long)data[readerIndex++]) << 16 |
          ((long)data[readerIndex++]) << 8 |
          ((long)data[readerIndex++]);
}

float Buf::readFloat()
{
  checkReadBound(sizeof (float));

  char cs[sizeof (float)];
  memcpy(cs, data + readerIndex, sizeof (float));
  readerIndex += sizeof (float);
  return *reinterpret_cast<float*> (cs);
}

double Buf::readDouble()
{
  checkReadBound(sizeof (double));

  char cs[sizeof (double)];
  memcpy(cs, data + readerIndex, sizeof (double));
  readerIndex += sizeof (double);
  return *reinterpret_cast<double*> (cs);
}

string *Buf::readString()
{
  size_t len = readInt();
  checkReadBound(len);

  char str[len + 1];
  str[len] = '\0';
  memcpy(str, data + readerIndex, len);
  readerIndex += len;
  return new string(str);
}

void Buf::checkWriteBound(size_t neededspace)
{
  if (writerIndex + neededspace >= allocedSize)
  {
    char *data = (char*) realloc(data, allocedSize + MEMBLOCK);
    if (data == NULL)
    {
      throw bad_alloc();
    }
  }
}

void Buf::checkReadBound(size_t neededspace)
{
  if (readerIndex + neededspace > writerIndex)
  {
    //throw index outof bound exception
  }
}
