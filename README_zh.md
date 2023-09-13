[English](./README.md) | **简体中文**
# libxpm
这是一个将xpm图片文件转换成pixmap数组的cpp库。适用于linux平台和android平台。

当然，你也可以直接使用tools目录中附带的xpm2rgb和xpm2png工具将xpm图片转换到对应的格式。

# 编译
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

# 运行和测试
tools/xpm2rgb工具测试
```
$ ./tools/xpm2rgb /usr/share/pixmaps/vim-16.xpm xpm-save.rgb
size: 16x16
pixel_format: rgb24

rgb raw图片查看：
$ ffplay -f rawvideo -pixel_format rgb24 -video_size 16x16 xpm-save.rgb
```

tools/xpm2png工具测试
```
$ ./tools/xpm2png /usr/share/pixmaps/python.xpm xpm-save.png
size: 32x32
pixel_format: rgb24
```
**备注：png格式文件直接使用图片查看工具打开即可。**

测试用例：
```
$ ctest --test-dir xpm/ -C DEBUG
Internal ctest changing into directory: /home/work/xpm2rgb/build/xpm
Test project /home/work/xpm2rgb/build/xpm
    Start 1: mytest
1/1 Test #1: mytest ...........................   Passed    1.41 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   1.41 sec
```

# 依赖
libxpm本身基于c++11，本身只是用了std库，并没有额外引入其他三方库：
```
$ ldd build/xpm/libxpm.so 
        linux-vdso.so.1 (0x00007ffec0d54000)
        libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f07bdced000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f07bdb6a000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f07bdb50000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f07bd98f000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f07bdf50000)
```
如果需要使用本代码中的xpm2png部分的转换逻辑，则需要额外引入libpng这个库：
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

对于libpng库，linux平台和android aosp(external/libpng)均自带这个库，因此该工程可以正常运行在linux和android平台上