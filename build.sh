mkdir -p build/rootfs
### KERNEL
pushd artefacts/linux-kernel
make -j$(nproc)
popd

cp artefacts/linux-kernel/arch/x86/boot/bzImage build

### BUSYBOX
pushd artefacts/busybox
make -j$(nproc)
make CONFIG_PREFIX=./../../build/rootfs/ install
popd

### HTOP
# sudo apt install libncursesw5-dev autotools-dev autoconf automake build-essential
pushd artefacts/htop
./autogen.sh 
./configure --enable-static
make -j$(nproc)

popd


### MAKE ROOT FS (SHOULD BE LAST)
pushd build/rootfs
mkdir bin dev etc home mnt proc sys usr 

# htop..
cp ../../artefacts/htop/htop usr/bin/
mkdir -p lib/terminfo
cp -r ../../configs/terminfo/. lib/terminfo


popd

cp configs/init build/rootfs

pushd build/rootfs
find . -print0 | cpio --null -ov --format=newc > ../initramfs.cpio 
gzip ../initramfs.cpio


popd
