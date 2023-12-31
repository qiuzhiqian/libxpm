#pragma once

#include <regex>
#include <map>
#include <string>
#include <vector>

namespace xpm {
struct RGB{
    uint32_t r;
    uint32_t g;
    uint32_t b;
};

class Parser{
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
    bool parse(const char* file);
    int width() const;
    int height() const;
    int pix_bits() const;
    void show_info() const;

    bool save(const char* file) const;
    void to_bitmap(char* data) const;
};
}
