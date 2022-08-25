#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


class car{
    private:
        int id;
        int luxury_coefficient;
        int time_left=0;
    public: 
        void set_info(int identification,int l_coefficient){
            id=identification;
            luxury_coefficient=l_coefficient;
        }
        void display_car(){
            cout<<"Car ID: "<<id<<endl;
            cout<<"Luxury coefficient: "<<luxury_coefficient<<endl;
        }
        void set_time_needed_for_cleaning(int worker_coefficient ){
            time_left= luxury_coefficient*worker_coefficient;
        }
        int get_time_left(){return time_left;}
        bool is_washing_done(){return (time_left==0);}
        void update_time_left(){if(time_left!=0)time_left--;}
        int get_id(){return id;}
        bool check_if_it_matches(int second_car_id){return (id==second_car_id);}
};


class worker{
    private:
        bool free=true;
        int id;
        int worker_time_coefficient;
        car *worker_car=NULL;
    public :
        void set_worker_info(int w_id,int time_coefficient){
            id=w_id;
            worker_time_coefficient=time_coefficient;
        }
        void display_worker(){
            cout<<"Worker ID: "<<id<<endl;
            if(free)
                cout <<"Free"<<endl;
            else {
                worker_car->display_car();
                cout<<"Time left: "<<worker_car->get_time_left()<<endl;
            }
        }
        bool is_free(){return free;}
        void assign_car(car* car_to_be_assigned,int set_time_or_not=1){
            free=false;
            worker_car=car_to_be_assigned;
            if(set_time_or_not==1)
                worker_car->set_time_needed_for_cleaning(worker_time_coefficient);
        }
        bool is_job_done(){
            if(worker_car!=NULL)
                return worker_car->is_washing_done();
            return false;
        }
        car* free_worker(){
            car* temp=worker_car;
            worker_car=NULL;
            free=true;
            return temp;
        }
        void do_job(){
            if(worker_car!=NULL)
                worker_car->update_time_left();
        }
        int get_car_id(){
            if(worker_car!=NULL)
                return worker_car->get_id();
            return -1;
        }
};




class stage{
    private:
        vector <car> waiting_for_being_accepted;
        vector <car> in_stage_cars;
        vector <worker> in_stage_workers;
    public: 
        void add_worker(worker worker_to_be_added)
        {
            in_stage_workers.push_back(worker_to_be_added);
        }
        void display_stage(int id_of_stage,vector <car> waiting_queue_cars){
            cout<<"Stage ID: "<<id_of_stage<<endl;
            for (int i=0 ; i<in_stage_workers.size();i++){
                in_stage_workers[i].display_worker();
            }
            cout<<"Cars in waiting queue: "<<endl;
            for (int i=0;i<waiting_queue_cars.size();i++){
                waiting_queue_cars[i].display_car();
            }
        }
        vector<car> get_cars()
        {
            return waiting_for_being_accepted;
        }
        worker* find_free_worker(){
            for (int i=0;i<in_stage_workers.size();i++){
                if (in_stage_workers[i].is_free())
                    return &in_stage_workers[i];
            }
        }
        void add_car_in_queue(car* goes_to_stage_car){
            if(goes_to_stage_car!=NULL){
                if(this->is_queue_free())
                    waiting_for_being_accepted.push_back(*goes_to_stage_car);
            }
        }
        void accept_car_from_queue(){
            if(waiting_for_being_accepted.empty())return ;
            vector <int> worker_car_ids;
            this->update_worker_reference_to_their_cars(worker_car_ids);
            car tempcar;
            tempcar=waiting_for_being_accepted[0];
            worker* freeworker=NULL;
            for (int i=0 ; i <in_stage_workers.size();i++){
                if(in_stage_workers[i].is_free())
                    {
                        freeworker=&in_stage_workers[i];
                        break;
                    }
            }
            if(freeworker!=NULL){
                in_stage_cars.push_back(tempcar);
                this->update_worker_reference_to_their_cars(worker_car_ids);
                freeworker->assign_car(&in_stage_cars.back());
                waiting_for_being_accepted.erase(waiting_for_being_accepted.begin());
            }
        }
        bool is_queue_free(){return waiting_for_being_accepted.empty();}
        car* pickup_done_car(){
            car* temp;
            for (int i=0;i<in_stage_workers.size();i++){
                if(in_stage_workers[i].is_job_done()){
                    temp=in_stage_workers[i].free_worker();
                    return temp;
                }   
            }
            return NULL;
        }
        void remove_car_by_address(car* car_pt){
            if(car_pt==NULL)return;
            for (int i=0;i<in_stage_cars.size();i++){
                if(car_pt==&in_stage_cars[i]){
                    in_stage_cars.erase(in_stage_cars.begin()+i);
                    return;
                }
            }
        }
        void wash_cars(){
            car* temp;
            for (int i=0;i<in_stage_workers.size();i++){
                in_stage_workers[i].do_job();
            }
        }
        bool empty(){return in_stage_cars.empty();}
        car* find_car_address(int id){
            for (int i=0;i<in_stage_cars.size();i++){
                if(in_stage_cars[i].check_if_it_matches(id))
                    return &in_stage_cars[i];
            }
            return NULL;
        }
        void update_worker_reference_to_their_cars(vector <int>&worker_car_ids){
            int current_worker_car_id;
            car* car_address;
            if(worker_car_ids.empty()){
                for (int i=0;i<in_stage_workers.size();i++){
                    if(!in_stage_workers[i].is_free()){
                        current_worker_car_id=in_stage_workers[i].get_car_id();
                        worker_car_ids.push_back(current_worker_car_id);
                    }
                    else worker_car_ids.push_back(-1);
                }
            }
            else {
                for (int i=0;i<in_stage_workers.size();i++){
                    if(worker_car_ids[i]==-1)continue;
                    car_address=this->find_car_address(worker_car_ids[i]);
                    in_stage_workers[i].assign_car(car_address,0);
                }
            }
        }
        bool does_it_have_cars(){
            return (!(in_stage_cars.empty()));
        }
};



class carwash {
    private : 
        int time_elpased=0;
        int new_worker_id=0;
        int new_car_id=0;
        vector <stage> carwash_stages;
        vector <car> waiting_cars;
        vector <car> done_washing_cars;

    public:
        void add_stage(vector < int> worker_time_coefficients);
        void add_car(int luxury_coefficient);
        void show_stage_info(int id_of_stage);
        void show_carwash_info();
        void advance_time();
        void accept_cars_in_stages(int i);
        void move_car_to_next_stage(int i);
        void wash_car_in_stages(int i);
        void finish();
        bool is_any_car_left_in_stages(){
            for (int i=0;i<carwash_stages.size();i++){
                if(carwash_stages[i].does_it_have_cars())
                    return true;
            }
            return false;
        }
        void move_cars_in_carwashqueue_to_stage_zero();
        void move_car_to_finished_list(car* car_to_be_moved);
};

void carwash::add_stage(vector < int > worker_time_coefficients){
    stage stage_to_be_pushed;
    worker temp_worker;
    for (int i=0 ; i < worker_time_coefficients.size(); i ++ ){
        temp_worker.set_worker_info(new_worker_id,worker_time_coefficients[i]);
        new_worker_id++;
        stage_to_be_pushed.add_worker(temp_worker);
    }
    carwash_stages.push_back(stage_to_be_pushed);
}

void carwash::add_car(int luxury_coefficient){
    car temp_car;
    temp_car.set_info(new_car_id,luxury_coefficient);
    waiting_cars.push_back(temp_car);
    new_car_id++;
}


void carwash :: show_stage_info(int id_of_stage){
    if (id_of_stage==0)
        carwash_stages[id_of_stage].display_stage(id_of_stage,waiting_cars);
    else 
        carwash_stages[id_of_stage].display_stage(id_of_stage,carwash_stages[id_of_stage].get_cars());
}


void carwash::show_carwash_info(){
    cout<<"Passed time: "<<time_elpased<<endl;
    cout<<"Cars waiting: "<<endl;
    for (int i=0;i<waiting_cars.size();i++)
        waiting_cars[i].display_car();
    cout<<"Stages info: "<<endl;
    for (int i=0;i<carwash_stages.size();i++)
        show_stage_info(i);
    cout<<"Cars finished: "<<endl;
    for (int i=0;i<done_washing_cars.size();i++){
        done_washing_cars[i].display_car();
    }
}
void carwash::move_cars_in_carwashqueue_to_stage_zero(){
    car tempcar;
    if(waiting_cars.empty()==false){
        tempcar=waiting_cars[0];
        waiting_cars.erase(waiting_cars.begin());
        carwash_stages[0].add_car_in_queue(&tempcar);
    }  
}
void carwash::accept_cars_in_stages(int i){
    carwash_stages[i].accept_car_from_queue();
}
void carwash::move_car_to_next_stage(int i){
    car* tempcar_pt;
    if(carwash_stages[i+1].is_queue_free()&& (i!=carwash_stages.size()-1)){
        tempcar_pt=carwash_stages[i].pickup_done_car();
        carwash_stages[i+1].add_car_in_queue(tempcar_pt);
        carwash_stages[i].remove_car_by_address(tempcar_pt);
    }
    if(i==carwash_stages.size()-1){
        tempcar_pt=carwash_stages.back().pickup_done_car();
        this->move_car_to_finished_list(tempcar_pt);
        carwash_stages.back().remove_car_by_address(tempcar_pt);
    }
}
void carwash::wash_car_in_stages(int i){
    carwash_stages[i].wash_cars();
}

void carwash::advance_time(){
    time_elpased++;

    this->move_cars_in_carwashqueue_to_stage_zero();
    for (int i=0;i<carwash_stages.size();i++){
        this->move_car_to_next_stage(i);
        this->wash_car_in_stages(i);
        this->accept_cars_in_stages(i);
    }
}

void carwash::finish(){
    bool condition1,condition2;
    condition1=(!waiting_cars.empty());
    condition2=this->is_any_car_left_in_stages();
    
    while (condition1 || condition2){
        this->advance_time();
        condition1=(!waiting_cars.empty());
        condition2=this->is_any_car_left_in_stages();
    }
}

void carwash::move_car_to_finished_list(car* car_to_be_moved){
    if(car_to_be_moved!=NULL){
        done_washing_cars.push_back(*car_to_be_moved);
    }
}

enum string_code{
    add_stage,add_car,advance_time,show_stage_info,show_carwash_info,finish
};

string_code hashit(string const& instring){
    if(instring=="add_stage")return add_stage;
    if(instring=="add_car")return add_car;
    if(instring=="advance_time")return advance_time;
    if(instring=="show_stage_info")return show_stage_info;
    if(instring=="show_carwash_info")return show_carwash_info;
    if(instring=="finish")return finish;
}



int main () {
    carwash ali_carwash;
    vector <int> worker_time_coefficients;
    int luxury_coefficient;
    int stage_number;
    int advance_time_index;
    string user_command;
while( getline(cin,user_command)){
    stringstream ss(user_command);
    string command_type;
    ss>>command_type;
    switch (hashit(command_type))
    {
        int temp;
        int num_of_workers;
    case add_stage:
        ss>>num_of_workers;
        for (int i=0;i<num_of_workers;i++){
            ss>>temp;
            worker_time_coefficients.push_back(temp);
        }
        ali_carwash.add_stage(worker_time_coefficients);
        worker_time_coefficients.clear();
        cout<<"OK"<<endl;
        break;
    case add_car:
        ss>>luxury_coefficient;
        ali_carwash.add_car(luxury_coefficient);
        cout<<"OK"<<endl;
        break;
    case advance_time:
        ss>>advance_time_index;
        do{
            ali_carwash.advance_time();
            advance_time_index--;
        }while(advance_time_index!=0);
        cout<<"OK"<<endl;
        break;
    case show_stage_info:
        ss>>stage_number;
        ali_carwash.show_stage_info(stage_number);
        break;
    case show_carwash_info:
        ali_carwash.show_carwash_info();
        break;
    case finish:
        ali_carwash.finish();
        cout<<"OK"<<endl;
    default:
        break;
    }
}
}