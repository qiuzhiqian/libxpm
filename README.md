**English** | [简体中文](./README_zh.md)

```
  _  _  _                            
 | |(_)| |__ __  __ _ __   _ __ ___  
 | || || '_ \\ \/ /| '_ \ | '_ ` _ \ 
 | || || |_) |>  < | |_) || | | | | |
 |_||_||_.__//_/\_\| .__/ |_| |_| |_|
                   |_|               
```
# libxpm
This is a cpp library to convert xpm image files to pixmap arrays. libxpm is available for linux platform and android platform.

Of course, you can also directly use the xpm2rgb and xpm2png tools included in the tools directory to convert xpm images to the corresponding formats

# compiling
## Linux
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Android
```
# mmm external/libxpm/
```

# Running and testing
tools/xpm2rgb test
```
$ ./tools/xpm2rgb /usr/share/pixmaps/vim-16.xpm xpm-save.rgb
size: 16x16
pixel_format: rgb24

rgb raw图片查看：
$ ffplay -f rawvideo -pixel_format rgb24 -video_size 16x16 xpm-save.rgb
```

tools/xpm2png test
```
$ ./tools/xpm2png /usr/share/pixmaps/python.xpm xpm-save.png
size: 32x32
pixel_format: rgb24
```
**Note: The png format files can be opened directly using the image viewer tool.**

test case:
```
$ make test
Running tests...
Test project /home/work/libxpm/build
    Start 1: mytest
1/1 Test #1: mytest ...........................   Passed    0.15 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.15 sec
```

# dependencies
libxpm itself is based on c++11, which itself just uses the std library, and doesn't additionally introduce other three-way libraries:
```
$ ldd build/xpm/libxpm.so 
        linux-vdso.so.1 (0x00007ffec0d54000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f07bdced000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f07bdb6a000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f07bdb50000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f07bd98f000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f07bdf50000)
```
If you need to use the conversion logic in the xpm2png part of this code, you need to introduce the library libpng additionally:
```
$ ldd build/tools/xpm2png 
        linux-vdso.so.1 (0x00007fff1eba5000)
        libxpm.so => /home/xml/work/code/cpp/xpm2rgb/build/xpm/libxpm.so (0x00007f27ddaea000)
        libpng16.so.16 => /lib/x86_64-linux-gnu/libpng16.so.16 (0x00007f27dda8f000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f27dd90b000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f27dd788000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f27dd76e000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f27dd5ab000)
        libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007f27dd58d000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f27ddba7000)
```
For the libpng library, both the linux platform and the android aosp (external/libpng) include this library, so the project can run normally on both linux and android platforms.