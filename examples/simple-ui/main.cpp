#include <iostream>

#include "fb.hpp"

int main() {
    
    auto &fb = Framebuffer::getInstance();

    for (auto i{0}; i < 256; ++i) {
        fb.put_rectangle(Pos(i, i), Pos(600 - i, 600 - i), Color::Grey(i));
    }
    
    fb.put_rectangle(Pos(0, 0), Pos(400, 400), Color::Red());
    fb.put_rectangle(Pos(100, 100), Pos(500, 500), Color::Green());
    fb.put_rectangle(Pos(200, 200), Pos(600, 600), Color::Blue());

    for (auto i{256}; i < 512; ++i) {
        for (auto j{256}; j < 512; ++j) {
            fb.put_pixel(Pos(j, i), Color(i*j, 0, 0));
        }
    }

    std::string str = "Hello world!!!!!!!";
    for (auto i{0}; i < str.length(); ++i) {
        fb.put_char(Pos(i * 8, 700), str[i], Color::Green());
    }

}