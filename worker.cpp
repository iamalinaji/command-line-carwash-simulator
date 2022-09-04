#include "worker.hpp"

void Worker::set_worker_info(int w_id, int time_coefficient)
{
    id = w_id;
    worker_time_coefficient = time_coefficient;
}
void Worker::display_worker()
{
    std::cout << "Worker ID: " << id << std::endl;
    if (free)
        std::cout << "Free" << std::endl;
    else
    {
        worker_car->display_car();
        std::cout << "Time left: " << worker_car->get_time_left() << std::endl;
    }
}
bool Worker::is_free()
{
    return free;
}
void Worker::assign_car(Car *car_to_be_assigned, bool set_time_or_not)
{
    free = false;
    worker_car = car_to_be_assigned;
    if (set_time_or_not == 1)
        worker_car->set_time_needed_for_cleaning(worker_time_coefficient);
}
bool Worker::is_job_done()
{
    if (worker_car != NULL)
        return worker_car->is_washing_done();
    return false;
}
Car *Worker::free_worker()
{
    Car *temp = worker_car;
    worker_car = NULL;
    free = true;
    return temp;
}
void Worker::do_job()
{
    if (worker_car != NULL)
        worker_car->update_time_left();
}
int Worker::get_car_id()
{
    if (worker_car != NULL)
        return worker_car->get_id();
    return -1;
}