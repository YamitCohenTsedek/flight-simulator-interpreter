
#ifndef FLIGHT_SIMULATOR_INTERPRETER_DATABASE_H
#define FLIGHT_SIMULATOR_INTERPRETER_DATABASE_H
#include <map>
#include <string.h>
#include <iostream>
#include <vector>
#include <mutex>
using namespace std;

class DataBase {
private:
    // The symbol table maps local variables to their double values (not including bounded variables).
    map<string, double> symbolTable;
    // bindingToSimulator maps bounded variables to their paths in the simulator.
    map<string, string> bindingToSimulator;
    // valuesFromSimulator maps paths of simulator to their double values.
    map<string, double> valuesFromSimulator;
    // pathsOfXml is a list of all the paths of the simulator from generic_small.xml file.
    vector<string> pathsOfXml;
    mutex locker;
    // The IDs of the server socket and the client socket.
    int serverSocketId;
    int clientSocketId;
	// A boolean variable which indicates whether the thread should stop.
    bool stopTheThread = false;

public:
    DataBase();

	/* Methods of the symbol table. */

	void addVarToSymbolTable(string varName);
    void assignInVar(string varName, double value);
    double getVarValue(string varName);
    bool isInSymbolTable(string varName);

    /* Methods of bindingToSimulator map. */

    void addBindingToSimulator(string varName, string path);
    bool isBoundedToSimulator(string varName);
    string getPath(string varName);

    /* Methods of valuesFromSimulator map. */

	double getSimulatorValue(string path);
    void updateSimulatorValue(int index, double value);
    double getValueOfSimulatorShort(string varName);
    bool existingPathOfXml(string varName);
    void setSimulatorValue(string path, double value);
    double getSimulatorAt(int index);

    /* Methods of sockets. */

    void saveServerSockedId(int socketID);
    int getServerSockedId();
    void saveClientSockedId(int socketID);
    int getClientSockedId();

    bool isThreadShouldStop() {
        return stopTheThread;
    }

    bool stopThread() {
        stopTheThread = true;
    }
};

#endif // FLIGHT_SIMULATOR_INTERPRETER_DATABASE_H