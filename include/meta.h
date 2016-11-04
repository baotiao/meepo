#ifndef INCLUDE_META_H_
#define INCLUDE_META_H_

#include <string>

#include "slash/include/slash_slice.h"

namespace bitcask {
/*
 * meta data off every record
 */
class Meta {
 public:
  // if you use stl, remember to implement no argument constructure
  Meta() {};
  Meta(std::string key, uint64_t file_num, uint32_t offset, uint32_t length) :
    key_(key),
    key_len_(key_.length()),
    file_num_(file_num),
    offset_(offset),
    length_(length) {};

  std::string ToString() const {
    char buf[100];
    snprintf(buf, sizeof(buf), "%u%u%u", file_num_, offset_, length_);
    return buf;
  };

  std::string key() const {
    return key_;
  }

  uint32_t file_num() const {
    return file_num_;
  }

  uint32_t offset() const {
    return offset_;
  }
  
  uint32_t length() const {
    return length_;
  }

  void EncodeTo(std::string *dst) const;

  void DecodeFrom(const slash::Slice& src);

 private:
  std::string key_;
  uint32_t key_len_;
  uint32_t file_num_;
  uint32_t offset_;
  uint32_t length_;
};

};  // namespace bitcask

#endif  // INCLUDE_META_H_
