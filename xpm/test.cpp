#include <iostream>
#include <vector>
#include "xpm.h"

int main(int argc,char** argv) {
    CXpm *xpm = new CXpm();

    std::vector<std::string> list{
        "/usr/share/themes/deepin/xfwm4/title-5-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/close-active.xpm",
"/usr/share/pixmaps/openjdk-11.xpm",
"/usr/share/themes/deepin-dark/xfwm4/hide-prelight.xpm",
"/usr/share/themes/deepin-dark/xfwm4/top-right-active.xpm",
"/usr/share/themes/deepin/xfwm4/hide-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/shade-pressed.xpm",
"/usr/share/themes/deepin/xfwm4/maximize-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-5-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/menu-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-4-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/hide-prelight.xpm",
"/usr/share/themes/deepin/xfwm4/close-pressed.xpm",
"/usr/share/themes/deepin-dark/xfwm4/stick-pressed.xpm",
"/usr/share/pixmaps/pstree16.xpm",
"/usr/share/themes/deepin/xfwm4/maximize-pressed.xpm",
"/opt/apps/org.gimp/files/bookworm-env/usr/share/ghostscript/10.00.0/lib/gs_t.xpm",
"/usr/share/themes/deepin/xfwm4/top-right-active.xpm",
"/opt/apps/org.gimp/files/bookworm-env/usr/share/pixmaps/python3.xpm",
"/usr/share/pixmaps/vim-48.xpm",
"/usr/share/pixmaps/vim-16.xpm",
"/usr/share/themes/deepin/xfwm4/title-2-active.xpm",
"/usr/share/themes/deepin/xfwm4/menu-pressed.xpm",
"/usr/share/themes/deepin-dark/xfwm4/hide-pressed.xpm",
"/opt/apps/org.gimp/files/bookworm-env/usr/share/ghostscript/10.00.0/lib/gs_s.xpm",
"/usr/share/themes/deepin/xfwm4/maximize-prelight.xpm",
"/usr/share/ghostscript/9.53.3/lib/gs_m.xpm",
"/usr/share/themes/deepin-dark/xfwm4/maximize-pressed.xpm",
"/usr/share/themes/deepin-dark/xfwm4/close-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/shade-pressed.xpm",
"/usr/share/pixmaps/python3.7.xpm",
"/usr/share/themes/deepin-dark/xfwm4/stick-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-2-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-5-active.xpm",
"/usr/share/ghostscript/9.53.3/lib/gs_t.xpm",
"/usr/share/themes/deepin/xfwm4/title-4-active.xpm",
"/usr/share/themes/deepin/xfwm4/hide-active.xpm",
"/usr/share/themes/deepin/xfwm4/title-4-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/hide-active.xpm",
"/usr/share/pixmaps/vim-32.xpm",
"/usr/share/themes/deepin-dark/xfwm4/shade-active.xpm",
"/opt/apps/org.gimp/files/bookworm-env/usr/share/ghostscript/10.00.0/lib/gs_m.xpm",
"/usr/share/themes/deepin-dark/xfwm4/maximize-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-1-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/title-5-active.xpm",
"/usr/share/icons/hicolor/32x32/apps/vlc.xpm",
"/usr/share/themes/deepin/xfwm4/top-left-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/menu-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/top-right-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/stick-pressed.xpm",
"/usr/share/themes/deepin/xfwm4/maximize-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/title-2-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/top-left-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/top-left-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/menu-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/stick-active.xpm",
"/usr/share/themes/deepin/xfwm4/title-3-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/stick-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/hide-pressed.xpm",
"/usr/share/themes/deepin/xfwm4/title-1-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-2-inactive.xpm",
"/usr/share/ghostscript/9.53.3/lib/gs_l.xpm",
"/usr/share/themes/deepin-dark/xfwm4/maximize-prelight.xpm",
"/usr/share/themes/deepin/xfwm4/title-1-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/close-pressed.xpm",
"/usr/share/themes/deepin-dark/xfwm4/maximize-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/title-3-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/close-prelight.xpm",
"/usr/share/themes/deepin-dark/xfwm4/top-left-active.xpm",
"/usr/share/themes/deepin/xfwm4/stick-active.xpm",
"/usr/share/ghostscript/9.53.3/lib/gs_s.xpm",
"/usr/share/themes/deepin/xfwm4/top-right-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/close-inactive.xpm",
"/opt/apps/org.gimp/files/bookworm-env/usr/share/pixmaps/python3.11.xpm",
"/usr/share/themes/deepin-dark/xfwm4/shade-inactive.xpm",
"/usr/share/themes/deepin/xfwm4/shade-active.xpm",
"/usr/share/icons/hicolor/32x32/apps/vlc-xmas.xpm",
"/usr/share/themes/deepin/xfwm4/close-prelight.xpm",
"/opt/apps/org.gimp/files/bookworm-env/usr/share/ghostscript/10.00.0/lib/gs_l.xpm",
"/usr/share/themes/deepin-dark/xfwm4/menu-active.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-1-active.xpm",
"/usr/share/pixmaps/python2.7.xpm",
"/usr/share/themes/deepin-dark/xfwm4/hide-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-3-active.xpm",
"/usr/share/pixmaps/python2.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-3-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/title-4-active.xpm",
"/usr/share/themes/deepin/xfwm4/shade-inactive.xpm",
"/usr/share/pixmaps/python3.xpm",
"/usr/share/themes/deepin-dark/xfwm4/close-inactive.xpm",
"/usr/share/themes/deepin-dark/xfwm4/menu-pressed.xpm",
"/usr/share/pixmaps/python.xpm",
"/usr/share/pixmaps/pstree32.xpm",
"/usr/share/icons/hicolor/16x16/apps/vlc.xpm",
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