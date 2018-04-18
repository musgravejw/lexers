#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "token.cpp"

class Scanner {
  private:
    string T_MODEL;
    string T_INPUT;
    string T_LATCH;
    string T_OUTPUT;
    string T_NAMES;
    string T_GATES;
    string T_END;
    std::ifstream file;

    void set(Token *token, string token_class, string lexeme) {
      token->token_class = token_class;
      token->lexeme = lexeme;
    }

  public:
    Scanner(string filename) {
      this->T_MODEL = ".model";
      this->T_INPUT = ".inputs";
      this->T_LATCH = ".latch";
      this->T_OUTPUT = ".outputs";
      this->T_NAMES = ".names";
      this->T_GATES = ".gates";
      this->T_END = ".end";

      this->file.open(filename);
    }

    ~Scanner() {
      this->file.close();
    }

    Token next() {
      Token token;
      string t;
      this->file >> t;

      if (t == T_MODEL) {
        set(&token, "keyword", "model");
      } else if (t == T_INPUT) {
        set(&token, "keyword", "inputs");
      } else if (t == T_LATCH) {
        set(&token, "keyword", "latch");
      } else if (t == T_OUTPUT) {
        set(&token, "keyword", "outputs");
      } else if (t == T_NAMES) {
        set(&token, "keyword", "names");
      } else if (t == T_GATES) {
        set(&token, "keyword", "gates");
      } else if (t == T_END) {
        set(&token, "keyword", "end");
      } else if (std::regex_match (t, std::regex("[01]{1}") )) {
        set(&token, "gate-output", t);
      } else if (std::regex_match (t, std::regex("[01-]{1,}") )) {
        set(&token, "gate-input", t);
      // } else if () { // check end of file, in case there is no end keyword
        // return EOF
      } else {
        set(&token, "identifier", t);
      }

      return token;
    }
};
