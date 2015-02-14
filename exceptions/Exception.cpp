/* 
 * File:   Exception.cpp
 * Author: alex
 * 
 * Created on 12. Februar 2015, 22:43
 */

#include "Exception.h"

Exception::Exception() : exception(), message('\0')
{
}

Exception::Exception(char* message) : exception(), message(message)
{
}

Exception::Exception(const Exception& orig)
{
}

Exception::~Exception()
{
}

const char* Exception::what() const noexcept
{
  return message;
}

