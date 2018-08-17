// Copyright (c) 2018 winking324
//


#include "model/flv_audio.h"
#include "commons/read_bytes.h"


namespace flv_parser {


FlvAudio::FlvAudio() {
}

FlvAudio::~FlvAudio() {
}

size_t FlvAudio::ParseData(const std::string &data, size_t pos, size_t length) {
  size_t read_pos = pos;
  size_t audio_length = length;
  uint8_t sound_byte = ReadByte(&data[read_pos++]);
  --audio_length;

  format_ = (sound_byte & 0xF0) >> 4;
  rate_ = (sound_byte & 0x0C) >> 2;
  size_ = (sound_byte & 0x02) >> 1;
  type_ = (sound_byte & 0x01);

  if (format_ == AUDIO_FORMAT_AAC) {
    aac_packet_type_ = ReadByte(&data[read_pos++]);
    --audio_length;
  }

  FlvData::ParseData(data, read_pos, audio_length);
  return length;
}

YAML::Node FlvAudio::Detail() {
  YAML::Node root;
  root["SoundFormat"] = SoundFormat();
  root["SoundRate"] = SoundRate();
  root["SoundSize"] = SoundSize();
  root["SoundType"] = SoundType();
  if (format_ == AUDIO_FORMAT_AAC) {
    root["AACPacketType"] = AACPacketType();
  }
  return root;
}

std::string FlvAudio::SoundFormat() {
  switch (format_) {
    case AUDIO_FORMAT_PLATFORM_ENDIAN_LINEAR_PCM:
      return "Linear PCM, platform endian";
    case AUDIO_FORMAT_ADPCM:
      return "ADPCM";
    case AUDIO_FORMAT_MP3:
      return "MP3";
    case AUDIO_FORMAT_LITTLE_ENDIAN_LINEAR_PCM:
      return "Linear PCM, little endian";
    case AUDIO_FORMAT_NELLYMOSER_16_KHZ_MONO:
      return "Nellymoser 16 kHz mono";
    case AUDIO_FORMAT_NELLYMOSER_8_KHZ_MONO:
      return "Nellymoser 8 kHz mono";
    case AUDIO_FORMAT_NELLYMOSER:
      return "Nellymoser";
    case AUDIO_FORMAT_G_711_A_LAW_LOGARITHMIC_PCM:
      return "G.711 A-law logarithmic PCM";
    case AUDIO_FORMAT_G_711_MU_LAW_LOGARITHMIC_PCM:
      return "G.711 mu-law logarithmic PCM";
    case AUDIO_FORMAT_RESERVED:
      return "reserved";
    case AUDIO_FORMAT_AAC:
      return "AAC";
    case AUDIO_FORMAT_SPEEX:
      return "Speex";
    case AUDIO_FORMAT_MP3_8_KHZ:
      return "MP3 8 kHz";
    case AUDIO_FORMAT_DEVICE_SPECIFIC_SOUND:
      return "Device-specific sound";
    default:
      return "Unknown sound format: " +
          std::to_string(static_cast<uint32_t>(format_));
  }
}

std::string FlvAudio::SoundRate() {
  switch (rate_) {
    case AUDIO_RATE_5_5_KHZ:
      return "5.5 kHz";
    case AUDIO_RATE_11_KHZ:
      return "11 kHz";
    case AUDIO_RATE_22_KHZ:
      return "22 kHz";
    case AUDIO_RATE_44_KHZ:
      return "44 kHz";
    default:
      return  "Unknown sound rate: " +
          std::to_string(static_cast<uint32_t>(rate_));
  }
}

std::string FlvAudio::SoundSize() {
  switch (size_) {
    case AUDIO_SIZE_8_BIT_SAMPLES:
      return "8-bit samples";
    case AUDIO_SIZE_16_BIT_SAMPLES:
      return "16-bit samples";
    default:
      return "Unknown sound size: " +
          std::to_string(static_cast<uint32_t>(size_));
  }
}

std::string FlvAudio::SoundType() {
  switch (type_) {
    case AUDIO_CHANNEL_MONO:
      return "Mono sound";
    case AUDIO_CHANNEL_STEREO:
      return "Stereo sound";
    default:
      return "Unknown sound type: " +
          std::to_string(static_cast<uint32_t>(type_));
  }
}

std::string FlvAudio::AACPacketType() {
  switch (aac_packet_type_) {
    case AAC_SEQUENCE_HEADER:
      return "AAC sequence header";
    case AAC_RAW:
      return "AAC raw";
    default:
      return "Unknown AAC packet type: " +
          std::to_string(static_cast<uint32_t>(aac_packet_type_));
  }
}


}  // namespace flv_parser

