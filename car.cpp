#include "car.hpp"


void Car::set_info(int identification, int l_coefficient)
{
    id = identification;
    luxury_coefficient = l_coefficient;
}
void Car::display_car()
{
    std::cout << "Car ID: " << id << std::endl;
    std::cout << "Luxury coefficient: " << luxury_coefficient << std::endl;
}
void Car::set_time_needed_for_cleaning(int worker_coefficient)
{
    time_left = luxury_coefficient * worker_coefficient;
}
int Car::get_time_left()
{
    return time_left;
}
bool Car::is_washing_done()
{
    return (time_left == 0);
}
void Car::update_time_left()
{
    if (time_left != 0)
        time_left--;
}
int Car::get_id()
{
    return id;
}
bool Car::check_if_it_matches(int second_car_id)
{
    return (id == second_car_id);
}
