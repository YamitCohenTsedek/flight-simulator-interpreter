
#include "ConnectCommand.h"
#include "Lexer.h"
using namespace std;

// Perform the connect command.
int ConnectCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    // The current index is on the string "connect", promote it by 1.
    ++index;
    // The current index is the host, save it and promote the index
    string host = strings[index];
    string onlyString = "";
    ++index;
    vector<string> portParams;
    while (strings[index] != "\n") {
        // If it is a variable, find its value and convert it to string type.
        if (dataBase->isInSymbolTable(strings[index])) {
            string varValue = to_string(dataBase->getVarValue(strings[index]));
            onlyString = onlyString + varValue;
        }
        onlyString = onlyString + strings[index];
        ++index;
    }
    Lexer lexer = Lexer();
    vector<string> splitedScript = lexer.spiltInfoToStrings(onlyString);
    splitedScript.pop_back();
    // Find the parameters by Shunting Yard algorithm.
    shuntingYard.set(splitedScript);
    int port = shuntingYard.getEvaluation()->calculate();
    // Create the data writer client and its socket.
    DataWriterClient dataWriterClient = DataWriterClient();
    dataWriterClient.createSocket(host, port, dataBase);
    // The current index is on the string '\n', promote it by 1.
    return ++index;
}