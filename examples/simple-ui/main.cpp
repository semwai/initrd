#include <iostream>
#include <chrono>
#include <thread>
#include <random>


#include "fb.hpp"
#include "guitext.hpp"

int main() {
    
    auto &fb = Framebuffer::getInstance();

    // for (auto i{0}; i < 256; ++i) {
    //     fb.put_rectangle({Pos(i, i), Pos(600 - i, 600 - i)}, Color::Grey(i));
    // }
    
    // fb.put_rectangle({Pos(0, 0), Pos(400, 400)}, Color::Red());
    // fb.put_rectangle({Pos(100, 100), Pos(500, 500)}, Color::Green());
    // fb.put_rectangle({Pos(200, 200), Pos(600, 600)}, Color::Blue());

    // for (auto i{256}; i < 512; ++i) {
    //     for (auto j{256}; j < 512; ++j) {
    //         fb.put_pixel(Pos(j, i), Color(i*j, 0, 0));
    //     }
    // }

    // std::string str = "Hello world!!!!!!! 0123456789ABCDEF QWERTY 123456 AAAABBBBCCCCDDD";
    // for (auto i{0}; i < str.length(); ++i) {
    //     fb.put_char(Pos(i * 8, 700), str[i], Color::Green());
    // }

    // fb.put_rectangle({Pos(0, 0), Pos(400, 100)}, Color::Grey(0));

    // auto guitext = GuiText(Pos(0, 0), 10, 10);
    // guitext.put_str(str);

    // {
    //     auto guitext = GuiText(Pos(110, 110), 20, 10);
    //     guitext.put_str(str);
    // }

    {
        fb.put_rectangle({Pos(310, 310), Pos(24*8, 7*8)}, Color::Grey(32));
        auto guitext = GuiText(Pos(310, 310), 24, 7);

        std::string str = "Hello world!0123456789";
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0,str.length()); 
        

        for (auto i{0}; i < 1000; ++i) {
            
            
            guitext.put_char(str[dist(rng)]);
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        
    }
}