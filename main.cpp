
#include "Lexer.h"
#include "Parser.h"
#include <vector>
#include <string.h>
#include "ShuntingYard.h"
#include "Exit.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::invalid_argument("Error: no script file provided as an argument to main.");
    }
    // The lexer is in charge of reading the script and split it into strings.
    Lexer l = Lexer();
    vector<string> s = l.readFromFile(argv[1]);
    // The parser is in charge of running over the strings and executing the corresponding commands.
    Parser parser =  Parser();
    /*
     * The database contains a lot of data that is required for the whole program, such as the symbol table,
     * the paths of the simulator and more.
     */
    DataBase* dataBase = new DataBase();
    parser.interpretScript(s, dataBase);
    // Close all the sockets & threads.
    Exit exit = Exit();
    // Free the allocated memory of the database.
    delete dataBase;
    return 0;
}
