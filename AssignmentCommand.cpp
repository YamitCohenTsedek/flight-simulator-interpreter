
#include "AssignmentCommand.h"

// Perform the assignment command.
int AssignmentCommand::doCommand(vector<string> strings, int index, DataBase* dataBase) {
    // The current index is on the string '=', thus the name of the variable is in index-1.
    string varName = strings[index - 1];
    // The current index is on the string '=', promote it by 1.
    ++index;
    vector<string> assignmentExp;
    double result;
    // If we want to change the values of the simulator (by a variable binding):
    if (dataBase->isBoundedToSimulator(varName)) {
        // Find the path of the variable among the paths of the simulator.
        string path = dataBase->getPath(varName);
        double result = calculateDouble(strings, index, dataBase);
        dataBase->setSimulatorValue(path, result);
        // If it is an existing path of the simulator, write to the socket to set the simulator's values.
        if (dataBase->existingPathOfXml(path)) {
            // Get the ID of the control client socket from the data base.
            int clientSocketID = dataBase->getClientSockedId();
            // Assign the value in the path of the simulator by writing to the socket.
            sendMesseage(clientSocketID, result, path);
        }
        // Promote the index by 1.
        return ++index;
    }

    /* Assignment in a variable from the symbol table. */
    else if (dataBase->isInSymbolTable(varName)) {
        double result = calculateDouble(strings, index, dataBase);
        dataBase->assignInVar(varName, result);
    }

    // The current index is on the string '\n', promote it by 1.
    return ++index;
}

// Send a message to the simulator through a socket to set its values. 
void AssignmentCommand::sendMesseage(int sockfd, double value, string path) {
    // Create the message for setting the simulator's values.
    string message = "set " + path + " " + to_string(value) + " \r\n";
    ssize_t n = write(sockfd, message.c_str(), message.length());
    if (n < 0) {
        perror("ERROR writing to socket.");
        exit(1);
    }
}

// Calculate the value that should be assigned to the variable.
double AssignmentCommand::calculateDouble(vector<string>& strings, int& index, DataBase* dataBase) {
    string onlyString = "";
    while (strings[index] != "\n") {
        // If the variable is in the symbol table, find its value and convert it to a string type.
        if (dataBase->isInSymbolTable(strings[index])) {
            string varValue = to_string(dataBase->getVarValue(strings[index]));
            strings[index] = varValue;
        }
        // If the variable is in the map of the simulator's bindings, find its value and convert it to a string type.
        if (dataBase->isBoundedToSimulator(strings[index])) {
            string path = dataBase->getPath(strings[index]);
            string varValue = to_string(dataBase->getSimulatorValue(path));
            strings[index] = varValue;
        }
        onlyString = onlyString + strings[index];
        // Promote the index by 1.
        ++index;
    }
    Lexer lexer = Lexer();
    vector<string> splitedScript = lexer.spiltInfoToStrings(onlyString);
    splitedScript.pop_back();
    // Calculate the value of the expression using the Shunting Yard algorithm.
    shuntingYard.set(splitedScript);
    return shuntingYard.getEvaluation()->calculate();
}