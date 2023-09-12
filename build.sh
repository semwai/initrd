mkdir -p build/rootfs

pushd artefacts/linux-kernel
make -j$(nproc)
popd

cp artefacts/linux-kernel/arch/x86/boot/bzImage build


pushd artefacts/busybox
make -j$(nproc)
make CONFIG_PREFIX=./../../build/rootfs/ install
popd


pushd build/rootfs
mkdir bin dev etc home mnt proc sys usr 
popd

cp configs/init build/rootfs

pushd build/rootfs
find . -print0 | cpio --null -ov --format=newc > ../initramfs.cpio 
gzip ../initramfs.cpio


popd
