// Copyright (c) 2018 winking324
//


#include "commons/read_bytes.h"


namespace flv_parser {


uint8_t ReadByte(const char *data) {
  return static_cast<uint8_t>(data[0]);
}

uint16_t Read2Bytes(const char *data) {
  uint16_t offset1 = static_cast<uint16_t>(ReadByte(data) << 8);
  uint16_t offset2 = static_cast<uint16_t>(ReadByte(data + 1));
  return static_cast<uint16_t>(offset1 | offset2);
}

uint32_t Read3Bytes(const char *data) {
  uint32_t offset1 = static_cast<uint32_t>(ReadByte(data) << 16);
  uint32_t offset2 = static_cast<uint32_t>(ReadByte(data + 1) << 8);
  uint32_t offset3 = static_cast<uint32_t>(ReadByte(data + 2));
  return static_cast<uint32_t>(offset1 | offset2 | offset3);
}

uint32_t Read4Bytes(const char *data) {
  uint32_t offset1 = static_cast<uint32_t>(ReadByte(data) << 24);
  uint32_t offset2 = static_cast<uint32_t>(ReadByte(data + 1) << 16);
  uint32_t offset3 = static_cast<uint32_t>(ReadByte(data + 2) << 8);
  uint32_t offset4 = static_cast<uint32_t>(ReadByte(data + 3));
  return static_cast<uint32_t>(offset1 | offset2 | offset3 | offset4);
}


}  // namespace flv_parser

