#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/* our detach-from-tty function */
void detach_tty()
{
  /* try to open the controlling TTY */
  int fd=open("/dev/tty",O_RDWR);
  if(fd<0){
      /* failed: we do not need to detach */
      fprintf(stderr,"No TTY to begin with.\n");
      return;
    }

  /* try to detach */
  if(ioctl(fd,TIOCNOTTY))
          fprintf(stderr,"Warning: unable to detach from TTY\n");
  else
          fprintf(stderr,"Detached.\n");

  /* close the handle, it is not needed anymore */
  close(fd);
}

int main(int argc,char**argv)
{
  /* do we have something to do? */
  if(argc<2){
      fprintf(stderr,"Usage: %s command [arguments...]\n",argv[0]);
      return 1;
    }
  /* detach controlling TTY */
  detach_tty();
  /* call original program */
  execvp(argv[1],argv+1);
  /* normally execvp does not return*/
  /* the call failed for some reason */
  fprintf(stderr,"Unable to execute: %s.\n", strerror(errno));
  return 1;
}
