#include <iostream>
#include "Protocol.h"
int main() {
    Protocol p;
    std::string s ="";
    while (s == ""){
        std::cin>>s;
        p.Run();
    }
    return 0;
}
