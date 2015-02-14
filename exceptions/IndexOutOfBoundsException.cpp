/* 
 * File:   IndexOutOfBoundsException.cpp
 * Author: alex
 * 
 * Created on 14. Februar 2015, 12:03
 */

#include "IndexOutOfBoundsException.h"

IndexOutOfBoundsException::IndexOutOfBoundsException(size_t index, size_t max)
: Exception("index was " + index + "but size was " + max), index(index), max(max)
{
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException& orig)
{
}

IndexOutOfBoundsException::~IndexOutOfBoundsException()
{
}

