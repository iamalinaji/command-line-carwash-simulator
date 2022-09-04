#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Car
{
  private:
    int id;
    int luxury_coefficient;
    int time_left = 0;

  public:
    void set_info(int identification, int l_coefficient);
    void display_car();
    void set_time_needed_for_cleaning(int worker_coefficient);
    int get_time_left();
    bool is_washing_done();
    void update_time_left();
    int get_id();
    bool check_if_it_matches(int second_car_id);
};