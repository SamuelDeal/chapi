#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

#include <string>

class NetworkConfig {
public:
    NetworkConfig();

    void load();
    void save();
    void apply();

    bool isDHCP() const;
    std::string getIp() const;
    std::string getNetmask() const;
    std::string getGateway() const;

    void setDHCP(bool value);
    void setIp(const std::string &value);
    void setNetmask(const std::string &value);
    void setGateway(const std::string &value);

protected:
    bool _dhcp;
    std::string _ip;
    std::string _netmask;
    std::string _gateway;
};

#endif // NETWORKCONFIG_H
