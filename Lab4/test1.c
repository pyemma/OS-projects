#include <unistd.h>
#include <syscall.h>
#include <stdio.h>


int main()
{
  syscall(351,1000,"gedit");
  return 0;
}
