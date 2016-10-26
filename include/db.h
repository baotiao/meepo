#ifndef INCLUDE_BITCASK_DB_H_
#define INCLUDE_BITCASK_DB_H_

#include "slash/include/slash_slice.h"
#include "slash/include/slash_status.h"

#include "include/options.h"

namespace bitcask {
using namespace slash;
class DB {
 public:
  DB();
  virtual ~DB();
  static Status Open(const Options& options, const std::string& name, 
      DB** dbptr);

  virtual Status Get(const ReadOptions& option, const Slice& key, 
      std::string* value) = 0;

  virtual Status Put(const WriteOptions& options, const Slice& key, 
      const Slice& value) = 0;

  virtual Status Delete(const WriteOptions& options, 
      const Slice& key) = 0;
  
 private:
  DB(const DB&);
  void operator=(const DB&);
};

}  // namespace bitcask
#endif  // INCLUDE_BITCASK_DB_H_
