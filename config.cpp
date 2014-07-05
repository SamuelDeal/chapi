#include "config.h"

#include <fstream>
#include <sstream>

#include "const.h"

Config::Config(){
}

void Config::load() {
    std::ifstream cfgFile(CONFIG_FILE);
    std::string line;
    while(std::getline(cfgFile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if(!std::getline(is_line, key, '=')) {
            continue;
        }
        std::string value;
        if(!std::getline(is_line, value)) {
            continue;
        }
        _kvs[key] = value;
    }
}

void Config::save() {
    std::ofstream cfgFile(CONFIG_FILE, std::ios_base::out|std::ios_base::trunc);
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
