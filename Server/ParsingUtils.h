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
    static std::string extractSubstringBetweenDelimiters(const std::string &str, char delimiter) {
        size_t startPos = str.find(delimiter);
        if (startPos == std::string::npos) {
            return "";  // Delimiter not found
        }

        size_t endPos = str.find(delimiter, startPos + 1);
        if (endPos == std::string::npos) {
            return "";  // Second occurrence of the delimiter not found
        }

        // Extract the substring between the delimiters
        return str.substr(startPos +1, endPos - startPos -1);
    }
};


#endif //SERVER_PARSINGUTILS_H
