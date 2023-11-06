# brctl addbr br0
# brctl addif br0 eth0
qemu-system-x86_64\
 -kernel artefacts/linux-kernel/arch/x86/boot/bzImage \
 -initrd ./build/initramfs.cpio.gz\
 -m 256 \
 -netdev user,id=network0 -device e1000,netdev=network0,mac=52:54:00:12:34:56
 #-no-acpi

# -append "console=ttyS0" \
#-nographic\
# -net nic,model=virtio \
# -net bridge,br=br0 \
