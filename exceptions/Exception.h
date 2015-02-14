/* 
 * File:   Exception.h
 * Author: alex
 *
 * Created on 12. Februar 2015, 22:43
 */

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include <exception>

using std::exception;

class Exception : public exception
{
public:
  Exception();
  Exception(char* message);
  Exception(const Exception& orig);
  virtual ~Exception();
  virtual const char* what() const noexcept;
private:
  char* message;
};

#endif	/* EXCEPTION_H */

