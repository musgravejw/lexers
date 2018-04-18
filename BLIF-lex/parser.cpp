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

		bool model() {
			if (check("keyword", "model")) {
				next();
				if (is_identifier()) {

					// add token to symbol table

					next();
					return true;
				}
			}

			return false;
		}

		bool inputs() {
			if (check("keyword", "inputs")) {
				next();
				// list of identifiers
				while(is_identifier()) {
					next();
				}

				return true;
			}

			return false;
		}

		bool latch() {
			if (check("keyword", "latch")) {
				next();

				// list of identifiers
				while(is_identifier()) {
					next();
				}

				return true;
			}

			return false;
		}

		bool outputs() {
			if (check("keyword", "outputs")) {
				next();

				// list of identifiers
				while(is_identifier()) {
					next();
				}

				return true;
			}

			return false;
		}

		bool gates() {
			int n = 0;
			string *inputs = new string[20];
			string *values = new string[20];

			if (check("keyword", "names")) {
				// n number of named inputs
				next();

				do {
					inputs[n++] = this->token.lexeme;

					next();
				} while(is_identifier());

				// final one is the output identifier

				// elements in a row are AND-ed together
				// all rows are OR-ed

				while (!check_token_class("keyword")) {
					if (check_token_class("gate-input")) {
						// do something with the input

						for (int i = 0; i < n; i++) {
							values[i] = this->token.lexeme[i];
						}

						next();
						if (check_token_class("gate-output")) {
							// output value is this->token.lexeme;

							next();
						} else {
							return parse_error("gate output");
						}
					} else {
						return parse_error("gate input");
					}
				}

				return true;
			}

			return false;
		}

		bool end() {
			if (check("keyword", "end")) {
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

			if (model()) {
				if (inputs()) {
					if (outputs()) {
						if (!latch()) parse_error(".latch");

						while (!gates()) {
							latch();
						}

						if (!gates()) parse_error(".gates");

						while(!end()) {
							gates();

							if (end()) {
								cout << "Parse completed successfully" << "\n";
								return;
							}
						}
					} else {
						parse_error(".outputs");
					}
				} else {
					parse_error(".inputs");
				}
			} else {
				parse_error(".model");
			}
		}
};
