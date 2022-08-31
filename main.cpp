#include "header.hpp"
using namespace std;
int main()
{
    carwash ali_carwash;
    vector<int> worker_time_coefficients;
    int luxury_coefficient;
    int stage_number;
    int advance_time_index;
    string user_command;
    while (getline(cin, user_command))
    {
        stringstream ss(user_command);
        string command_type;
        ss >> command_type;
        switch (hashit(command_type))
        {
            int temp;
            int num_of_workers;
        case commandtype::add_stage:
            ss >> num_of_workers;
            for (int i = 0; i < num_of_workers; i++)
            {
                ss >> temp;
                worker_time_coefficients.push_back(temp);
            }
            ali_carwash.add_stage(worker_time_coefficients);
            worker_time_coefficients.clear();
            cout << "OK" << endl;
            break;
        case commandtype::add_car:
            ss >> luxury_coefficient;
            ali_carwash.add_car(luxury_coefficient);
            cout << "OK" << endl;
            break;
        case commandtype::advance_time:
            ss >> advance_time_index;
            do
            {
                ali_carwash.advance_time();
                advance_time_index--;
            } while (advance_time_index != 0);
            cout << "OK" << endl;
            break;
        case commandtype::show_stage_info:
            ss >> stage_number;
            ali_carwash.show_stage_info(stage_number);
            break;
        case commandtype::show_carwash_info:
            ali_carwash.show_carwash_info();
            break;
        case commandtype::finish:
            ali_carwash.finish();
            cout << "OK" << endl;
        default:
            break;
        }
    }
}