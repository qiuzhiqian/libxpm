#include <iostream>
#include "../xpm/xpm.h"

int main(int argc,char** argv) {
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " xpm_file_path rgb_file_path" << std::endl;
        return 0;
    }

    auto xpm = std::unique_ptr<xpm::Parser>(new xpm::Parser());
    if(xpm->parse(argv[1])) {
        xpm->show_info();
        xpm->save(argv[2]);
    } else {
        std::cout << "parser error." << std::endl;
    }
    
    return 0;
}