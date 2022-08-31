#include "carwash.hpp"
enum string_code
{
    add_stage,
    add_car,
    advance_time,
    show_stage_info,
    show_carwash_info,
    finish
};

string_code hashit(std::string const &instring)
{
    if (instring == "add_stage")
        return add_stage;
    if (instring == "add_car")
        return add_car;
    if (instring == "advance_time")
        return advance_time;
    if (instring == "show_stage_info")
        return show_stage_info;
    if (instring == "show_carwash_info")
        return show_carwash_info;
    if (instring == "finish")
        return finish;
}