#pragma once
#include <stdint.h>

#ifdef WIN32
// #include "WarningException.h"
// #include <SDKDDKVer.h>
// #include "winsock2.h"
// #include <stdio.h>
// #include <tchar.h>
// #include <assert.h>
// #include <string>
// //typedef char				int8_t;
// typedef unsigned char		uint8_t;
// typedef short				int16_t;
// typedef unsigned short		uint16_t;
// typedef int					int32_t;
// typedef unsigned int		uint32_t;
// typedef long long			int64_t;
// typedef unsigned long long	uint64_t;
// #define snprintf _snprintf

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include <fstream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#endif

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
