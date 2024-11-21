#include <iostream>
#include <fstream>
#include <sstream>

#include "Log.h"
#include "Lexer.h"
#include "Parser.h"
#include "OBJgen/Gen.h"

static std::string GetFileContents(std::string filePath) {
	std::ifstream file(filePath);

	std::stringstream buf;
	buf << file.rdbuf();

	return buf.str();
}

static void Usage(std::string program) {
	INFO("usage: {0} [ FLAGS ]", program);
	std::cout << "FLAGS:" << std::endl;
	std::cout << "   -f, --file [INPUT]:    takes in a source for the assembler to read" << std::endl;
	std::cout << "   -o, --out [OUTPUT]:    specifies output file name, default: [INPUT].obj" << std::endl;
	std::cout << "   -h, --help:            displays this message" << std::endl;
}

static std::string Shift(int &argc, char ***argv) {
	char *last = **argv;
	*argv += 1;
	argc -= 1;

	return std::string(last);
}

using namespace ASM32;

int main(int argc, char **argv) {
	ASM32::Log::Init();

	std::string program = Shift(argc, &argv);
	if (argc < 1) {
		Usage(program);
		ERROR("no arguments supplied!");
		exit(1);
	}

	while (argc > 0) {
		std::string arg = Shift(argc, &argv);

		if (arg == "-f" || arg == "--file") {
			if (argc < 1) {
				ERROR("no input file provided!");
				exit(1);
			}

			std::string input = Shift(argc, &argv);
			std::string contents = GetFileContents(input);
			Lexer lexer(contents);
			Parser parser(lexer);
			parser.Parse();
			
			OBJGen gen(parser.GetExprs(), "output.obj");
		} else if (arg == "-o" || arg == "--out") {

		} else if (arg == "-h" || arg == "--help") {
			Usage(program);
			exit(0);
		} else {
			Usage(program);
			ERROR("invalid flag `{0}`", arg);
			exit(1);
		}
	}

	return 0;
}