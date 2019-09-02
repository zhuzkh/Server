#pragma once

#if defined (__GNUC__)
#include <stdint.h>
#include <inttypes.h>
#include <cstddef>

# if __WORDSIZE == 64
#  define __I64_FORMAT__	"%ld"
#  define __U64_FORMAT__	"%lu"
# else
#  define __I64_FORMAT__	"%lld"
#  define __U64_FORMAT__	"%llu"
# endif

#endif // __GNUC__

#if defined (_MSC_VER)
#include <stdio.h>

#endif	// _MSC_VER
#include "MemoryPool.h"

enum
{
	SIZE_MSG_BUFF = (uint16_t)0xFFFF,		// 协议包编解码缓冲区的最大长度
	MSG_SS_HEAD_LENGTH = (uint16_t)32,			// server to server协议头部的长度
	MSG_CS_HEAD_LENGTH = (uint16_t)10,			// client to server协议头部的长度
	MAX_C2S_MSG_BODY_SIZE = (uint16_t)0x1400,		// 客户端至服务器的协议体最大长度
	MAX_S2C_MSG_BODY_SIZE = (uint16_t)0x8000,		// 服务器至客户端的协议体最大长度
	SESSION_KEY_SIZE = 16,					// 此长度为16不变
	MAX_GAME_TAG_LENGTH = 32,
};

enum
{
	PACKET_FLAG_COMPRESS_MASK = (uint16_t)0x0003,
	PACKET_FLAG_CRYPT_MASK = (uint16_t)0x000C,
	PACKET_FLAG_MULTICAST_MASK = (uint16_t)0x0010,
	PACKET_FLAG_BROADCAST_MASK = (uint16_t)0x0020,
	PACKET_FLAG_ROUTER_MASK = (uint16_t)0x0040,
	PACKET_FLAG_CLOSE_SOCKET_MASK = (uint16_t)0x0080,
};

enum
{
	COMPRESS_ALGORITHM_NONE = (uint16_t)0x0000,	// 无压缩	 
	COMPRESS_ALGORITHM_7ZIP = (uint16_t)0x0001,	// 7ZIP压缩
};

enum
{
	CRYPT_ALGORITHM_NONE = (uint16_t)0x0000,	// 无加密	
	CRYPT_ALGORITHM_XTEA_ROUND8 = (uint16_t)0x0004,	// 8轮XTEA迭代
	CRYPT_ALGORITHM_XTEA_ROUND16 = (uint16_t)0x0008,	// 16轮XTEA迭代
};

enum ADDRESS_TYPE
{
	AR_TYPE_BEGIN = 0,
	AR_TYPE_CLIENT = 1,
	AR_TYPE_LOGIN = 2,
	AR_TYPE_GAME = 3,
	AR_TYPE_GATEWAY = 4,
	AR_TYPE_GAMEDB = 5,
	AR_TYPE_MANAGE = 6,
	AR_TYPE_PAY = 7,
	AR_TYPE_CMM = 8,
	AR_TYPE_OSS = 9,
	AR_TYPE_GM = 10,
	AR_TYPE_GMCLIENT = 11,
	AR_TYPE_BUSINESS = 12,
	AR_TYPE_MAIL = 13,
	//AR_TYPE_VERIFY		= 12,
	MAX_AR_TYPE_COUNT,

	AR_TYPE_END = 255,
	//注意，TYPE值范围为[0,255]
};

#define MAX_IP_STR_LENGTH			16
#define MAX_REDEEMKEY_STR_LENGTH	20
#define MAX_REDEEMEXTRA_STR_LENGTH	100

#pragma pack(push, 1)
struct MsgHeader
{
	uint16_t length;
	uint32_t player_id;
	uint32_t msg_id;
};
#pragma pack(pop)


constexpr int32_t MSG_MAX_LEN = 40 * 1024;  /* c2s,s2c的最大包长度 40k*/
constexpr int32_t MSG_HEADER_LEN = sizeof(MsgHeader);
constexpr int32_t MSG_BODY_LEN = MSG_MAX_LEN - MSG_HEADER_LEN;

namespace eMSG_BUFFER_LENGTH
{
	enum e
	{
		BYTES_32 = 32,
		BYTES_64 = 64,
		BYTES_128 = 128,
		BYTES_256 = 256,
		BYTES_512 = 512,
		BYTES_1024 = 1024,
		BYTES_2048 = 2048,
		BYTES_4096 = 4096,
 		BYTES_MAX = MSG_MAX_LEN,
	};
}

class MsgBufferBase 
{
public:
	MsgBufferBase() : p_data(nullptr)
	{

	}
	virtual void Recycle() = 0;
	virtual size_t GetSize() = 0;
	char* p_data;
};

template<size_t size>
class MsgBuffer : public MsgBufferBase
{
public:
	MsgBuffer()
	{
		memset(m_data, 0, size);
		p_data = m_data;
	}
	void Recycle()
	{
		m_func(this);
	}
	size_t GetSize()
	{
		return sizeof(m_data);
	}
	char m_data[size];
	std::function<void(MsgBuffer*)> m_func;
};


