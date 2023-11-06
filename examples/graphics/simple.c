#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>

unsigned char *f;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

#define WIDTH 1024
#define HEIGHT 768

void demo()
{
    int k = 0;
    int offset;
    while (1)
    {
        for (int i = 0; i < HEIGHT; ++i)
        {
            for (int j = 0; j < WIDTH; ++j)
            {
                offset = (i * WIDTH + j) * 4;
                f[offset + 0] = (i * j + k);
                f[offset + 1] = (i+ j + k);
                f[offset + 2] = 0;
                f[offset + 3] = 0; // May not be neeeded
            }
        }
        ++k;
    }
}
int main()
{

    FILE *fb0 = open("/dev/fb0", O_RDWR);
    if (fb0 == -1)
    {
        printf("%d %s\n", errno, strerror(errno));
        exit(errno);
    }

    // Get fixed screen information
    if (ioctl(fb0, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        printf("%d %s\n", errno, strerror(errno));
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fb0, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        printf("%d %s\n", errno, strerror(errno));
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    int screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    printf("screensize = %d\n", screensize);
    f = (unsigned char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb0, 0);
    if (f == MAP_FAILED)
    {
        printf("%d %s\n", errno, strerror(errno));
        exit(errno);
    }

    memset(f, 55, screensize);

    demo();
}