#ifndef LOG_H_
#define LOG_H_

#include <string>

namespace log {
    /* setup functions */
    void start();
    void end();

    /* logging commands */
    void msg(std::string const& m);
    void error(std::string const& m);
}

#endif
