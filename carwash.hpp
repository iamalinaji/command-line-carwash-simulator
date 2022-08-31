#include "stage.hpp"

class carwash
{
  private:
    int time_elpased = 0;
    int new_worker_id = 0;
    int new_car_id = 0;
    std::vector<stage> carwash_stages;
    std::vector<car> waiting_cars;
    std::vector<car> done_washing_cars;

  public:
    void add_stage(std::vector<int> worker_time_coefficients);
    void add_car(int luxury_coefficient);
    void show_stage_info(int id_of_stage);
    void show_carwash_info();
    void advance_time();
    void accept_cars_in_stages(int i);
    void move_car_to_next_stage(int i);
    void wash_car_in_stages(int i);
    void finish();
    bool is_any_car_left_in_stages()
    {
        for (int i = 0; i < carwash_stages.size(); i++)
        {
            if (carwash_stages[i].does_it_have_cars())
                return true;
        }
        return false;
    }
    void move_cars_in_carwashqueue_to_stage_zero();
    void move_car_to_finished_list(car *car_to_be_moved);
};