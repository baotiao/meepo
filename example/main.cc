#include <stdio.h>
#include <unistd.h>
#include <linux/falloc.h>
#include <fcntl.h>

#include "xdebug.h"
#include "include/db.h"
#include "output/include/options.h"

int main()
{
  bitcask::Options op;
  

  bitcask::DB *db;
  db = NULL;
  bitcask::DB::Open(op, "./db", &db);

  // bitcask::WriteOptions wop;

  // db->Put(wop, "zz", "czzzz");


  return 0;
}
