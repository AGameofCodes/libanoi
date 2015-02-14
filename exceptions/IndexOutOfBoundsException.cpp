/* 
 * File:   IndexOutOfBoundsException.cpp
 * Author: alex
 * 
 * Created on 14. Februar 2015, 12:03
 */

#include <string>

#include "IndexOutOfBoundsException.h"

using std::string;

IndexOutOfBoundsException::IndexOutOfBoundsException(size_t index, size_t max)
: Exception((char*)(string("index was ") + std::to_string(index) + string("but size was ") + std::to_string(max)).c_str()), index(index), max(max)
{
}

IndexOutOfBoundsException::IndexOutOfBoundsException(const IndexOutOfBoundsException& orig)
{
}

IndexOutOfBoundsException::~IndexOutOfBoundsException()
{
}

