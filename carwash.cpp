#include "carwash.hpp"

void carwash::add_stage(std::vector<int> worker_time_coefficients)
{
    stage stage_to_be_pushed;
    worker temp_worker;
    for (int i = 0; i < worker_time_coefficients.size(); i++)
    {
        temp_worker.set_worker_info(new_worker_id, worker_time_coefficients[i]);
        new_worker_id++;
        stage_to_be_pushed.add_worker(temp_worker);
    }
    carwash_stages.push_back(stage_to_be_pushed);
}

void carwash::add_car(int luxury_coefficient)
{
    car temp_car;
    temp_car.set_info(new_car_id, luxury_coefficient);
    waiting_cars.push_back(temp_car);
    new_car_id++;
}

void carwash ::show_stage_info(int id_of_stage)
{
    if (id_of_stage == 0)
        carwash_stages[id_of_stage].display_stage(id_of_stage, waiting_cars);
    else
        carwash_stages[id_of_stage].display_stage(id_of_stage, carwash_stages[id_of_stage].get_cars());
}

void carwash::show_carwash_info()
{
    std::cout << "Passed time: " << time_elpased << std::endl;
    std::cout << "Cars waiting: " << std::endl;
    for (int i = 0; i < waiting_cars.size(); i++)
        waiting_cars[i].display_car();
    std::cout << "Stages info: " << std::endl;
    for (int i = 0; i < carwash_stages.size(); i++)
        show_stage_info(i);
    std::cout << "Cars finished: " << std::endl;
    for (int i = 0; i < done_washing_cars.size(); i++)
    {
        done_washing_cars[i].display_car();
    }
}
void carwash::move_cars_in_carwashqueue_to_stage_zero()
{
    car tempcar;
    if (waiting_cars.empty() == false)
    {
        tempcar = waiting_cars[0];
        waiting_cars.erase(waiting_cars.begin());
        carwash_stages[0].add_car_in_queue(&tempcar);
    }
}
void carwash::accept_cars_in_stages(int i)
{
    carwash_stages[i].accept_car_from_queue();
}
void carwash::move_car_to_next_stage(int i)
{
    car *tempcar_pt;
    if (carwash_stages[i + 1].is_queue_free() && (i != carwash_stages.size() - 1))
    {
        tempcar_pt = carwash_stages[i].pickup_done_car();
        carwash_stages[i + 1].add_car_in_queue(tempcar_pt);
        carwash_stages[i].remove_car_by_address(tempcar_pt);
    }
    if (i == carwash_stages.size() - 1)
    {
        tempcar_pt = carwash_stages.back().pickup_done_car();
        this->move_car_to_finished_list(tempcar_pt);
        carwash_stages.back().remove_car_by_address(tempcar_pt);
    }
}
void carwash::wash_car_in_stages(int i)
{
    carwash_stages[i].wash_cars();
}

void carwash::advance_time()
{
    time_elpased++;

    this->move_cars_in_carwashqueue_to_stage_zero();
    for (int i = 0; i < carwash_stages.size(); i++)
    {
        this->move_car_to_next_stage(i);
        this->wash_car_in_stages(i);
        this->accept_cars_in_stages(i);
    }
}

void carwash::finish()
{
    bool condition1, condition2;
    condition1 = (!waiting_cars.empty());
    condition2 = this->is_any_car_left_in_stages();

    while (condition1 || condition2)
    {
        this->advance_time();
        condition1 = (!waiting_cars.empty());
        condition2 = this->is_any_car_left_in_stages();
    }
}

void carwash::move_car_to_finished_list(car *car_to_be_moved)
{
    if (car_to_be_moved != NULL)
    {
        done_washing_cars.push_back(*car_to_be_moved);
    }
}