#include <iostream>
#include <vector>
#include "xpm.h"

int main(int/* argc*/,char**/* argv*/) {
    std::vector<std::string> list{
        "../res/logo_1.xpm",
        "../res/logo_2.xpm",
        "../res/logo_3.xpm",
        "../res/logo_4.xpm",
        "../res/logo_5.xpm",
        "../res/logo_6.xpm",
        "../res/logo_7.xpm",
        "../res/logo_8.xpm",
        "../res/logo_9.xpm",
        "../res/logo_10.xpm",
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