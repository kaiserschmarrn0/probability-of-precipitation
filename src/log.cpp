#include "log.h"
#include <iostream>

void log::start() {}
void log::end() {}

void log::msg(std::string const& m) {
    std::cerr << m << std::endl;
}
void log::error(std::string const& m) {
    std::cerr << "[!] E: " << m << std::endl;
}
