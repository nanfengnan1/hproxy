#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <stdint.h>

#include "hlib.h"

typedef union {
	uint8_t data[4];
	uint32_t data_u32;
	uint8_t as_u8[4];
	uint16_t as_u16[2];
	uint32_t as_u32;
} ip4_address_t;

typedef union {
	uint8_t as_u8[16];
	uint16_t as_u16[8];
	uint32_t as_u32[4];
	uint64_t as_u64[2];
} __hlib_packed ip6_address_t;

typedef HLIB_PACKED(union ip46_address_t_ {
	struct {
		uint32_t pad[3];
		ip4_address_t ip4;
	};

	ip6_address_t ip6;
	uint8_t as_u8[16];
	uint64_t as_u64[2];
}) ip46_address_t;


#endif
