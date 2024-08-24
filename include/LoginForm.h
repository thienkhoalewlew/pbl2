#pragma once
#include "../include/User.h"
#include <string>

class LoginForm {
public:
    static std::string login(const std::string& username, const std::string& password);
};