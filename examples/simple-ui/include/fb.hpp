#pragma once

#include <cstdint>
#include <iostream>

#include <tl/expected.hpp>

#include <linux/fb.h>


class Pos {
  public:
    Pos(uint x, uint y) : x(x), y(y) {}
    uint x;
    uint y;
};

class Rectange {
  public:
    Pos start{ 0, 0};
    Pos end{ 0, 0};
};

class Color {
  public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a)
     {}

    static Color Red(uint8_t r = 255, uint8_t a = 255) {
        return Color(r, 0, 0);
    }

    static Color Green(uint8_t g = 255, uint8_t a = 255) {
        return Color(0, g, 0);
    }

    static Color Blue(uint8_t b = 255, uint8_t a = 255) {
        return Color(0, 0, b);
    }

    static Color Grey(uint8_t c = 255, uint8_t a = 255) {
        return Color(c, c, c, a);
    }

    uint8_t r, g, b, a = 0;
};

class Framebuffer
{
private:
    Framebuffer() {}
    Framebuffer(const Framebuffer &);
    Framebuffer &operator=(Framebuffer &);

    tl::expected<void, std::string>  init_fb();

    uint8_t *f;
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
    void put_rectangle(Rectange rec, Color c);
    void put_char(Pos pos, char s, Color c);

    // для скроллинга удобно
    void copy_up(Rectange rec, uint x);
};

