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
  const bitcask::ReadOptions rop;

  std::string key("aaa");
  std::string val("bbb");

  if (db == NULL) {
    printf("db error\n");
    return -1;
  }
  std::string value;
  Slice s1("c");
  for (int i = 0; i < 100000000; i++) {
    s = db->Put(wop, "a", "b");
    s = db->Put(wop, "c", "d");
    s = db->Put(wop, "e", "f");
    s = db->Get(rop, s1, &value);
  }


  printf("%s\n", value.c_str());

  delete db;

  printf("success\n");

  return 0;
}
