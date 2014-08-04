#include "config.h"

#include <fstream>
#include <sstream>

#include "const.h"
#include "stringutils.h"

Config::Config(){
    _isSet = false;
    load();
}

void Config::load() {
    std::ifstream cfgFile(CONFIG_FOLDER "/" CONFIG_FILE);
    std::string line;
    while(std::getline(cfgFile, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if(!std::getline(lineStream, key, '=')) {
            continue;
        }
        std::string value;
        if(!std::getline(lineStream, value)) {
            continue;
        }
        _kvs[trim(key)] = trim(value);
    }
}

bool Config::isSet() const {
    return _isSet;
}

void Config::save() {
    std::ofstream cfgFile(CONFIG_FOLDER "/" CONFIG_FILE, std::ios_base::out|std::ios_base::trunc);
    std::string line;
    for(auto it = _kvs.begin(); it != _kvs.end(); it++){
        cfgFile << it->first << "=" << it->second << "\n";
    }
}

std::string Config::get(const std::string &key, const std::string &defaultVal) {
    auto it = _kvs.find(key);
    if(it == _kvs.end()){
        return defaultVal;
    }
    else {
        return it->second;
    }
}

void Config::set(const std::string &key, const std::string &value) {
    _kvs[key] = value;
}
