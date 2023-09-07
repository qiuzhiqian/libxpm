#include "utils.h"

std::string& trim(std::string &s) {
    if (!s.empty()) {
        s.erase(0,s.find_first_not_of(" "));
        s.erase(0,s.find_first_not_of("\t"));
    	s.erase(s.find_last_not_of(" ") + 1);
        s.erase(s.find_last_not_of("\t") + 1);
    }
    return s;
}

std::vector<std::string> split(std::string str,std::string pattern) {
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
    for(int i=0; i<size; i++) {
        pos=str.find(pattern,i);
        if(pos < size) {
            std::string s=str. substr(i,pos-i);
            if(!s.empty()) {
                result.push_back(s);
            }
            i=pos+pattern.size() - 1;
        }
    }
    return result;
}