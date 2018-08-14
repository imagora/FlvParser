// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include "model/flv_tag.h"


namespace flv_parser {


class FlvBody {
 public:
  FlvBody();

  size_t ParseData(const std::string &data);

 private:
  uint32_t previous_size_;
  FlvTag tag_;
};


}  // namespace flv_parser

