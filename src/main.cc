#include <stdio.h>
#include <unistd.h>
#include <linux/falloc.h>
#include <fcntl.h>

int main()
{
  int fd = open("./fal", O_RDWR);

  int mode = FALLOC_FL_KEEP_SIZE;

  off_t offset = 0;
  off_t len = 1024 * 1024 * 1024 ;

  fallocate(fd, mode, offset, len);

  close(fd);

  return 0;
}
