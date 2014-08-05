#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>


class Error : public std::exception
{
public:
    enum Kind {
        noneError,
        systemError,
        configError,
        otherError,
        unknownError
    };

    static Error system(const std::string &);
    static Error config(const std::string &);
    static Error other(const std::string &);
    static Error unknown(const std::string &);

    Error(Kind = noneError, const std::string& = "");

    Kind getKind() const;
    virtual const char* what() const noexcept(true);

private:
    std::string _msg;
    Kind _kind;
};

#endif // ERROR_H
