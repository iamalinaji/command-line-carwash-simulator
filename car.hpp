#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class car
{
  private:
    int id;
    int luxury_coefficient;
    int time_left = 0;

  public:
    void set_info(int identification, int l_coefficient)
    {
        id = identification;
        luxury_coefficient = l_coefficient;
    }
    void display_car()
    {
        std::cout << "Car ID: " << id << std::endl;
        std::cout << "Luxury coefficient: " << luxury_coefficient << std::endl;
    }
    void set_time_needed_for_cleaning(int worker_coefficient)
    {
        time_left = luxury_coefficient * worker_coefficient;
    }
    int get_time_left()
    {
        return time_left;
    }
    bool is_washing_done()
    {
        return (time_left == 0);
    }
    void update_time_left()
    {
        if (time_left != 0)
            time_left--;
    }
    int get_id()
    {
        return id;
    }
    bool check_if_it_matches(int second_car_id)
    {
        return (id == second_car_id);
    }
};