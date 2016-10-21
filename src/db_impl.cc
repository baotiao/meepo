#include "src/db_impl.h"

#include "slash/slash_status.h"

namespace bitcask {

using namespace slash;

DBImpl::DBImpl() :
  file_num_(0) {
}

DBImpl::~DBImpl() {
}

Status DB::Open() {

}

Status DBImpl::Get(const ReadOptions& option, const Slice& key, 
    std::string* value) {
}
Status Put(const WriteOptions& options, const Slice& key, 
    const Slice& value);

}  // namespace bitcask
