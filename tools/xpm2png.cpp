#include <png.h>
#include <iostream>
#include "../xpm/xpm.h"

/* 写入 png 文件 */
int write_png(const char *file_name, int width,int height, int bit_depth, unsigned char* image) {
    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;

    /* 打开需要写入的文件 */
    fp = fopen(file_name, "wb");
    if (fp == NULL)
        return -1;

    /* 创建并初始化 png_struct 及其所需的错误处理函数，如果你想使用默
    * 认的 stderr 和 longjump() 方法，你可以将最后三个参数设为 NULL，
    * 在使用动态链接库的情况下，我们也会检测函数库版本是否与在编译时
    * 使用的版本是否兼容。（必要）
    */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL)
    {
        fclose(fp);
        return -1;
    }

    /* 分配内存并初始化图像信息数据。（必要）*/
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        fclose(fp);
        png_destroy_write_struct(&png_ptr,  NULL);
        return -1;
    }

    /* 设置错误处理。如果你在调用 png_create_write_struct() 时没
    * 有设置错误处理函数，那么这段代码是必须写的。*/
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        /* 如果程序跑到这里了，那么写入文件时出现了问题 */
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return -1;
    }

    /* 设置输出控制，如果你使用的是 C 的标准 I/O 流 */
    png_init_io(png_ptr, fp);

    /* 这是一种复杂的做法 */

    /* （必需）在这里设置图像的信息，宽度、高度的上限是 2^31。
    * bit_depth 取值必需是 1、2、4、8 或者 16, 但是可用的值也依赖于 color_type。
    * color_type 可选值有： PNG_COLOR_TYPE_GRAY、PNG_COLOR_TYPE_GRAY_ALPHA、
    * PNG_COLOR_TYPE_PALETTE、PNG_COLOR_TYPE_RGB、PNG_COLOR_TYPE_RGB_ALPHA。
    * interlace 可以是 PNG_INTERLACE_NONE 或 PNG_INTERLACE_ADAM7,
    * 而 compression_type 和 filter_type 目前必需是 PNG_COMPRESSION_TYPE_BASE
    * 和 and PNG_FILTER_TYPE_BASE。
    */
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    /* 写入文件头部信息（必需） */
    png_write_info(png_ptr, info_ptr);

    if (height > PNG_UINT_32_MAX/(sizeof (png_bytep)))
        png_error (png_ptr, "Image is too tall to process in memory");

    /* 将这些像素行指针指向你的 "image" 字节数组中对应的位置，即：指向每行像素的起始处 */
    png_uint_32 k;
    png_bytep row_pointers[height];
    for (k = 0; k < height; k++) {
        row_pointers[k] = (png_bytep)image + k*width*bit_depth/8*3;
    }

    /* 一次调用就将整个图像写进文件 */
    png_write_image(png_ptr, row_pointers);
    /* 必需调用这个函数完成写入文件其余部分 */
    png_write_end(png_ptr, info_ptr);
    /* 写完后清理并释放已分配的内存 */
    png_destroy_write_struct(&png_ptr, &info_ptr);
    /* 关闭文件 */
    fclose(fp);

    /* That's it */
    return 0;
}

int main(int argc,char** argv) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " xpm_file_path rgb_file_path" << std::endl;
        return 0;
    }

    auto xpm = std::unique_ptr<xpm::Parser>(new xpm::Parser());
    if(xpm->parser(argv[1])) {
        xpm->show_info();
        
        int bytes_cout = xpm->pix_bits()/8 * xpm->height() * xpm->width();
        char* pixmap = (char *)malloc(bytes_cout);
        xpm->to_bitmap(pixmap);

        write_png(argv[2], xpm->width(), xpm->height(), xpm->pix_bits()/3, (unsigned char*)pixmap);
    } else {
        std::cout << "parser error." << std::endl;
    }
    
    return 0;
}