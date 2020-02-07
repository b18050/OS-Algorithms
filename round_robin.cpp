#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

#define TQ 2
#define NB_PROCESS 7

using namespace std;


class Process{
	public:
		int process_id;
		int arrival_time;
		int burst_time;
		int remaining_time;
		int completion_time = 0;
		int turn_around_time = -1;
		int waiting_time = -1;
		
		Process(int p_id, int a_time, int b_time){
			this->process_id = p_id;
			this->arrival_time = a_time;
			this->burst_time = b_time;
			this->remaining_time = this->burst_time;
		}
		
		bool operator==(Process& p){
			if (this->process_id == p.process_id) return true;
			return false;
		}
		
		bool operator!=(Process& p){
			if (this->process_id == p.process_id) return false;
			return true;
		}
};

int main(){
	
	int process_id[] = {0, 1, 2, 3, 4, 5, 6};
	int arrival_time[] = {9, 1, 4, 5, 2, 30, 29};
	int burst_time[] = {10, 2, 1, 5, 7, 3, 6};
	
	vector<Process> process_list;
	
	queue<Process*> ready_queue;
	vector<Process> gantt;


	Process idle(-1,0,0);


	for(int i=0; i<NB_PROCESS; i++)
		process_list.push_back(Process(process_id[i], arrival_time[i], burst_time[i]));


// Bubble sort on arrival_time:
	for(int i=0; i<NB_PROCESS; i++)
		for (int j=1; j<NB_PROCESS-i; j++)
			if (process_list.at(j).arrival_time < process_list.at(j-1).arrival_time){
				Process temp = process_list.at(j);
				process_list.at(j) = process_list.at(j-1);
				process_list.at(j-1)= temp;
			}
			
	if(process_list.at(0).arrival_time > 0){
		idle.completion_time = process_list.at(0).arrival_time;
		gantt.push_back(idle);
	}
	
	ready_queue.push(&process_list.at(0));
	
	while( !ready_queue.empty() ){
		Process* current = ready_queue.front();
		ready_queue.pop();
		

		if(current->remaining_time <= TQ){
			current->completion_time = gantt.back().completion_time + current->remaining_time;
			current->remaining_time = 0;
		}
		else{
			current->completion_time = gantt.back().completion_time + TQ;
			current->remaining_time = current->remaining_time - TQ;
		}
		
		
		for(Process& p: process_list){
			if(p.arrival_time > gantt.back().completion_time && p.arrival_time <= current->completion_time ){
				ready_queue.push(&p);
			}
		}
		
		if(current->remaining_time != 0)
			ready_queue.push(current);
		
		gantt.push_back(*current);

		
		if (ready_queue.empty() )
			for (Process& p: process_list)
				if(p.remaining_time != 0 ){
					idle.arrival_time = gantt.back().completion_time;
					idle.completion_time = p.arrival_time;
					gantt.push_back(idle);
					ready_queue.push(&p);
					break;
				}
		
	}
	
	
	cout << "CPU Scheduling:" << endl << "Round Robin Scheduling:";
	
	printf("\n\n %15s | %15s | %15s | %15s | %15s | %15s |\n\n", "Process Id",
						"Arrival Time",
						"Burst Time",
						"Completion Time",
						"Turn Around T.",
						"Waiting Time");
	
// Bubble sort on process_id:

//	for(int i=0; i<NB_PROCESS; i++)
//		for (int j=1; j<NB_PROCESS-i; j++)
//			if (process_list.at(j).process_id < process_list.at(j-1).process_id){
//				Process temp = process_list.at(j);
//				process_list.at(j) = process_list.at(j-1);
//				process_list.at(j-1) = temp; 
//			}
	
	reverse( gantt.begin(), gantt.end() );
	for(Process& process_list_p: process_list){
		
		for(Process& gantt_p: gantt )
			if(gantt_p.process_id == process_list_p.process_id){
				
				process_list_p.completion_time = gantt_p.completion_time;
				process_list_p.turn_around_time = process_list_p.completion_time - process_list_p.arrival_time;
				process_list_p.waiting_time = process_list_p.turn_around_time - process_list_p.burst_time;
				
				break;
			}
		
		printf("  %14d |  %14d |  %14d |  %14d |  %14d |  %14d |\n", process_list_p.process_id,
							process_list_p.arrival_time,
							process_list_p.burst_time,
							process_list_p.completion_time,
							process_list_p.turn_around_time,
							process_list_p.waiting_time);
	}
	
	
	
	reverse( gantt.begin(), gantt.end() );
	cout << "\n\nGantt Chart:\n ";
	for (Process& p: gantt)
		if (p.process_id == -1)
			printf("   idle |");
		else
			printf("     P%d |", p.process_id);
	
	
	cout << endl << 0;
	
	for (Process& p: gantt)
		printf("     %2d |", p.completion_time);
	
	
	
		
	return 0;
}
