#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "token.cpp"

class Scanner {
  private:
    string T_GRAPH;

    std::ifstream file;

    void set(Token *token, string token_class, string lexeme) {
      token->token_class = token_class;
      token->lexeme = lexeme;
    }

  public:
    Scanner(string filename) {
      this->T_GRAPH = "graph";

      this->file.open(filename);
    }

    ~Scanner() {
      this->file.close();
    }

    Token next() {
      Token token;
      string t;
      this->file >> t;

      if (t == T_GRAPH) {
        set(&token, "keyword", "graph");
      } else if (std::regex_match (t, std::regex("[->]") )) {
        set(&token, "directed_edge", t);
      } else if (std::regex_match (t, std::regex("[-]{2}") )) {
        set(&token, "undirected_edge", t);
      } else if (std::regex_match (t, std::regex("[{]") )) {
        set(&token, "left_brace", t);
      } else if (std::regex_match (t, std::regex("[}]") )) {
        set(&token, "right_brace", t);
      // } else if () { // check end of file, in case there is no end keyword
        // return EOF
      } else {
        set(&token, "identifier", t);
      }

      return token;
    }
};
