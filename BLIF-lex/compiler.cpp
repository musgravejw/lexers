#include <iostream>
#include "Parser.cpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Usage: compiler [filename]" << "\n";
		return 1;
	}

	Parser *parser = new Parser(argv[1]);
  parser->start();

	return 0;
}
