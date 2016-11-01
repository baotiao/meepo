#include <string>

#include "include/db.h"
#include "src/db_impl.h"

#include "slash/output/include/slash_status.h"
#include "slash/output/include/slash_slice.h"

using namespace bitcask;
using namespace slash;

int main()
{
  const bitcask::Options op;
  

  bitcask::DB *db = new DBImpl();
  db = NULL;
  std::string db_name = "./db";
  slash::Status s = bitcask::DB::Open(op, db_name, &db);

  const bitcask::WriteOptions wop;

  std::string key("aaa");
  std::string val("bbb");

  if (db == NULL) {
    printf("db error\n");
    return -1;
  }
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);
  s = db->Put(wop, key, val);

  delete db;

  printf("success\n");

  return 0;
}
