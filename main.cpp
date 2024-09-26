#include <iostream>
#include <fstream>
#include <string>

#include "scanner.h"
#include "parser.h"
#include "visitor.h"

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect launch arguments. Please type: " << argv[0] << " <input_file_name>" << "\n";
        exit(1);
    }

    ifstream infile(argv[1]);
    if (!infile.is_open())
    {
        cout << "File" << argv[1] << " could not be opened." << "\n";
        exit(1);
    }

    string input, line;

    while (getline(infile, line))
    {
        input += line + '\n';
    }
    infile.close();

    Scanner scanner(input.c_str());

    string input_copy = input;

    Scanner scanner_test(input_copy.c_str());

    // test_scanner(&scanner_test);

    cout << "Scanning successful." << "\n";
    cout << "Starting parsing process." << "\n";

    Parser parser(&scanner);
    try
    {
        Program *program = parser.parseProgram();
        cout << "Parsing successful" << "\n";
        cout << "Starting visitor process." << "\n";

        // Creating visitors
        PrintVisitor printVisitor;
        EVALVisitor evalVisitor;

        cout << "Print Visitor:" << "\n";
        printVisitor.imprimir(program);

        cout << "\n";

        cout << "Execute Visitor:" << "\n";
        evalVisitor.ejecutar(program);

        delete program;
    }
    catch (const exception &e)
    {
        cout << "Execution error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}