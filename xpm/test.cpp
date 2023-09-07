#include <iostream>
#include <vector>
#include "xpm.h"

int main(int argc,char** argv) {
    CXpm *xpm = new CXpm();

    std::vector<std::string> list{
        "/usr/share/pixmaps/openjdk-11.xpm",
        "/usr/share/pixmaps/pstree16.xpm",
        "/usr/share/pixmaps/vim-48.xpm",
        "/usr/share/pixmaps/vim-16.xpm",
        "/usr/share/pixmaps/python3.7.xpm",
        "/usr/share/pixmaps/vim-32.xpm",
        "/usr/share/icons/hicolor/32x32/apps/vlc.xpm",
        "/usr/share/icons/hicolor/32x32/apps/vlc-xmas.xpm",
        "/usr/share/pixmaps/python2.7.xpm",
        "/usr/share/pixmaps/pstree32.xpm",
        "/usr/share/icons/hicolor/16x16/apps/vlc.xpm"
    };
    for(auto i:list) {
        std::cout << "parser: " << i<< std::endl;
        CXpm xpm;
        if(xpm.parser(i.c_str())) {
            xpm.show_info();
        } else {
            std::cerr << "xpm parser failed." << std::endl;
            return -1;
        }
        
    }
    return 0;
}