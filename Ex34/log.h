#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <exception>
#include "timing.h"

class Log
{
public:
    virtual void addEvt(
        const TIME::Date &d,
        const TIME::Horaire &h,
        const std::string &s) = 0;

    virtual void displayLog(std::ostream &f) const = 0;

    virtual ~Log() = default;
};

// 自定义异常
class LogError : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Log error: event date/time earlier than last event";
    }
};

#endif