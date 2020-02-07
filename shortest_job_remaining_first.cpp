#include<iostream>
#include<vector>
#include<algorithm>

#define NB_PROCESS 6

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
		
		bool operator!=(Process& p){
			if (this->process_id == p.process_id) return false;
			return true;
		}
};


int main(){
	int process_id[] = {0, 1, 2, 3, 4, 5};
	int arrival_time[] = {2, 1, 2, 5, 25, 24};
	int burst_time[] = {6, 3, 2, 5, 2, 7};
	
	vector<Process> process_list;
	vector<Process> gantt;
	
	vector<Process*> ready_vector;
	
	Process idle(-1,0,0);

	
	
	for(int i=0; i<NB_PROCESS; i++)
		process_list.push_back(Process(process_id[i], arrival_time[i], burst_time[i]));

		
	// Bubble sort on arrival_time:
	for(int i=0; i<NB_PROCESS; i++)
		for (int j=1; j<NB_PROCESS-i; j++)
			if (process_list.at(j).arrival_time < process_list.at(j-1).arrival_time){
				Process temp = process_list.at(j);
				process_list.at(j) = process_list.at(j-1);
				process_list.at(j-1) = temp;
			}
			
			
	if(process_list.at(0).arrival_time > 0)
		idle.completion_time = process_list.at(0).arrival_time;	
	
	
	gantt.push_back(idle);
	
	ready_vector.push_back(&process_list.at(0));
	
	while( !ready_vector.empty() ){
		
//		Bubble sort based on remaining time:
		for(int i=0; i<ready_vector.size(); i++)
			for(int j=1; j<ready_vector.size()-i; j++)
				if (ready_vector.at(j)->remaining_time < ready_vector.at(j-1)->remaining_time){
					Process* temp = ready_vector.at(j);
					ready_vector.at(j) = ready_vector.at(j-1);
					ready_vector.at(j-1) = temp;
				}
			
		
		
		Process* current = ready_vector.at(0);
		ready_vector.erase(ready_vector.begin());
		
		current->completion_time = gantt.back().completion_time + 1;
		current->remaining_time--;
		
		
		for (Process& p: process_list)
			if(p.arrival_time > gantt.back().completion_time && p.arrival_time <= current->completion_time)
				{cout <<"here";
				ready_vector.push_back(&p);
				}
		
		
		if (current->remaining_time != 0)
			ready_vector.push_back(current);
		
		gantt.push_back(*current);
		
		
		
		if ( ready_vector.empty() )
			for(Process& p: process_list)
				if(p.remaining_time != 0){
					idle.arrival_time = gantt.back().completion_time;
					idle.completion_time = p.arrival_time;
					gantt.push_back(idle);
					ready_vector.push_back(&p);
					break;
				}
		
	}
	
	
	
	cout << "CPU Scheduling:" << endl << "Shortest Job Remaining First Scheduling:";
	
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
	
// till here
	
	
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
	
//	comment this out to print all blocks separately
	for(int i=gantt.size()-1; i>0; i--){
		if(gantt.at(i).process_id == gantt.at(i-1).process_id){
			gantt.erase(gantt.begin()+i-1);
			
		}
	}
//  till here
	
	cout << "\n\nGantt Chart:\n ";
	for (Process& p: gantt)
		if (p.process_id == -1){
			if (p.completion_time != 0)
				printf("   idle |");
		}
		else
			printf("     P%d |", p.process_id);
	
	
	cout << endl << 0;
	
	for (Process& p: gantt)
		if (p.completion_time)
			printf("     %2d |", p.completion_time);
	
	
	
	
	return 0;
}
