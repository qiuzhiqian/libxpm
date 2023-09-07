# xpm2rgb
这是一个将xpm图片文件转换成rgb格式(pixmap)的命令行工具。当然你也可以直接使用其库文件即可.

# 编译
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# 运行和测试
```
$ ./tools/xpm2rgb /usr/share/pixmaps/vim-16.xpm
size: 16x16
pixel_format: rgb24

rgb raw图片查看：
$ ffplay -f rawvideo -pixel_format rgb24 -video_size 16x16 xpm-save.rgb
```

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