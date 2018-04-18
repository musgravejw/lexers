#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "scanner.cpp"

class Parser {
	private:
		Scanner *scanner;
		Token token;

	  void next() {
			// check for end of file token
			this->token = this->scanner->next();
			cout << this->token.lexeme << " " << this->token.token_class << "\n";
		}

		bool check(string token_class, string lexeme) {
			return (this->token.token_class == token_class) && (this->token.lexeme == lexeme);
		}

		bool check_token_class(string token_class) {
			return this->token.token_class == token_class;
		}

		bool is_identifier() {
			return check_token_class("identifier");
		}

		bool parse_error(string message) {
			cout << "Syntax error:  missing keyword or identifier " << message << "\n";
			return false;
		}

		void error(string message) {
			cout << message << "\n";
		}

		bool type_error(string message) {
			cout << message;
			return false;
		}

		bool graph() {
			if (check("keyword", "graph")) {
				next();
				if (is_identifier()) {

					// add token to symbol table
					next();

					if (check_token_class("left_brace")) {
						next();
						return true;
					}
				}
			}

			return false;
		}

		bool edge() {
			if (is_identifier()) {
				next();
				if (check_token_class("directed_edge") || check_token_class("undirected_edge")) {
					next();
					if (is_identifier()) {
						next();
						return true;
					}
				}
			}

			return false;
		}

		bool end() {
			if (check_token_class("right_brace")) {
				return true;
			} else {
				return false;
			}
		}

	public:
		Parser(string filename) {
			this->scanner = new Scanner(filename);
		}

		void start() {
			next();

			if (graph()) {
				while (edge()) {
					;
				}

				if (end()) {
					cout << "Parse completed successfully" << "\n";
					return;
				}
			}
		}
};
