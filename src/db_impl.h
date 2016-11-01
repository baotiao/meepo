#ifndef SRC_DB_IMPL_H_
#define SRC_DB_IMPL_H_

#include <unordered_map>
#include <map>

#include "slash/include/slash_slice.h"
#include "slash/include/env.h"
#include "include/db.h"
#include "include/options.h"

namespace bitcask {
using namespace slash;

class DBImpl : public DB {
 public:
  /*
   * meta data off every record
   */
  struct Meta {
    Meta(uint64_t fn, uint32_t ost, uint32_t sz) :
      file_num(fn),
      offset(ost),
      length(sz) {};

    uint64_t file_num;
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

  std::string NewFileName();
  std::string NewMetaFile();

  uint64_t file_num_;

  std::string now_file_;
  std::string meta_file_;

  uint32_t offset_;

  WritableFile *writefile_;
  WritableFile *metafile_;

  std::string db_path_;

  /*
   * key to DBInode mapping
   */
  std::map<std::string, Meta> inodes_;

};

}  // namespace bitcask

#endif  // SRC_DB_IMPL_H_
