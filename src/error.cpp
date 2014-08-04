#include "error.h"

#include <errno.h>
#include <string.h>

Error::Error(Kind kind, const std::string &what) {
    _msg = what;
    _kind = kind;
}

const char* Error::what() const noexcept(true) {
    return _msg.c_str();
}

Error::Kind Error::getKind() const {
    return _kind;
}


Error Error::system(const std::string &str) {
    int err = errno;
    return Error(Error::systemError, str + ":" + strerror(err));
}

Error Error::config(const std::string &str) {
    return Error(Error::configError, str);
}

Error Error::other(const std::string &str) {
    return Error(Error::otherError, str);
}
