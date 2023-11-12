#pragma once


#include <iostream>

#include <tl/expected.hpp>

#include <linux/fb.h>

class Pos {
  public:
    Pos(unsigned int x, unsigned int y) : x(x), y(y) {}
    unsigned int x;
    unsigned int y;
};

class Color {
  public:
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : r(r), g(g), b(b), a(a)
     {}

    static Color Red(unsigned char r = 255, unsigned char a = 255) {
        return Color(r, 0, 0);
    }

    static Color Green(unsigned char g = 255, unsigned char a = 255) {
        return Color(0, g, 0);
    }

    static Color Blue(unsigned char b = 255, unsigned char a = 255) {
        return Color(0, 0, b);
    }

    static Color Grey(unsigned char c = 255, unsigned char a = 255) {
        return Color(c, c, c, a);
    }

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
    void put_rectangle(Pos pos1, Pos pos2, Color c);
    void put_char(Pos pos, char s, Color c);
};

