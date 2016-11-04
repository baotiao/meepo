#include "include/meta.h"

#include <stdint.h>
#include <string>

#include "slash/include/slash_slice.h"

namespace bitcask {

void Meta::EncodeTo(std::string *dst) const {
  char buf[8];
  memcpy(buf, &key_len_, sizeof(key_len_));
  dst->append(buf, sizeof(key_len_));
  memcpy(buf, &file_num_, sizeof(file_num_));
  dst->append(buf, sizeof(file_num_));
  memcpy(buf, &offset_, sizeof(offset_));
  dst->append(buf, sizeof(offset_));
  memcpy(buf, &length_, sizeof(length_));
  dst->append(buf, sizeof(length_));
  return;
}

void Meta::DecodeFrom(const slash::Slice& src) {
  memcpy((char *)(&key_len_), src.data(), sizeof(key_len_));
  memcpy((char *)(&file_num_), src.data() + sizeof(key_len_), sizeof(file_num_));
  memcpy((char *)(&offset_), src.data() + sizeof(key_len_) + sizeof(file_num_), sizeof(offset_));
  memcpy((char *)(&length_), src.data() + sizeof(key_len_) + sizeof(file_num_) + sizeof(offset_), sizeof(length_));
}

};  // namespace bitcask
