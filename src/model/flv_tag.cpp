// Copyright (c) 2018 winking324
//


#include "model/flv_tag.h"

#include <memory>
#include <sstream>
#include <QDebug>

#include "commons/read_bytes.h"

#include "model/flv_audio.h"
#include "model/flv_video.h"
#include "model/flv_script.h"


namespace flv_parser {


static const size_t kTagHeaderSize = 11;


FlvTag::FlvTag() {
  reserved_ = 0;
  filter_ = 0;
  type_ = 0;
  size_ = 0;
  timestamp_ = 0;
  timestamp_extended_ = 0;
  stream_id_ = 0;
}

size_t FlvTag::ParseData(const std::string &data, size_t pos) {
  if (data.size() < kTagHeaderSize + pos) {
    qWarning() << "read flv tag failed, data size: " << data.size();
    return 0;
  }

  size_t read_pos = pos;
  uint8_t type_byte = ReadByte(&data[read_pos++]);
  reserved_ = (type_byte & 0xC0) >> 6;
  filter_ = (type_byte & 0x40) >> 5;
  type_ = (type_byte & 0x1F);

  size_ = Read3Bytes(&data[read_pos]);
  read_pos += 3;

  timestamp_ = Read3Bytes(&data[read_pos]);
  read_pos += 3;

  timestamp_extended_ = ReadByte(&data[read_pos++]);

  stream_id_ = Read3Bytes(&data[read_pos]);
  read_pos += 3;

  if (size_ + read_pos > data.size()) {
    qWarning() << "read flv tag failed, data size: " << data.size()
               << ", need: " << size_;
    return 0;
  }

  size_t read_data_size = 0;
  switch (type_) {
    case AUDIO_TAG:
      read_data_size = ParseAudio(data, read_pos);
    break;
    case VIDEO_TAG:
      read_data_size = ParseVideo(data, read_pos);
    break;
    case SCRIPT_TAG:
      read_data_size = ParseScript(data, read_pos);
    break;
    default:
      qInfo() << "cannot parse tag type: " << type_ << ", ignore this tag";
      read_data_size = size_;
    break;
  }

  qInfo() << "read flv tag, reserved: " << reserved_ << ", filter: " << filter_
          << ", tag type: " << type_ << ", data size: " << size_
          << ", timestamp: " << timestamp_ << ", timestamp extended: "
          << timestamp_extended_ << ", stream id: " << stream_id_
          << ", data size: " << read_data_size << ", read pos: " << read_pos;
  return read_data_size + kTagHeaderSize;
}

std::string FlvTag::Type() {
  switch (type_) {
    case AUDIO_TAG:
      return "Audio";
    case VIDEO_TAG:
      return "Video";
    case SCRIPT_TAG:
      return "Script";
    default:
      return "Unknown";
  }
}

std::string FlvTag::Info() {
  std::string data_info = data_->Info();
  std::stringstream ss;
  ss << "Filter:" << static_cast<uint32_t>(filter_) << "|"
     << "Size:" << size_ << "|"
     << "Timestamp:"
     << (static_cast<uint32_t>(timestamp_extended_) << 24 | timestamp_)
     << (data_info.empty() ? "" : "|") << data_info;
  return ss.str();
}

YAML::Node FlvTag::Detail() {
  YAML::Node root;
  root["Reserved"] = static_cast<uint32_t>(reserved_);
  root["Filter"] = static_cast<uint32_t>(filter_);
  root["TagType"] = Type();
  root["DataSize"] = size_;
  root["Timestamp"] = timestamp_;
  root["TimestampExtended"] = static_cast<uint32_t>(timestamp_extended_);
  root["StreamID"] = stream_id_;
  if (data_) {
    root[Type()] = data_->Detail();
  }
  return root;
}

std::string FlvTag::Data() {
  if (data_) {
    return data_->Data();
  }
  return "";
}

size_t FlvTag::ParseAudio(const std::string &data, size_t pos) {
  data_.reset(new FlvAudio());
  return data_->ParseData(data, pos, size_);
}

size_t FlvTag::ParseVideo(const std::string &data, size_t pos) {
  data_.reset(new FlvVideo());
  return data_->ParseData(data, pos, size_);
}

size_t FlvTag::ParseScript(const std::string &data, size_t pos) {
  data_.reset(new FlvScript());
  return data_->ParseData(data, pos, size_);
}


}  // namespace flv_parser

