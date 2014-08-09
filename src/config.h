#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
public:
    Config();

    void clear();
    void load();
    void save();
    bool isEmpty() const;
    bool isSet(const std::string&) const;
    std::string get(const std::string &key, const std::string &defaultVal = "");
    void set(const std::string &key, const std::string &value);

private:
    std::map<std::string, std::string> _kvs;
};

#endif // CONFIG_H
