/* Public domain by Valentin Hilbig, webmaster@scylla-charybdis.com
 * as long as nobody else claims the copyright for this
 */
#include <stdio.h>
#include <linux/kd.h>

#include <sys/ioctl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define	CONSOLE	"/dev/tty0"

int
main(int argc, char **argv)
{
  int	i;
  long	pitch, ms, w;
  int	fd;

  fd	= 1;
  if (ioctl(fd, KDMKTONE, 0))
    fd	= open(CONSOLE, O_RDONLY);
  if (fd<0)
    {
      perror(CONSOLE);
      return 1;
    }
  for (i=1; i<argc; )
    {
      pitch	= 0;
      ms	= 0;
      w		= 0;
      sscanf(argv[i], "%ld:%ld:%ld", &pitch, &ms, &w);
      if (pitch)
	pitch	= 1193180 / pitch;
      if (!ms)
	ms	= 100;
      if (!w)
	w	= ms;
      ioctl(fd, KDMKTONE, (ms<<16)|pitch);
      if (++i<argc || w)
	usleep((w ? w : ms)*1000);
    }
  return 0;
}
