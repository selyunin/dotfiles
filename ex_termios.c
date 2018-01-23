#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>


#define dev "/dev/ttyUSB1"

void delay(int milliseconds)
{
    long pause;
    clock_t now,then;
	//int CLOCKS_PER_SEC = 10000000;
    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int main(void)
{
    int fd;
    struct termios old_termios;
    struct termios new_termios;

    fd = open(dev, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        fprintf(stderr, "error, counldn't open file %s\n", dev);
        return 1;
    }
    if (tcgetattr(fd, &old_termios) != 0) {
        fprintf(stderr, "tcgetattr(fd, &old_termios) failed: %s\n", strerror(errno));
        return 1;
    }
    memset(&new_termios, 0, sizeof(new_termios));
    new_termios.c_iflag = IGNPAR;
    new_termios.c_oflag = 0;
    new_termios.c_cflag = CS8 | CREAD | CLOCAL | HUPCL;
    new_termios.c_lflag = 0;
    new_termios.c_cc[VINTR]    = 0;
    new_termios.c_cc[VQUIT]    = 0;
    new_termios.c_cc[VERASE]   = 0;
    new_termios.c_cc[VKILL]    = 0;
    new_termios.c_cc[VEOF]     = 4;
    new_termios.c_cc[VTIME]    = 0;
    new_termios.c_cc[VMIN]     = 1;
    new_termios.c_cc[VSWTC]    = 0;
    new_termios.c_cc[VSTART]   = 0;
    new_termios.c_cc[VSTOP]    = 0;
    new_termios.c_cc[VSUSP]    = 0;
    new_termios.c_cc[VEOL]     = 0;
    new_termios.c_cc[VREPRINT] = 0;
    new_termios.c_cc[VDISCARD] = 0;
    new_termios.c_cc[VWERASE]  = 0;
    new_termios.c_cc[VLNEXT]   = 0;
    new_termios.c_cc[VEOL2]    = 0;

    if (cfsetispeed(&new_termios, B115200) != 0) {
        fprintf(stderr, "cfsetispeed(&new_termios, B115200) failed: %s\n", strerror(errno));
        return 1;
    }
    if (cfsetospeed(&new_termios, B115200) != 0) {
        fprintf(stderr, "cfsetospeed(&new_termios, B115200) failed: %s\n", strerror(errno));
        return 1;
    }
    if (tcsetattr(fd, TCSANOW, &new_termios) != 0) {
        fprintf(stderr, "tcsetattr(fd, TCSANOW, &new_termios) failed: %s\n", strerror(errno));
        return 1;
    }


    // Now read() and write() to the device at your heart's delight
	const char* buf = "help\n";

	printf("configuration done\n");
	printf("writing %lu bytes: %s\n", sizeof(buf), buf);
	write(fd, buf, sizeof(buf));

	char read_buf [10000];
	memset(read_buf, 0, sizeof(read_buf));
	delay(2);

	printf("reading from port: %lu \n", sizeof(read_buf));
	read(fd, &read_buf, sizeof(read_buf));
	printf("reading done: %s\n", read_buf);

    // Before leaving, reset the old serial settings.
    tcsetattr(fd, TCSANOW, &old_termios);
    return 0;
}
