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
  Status s;
  *dbptr = NULL;
  DBImpl *impl = new DBImpl();
  if (impl == NULL) {
    printf("impl null");
    log_info("impl error");
    return s;
  } else {
    printf("impl not null\n");
  }

  *dbptr = impl;

  return s;
}

DBImpl::DBImpl() :
  file_num_(0),
  offset_(0),
  db_path_("./db") {
  CreateDir(db_path_);
  now_file_ = NewFileName();
  NewWritableFile(now_file_, &writefile_);
  meta_file_ = NewMetaFile();
  NewWritableFile(meta_file_, &metafile_);
}

DBImpl::~DBImpl() {
  delete writefile_;
}

Status DBImpl::Get(const ReadOptions& option, const Slice& key, 
    std::string* value) {
  Status s;
  return s;
}

Status DBImpl::Put(const WriteOptions& options, const Slice& key, 
    const Slice& value) {
  Status s;
  uint32_t sz = value.size();
  Meta meta1(file_num_, offset_, sz);
  log_info("meta file_num %d %d", meta1.file_num, meta1.length);
  // Meta meta;
  // meta.file_num = file_num_;
  // meta.offset = offset_;
  // meta.length = value.size();
  inodes_[key.ToString()] = meta1;
  // inodes_.insert(key.ToString(), meta);
  offset_ += value.size();
  writefile_->Append(value);
  // metafile_->Append(meta);

  log_info("write success\n");

  return s;
}

Status DBImpl::Delete(const WriteOptions& options, const Slice& key) {
  Status s;
  return s;
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
