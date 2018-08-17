// Copyright (c) 2018 winking324
//


#include "model/flv_video.h"
#include "commons/read_bytes.h"


namespace flv_parser {


FlvVideo::FlvVideo() {
}

FlvVideo::~FlvVideo() {
}

size_t FlvVideo::ParseData(const std::string &data, size_t pos, size_t length) {
  size_t read_pos = pos;
  uint8_t video_byte = ReadByte(&data[read_pos++]);

  frame_type_ = (video_byte & 0xF0) >> 4;
  codec_id_ = (video_byte & 0x0F);

  if (codec_id_ == VIDEO_CODEC_AVC) {
    avc_packet_type_ = ReadByte(&data[read_pos++]);
    composition_time_ = Read3Bytes(&data[read_pos]);
    read_pos += 3;
  }

  FlvData::ParseData(data, read_pos, length - read_pos + pos);
  return length;
}

YAML::Node FlvVideo::Detail() {
  YAML::Node root;
  root["FrameType"] = FrameType();
  root["CodecID"] = CodecID();
  root["AVCPacketType"] = AVCPacketType();
  root["CompositionTime"] = composition_time_;
  return root;
}

std::string FlvVideo::FrameType() {
  switch (frame_type_) {
    case VIDEO_KEY_FRAME:
      return "key frame (for AVC, a seekable frame)";
    case VIDEO_INTER_FRAME:
      return "inter frame (for AVC, a non-seekable frame)";
    case VIDEO_DISPOSABLE_INTER_FRAME:
      return "disposable inter frame (H.263 only)";
    case VIDEO_GENERATED_KEY_FRAME:
      return "generated key frame (reserved for server use only)";
    case VIDEO_INFO_AND_COMMAND_FRAME:
      return "video info/command frame";
    default:
      return "Unknown frame type: " +
          std::to_string(static_cast<uint32_t>(frame_type_));
  }
}

std::string FlvVideo::CodecID() {
  switch (codec_id_) {
    case VIDEO_CODEC_SORENSON_H263:
      return "Sorenson H.263";
    case VIDEO_CODEC_SCREEN:
      return "Screen video";
    case VIDEO_CODEC_ON2_VP6:
      return "On2 VP6";
    case VIDEO_CODEC_ON2_VP6_WITH_ALPHA_CHANNEL:
      return "On2 VP6 with alpha channel";
    case VIDEO_CODEC_SCREEN_V2:
      return "Screen video version 2";
    case VIDEO_CODEC_AVC:
      return "AVC";
    default:
      return "Unknown codec id: " +
          std::to_string(static_cast<uint32_t>(codec_id_));
  }
}

std::string FlvVideo::AVCPacketType() {
  switch (avc_packet_type_) {
    case AVC_SEQUENCE_HEADER:
      return "AVC sequence header";
    case AVC_NALU:
      return "AVC NALU";
    case AVC_END_OF_SEQUENCE:
      return "AVC end of sequence";
    default:
      return "Unknown AVC packet type: " +
          std::to_string(static_cast<uint32_t>(avc_packet_type_));
  }
}


}  // namespace flv_parser

