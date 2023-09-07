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
    int m_height=0;
    int m_width=0;
    int m_color_count=0;
    int m_chars=0;
    int m_pix_bits=0;

    std::map<std::string,RGB> m_meta;
    std::vector<std::vector<RGB>> m_pixmap;

    std::map<std::string,RGB> m_color_cache;

    public:
    bool parser(const char* file);
    int width();
    int height();
    void show_info();

    bool save(const char* file);
    void to_bitmap(char* data);
};