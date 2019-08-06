#pragma once
#include <stdint.h>

using namespace std;

#define SAFE_DELETE(p)  if (p != NULL) { delete p ;p = NULL;}
