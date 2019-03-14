#include "log.hh"

#include <fstream>
#include <iomanip>

bool Log::display = true;
std::shared_ptr<std::ostream> NULLOSTREAM;

void init_logs()
{
    auto v = std::make_shared<std::ofstream>();
    v->open("/dev/null");
    NULLOSTREAM = v;
}

Log::Log(std::string tag)
    : tag_{tag}
    , error_{false}
{}

Log::Log(std::string tag, bool error)
    : tag_{tag}
    , error_{error}
{}

std::ostream& Log::operator<<(std::string message)
{
    if (Log::display || error_)
    {
        std::ostream& s = std::clog << "[";
        if (error_)
            s << "\033[1;31m";
        else
            s << "\033[1;32m";
        s << tag_ << "\033[0m" << std::setw(12 - tag_.length()) << "] "
          << message;
        return s;
    } else
    {
        return *NULLOSTREAM;
    }
}
