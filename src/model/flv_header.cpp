// Copyright (c) 2018 winking324
//


#include "model/flv_header.h"

#include <QDebug>

#include "commons/read_bytes.h"


namespace flv_parser {


FlvHeader::FlvHeader() {
}

size_t FlvHeader::ParseData(const std::string &data) {
  size_t read_pos = 0;
  signature_[0] = ReadByte(&data[read_pos++]);
  signature_[1] = ReadByte(&data[read_pos++]);
  signature_[2] = ReadByte(&data[read_pos++]);

  // Signature byte always 'F'(0x46) 'L'(0x4C) 'V'(0x56)
  if (signature_[0] != 0x46 || signature_[1] != 0x4C || signature_[2] != 0x56) {
    return 0;
  }

  // File version (for example, 0x01 for FLV version 1)
  version_ = ReadByte(&data[read_pos++]);

  uint8_t type_byte = ReadByte(&data[read_pos++]);
  reserved1_ = (type_byte & 0xF8) >> 3;  // Shall be 0
  audio_flag_ = (type_byte & 0x04) >> 2;  // 1 = Audio tags are present
  reserved2_ = (type_byte & 0x02) >> 1;  // Shall be 0
  video_flag_ = (type_byte & 0x01);  // 1 = Video tags are present

  // The length of this header in bytes
  data_offset_ = Read4Bytes(&data[read_pos]);
  read_pos += 4;

  qInfo() << "read flv header, signature: " << signature_[0] << " "
          << signature_[1] << " " << signature_[2] << ", version: "
          << version_ << ", reserved: " << reserved1_ << ", audio: "
          << audio_flag_ << ", reserved: " << reserved2_ << ", video: "
          << video_flag_ << ", offset: " << data_offset_;

  if (read_pos != data_offset_) {
    qCritical() << "error: offset size(" << data_offset_ << ") != read offset("
                << read_pos << ")";
    return 0;
  }

  return read_pos;
}


}  // namespace flv_parser

