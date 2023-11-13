#include "include/guitext.hpp"

void GuiText::increment_buffer() {
    if (current_.x < w_) {
        current_.x++;
        return;
    }

    if (current_.y < h_) {
        current_.x = 0;
        current_.y ++;
        return;
    }

    current_.x = 0;
    auto &fb = Framebuffer::getInstance();
    fb.copy_up({start_, Pos(start_.x + w_ * font_size_, start_.y + h_ * font_size_ )}, font_size_);
    fb.put_rectangle({ Pos(start_.x, start_.y + (h_ - 2) * font_size_), Pos(start_.x + w_ * font_size_, start_.y + (h_ - 1) * font_size_) }, bg_color_);
    std::cout << "up\n";
    // TODO: move buffer ?
}

void GuiText::put_char(char c) {
    Framebuffer::getInstance().put_char(Pos(start_.x + current_.x * font_size_, start_.y + current_.y * font_size_), c, text_color_);
    increment_buffer();
}

void GuiText::put_str(std::string s) {
    
    for (auto i{0}; i < s.length(); ++i) {
        Framebuffer::getInstance().put_char(Pos(start_.x + current_.x * font_size_, start_.y + current_.y * font_size_), s[i], text_color_);
        increment_buffer();
    }
    
}