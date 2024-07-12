# opengl-es-training

## Prerequisites
To be able to run it on Linux, please install the following packages:

```console
sudo apt-get install libgles2-mesa-dev libgstreamer1.0-dev
```

## Build

To build natively for Linux x64 platform and use X11 as the EGL backend:

```console
make
```

To cross-compile for Linux ARM 32 bits and use the Linux Framebuffer as the EGL backend:

```console
export PATH=/home/cross/7.4.1_Linaro_glibc_2.27/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/:$PATH
make NATIVE_DISPLAY_TYPE=fb FB_NUMBER=0 CROSS_COMPILE=arm-linux-gnueabihf- \
    GPU_PKG_CONFIG=/home/gpu/imx-gpu-viv-6.2.4.p4.0-aarch32/usr/lib/pkgconfig/egl.pc
```

## Build configuration

```console
# To select the Linux framebuffer as the EGL backend, used in embedded environments:
NATIVE_DISPLAY_TYPE=fb

# To select the X Window System (X11) as the EGL backend, used in desktop environments:
NATIVE_DISPLAY_TYPE=x11

# To select the /dev/fb0 Linux framebuffer device as the EGL Native display,
# only used if NATIVE_DISPLAY_TYPE=fb:
FB_NUMBER=0

# To select the /dev/fb1 Linux framebuffer device as the EGL Native display,
# only used if NATIVE_DISPLAY_TYPE=fb:
FB_NUMBER=1

# To specify the prefix of the toolchain used for cross-compiling:
CROSS_COMPILE=arm-linux-gnueabihf-

# To specify the path to the GPU OpenGL libraries pkg-config .pc file:
GPU_PKG_CONFIG=/home/gpu/imx-gpu-viv-6.2.4.p4.0-aarch32/usr/lib/pkgconfig/egl.pc
```
