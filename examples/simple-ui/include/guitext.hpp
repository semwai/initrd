#include <iostream>
#include "fb.hpp"

class GuiText {
  private:
    Pos start_;
    unsigned int w_;
    unsigned int h_;
    unsigned int font_size_{8};
    
    Color bg_color_{Color::Grey(0)};
    Color text_color_{Color::Grey(255)};
    Pos current_{Pos(0, 0)};



  public:

    GuiText(Pos start, unsigned int w = 80, unsigned int h = 25) : start_(start), w_(w), h_(h) {
    }


    void put_char(char c);

    void put_str(std::string c);

    void increment_buffer();

};