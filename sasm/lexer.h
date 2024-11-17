#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

typedef uint8_t byte;                     // Define a byte as 8-bit unsigned integer
typedef std::vector<std::string> strings; // Alias for a vector of strings

// Enum for Lexer states
enum State : byte {
    START,
    READCHAR,
    READBLOCK,
    SKIP,
    DUMP,
    COMMENT,
    END
};

// Lexer class definition
class Lexer {
private:
    // Helper functions
    bool my_isspace(char c);      // Checks if a character is whitespace
    bool isspecial(char c);       // Checks if a character is a special symbol
    bool isgroup(char c);         // Checks if a character is a grouping symbol (e.g., '(', ')')
    
    // Private members
    char end_char;                // Ending character for blocks or groups
    char beg_char;                // Beginning character for blocks or groups

public:
    // Public interface
    strings lex(std::string s);   // Lexical analysis function to tokenize a string
};

#endif // LEXER_H
