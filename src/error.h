#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>


class Error : public std::exception
{
public:
    enum Kind {
        systemError,
        configError,
        otherError
    };

    static Error system(const std::string &);
    static Error config(const std::string &);
    static Error other(const std::string &);


    Error(Kind, const std::string &);

    Kind getKind() const;
    virtual const char* what() const noexcept(true);

private:
    std::string _msg;
    Kind _kind;
};

#endif // ERROR_H
