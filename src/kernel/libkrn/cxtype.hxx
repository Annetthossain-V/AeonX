#pragma once
#include <stddef.h>

namespace type
{

class String
{
public:

private:
  char* ptr;
  size_t len;
  size_t cap;
};

}
