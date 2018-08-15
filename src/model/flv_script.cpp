// Copyright (c) 2018 winking324
//


#include "model/flv_script.h"

#include <QDebug>

#include "commons/read_bytes.h"


namespace flv_parser {


FlvScript::FlvScript() {
  parser_ = {
    {SCRIPT_DATA_NUMBER, &FlvScript::ParseDataNumber},
    {SCRIPT_DATA_BOOLEAN, &FlvScript::ParseDataBool},
    {SCRIPT_DATA_STRING, &FlvScript::ParseDataString},
    {SCRIPT_DATA_OBJECT, &FlvScript::ParseDataObject},
    {SCRIPT_DATA_REFERENCE, &FlvScript::ParseDataReference},
    {SCRIPT_DATA_ECMA_ARRAY, &FlvScript::ParseDataEcmaArrary},
    {SCRIPT_DATA_STRICT_ARRAY, &FlvScript::ParseDataStrictArray},
    {SCRIPT_DATA_DATE, &FlvScript::ParseDataDate},
    {SCRIPT_DATA_LONG_STRING, &FlvScript::ParseDataLongString},
    {SCRIPT_DATA_VALUE, &FlvScript::ParseDataValue},
  };

  creator_ = {
    {SCRIPT_DATA_NUMBER, &DataCreator<FlvScriptDataNumber>::New},
    {SCRIPT_DATA_BOOLEAN, &DataCreator<FlvScriptDataBool>::New},
    {SCRIPT_DATA_STRING, &DataCreator<FlvScriptDataString>::New},
    {SCRIPT_DATA_OBJECT, &DataCreator<FlvScriptDataObject>::New},
    {SCRIPT_DATA_REFERENCE, &DataCreator<FlvScriptDataReference>::New},
    {SCRIPT_DATA_ECMA_ARRAY, &DataCreator<FlvScriptDataEcmaArrary>::New},
    {SCRIPT_DATA_STRICT_ARRAY, &DataCreator<FlvScriptDataStrictArray>::New},
    {SCRIPT_DATA_DATE, &DataCreator<FlvScriptDataDate>::New},
    {SCRIPT_DATA_LONG_STRING, &DataCreator<FlvScriptDataLongString>::New},
    {SCRIPT_DATA_VALUE, &DataCreator<FlvScriptDataValue>::New},
  };
}

FlvScript::~FlvScript() {
}

size_t FlvScript::ParseData(const std::string &data, size_t pos,
                            size_t length) {
  size_t read_pos = pos;
  read_pos += ParseDataValue(data, read_pos, length, &name_);
  read_pos += ParseDataValue(data, read_pos, length - read_pos + pos,
                             &value_);
  return length;
}

size_t FlvScript::ParseDataValue(const std::string &data, size_t pos,
                                 size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataValue *script_data = dynamic_cast<FlvScriptDataValue *>(value);

  if (length < 1) return 0;
  script_data->type_ = ReadByte(&data[read_pos++]);

  auto parser_iter = parser_.find(script_data->type_);
  if (parser_iter == parser_.end()) {
    qCritical() << "read flv script, cannot find parser type: "
                << script_data->type_;
    return 0;
  }

  auto creator_iter = creator_.find(script_data->type_);
  if (creator_iter == creator_.end()) {
    qCritical() << "read flv script, cannot find creator type: "
                << script_data->type_;
    return 0;
  }

  script_data->value_.reset((creator_iter->second)());
  size_t data_size = (this->*(parser_iter->second))(data, read_pos,
                                                    length - read_pos + pos,
                                                    script_data->value_.get());
  if (data_size == 0) {
    qCritical() << "read flv script, connot parse type: " << script_data->type_;
    return 0;
  }

  read_pos += data_size;
  return read_pos - pos;
}

size_t FlvScript::ParseDataNumber(const std::string &data, size_t pos,
                                  size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataNumber *script_data = dynamic_cast<FlvScriptDataNumber *>(value);

  if (length < 8) return 0;

  uint64_t uint64_value = Read8Bytes(&data[read_pos]);
  read_pos += 8;
  script_data->double_data_ = *(reinterpret_cast<double *>(&uint64_value));
  return read_pos - pos;
}

size_t FlvScript::ParseDataBool(const std::string &data, size_t pos,
                                size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataBool *script_data = dynamic_cast<FlvScriptDataBool *>(value);

  if (length < 1) return 0;

  script_data->bool_data_ = ReadByte(&data[read_pos++]);
  return read_pos - pos;
}

size_t FlvScript::ParseDataReference(const std::string &data, size_t pos,
                                     size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataReference *script_data =
      dynamic_cast<FlvScriptDataReference *>(value);

  if (length < 2) return 0;

  script_data->reference_data_ = Read2Bytes(&data[read_pos]);
  read_pos += 2;
  return read_pos - pos;
}

size_t FlvScript::ParseDataString(const std::string &data, size_t pos,
                                  size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataString *script_data = dynamic_cast<FlvScriptDataString *>(value);

  if (length < 2) return 0;

  script_data->string_length_ = Read2Bytes(&data[read_pos]);
  read_pos += 2;

  if (length < script_data->string_length_) return 0;

  script_data->string_data_ =
      std::string(data, read_pos, script_data->string_length_);
  read_pos += script_data->string_length_;
  return read_pos - pos;
}

size_t FlvScript::ParseDataLongString(const std::string &data, size_t pos,
                                      size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataLongString *script_data =
      dynamic_cast<FlvScriptDataLongString *>(value);

  if (length < 4) return 0;

  script_data->string_length_ = Read4Bytes(&data[read_pos]);
  read_pos += 4;

  if (length < script_data->string_length_) return 0;

  script_data->string_data_ = std::string(data, read_pos,
                                          script_data->string_length_);
  read_pos += script_data->string_length_;
  return read_pos - pos;
}

size_t FlvScript::ParseDataStrictArray(const std::string &data, size_t pos,
                                       size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataStrictArray *script_data =
      dynamic_cast<FlvScriptDataStrictArray *>(value);

  if (length < 4) return 0;

  script_data->strict_array_length_ = Read4Bytes(&data[read_pos]);
  read_pos += 4;

  for (uint32_t i = 0; i < script_data->strict_array_length_; ++i) {
    FlvScriptDataValue data_value;
    read_pos += ParseDataValue(data, read_pos, length - read_pos + pos,
                               &data_value);
    script_data->strict_array_value_.push_back(data_value);
  }

  return read_pos - pos;
}

size_t FlvScript::ParseDataDate(const std::string &data, size_t pos,
                                size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataDate *script_data = dynamic_cast<FlvScriptDataDate *>(value);

  if (length < 10) return 0;

  uint64_t uint64_value = Read8Bytes(&data[read_pos]);
  read_pos += 8;
  script_data->date_time_ = *(reinterpret_cast<double *>(&uint64_value));

  script_data->local_date_time_offset_ =
      static_cast<int16_t>(Read2Bytes(&data[read_pos]));
  read_pos += 2;
  return read_pos - pos;
}

size_t FlvScript::ParseDataObjectProperty(const std::string &data, size_t pos,
                                          size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataObjectProperty *script_data =
      dynamic_cast<FlvScriptDataObjectProperty *>(value);

  read_pos += ParseDataString(data, read_pos, length,
                              &script_data->property_name_);
  read_pos += ParseDataValue(data, read_pos, length - read_pos + pos,
                             &script_data->property_data_);

  return read_pos - pos;
}

size_t FlvScript::ParseDataObject(const std::string &data, size_t pos,
                                  size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataObject *script_data = dynamic_cast<FlvScriptDataObject *>(value);
  while (!(data[read_pos] == 0x0 && data[read_pos + 1] == 0x0 &&
           data[read_pos + 2] == 0x9)) {
    if (length < 3) return 0;

    FlvScriptDataObjectProperty data_value;
    size_t property_size = ParseDataObjectProperty(data, read_pos,
                                                   length - read_pos + pos,
                                                   &data_value);
    if (property_size == 0) return 0;

    read_pos += property_size;
    script_data->object_properties_.push_back(data_value);
  }

  read_pos += 3;
  return read_pos - pos;
}

size_t FlvScript::ParseDataEcmaArrary(const std::string &data, size_t pos,
                                      size_t length, FlvScriptData *value) {
  size_t read_pos = pos;
  FlvScriptDataEcmaArrary *script_data =
      dynamic_cast<FlvScriptDataEcmaArrary *>(value);

  if (length < 4) return 0;
  script_data->ecma_array_length_ = Read4Bytes(&data[read_pos]);
  read_pos += 4;

  while (!(data[read_pos] == 0x0 && data[read_pos + 1] == 0x0 &&
           data[read_pos + 2] == 0x9)) {
    if (length < 3) return 0;

    FlvScriptDataObjectProperty data_value;
    size_t property_size = ParseDataObjectProperty(data, read_pos,
                                                   length - read_pos + pos,
                                                   &data_value);
    if (property_size == 0) return 0;

    read_pos += property_size;
    script_data->variables_.push_back(data_value);
  }

  read_pos += 3;
  return read_pos - pos;
}


}  // namespace flv_parser

