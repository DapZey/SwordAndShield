//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PARSINGUTILS_H
#define SERVER_PARSINGUTILS_H
#include "string"
class ParsingUtils {
public:
    static bool containsChar(const std::string &str, char ch) {
        // Use the find method to check if the character is in the string
        return str.find(ch) != std::string::npos;
    }
};


#endif //SERVER_PARSINGUTILS_H
