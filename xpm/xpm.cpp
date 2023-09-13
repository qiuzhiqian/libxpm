#include "xpm.h"
#include "utils.h"

#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

const std::map<std::string, RGB> color_name_map= {
    {"aqua", {0x00,0xff,0xff}},
    {"black", {0x00,0x00,0x00}},
    {"blue", {0x00,0x00,0xff}},
    {"fuchsia", {0xff,0x00,0xff}},

    {"gray", {0x80,0x80,0x80}},
    {"green", {0x00,0x80,0x00}},
    {"lime", {0x00,0xff,0x00}},
    {"maroon", {0x80,0x00,0x00}},

    {"navy", {0x00,0x00,0x80}},
    {"olive", {0x80,0x80,0x00}},
    {"purple", {0x80,0x00,0x80}},
    {"red", {0xff,0x00,0x00}},

    {"silver", {0xc0,0xc0,0xc0}},
    {"teal", {0x00,0x80,0x80}},
    {"white", {0xff,0xff,0xff}},
    {"yellow", {0xff,0xff,0x00}},
};

static bool start_line(const char* str) {
    std::smatch m;
    std::string s(str);
    std::regex reg("char\\s*\\*\\s*[a-zA-Z0-9\\-\\._\\s]+\\[\\]\\s*=\\s\\{");
    return std::regex_search(s, m, reg);
}

static bool end_line(const char* str) {
    std::smatch m;
    std::string s(str);
    std::regex reg("^\\s*\\};");
    return std::regex_search(s, m, reg);
}

static bool end_line_with_sysmble(const char* str, std::string& content) {
    std::smatch m;
    std::string s(str);
    std::regex reg("^\\s*(\".*\")\\s*\\};");
    //bool res = std::regex_search(s, m, reg);
    while (std::regex_search (s, m, reg)) {
        if(m.length()>=2) {
            content = std::string(m[1]);
            return true;
        }
        s = m.suffix().str();
    }
    return false;
}

static std::string get_raw_content(const char* str) {
    std::smatch m;
    std::string s(str);
    std::regex reg("^\\s*\"(.*)\"");
    while (std::regex_search (s, m, reg)) {
        if(m.length()>=2) {
            return std::string(m[1]);
        }
        s = m.suffix().str();
    }
    return std::string();
}

void rgb24to48(RGB& rgb) {
    rgb.r = (double)rgb.r * 0xffff / 0xff;
    rgb.g = (double)rgb.g * 0xffff / 0xff;
    rgb.b = (double)rgb.b * 0xffff / 0xff;
}

//aqua、black、blue、fuchsia、gray、green、lime、maroon、navy、olive、purple、red、silver、teal、white、yellow。
RGB get_color_by_name(const std::string color) {
    RGB rgb;
    if(color.compare(0, 4, "gray") == 0 && color.size() > 4) {
        rgb.r = static_cast<uint32_t>(std::stoi(color.substr(4)));
        rgb.g = rgb.r;
        rgb.b = rgb.r;
    } else {
        rgb = color_name_map.at(color);
    }
    return rgb;
}

bool CXpm::parser(const char *file) {
    std::ifstream infile;
	infile.open(file, std::ios::in);
	if (!infile.is_open()) {
		return false;
	}
	
    std::string buf;
    bool origin_started = false;
    int line_num = 0;
	while (std::getline(infile, buf)) {
        trim(buf);
        //std::cout << buf << std::endl;

        bool close_after = false;
        std::string endline;
        if(start_line(buf.c_str())) {
            origin_started = true;
            //std::cout << "this is start line" << std::endl;
            continue;
        } else if(end_line(buf.c_str())) {
            origin_started = false;
            //std::cout << "this is end line" << std::endl;
            break;
        } else if(end_line_with_sysmble(buf.c_str(), endline)) {
            buf = endline;
            close_after = true;
            //std::cout << "this is end line with sysmble" << std::endl;
        }

        if(origin_started) {
            auto content = get_raw_content(buf.c_str());
            std::replace(content.begin(),content.end(),'\t',' ');
            if(!content.empty() && content.size() >= 5) {
                // find c token
                if(line_num == 0) {
                    //first line
                    trim(content);
                    auto tokens = split(content," ");
                    //std::cout << tokens.size() << std::endl;
                    if(tokens.size() >= 4) {
                        this->m_width = std::stoi(tokens[0]);
                        this->m_height = std::stoi(tokens[1]);
                        this->m_color_count = std::stoi(tokens[2]);
                        this->m_chars = std::stoi(tokens[3]);
                        //std::cout << this->m_width << " " \
                        //    << this->m_height << " " \
                        //    << this->m_color_count << " "  \
                        //    << this->m_chars \
                        //    << std::endl;
                        for(auto w = 0;w < this->m_height; w++) {
                            std::vector<RGB> line;
                            line.resize(this->m_width);
                            this->m_pixmap.push_back(line);
                        }
                    }
                } else if(line_num <= this->m_color_count) {
                    std::string key = content.substr(0, this->m_chars);
                    std::string color_token = content.substr(this->m_chars);
                    trim(color_token);
                    //std::cout << "color_token=" << color_token << std::endl;
                    auto c = split(color_token, std::string(" "));
                    //std::cout << "key= " << key << " " << c.size() << " " << c[0][0] << " " << c[0].size() << std::endl;

                    int color_pos = -1;
                    for(int i=0; i<c.size(); i++) {
                        trim(c[i]);
                        //std::cout << "c i=" << i <<"="<<c[i] << std::endl;
                        if(c[i] == "c") {
                            //std::cout << "find c token index " << i <<" " << c.size() << std::endl;
                            color_pos = i+1;
                            break;
                        }
                    }

                    if(color_pos < c.size() && color_pos >= 0) {
                        uint32_t r;
                        uint32_t g;
                        uint32_t b;
                        std::string symble = c.at(color_pos);
                        std::string lower_symble = symble;
                        std::transform(symble.begin(),symble.end(),lower_symble.begin(),::tolower);

                        if(symble.at(0) == '#') {
                            if(this->m_pix_bits == 0) {
                                this->m_pix_bits = (symble.size() - 1) *4; 
                            }
                            
                            int len = this->m_pix_bits/12;
                            r = static_cast<uint32_t>(std::stoi(symble.substr(1,len),0,16));
                            g = static_cast<uint32_t>(std::stoi(symble.substr(1 + len, len),0,16));
                            b = static_cast<uint32_t>(std::stoi(symble.substr(1 + len * 2, len),0,16));
                            this->m_meta[key] = RGB{r, g, b};
                        } else if(lower_symble == "none") {
                            this->m_color_cache[key] = RGB{0xff,0xff,0xff};
                        } else {
                            RGB rgb;
                            try {
                                rgb = get_color_by_name(symble);
                            }
                            catch (const std::out_of_range& oor) {
                                infile.close();
                                return false;
                            }
                            this->m_color_cache[key] = rgb;
                            //std::cout << "has gray pix: " << r << std::endl;
                        }
                        //std::cout << r << " " << g << " " << b << " " << std::endl;
                        
                    } else {
                        infile.close();
                        return false;
                    }

                    // 已经到了color规则的最后一行，需要在此处把前面cache的颜色进行重新处理。
                    if(line_num == this->m_color_count) {
                        if(this->m_pix_bits == 0) {
                            this->m_pix_bits = 24;
                        }
                        for (auto it=this->m_color_cache.begin(); it!=this->m_color_cache.end(); ++it){
                            if(this->m_pix_bits == 48) {
                                rgb24to48(it->second);
                            }
                            this->m_meta[it->first]=it->second;
                        }
                    }
                } else {
                    if(content.size() == this->m_width * this->m_chars) {
                        int y = line_num- ( 1 + this->m_color_count);
                        for(auto w=0;w<content.size();) {
                            int x = w/this->m_chars;
                            std::string pix = content.substr(w, this->m_chars);
                            w+=this->m_chars;
                            RGB rgb = this->m_meta.at(pix);
                            this->m_pixmap[y][x] = rgb;
                        }
                    }
                }

                line_num++;
            } else {
                // TODO 此处需要过滤注释行
                //infile.close();
                //return false;
            }
        }

        if(close_after) {
            origin_started = false;
            close_after = false;
            break;
        }
	}
    infile.close();
    if(this->m_height != this->m_pixmap.size()) {
        return false;
    }

    if(this->m_pixmap.empty() || this->m_pixmap.at(0).empty()) {
        return false;
    }
    return true;
}

int CXpm::width() {
    if(this->m_pixmap.empty()) {
        return 0;
    }
    return this->m_pixmap[0].size();
}

int CXpm::height() {
    return this->m_pixmap.size();
}

int CXpm::pix_bits() {
    return this->m_pix_bits;
}

void CXpm::show_info() {
    std::cout << "size: " << this->m_width << "x" << this->m_height << std::endl;
    std::cout << "pixel_format: " << "rgb" << this->m_pix_bits << std::endl;
}

// 保存后可以使用
// 类似ffplay -f rawvideo -pixel_format rgb24 -video_size 16x16 xpm-save.rgb
// 的命令来查看
bool CXpm::save(const char *file) {
    std::ofstream outfile;
	outfile.open(file, std::ios::out|std::ios::binary);
	if (!outfile.is_open()) {
		return false;
	}

    for(auto y = 0;y < this->height();y++) {
        for(auto x = 0;x < this->width();x++) {
            auto rgb= this->m_pixmap.at(y).at(x);
            int len = this->m_pix_bits/24;
            outfile.write((char *)&(rgb.r), len);
            outfile.write((char *)&(rgb.g), len);
            outfile.write((char *)&(rgb.b), len);
        }
    }
    outfile.close();
    return true;
}

void CXpm::to_bitmap(char *data) {
    int start_index = 0;
    for(auto y = 0;y < this->height();y++) {
        for(auto x = 0;x < this->width();x++) {
            auto rgb= this->m_pixmap.at(y).at(x);
            int len = this->m_pix_bits/24;
            memcpy(data + start_index, (char *)&(rgb.r), len);
            start_index+=len;
            memcpy(data + start_index, (char *)&(rgb.g), len);
            start_index+=len;
            memcpy(data + start_index, (char *)&(rgb.b), len);
            start_index+=len;
        }
    }
}