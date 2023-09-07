#include "xpm.h"
#include "utils.h"

#include <fstream>
#include <iostream>

static bool start_line(const char* str) {
    std::smatch m;
    std::string s(str);
    std::regex reg("char\\s*\\*\\s*[a-zA-Z0-9\\-\\._\\s]+\\[\\]\\s*=\\s\\{");
    return std::regex_search(s, m, reg);
}

static bool end_line(const char* str) {
    std::smatch m;
    std::string s(str);
    std::regex reg("^\\s*};");
    return std::regex_search(s, m, reg);
}

static bool end_line_with_sysmble(const char* str, std::string& content) {
    std::smatch m;
    std::string s(str);
    std::regex reg("^\\s*(\".*\")\\s*};");
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
            continue;
        } else if(end_line_with_sysmble(buf.c_str(), endline)) {
            buf = endline;
            close_after = true;
            //std::cout << "this is end line with sysmble" << std::endl;
        }

        if(origin_started) {
            auto content = get_raw_content(buf.c_str());
            if(!content.empty() && content.size() >= 5) {
                //std::cout << content << std::endl;
                if(line_num == 0) {
                    //first line
                    trim(content);
                    auto tokens = split(content," ");
                    //std::cout << tokens.size() << std::endl;
                    if(tokens.size() == 4) {
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
                    auto c = split(color_token, std::string(" "));
                    //std::cout << "key= " << key << " " << c.size() << " " << c[1] << std::endl;
                    if(c.size() == 2 || c.size() == 4) {
                        uint32_t r;
                        uint32_t g;
                        uint32_t b;
                        std::string symble = c.at(c.size() -1);
                        //std::cout << "sysmble: " << symble << std::endl;

                        if(symble.at(0) == '#') {
                            this->m_pix_bits = (symble.size() - 1) *4; 
                            int len = this->m_pix_bits/12;
                            r = static_cast<uint32_t>(std::stoi(symble.substr(1,len),0,16));
                            g = static_cast<uint32_t>(std::stoi(symble.substr(1 + len, len),0,16));
                            b = static_cast<uint32_t>(std::stoi(symble.substr(1 + len * 2, len),0,16));
                        } else if(symble == "None") {
                            r = 0;
                            g = 0;
                            b = 0;
                        } else if(symble.compare(0, 4, "gray") == 0){
                            r = static_cast<uint32_t>(std::stoi(symble.substr(4)));
                            g = r;
                            b = r;
                            //std::cout << "has gray pix: " << r << std::endl;
                        } else {
                            infile.close();
                            return false;
                        }
                        //std::cout << r << " " << g << " " << b << " " << std::endl;
                        this->m_meta[key] = RGB{r, g, b};
                    } else {
                        infile.close();
                        return false;
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
        }
	}
    infile.close();
    if(this->m_height != this->m_pixmap.size()) {
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