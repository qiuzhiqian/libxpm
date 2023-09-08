# libxpm
这是一个将xpm图片文件转换成pixmap数组的cpp库。

当然，你也可以直接使用tools目录中附带的xpm2rgb和xpm2png根据对xpm图片进行格式转换

# 编译
```
$ mkdir build
$ cd build
$ cmake ..
$ make
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
png格式文件直接使用图片查看工具打开即可。

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