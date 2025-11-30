#pragma once

#define BOOL unsigned int
#define TRUE 1
#define FALSE 0

#ifdef __cplusplus
template<typename T, typename P>
struct Result {
  union val {
    T val;
    P err;
  };
  BOOL has_value;
};

#endif
