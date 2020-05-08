#pragma once
#include <stdint.h>

 using namespace std;

#define SAFE_DELETE(p)  if (p != nullptr) { delete p ;p = nullptr;}

 inline int Abs(int x)
 {
	 int y = x >> 31;
	 return (x + y) ^ y;
 }

 inline int Max(int x, int y)
 {
	 return y & ((x - y) >> 31) | x & ~((x - y) >> 31);
 }
