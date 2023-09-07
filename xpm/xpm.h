#pragma once

#include <regex>
#include <map>
#include <string>
#include <vector>

struct RGB{
    uint32_t r;
    uint32_t g;
    uint32_t b;
};

class CXpm{
    private:
    int m_height;
    int m_width;
    int m_color_count;
    int m_chars;
    int m_pix_bits;

    std::map<std::string,RGB> m_meta;
    std::vector<std::vector<RGB>> m_pixmap;

    std::map<std::string,RGB> m_color_cache;

    public:
    bool parser(const char* file);
    int width();
    int height();
    void show_info();

    bool save(const char* file);
};