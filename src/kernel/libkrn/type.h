#pragma once

#define BOOL unsigned int
#define TRUE 1
#define FALSE 0

#ifdef __cplusplus
template<typename T, typename P>
struct Result {
  union val {
    T* val;
    P* err;
  };
  BOOL is_error;
};

template<typename T>
struct Option {
  T* val;
  BOOL is_valid;
};

#endif
