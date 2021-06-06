#include <iostream>
#include <string>
std::string replace(std::string s){
    std::string temp;
    temp.reserve(s.size());
    int l = s.size() -1;
    int curr = 0;
    while(curr < l){
        if(s[curr] !='\\') {
            temp.push_back(s[curr]); 
        }else {
            curr++;
            switch(s[curr]){
                case 'b': temp.push_back('\b'); break;
                case 't': temp.push_back('\t'); break;
                case 'n': temp.push_back('\n'); break;
                case 'f': temp.push_back('\f'); break;
                default : temp.push_back(s[curr]); break;
            } 
        }
        curr++;
    }
    if(s[curr] !='\\')
        temp.push_back(s[curr]);
    return temp;
}

int main(int argc, char** argv){
    std::string s = "\\0\\1\\2\\\\0\\\\1\\\\2\\t\\f\\b\\n\\r\\a\\b\\c\\d\\e\\f\\g";
;
    std::cout << replace(s) << std::endl;
}