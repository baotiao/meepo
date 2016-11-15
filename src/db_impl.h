#ifndef SRC_DB_IMPL_H_
#define SRC_DB_IMPL_H_

#include <unordered_map>
#include <map>

#include "slash/include/slash_slice.h"
#include "slash/include/env.h"
#include "include/db.h"
#include "include/options.h"
#include "include/meta.h"


namespace bitcask {

class Meta;

using namespace slash;

class DBImpl : public DB {
 public:
  DBImpl();
  virtual ~DBImpl();

  virtual Status Get(const ReadOptions& option, const Slice& key, 
      std::string* value);

  virtual Status Put(const WriteOptions& options, const Slice& key, 
      const Slice& value);

  virtual Status Delete(const WriteOptions& options, 
      const Slice& key);

  virtual Status ListKeys(const ReadOptions& options); 

  virtual Status Merge();

  virtual Status Sync();
  

 private:

  std::string NewFileName();
  std::string NewMetaFile();
  std::string ReadFileName(const uint32_t sst_num);

  uint32_t file_num_;

  std::string now_file_;
  std::string meta_file_;

  uint32_t offset_;

  WritableFile *writefile_;
  WritableFile *metafile_;

  SequentialFile *readfile_;

  std::string db_path_;

  /*
   * key to DBInode mapping
   */
  std::unordered_map<std::string, Meta *> inodes_;

  std::vector<SequentialFile *> file_table_;
  DBImpl(const DBImpl&);
  void operator =(const DBImpl&);

};

}  // namespace bitcask

#endif  // SRC_DB_IMPL_H_
