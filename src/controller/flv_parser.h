// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <list>
#include <string>
#include "model/flv_header.h"
#include "model/flv_body.h"


namespace flv_parser {


class FlvParser {
  typedef std::list<FlvBody> FlvBodys;
 public:
  FlvParser();

  ~FlvParser();

  int ParseData(const std::string &data);

 private:
  std::string buffer_;
  FlvHeader flv_header_;
  FlvBodys flv_bodys_;
};


}  // namespace flv_parser

