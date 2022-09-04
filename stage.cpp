#include "stage.hpp"

void Stage::add_worker(Worker worker_to_be_added)
{
    in_stage_workers.push_back(worker_to_be_added);
}
void Stage::display_stage(int id_of_stage, std::vector<Car> waiting_queue_cars)
{
    std::cout << "Stage ID: " << id_of_stage << std::endl;
    for (int i = 0; i < in_stage_workers.size(); i++)
    {
        in_stage_workers[i].display_worker();
    }
    std::cout << "Cars in waiting queue: " << std::endl;
    for (int i = 0; i < waiting_queue_cars.size(); i++)
    {
        waiting_queue_cars[i].display_car();
    }
}
std::vector<Car> Stage::get_cars()
{
    return waiting_for_being_accepted;
}
Worker *Stage::find_free_worker()
{
    for (int i = 0; i < in_stage_workers.size(); i++)
    {
        if (in_stage_workers[i].is_free())
            return &in_stage_workers[i];
    }
    return NULL;
}
void Stage::add_car_in_queue(Car *goes_to_stage_car)
{
    if (goes_to_stage_car != NULL)
    {
        if (this->is_queue_free())
            waiting_for_being_accepted.push_back(*goes_to_stage_car);
    }
}
void Stage::accept_car_from_queue()
{
    if (waiting_for_being_accepted.empty())
        return;
    std::vector<int> worker_car_ids;
    this->update_worker_reference_to_their_cars(worker_car_ids);
    Car tempcar;
    tempcar = waiting_for_being_accepted[0];
    Worker *freeworker = NULL;
    for (int i = 0; i < in_stage_workers.size(); i++)
    {
        if (in_stage_workers[i].is_free())
        {
            freeworker = &in_stage_workers[i];
            break;
        }
    }
    if (freeworker != NULL)
    {
        in_stage_cars.push_back(tempcar);
        this->update_worker_reference_to_their_cars(worker_car_ids);
        freeworker->assign_car(&in_stage_cars.back());
        waiting_for_being_accepted.erase(waiting_for_being_accepted.begin());
    }
}
bool Stage::is_queue_free()
{
    return waiting_for_being_accepted.empty();
}
Car *Stage::pickup_done_car()
{
    Car *temp;
    for (int i = 0; i < in_stage_workers.size(); i++)
    {
        if (in_stage_workers[i].is_job_done())
        {
            temp = in_stage_workers[i].free_worker();
            return temp;
        }
    }
    return NULL;
}
void Stage::remove_car_by_address(Car *car_pt)
{
    if (car_pt == NULL)
        return;
    for (int i = 0; i < in_stage_cars.size(); i++)
    {
        if (car_pt == &in_stage_cars[i])
        {
            in_stage_cars.erase(in_stage_cars.begin() + i);
            return;
        }
    }
}
void Stage::wash_cars()
{
    Car *temp;
    for (int i = 0; i < in_stage_workers.size(); i++)
    {
        in_stage_workers[i].do_job();
    }
}
bool Stage::empty()
{
    return in_stage_cars.empty();
}
Car *Stage::find_car_address(int id)
{
    for (int i = 0; i < in_stage_cars.size(); i++)
    {
        if (in_stage_cars[i].check_if_it_matches(id))
            return &in_stage_cars[i];
    }
    return NULL;
}
void Stage::update_worker_reference_to_their_cars(std::vector<int> &worker_car_ids)
{
    int current_worker_car_id;
    Car *car_address;
    if (worker_car_ids.empty())
    {
        for (int i = 0; i < in_stage_workers.size(); i++)
        {
            if (!in_stage_workers[i].is_free())
            {
                current_worker_car_id = in_stage_workers[i].get_car_id();
                worker_car_ids.push_back(current_worker_car_id);
            }
            else
                worker_car_ids.push_back(-1);
        }
    }
    else
    {
        for (int i = 0; i < in_stage_workers.size(); i++)
        {
            if (worker_car_ids[i] == -1)
                continue;
            car_address = this->find_car_address(worker_car_ids[i]);
            in_stage_workers[i].assign_car(car_address, false);
        }
    }
}
bool Stage::does_it_have_cars()
{
    return (!(in_stage_cars.empty()));
}