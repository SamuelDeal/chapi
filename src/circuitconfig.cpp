#include "circuitconfig.h"

#include <fstream>
#include <sstream>

#include "const.h"
#include "stringutils.h"
#include "srinfo.h"
#include "error.h"

CircuitConfig::CircuitConfig() {
    _current = NULL;
    load();
}

CircuitConfig::~CircuitConfig() {
    for(auto i = _inputs.begin(); i != _inputs.end(); i++){
        delete(*i);
    }
    for(auto i = _outputs.begin(); i != _outputs.end(); i++){
        delete(*i);
    }
}

void CircuitConfig::load() {
    std::ifstream cfgFile("home/sam/test_circuit"); //CONFIG_FOLDER "/" CIRCUIT_FILE);
    std::string line;
    while(std::getline(cfgFile, line)) {
        line = trim(line);
        if((line.length() == 0) || (line[0] == '#')){
            continue;
        }
        if(line == "[INPUT SR]"){
            validate();
            _current = new SRInfo();
            _inputs.push_back(_current);
            continue;
        }
        else if(line == "[OUTPUT SR]") {
            validate();
            _current = new SRInfo();
            _outputs.push_back(_current);
            continue;
        }

        if(_current == NULL){
            throw Error::config("invalid circuit config");
        }

        std::istringstream lineStream(line);
        std::string key;
        if(!std::getline(lineStream, key, '=')) {
            throw Error::config("invalid circuit config");
        }
        unsigned int value;
        lineStream >> value;
        if(trim(key) == "latch"){
            _current->latchPin = value;
        }
        if(trim(key) == "clock"){
            _current->clockPin = value;
        }
        if(trim(key) == "data"){
            _current->dataPin = value;
        }
        if(trim(key) == "size"){
            _current->size = value;
        }
        else{
            unsigned int index = 0;
            std::istringstream(key) >> index;
            if(index > 1024){
                throw Error::config("invalid circuit config");
            }
            if(_current->pins.size() < index){
                _current->pins.resize(index, -1);
            }
            _current->pins[index] = value;
        }
    }
    validate();
}

void CircuitConfig::validate() {
    if(_current == NULL){
        return;
    }
    if((_current->dataPin == -1) || (_current->clockPin == -1) || (_current->latchPin == -1) || (_current->size == -1)) {
        throw Error::config("invalid circuit config: SR not fully defined");
    }
}

std::list<SRInfo*> CircuitConfig::getInputs() const {
    return _inputs;
}

std::list<SRInfo*> CircuitConfig::getOutputs() const {
    return _outputs;
}
