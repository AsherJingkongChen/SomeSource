#ifndef CIIS_ERROR_H
#define CIIS_ERROR_H

#include <stdexcept>

class error : public std::exception {
private:
    std::string error_message;
public:
    error(const std::string& emsg) {
        error_message = emsg;
    }
    const char* what() const noexcept {
        return error_message.c_str();
    }
};

#endif //CIIS_ERROR_H
