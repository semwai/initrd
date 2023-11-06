KERNEL_VERSION=4.9.126
KERNEL_GZ=linux-${KERNEL_VERSION}.tar.xz  
BUSY_VERSION=1.36.1
BUSY_GZ=busybox-${BUSY_VERSION}.tar.bz2
HTOP_VERSION=3.2.2
HTOP_GZ=htop-${HTOP_VERSION}.tar.xz

mkdir -p artefacts

pushd artefacts

if [ ! -e "$KERNEL_GZ" ] ; then
    wget https://cdn.kernel.org/pub/linux/kernel/v4.x/${KERNEL_GZ}
    tar xf ${KERNEL_GZ}
    mv linux-${KERNEL_VERSION} linux-kernel
else
    echo "found $KERNEL_GZ file"
fi

if [ ! -e "$BUSY_GZ" ] ; then
    wget https://busybox.net/downloads/${BUSY_GZ}
    tar xf ${BUSY_GZ}
    mv busybox-${BUSY_VERSION} busybox
else
    echo "found $BUSY_GZ file"
fi

if [ ! -e "$HTOP_GZ" ] ; then
    wget https://github.com/htop-dev/htop/releases/download/${HTOP_VERSION}/${HTOP_GZ}
    tar xf ${HTOP_GZ}
    mv htop-${HTOP_VERSION} htop
else
    echo "found $HTOP_GZ file"
fi


popd 