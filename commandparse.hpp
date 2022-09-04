#ifndef COMMANDPARSE_HPP
#define COMMANDPARSE_HPP

#include "carwash.hpp"
enum class commandtype
{
    add_stage,
    add_car,
    advance_time,
    show_stage_info,
    show_carwash_info,
    finish,
    unkown_command
};

commandtype hashit(std::string const &instring)
{
    if (instring == "add_stage")
        return commandtype::add_stage;
    if (instring == "add_car")
        return commandtype::add_car;
    if (instring == "advance_time")
        return commandtype::advance_time;
    if (instring == "show_stage_info")
        return commandtype::show_stage_info;
    if (instring == "show_carwash_info")
        return commandtype::show_carwash_info;
    if (instring == "finish")
        return commandtype::finish;
    else
        return commandtype::unkown_command;
}

#endif