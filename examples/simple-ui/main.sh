cp build/main ../../build/rootfs/
pushd ../../build/rootfs
find . -print0 | cpio --null -ov --format=newc > ../initramfs.cpio 
gzip -f ../initramfs.cpio
popd

pushd ../../

./run.sh
popd