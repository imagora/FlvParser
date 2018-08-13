// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include <string>
#include "model/flv_tag.h"


namespace flv_parser {


class FlvData {
 public:
  virtual ~FlvData() = 0;

  virtual int ParseData(const std::string &data) = 0;

 private:
  std::string data_;
};


}  // namespace flv_parser

