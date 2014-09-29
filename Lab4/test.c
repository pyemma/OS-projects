#include <unistd.h>
#include <syscall.h>
#include <stdio.h>


int main()
{
  syscall(351,1000,NULL);
  return 0;
}
