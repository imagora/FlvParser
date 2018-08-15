// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include <string>


namespace flv_parser {


uint8_t ReadByte(const char *data);

uint16_t Read2Bytes(const char *data);

uint32_t Read3Bytes(const char *data);

uint32_t Read4Bytes(const char *data);

uint64_t Read8Bytes(const char *data);


}  // namespace flv_parser
