// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <string>
#include <inttypes.h>
#include <yaml-cpp/yaml.h>


namespace flv_parser {


class FlvData {
 public:
  FlvData();

  virtual ~FlvData();

  virtual size_t ParseData(const std::string &data, size_t pos, size_t length);

  virtual std::string Info();

  virtual YAML::Node Detail();

  virtual const std::string &Data();

 private:
  std::string data_;
};


}  // namespace flv_parser

