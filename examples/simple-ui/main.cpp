#include <iostream>

#include "fb.hpp"

int main() {
    
    auto &fb = Framebuffer::getInstance();

    for (unsigned int i{256}; i < 512; ++i) {
        for (unsigned int j{256}; j < 512; ++j) {
            fb.put_pixel({.x = j, .y = i}, {.r=255, .g=255, .b=0});
        }
    }
}

/*

cp build/main ../../build/rootfs/
pushd ../../build/rootfs
find . -print0 | cpio --null -ov --format=newc > ../initramfs.cpio 
gzip ../initramfs.cpio
popd

*/