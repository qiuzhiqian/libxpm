#include <iostream>
#include "xpm.h"

int main(int argc,char** argv) {
    CXpm *xpm = new CXpm();
    if(xpm->parser(argv[1])) {
        xpm->show_info();
        xpm->save("./xpm-save.rgb");
    } else {
        std::cout << "parser error." << std::endl;
    }
    
    return 0;
}