#ifndef SRC_DB_IMPL_H_
#define SRC_DB_IMPL_H_

#include <inordered_map>

#include "third/slash/slash_slice.h"
#include "include/db.h"

namespace bitcask {
using namespace slash;

class DBImpl : public DB {
 public:
  /*
   * meta data off every record
   */
  struct Meta {
    uint32_t file_num;
    uint32_t offset;
    uint32_t length;
  };
  DBImpl();
  virtual ~DBImpl();

  virtual Status Get(const ReadOptions& option, const Slice& key, 
      std::string* value);

  virtual Status Put(const WriteOptions& options, const Slice& key, 
      const Slice& value);

  virtual Status Delete(const WriteOptions& options, 
      const Slice& key);
 private:

  uint64_t file_num_;

  std::string db_path_;
  /*
   * key to DBInode mapping
   */
  inordered_map<std::string, Meta> inodes_;

};

}  // namespace bitcask

#endif  // SRC_DB_IMPL_H_
