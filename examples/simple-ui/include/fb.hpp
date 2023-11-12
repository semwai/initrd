#pragma once


#include <iostream>

#include <tl/expected.hpp>

#include <linux/fb.h>

struct Pos {
    unsigned int x;
    unsigned int y;
};

struct Color {
    unsigned char r, g, b, a = 0;
};

class Framebuffer
{
private:
    Framebuffer() {}
    Framebuffer(const Framebuffer &);
    Framebuffer &operator=(Framebuffer &);

    tl::expected<void, std::string>  init_fb();

    unsigned char *f;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;

public:
    static Framebuffer &getInstance()
    {
        static Framebuffer instance;
        static bool init;
        if (!init) {
            auto res = instance.init_fb();
            if (!res.has_value()) {
                std::cout << "Framebuffer init error: " << res.error() << '\n';
            } else {
                init = true;
            }
            
        }
        return instance;
    }

    void put_pixel(Pos pos, Color c);
};