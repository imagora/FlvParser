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

uint64_t Read8Bytes(const char *data) {
  uint64_t offset1 = static_cast<uint64_t>(ReadByte(data)) << 56;
  uint64_t offset2 = static_cast<uint64_t>(ReadByte(data + 1)) << 48;
  uint64_t offset3 = static_cast<uint64_t>(ReadByte(data + 2)) << 40;
  uint64_t offset4 = static_cast<uint64_t>(ReadByte(data + 3)) << 32;
  uint64_t offset5 = static_cast<uint64_t>(ReadByte(data + 4)) << 24;
  uint64_t offset6 = static_cast<uint64_t>(ReadByte(data + 5)) << 16;
  uint64_t offset7 = static_cast<uint64_t>(ReadByte(data + 6)) << 8;
  uint64_t offset8 = static_cast<uint64_t>(ReadByte(data + 7));
  return static_cast<uint64_t>(offset1 | offset2 | offset3 | offset4 |
                               offset5 | offset6 | offset7 | offset8);
}


}  // namespace flv_parser

