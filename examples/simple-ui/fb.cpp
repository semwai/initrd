#include "include/fb.hpp"
#include "include/font8x8_basic.hpp"

#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <fmt/format.h>


#include <chrono>
#include <thread>

tl::expected<void, std::string> Framebuffer::init_fb() {
    auto fb0 = open("/dev/fb0", O_RDWR);
    if (fb0 == -1)
    {
        return tl::unexpected(strerror(errno));
    }
    // Get fixed screen information
    if (ioctl(fb0, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        return tl::unexpected(fmt::format("{} - Error reading fixed information", strerror(errno)));
    }
    // Get variable screen information
    if (ioctl(fb0, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        return tl::unexpected(fmt::format("{} - Error reading variable information", strerror(errno)));
    }
    int screensize = Framebuffer::vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    f = (unsigned char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb0, 0);
    if (f == MAP_FAILED)
    {
        return tl::unexpected(strerror(errno));
    }
    return {};
}

void Framebuffer::put_pixel(Pos pos, Color c) {
    assert (pos.x >= 0 && pos.x < vinfo.xres && pos.y >= 0 && pos.y < vinfo.yres);

    auto offset = (pos.y * vinfo.xres + pos.x) * 4;
    f[offset + 0] = c.b;
    f[offset + 1] = c.g;
    f[offset + 2] = c.r;
    f[offset + 3] = c.a;
}

void Framebuffer::put_rectangle(Rectange rec, Color c) {
    for (auto i{rec.start.y}; i < rec.end.y; ++i) {
        for (auto j{rec.start.x}; j < rec.end.x; ++j) {
            auto offset = (i * vinfo.xres + j) * 4;
            f[offset + 0] = c.b;
            f[offset + 1] = c.g;
            f[offset + 2] = c.r;
            f[offset + 3] = c.a;
        }
    }
}

void Framebuffer::put_char(Pos pos, char s, Color c) {

    int set;
    for (int y=0; y < 8; ++y) {
        for (int x=0; x < 8; ++x) {
            set = font8x8_basic[s][y] & static_cast<unsigned char>(1 << x);
            if (set) {
                put_pixel(Pos(pos.x + x, pos.y + y), c);
            }
        }
    }
}

void Framebuffer::copy_up(Rectange rec, uint x) {

    auto w = (vinfo.xres) * (vinfo.bits_per_pixel / 8);
    
    auto f_offset = f + (rec.start.y * vinfo.xres + rec.start.x) * 4;

    auto h = rec.end.y - rec.start.y;


    for (auto i{0}; i < h; ++i) {
        std::memmove(f_offset + w*i , f_offset + w*(i + x), w);
    }
    
}