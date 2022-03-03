#include <iostream>
#include "tinyxml.h"

struct Monke {
    int a[10000];
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    TiXmlDocument doc;
    if(!doc.LoadFile("test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cout << " Joe (Biden) Mama \n";
    }

    Monke* randomshit = new Monke;

    return 0;
}
