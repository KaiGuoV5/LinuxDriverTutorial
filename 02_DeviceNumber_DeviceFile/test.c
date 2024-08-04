/* This is a test program for device number and device file module */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int dev = open("/dev/mydevice", O_RDONLY);
    if (dev < 0) {
        printf("Open device file failed!\n");
        return -1;
    }
    printf("Open device file success!\n");
    close(dev);
    return 0;
}
