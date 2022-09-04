#ifndef STAGE_HPP
#define STAGEWHPP

#include "worker.hpp"
class Stage
{
  private:
    std::vector<Car> waiting_for_being_accepted;
    std::vector<Car> in_stage_cars;
    std::vector<Worker> in_stage_workers;

  public:
    void add_worker(Worker worker_to_be_added);
    void display_stage(int id_of_stage, std::vector<Car> waiting_queue_cars);
    std::vector<Car> get_cars();
    Worker *find_free_worker();
    void add_car_in_queue(Car *goes_to_stage_car);
    void accept_car_from_queue();
    bool is_queue_free();
    Car *pickup_done_car();
    void remove_car_by_address(Car *car_pt);
    void wash_cars();
    bool empty();
    Car *find_car_address(int id);
    void update_worker_reference_to_their_cars(std::vector<int> &worker_car_ids);
    bool does_it_have_cars();
};

#endif