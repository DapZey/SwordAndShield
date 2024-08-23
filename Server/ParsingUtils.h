//
// Created by benra on 7/16/2024.
//

#ifndef SERVER_PARSINGUTILS_H
#define SERVER_PARSINGUTILS_H
#include "string"
#include "vector"
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
    static std::vector<std::string> splitstringbychar(const std::string& input, const std::string& delimiters) {
        std::vector<std::string> result;
        std::string::size_type start = 0;
        std::string::size_type pos;

        // Iterate until there are no more delimiters found
        while ((pos = input.find_first_of(delimiters, start)) != std::string::npos) {
            // Add the substring before the delimiter
            result.push_back(input.substr(start, pos - start));
            // Update starting position to skip the delimiter
            start = pos + 1;
        }

        // Add the last substring after the last delimiter (or the entire string if no delimiters)
        result.push_back(input.substr(start));

        return result;
    }
};


#endif //SERVER_PARSINGUTILS_H
