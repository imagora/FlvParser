// Copyright (c) 2018 winking324
//


#include "model/flv_body.h"

#include <QDebug>

#include "commons/error_code.h"
#include "commons/read_bytes.h"


namespace flv_parser {


FlvBody::FlvBody() {
}

size_t FlvBody::ParseData(const std::string &data) {
  if (data.size() < 4) return 0;

  size_t read_pos = 0;
  previous_size_ = Read4Bytes(&data[read_pos]);
  read_pos += 4;

  size_t tag_size = tag_.ParseData(data, read_pos);
  qInfo() << "read flv body, previous size: " << previous_size_
          << ", tag size: " << tag_size;
  if (tag_size > 0) {
    return tag_size + read_pos;
  }
  return 0;
}


}  // namespace flv_parser

