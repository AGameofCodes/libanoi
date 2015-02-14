/* 
 * File:   IndexOutOfBoundsException.h
 * Author: alex
 *
 * Created on 14. Februar 2015, 12:03
 */

#ifndef INDEXOUTOFBOUNDSEXCEPTION_H
#define	INDEXOUTOFBOUNDSEXCEPTION_H

#include "Exception.h"
#include <cstdlib>

class IndexOutOfBoundsException : public Exception
{
public:
  IndexOutOfBoundsException(size_t index, size_t max);
  IndexOutOfBoundsException(const IndexOutOfBoundsException& orig);
  virtual ~IndexOutOfBoundsException();
private:
  size_t index;
  size_t max;
};

#endif	/* INDEXOUTOFBOUNDSEXCEPTION_H */

