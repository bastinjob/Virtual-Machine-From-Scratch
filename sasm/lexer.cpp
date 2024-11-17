#include "lexer.h"
#include <cctype> // For isspace
#include <algorithm> // For std::remove_if

// Helper function to check if a character is whitespace
bool Lexer::my_isspace(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

// Helper function to check if a character is special
bool Lexer::isspecial(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == ';');
}

// Helper function to check if a character is a grouping symbol
bool Lexer::isgroup(char c) {
    return (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']');
}

// Tokenize a string into a vector of strings
strings Lexer::lex(std::string s) {
    strings tokens;
    std::string current;
    State state = START;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        switch (state) {
            case START:
                if (my_isspace(c)) {
                    state = SKIP;
                } else if (c == '/' && i + 1 < s.size() && s[i + 1] == '/') { 
                    // Start of a comment
                    state = COMMENT;
                    ++i; // Skip the next '/'
                } else if (isspecial(c)) {
                    tokens.push_back(std::string(1, c));
                } else if (isgroup(c)) {
                    tokens.push_back(std::string(1, c));
                } else {
                    current += c;
                    state = READCHAR;
                }
                break;

            case READCHAR:
                if (my_isspace(c) || isspecial(c) || isgroup(c)) {
                    if (!current.empty()) {
                        if (current == "DUMP" || current == "END") {
                            tokens.push_back(current); // Handle keywords
                        } else {
                            tokens.push_back(current);
                        }
                        current.clear();
                    }
                    state = START;
                    --i; // Reprocess this character in the START state
                } else {
                    current += c;
                }
                break;

            case COMMENT:
                if (c == '\n') {
                    state = START; // End of the comment, resume normal parsing
                }
                break;

            case SKIP:
                if (!my_isspace(c)) {
                    state = START;
                    --i; // Reprocess this character in the START state
                }
                break;

            default:
                break;
        }
    }

    // Add any remaining token
    if (!current.empty()) {
        if (current == "DUMP" || current == "END") {
            tokens.push_back(current); // Handle keywords
        } else {
            tokens.push_back(current);
        }
    }

    return tokens;
}
