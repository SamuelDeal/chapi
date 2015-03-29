#include "config.h"

#include <fstream>
#include <sstream>

#include "const.h"
#include "stringutils.h"
#include "error.h"

Config::Config(){
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

bool Config::isEmpty() const {
    return _kvs.empty();
}

bool Config::isSet(const std::string &key) const{
    return _kvs.find(key) != _kvs.end();
}

void Config::clear() {
    _kvs.clear();
}

void Config::save() {
    if(system("/bin/mount -o rw,remount " CONFIG_FOLDER) != 0){
        throw Error::system("mount failed");
    }
    { //ensure files are saved before remount
        std::ofstream cfgFile(CONFIG_FOLDER "/" CONFIG_FILE, std::ios_base::out|std::ios_base::trunc);
        std::string line;
        for(auto it = _kvs.begin(); it != _kvs.end(); it++){
            cfgFile << it->first << "=" << it->second << "\n";
        }
        cfgFile << std::endl;

        std::ofstream netFile(CONFIG_FOLDER "/interfaces", std::ios_base::out|std::ios_base::trunc);
        netFile << "auto lo\niface lo inet loopback\n\nallow-hotplug eth0\n";
        if(_kvs["dhcp"] == "1"){
            netFile << "iface eth0 inet dhcp\n";
        }
        else {
            netFile << "iface eth0 inet static\n";
            netFile << "  address " << _kvs["ip"] << "\n";
            if(_kvs.find("mask") != _kvs.end()){
                netFile << "  netmask " << _kvs["mask"] << "\n";
            }
            if(_kvs.find("gateway") != _kvs.end()){
                netFile << "  gateway " << _kvs["gateway"] << "\n";
            }
        }
        netFile << std::endl;
        if(_kvs.find("ip") != _kvs.end()) {
            std::ofstream fallbackFile(CONFIG_FOLDER "/fallback_ip.conf", std::ios_base::out|std::ios_base::trunc);
            fallbackFile << _kvs["ip"] << std::endl;
        }
        system("/bin/sync");
    }
    if(system("/bin/mount -o ro,remount " CONFIG_FOLDER) != 0){
        throw Error::system("mount failed");
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
