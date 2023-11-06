# kernel
#pushd artefacts/linux-kernel
cp configs/kernel/.config artefacts/linux-kernel
#make defconfig
#make kvm_guest.config

#popd

# busybox
pushd artefacts/busybox

make defconfig

cp ../../configs/busybox .config

popd