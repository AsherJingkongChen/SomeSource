#ifndef CIIS_ERROR_H
#define CIIS_ERROR_H

#include <stdexcept>
#include <string>

class error : public std::exception {
private:
    std::string error_message;
public:
    error(const char* emsg)
    {
        error_message = emsg;
    }

    const char* what() const noexcept override {
    return error_message.c_str(); }
};

#endif //CIIS_ERROR_H
