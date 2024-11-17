#include "lexer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <cctype> // For isdigit
#include <stdexcept> // For std::invalid_argument

typedef uint32_t i32;

using namespace std;

// Function prototypes
vector<i32> compileToInstructions(strings s);
bool isInteger(const string& s);
i32 maptoNumber(const string& s);

int main(int argc, char *argv[]) {
    // Check for input errors
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <sasm-filename> [output-filename]" << endl;
        return 1;
    }

    string outputFileName = "out.bin";
    if (argc > 2) {
        outputFileName = argv[2];
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cout << "Error: Could not open [" << argv[1] << "]" << endl;
        return 1;
    }

    string line;
    string contents;
    while (getline(infile, line)) {
        contents += line + "\n";
    }
    infile.close();

    // Parse the file
    Lexer lexer;
    strings lexemes = lexer.lex(contents);

    // Compile to binary
    vector<i32> instructions = compileToInstructions(lexemes);

    // Write to binary file
    ofstream ofile(outputFileName, ios::binary);
    if (!ofile.is_open()) {
        cout << "Error: Could not open output file [" << outputFileName << "]" << endl;
        return 1;
    }

    for (i32 instruction : instructions) {
        ofile.write(reinterpret_cast<char*>(&instruction), sizeof(i32));
    }
    ofile.close();

    cout << "Compilation successful. Output written to " << outputFileName << endl;
    return 0;
}

// Converts tokens to binary instructions
vector<i32> compileToInstructions(strings s) {
    vector<i32> instructions;

    for (const string& token : s) {
        if (isInteger(token)) {
            try {
                instructions.push_back(stoi(token));
            } catch (const std::invalid_argument&) {
                cout << "Error: Invalid integer token: " << token << endl;
            } catch (const std::out_of_range&) {
                cout << "Error: Integer out of range: " << token << endl;
            }
        } else {
            i32 instruction = maptoNumber(token);
            if (instruction != static_cast<i32>(-1)) {
                instructions.push_back(instruction);
            } else {
                cout << "Error: Invalid instruction: " << token << endl;
            }
        }
    }

    return instructions;
}

// Checks if a string represents an integer
bool isInteger(const string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '+' || s[0] == '-') start = 1;
    for (size_t i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

// Maps string tokens to binary instructions
i32 maptoNumber(const string& s) {
    if (s == "+") return 0x40000001;
    if (s == "-") return 0x40000002;
    if (s == "*") return 0x40000003;
    if (s == "/") return 0x40000004;
    return static_cast<i32>(-1); // Invalid
}
