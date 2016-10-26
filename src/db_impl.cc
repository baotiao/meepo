#include "src/db_impl.h"

#include "include/xdebug.h"
#include "slash/include/slash_status.h"
#include "slash/include/env.h"


namespace bitcask {

using namespace slash;

DB::DB() {
}


DB::~DB() {
}

Status DB::Open(const Options& options, const std::string& name, 
    DB** dbptr) {
  // DBImpl *impl = new DBImpl();

}

DBImpl::DBImpl() :
  file_num_(0),
  offset_(0),
  db_path_("./db") {
  CreateDir(db_path_);
  now_file_ = NewFileName();
  NewWritableFile(now_file_, &writefile_);
}

DBImpl::~DBImpl() {
  delete writefile_;
}

Status DBImpl::Get(const ReadOptions& option, const Slice& key, 
    std::string* value) {

}

Status DBImpl::Put(const WriteOptions& options, const Slice& key, 
    const Slice& value) {
  // Meta meta(file_num_, offset_, static_cast<uint32_t>(value.size()));
  Meta meta;
  meta.file_num = file_num_;
  meta.offset = offset_;
  meta.length = value.size();
  inodes_[key.ToString()] = meta;
  // inodes_.insert(key, meta);
  offset_ += value.size();
  writefile_->Append(value);
  log_info("write success\n");
}

Status DBImpl::Delete(const WriteOptions& options, const Slice& key) {

}

std::string DBImpl::NewFileName() {
  char buf[100];
  snprintf(buf, sizeof(buf), "/%d.sst", file_num_);
  return db_path_ + buf;
}

std::string DBImpl::NewMetaFile() {
  char buf[100];
  snprintf(buf, sizeof(buf), "/%d.index", file_num_);
  return db_path_ + buf;
}

}  // namespace bitcask
