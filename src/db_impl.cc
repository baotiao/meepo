#include "src/db_impl.h"

#include "include/xdebug.h"
#include "slash/include/slash_status.h"
#include "slash/include/env.h"
#include "include/meta.h"


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
  delete metafile_;
}

Status DBImpl::Get(const ReadOptions& option, const Slice& key, 
    std::string* value) {
  Status s;
  std::unordered_map<std::string, Meta>::iterator iter;
  iter = inodes_.find(key.ToString());
  if (iter == inodes_.end()) {
    return s; 
  }

  
  std::string read_file_ = ReadFileName((iter->second).file_num());
  log_info("%s", read_file_.c_str());
  s = NewSequentialFile(read_file_, &readfile_);
  log_info("status info %s", s.ToString().c_str());
  printf("%u ", (iter->second).offset());

  readfile_->Skip((iter->second).offset());

  slash::Slice *res = new Slice();
  char *scratch = (char *)malloc(10240 * sizeof(char *)); 

  readfile_->Read((iter->second).length(), res, scratch);
  log_info("%s", res->ToString().c_str());
  delete(readfile_);
  
  return s;
}

Status DBImpl::Put(const WriteOptions& options, const Slice& key, 
    const Slice& value) {
  Status s;
  uint32_t sz = value.size();
  Meta meta(key.ToString(), file_num_, offset_, sz);
  inodes_[key.ToString()] = meta;
  offset_ += value.size();
  writefile_->Append(value);
  std::string *p = new std::string();
  meta.EncodeTo(p);
  metafile_->Append(*p);
  metafile_->Append(meta.key());

  log_info("write success\n");

  return s;
}

Status DBImpl::Delete(const WriteOptions& options, const Slice& key) {
  Status s;
  return s;
}

Status DBImpl::ListKeys(const ReadOptions& options) {
}

Status DBImpl::Merge() {
}

Status DBImpl::Sync() {
}

std::string DBImpl::NewFileName() {
  char buf[100];
  snprintf(buf, sizeof(buf), "/%d.sst", file_num_);
  return db_path_ + buf;
}

std::string DBImpl::ReadFileName(const uint32_t sst_num) {
  char buf[100];
  snprintf(buf, sizeof(buf), "/%d.sst", sst_num);
  return db_path_ + buf;
}

std::string DBImpl::NewMetaFile() {
  char buf[100];
  snprintf(buf, sizeof(buf), "/%d.index", file_num_);
  return db_path_ + buf;
}

}  // namespace bitcask
