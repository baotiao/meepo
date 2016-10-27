#include <string>

#include "include/db.h"
#include "slash/output/include/slash_status.h"

// using namespace bitcask;
using namespace slash;
int main()
{
  const bitcask::Options op;
  

  bitcask::DB *db;
  db = NULL;
  std::string db_name = "./db";
  slash::Status s = bitcask::DB::Open(op, db_name, &db);

  bitcask::WriteOptions wop;

  // db->Put();

  delete db;

  printf("success\n");

  return 0;
}
