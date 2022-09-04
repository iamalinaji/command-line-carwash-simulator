#include "car.hpp"

class Worker
{
  private:
    bool free = true;
    int id;
    int worker_time_coefficient;
    Car *worker_car = NULL;

  public:
    void set_worker_info(int w_id, int time_coefficient);
    void display_worker();
    bool is_free();
    void assign_car(Car *car_to_be_assigned, bool set_time_or_not = true);
    bool is_job_done();
    Car *free_worker();
    void do_job();
    int get_car_id();
};