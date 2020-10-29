
#include "DataBase.h"

DataBase::DataBase() {
	// Add the paths of the simulator from generic_small.xml file.
	pathsOfXml.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
	pathsOfXml.push_back("/instrumentation/altimeter/indicated-altitude-ft");
	pathsOfXml.push_back("/instrumentation/altimeter/pressure-alt-ft");
	pathsOfXml.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
	pathsOfXml.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
	pathsOfXml.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
	pathsOfXml.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
	pathsOfXml.push_back("/instrumentation/encoder/indicated-altitude-ft");
	pathsOfXml.push_back("/instrumentation/encoder/pressure-alt-ft");
	pathsOfXml.push_back("/instrumentation/gps/indicated-altitude-ft");
	pathsOfXml.push_back("/instrumentation/gps/indicated-ground-speed-kt");
	pathsOfXml.push_back("/instrumentation/gps/indicated-vertical-speed");
	pathsOfXml.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
	pathsOfXml.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
	pathsOfXml.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
	pathsOfXml.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
	pathsOfXml.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
	pathsOfXml.push_back("/controls/flight/aileron");
	pathsOfXml.push_back("/controls/flight/elevator");
	pathsOfXml.push_back("/controls/flight/rudder");
	pathsOfXml.push_back("/controls/flight/flaps");
	pathsOfXml.push_back("/controls/engines/current-engine/throttle");
	pathsOfXml.push_back("/engines/engine/rpm");
	pathsOfXml.push_back("/sim/time/warp");
	pathsOfXml.push_back("/controls/switches/magnetos");
	pathsOfXml.push_back("/controls/engines/current-engine/mixture");
	pathsOfXml.push_back("/controls/switches/master-bat");
	pathsOfXml.push_back("/controls/switches/master-alt");
	pathsOfXml.push_back("/controls/switches/master-avionics");
	pathsOfXml.push_back("/sim/model/c172p/brake-parking");
	pathsOfXml.push_back("/controls/engines/engine/primer");
	pathsOfXml.push_back("/controls/switches/starter");
	pathsOfXml.push_back("/engines/active-engine/auto-start");
	pathsOfXml.push_back("/controls/flight/speedbrake");
	pathsOfXml.push_back("/instrumentation/heading-indicator/offset-deg");

	// Initialize a map that maps between the paths of simulator and their double values.
	for (int i = 0; i < pathsOfXml.size(); i++) {
		valuesFromSimulator[pathsOfXml[i]] = 0;
	}
}

/* Methods of the symbol table. */

void DataBase::addVarToSymbolTable(string varName) {
    unique_lock<mutex> lock(locker);
    symbolTable.insert(pair<string, double>(varName, 0));
    lock.unlock();
}

void DataBase::assignInVar(string varName, double value) {
    unique_lock<mutex> lock(locker);
    symbolTable[varName] = value;
    lock.unlock();
}

double DataBase::getVarValue(string varName) {
    map<string, double>::iterator it = symbolTable.find(varName);
    if (it != symbolTable.end()) {
        return (*it).second;
    } else {
        throw ("The var not found.");
    }
}

bool DataBase::isInSymbolTable(string varName) {
    std::map<string, double>::iterator it;
    it = symbolTable.find(varName);
    if (it != symbolTable.end()) {
        return true;}
    return false;

}

/* Methods of bindingToSimulator map. */

void DataBase::addBindingToSimulator(string varName, string path) {
    unique_lock<mutex> lock(locker);
    bindingToSimulator.insert(pair<string, string>(varName, path));
    lock.unlock();
}

bool DataBase::isBoundedToSimulator(string varName) {
    map<string, string>::iterator it = bindingToSimulator.find(varName);
    if (it != bindingToSimulator.end()) {
        return true;
    } else {
        false;
    }
}

string DataBase::getPath(string varName) {
    map<string, string>::iterator it = bindingToSimulator.find(varName);
    if (it != bindingToSimulator.end()) {
        return (*it).second;
    } else {
        throw ("the var not found");
    }
}

/* Methods of valuesFromSimulator map. */

double DataBase::getValueOfSimulatorShort(string varName){
    string path=this->getPath(varName);
    double value=this->getSimulatorValue(path);
    return value;
}

void DataBase::updateSimulatorValue(int index, double value) {
    unique_lock<mutex> lock(locker);
    string path = pathsOfXml[index];
    for (map<string, double>::iterator it = valuesFromSimulator.begin();
         it != valuesFromSimulator.end(); ++it) {
        if ((*it).first == path) {
            (*it).second = value;
        }
    }
    lock.unlock();
}

double DataBase::getSimulatorValue(string path) {
    for (map<string, double>::iterator it = valuesFromSimulator.begin();
         it != valuesFromSimulator.end(); ++it) {
        if ((*it).first == path) {
            return (*it).second;
        }
    }
}

void DataBase::setSimulatorValue(string path, double value) {
    unique_lock<mutex> lock(locker);
    for (map<string, double>::iterator it = valuesFromSimulator.begin();
         it != valuesFromSimulator.end(); ++it) {
        if ((*it).first == path) {
            (*it).second = value;
            return;
        } else {
            valuesFromSimulator.insert(std::pair<string,double>(path,value) );
        }
    }
    lock.unlock();
}

double DataBase::getSimulatorAt(int index) {
    string path = pathsOfXml[index];
    for (map<string, double>::iterator it = valuesFromSimulator.begin();
         it != valuesFromSimulator.end(); ++it) {
        if ((*it).first == path) {
            return (*it).second;
        }
    }
}

bool DataBase::existingPathOfXml(string varName) {
    for(int i=0;i<pathsOfXml.size();++i){
        if(pathsOfXml[i]==varName){
            return true;
        }
    }
    return false;
}

/* Methods of sockets. */

void DataBase::saveServerSockedId(int socketID) {
    unique_lock<mutex> lock(locker);
    serverSocketId = socketID;
    lock.unlock();
}

int DataBase::getServerSockedId() {
    return serverSocketId;
}

void DataBase::saveClientSockedId(int socketID) {
    unique_lock<mutex> lock(locker);
    clientSocketId = socketID;
    lock.unlock();
}

int DataBase::getClientSockedId() {
    return clientSocketId;
}