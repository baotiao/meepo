#include <stdio.h>
#include <unistd.h>
#include <linux/falloc.h>
#include <fcntl.h>

#include "xdebug.h"

int main()
{
  int fd = open("./tt", O_RDWR | O_CREAT | O_TRUNC);

  int mode = FALLOC_FL_KEEP_SIZE;

  off_t offset = 0;
  off_t len = 1024 * 1024 * 1024 ;

  fallocate(fd, mode, offset, len);

  write(fd, "heihei", 6);

  log_info("come here");

  close(fd);

  return 0;
}
