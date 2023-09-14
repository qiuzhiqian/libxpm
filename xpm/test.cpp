#include <iostream>
#include <vector>
#include "xpm.h"

int main(int argc,char** argv) {
    if(argc != 2) {
        std::cout << argv[0] << " test_xpm_dir" << std::endl;
        return -1;
    }
    std::vector<std::string> list{
        "logo_1.xpm",
        "logo_2.xpm",
        "logo_3.xpm",
        "logo_4.xpm",
        "logo_5.xpm",
        "logo_6.xpm",
        "logo_7.xpm",
        "logo_8.xpm",
        "logo_9.xpm",
        "logo_10.xpm",
    };

    for(auto i:list) {
        std::cout << "parser: " << i<< std::endl;
        xpm::Parser xpm;
        std::string path = std::string(argv[1]) + "/" + i;
        if(xpm.parser(path.c_str())) {
            xpm.show_info();
        } else {
            std::cerr << "xpm parser failed." << std::endl;
            return -1;
        }
        
    }
    return 0;
}