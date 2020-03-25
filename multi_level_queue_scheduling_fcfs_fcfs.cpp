#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

class Process{
	public:
		string process_id;
		int arrival_time;
		int burst_time;
		int completion_time = 0;
		int turn_around_time;
		int waiting_time;
		
		string type;
		
		Process(string process_id, int arrival_time, int burst_time, string type){
			this->process_id = process_id;
			this->arrival_time = arrival_time;
			this->burst_time = burst_time;
			this->type = type;
		}
};



int main(){
	
	string process_id_system[] = {"s1", "s2", "s3", "s4", "s5"};
	string process_id_user[] = {"u1", "u2", "u3", "u4"};
	
	int arrival_time_system[] = {4, 40,1,5, 8};
	int arrival_time_user[] = {5,3, 46, 2,};
	
	int burst_time_system[] = {10, 1,11,6, 3};
	int burst_time_user[] = {1,2,3,4};
	
	
	vector<Process> system_processes;
	vector<Process> user_processes;
	
	queue<Process*> system_queue;
	queue<Process*> user_queue;
	
	vector<Process> gantt;
	
	
	for(int i=0; i<5; i++){
		system_processes.push_back(Process(process_id_system[i], arrival_time_system[i], burst_time_system[i], string("system")));
	}
	
	
	for(int i=0; i<4; i++){
		user_processes.push_back(Process(process_id_user[i], arrival_time_user[i], burst_time_user[i], string("user")));
	}
	
	for(int i=0; i<5; i++){
		for(int j=0; j<4-i; j++){
			if (system_processes.at(j+1).arrival_time < system_processes.at(j).arrival_time){
				Process temp = system_processes.at(j);
				system_processes.at(j) = system_processes.at(j+1);
				system_processes.at(j+1) = temp;
			}
		}
	}
	
	
	for(int i=0; i<4; i++){
		for(int j=0; j<3-i; j++){

			if (user_processes.at(j+1).arrival_time < user_processes.at(j).arrival_time){
				Process temp = user_processes.at(j);
				user_processes.at(j) = user_processes.at(j+1);
				user_processes.at(j+1) = temp;
			}
		}
	}
	
	
	Process idle("-1", 0, 0, "");
	
	if (system_processes.at(0).arrival_time < user_processes.at(0).arrival_time){
		idle.completion_time = system_processes.at(0).arrival_time;
		system_queue.push(&system_processes.at(0));
	}
	else{
		idle.completion_time = user_processes.at(0).arrival_time;
		user_queue.push(&user_processes.at(0));
	}
	
	
	gantt.push_back(idle);
	
	while((!system_queue.empty()) || (!user_queue.empty())){
		Process* s = system_queue.front();
		Process* u = user_queue.front();
		
		Process *execute;
		
//		if(s != NULL && (u == NULL || s->arrival_time <= u->arrival_time)){
		if(s != NULL){
			execute = s;
//			s->completion_time = gantt.back().completion_time + s->burst_time;
//			s->turn_around_time = s->completion_time - s->arrival_time;
//			s->waiting_time = s->turn_around_time - s->burst_time;
			system_queue.pop();
//			gantt.push_back(*s);
		}
		else{
			execute = u;
//			u->completion_time = gantt.back().completion_time + u->burst_time;
//			u->turn_around_time = u->completion_time - u->arrival_time;
//			u->waiting_time = u->turn_around_time - u->burst_time;
			user_queue.pop();
//			gantt.push_back(*s);
		}
		
		execute->completion_time = gantt.back().completion_time + execute->burst_time;
		execute->turn_around_time = execute->completion_time - execute->arrival_time;
		execute->waiting_time = execute->turn_around_time - execute->burst_time;
		
		
		for(Process& p: system_processes){
			if(p.arrival_time > gantt.back().completion_time && p.arrival_time <= execute->completion_time){
				system_queue.push(&p);
			}
		}
		
		
		for(Process& p: user_processes){
			if(p.arrival_time > gantt.back().completion_time && p.arrival_time <= execute->completion_time){
				user_queue.push(&p);
			}
		}

		gantt.push_back(*execute);
		
		if((system_queue.empty()) && (user_queue.empty())){
			for(Process& p: system_processes){
				if(p.completion_time == 0){
					idle.arrival_time = gantt.back().completion_time;
					idle.completion_time = p.arrival_time;
					gantt.push_back(idle);
					system_queue.push(&p);
				}
			}
			
			if(system_queue.empty()){
				for(Process& p: user_processes){
					if(p.completion_time == 0){
						idle.arrival_time = gantt.back().completion_time;
						idle.completion_time = p.arrival_time;
						gantt.push_back(idle);
						system_queue.push(&p);
					}
				}
			}
		}
		
	}
	
//	float avg_tat = 0;
//	float avg_wt = 0;
	
	cout << "System Processes:\n";
	printf("%15s |%15s |%15s |%15s |%15s |%15s |\n", "Process Id", "Arr. Time", "Burst Time", "Compl. Time", "Turn A. Time", "Wait. Time");
	for(Process& p: system_processes){
		
		printf("%15s |%15d |%15d |%15d |%15d |%15d |\n", p.process_id.c_str(), p.arrival_time, p.burst_time, p.completion_time, p.turn_around_time, p.waiting_time);
//		avg_
	}
	
	
	cout << "\n\nUser Processes:\n";
	printf("%15s |%15s |%15s |%15s |%15s |%15s |\n", "Process Id", "Arr. Time", "Burst Time", "Compl. Time", "Turn A. Time", "Wait. Time");
	for(Process& p: user_processes){
		printf("%15s |%15d |%15d |%15d |%15d |%15d |\n", p.process_id.c_str(), p.arrival_time, p.burst_time, p.completion_time, p.turn_around_time, p.waiting_time);
	}
	
	cout << "\n\nGantt Chart:\n";
	
	for(Process& p: gantt){
		if (p.process_id == "-1"){
			cout << " idle" << " |";
		}
		else
//			cout << "    " << p.process_id << " |";
			printf(" %4s |", p.process_id.c_str());
	}
	cout << endl;
	
	for(Process& p: gantt){
//		cout << "    " << p.completion_time << " |";
		printf(" %4d |", p.completion_time);
	}
	

	return 0;
}
