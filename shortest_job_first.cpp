// shortest job first headet

#ifndef SHORTEST_JOB_FIRST_H
#define SHORTEST_JOB_FIRST_H

#include<iostream>
#include<cstdio>

using namespace std;

void shortest_job_first(){
	int process_id[] = {1, 2, 3, 4, 5},
		arrival_time[] = {20, 10, 1, 5, 24},
		burst_time[] = {10, 5, 6, 3, 11},
		completion_time[5] = {0},
		turn_around_time[5],
		waiting_time[5];
		
		
	int i, j;
	float avg_tat=0, avg_wt=0;
	
	for(i=0; i<5; i++){
		for(j=i+1; j<5; j++){
			if (burst_time[i] > burst_time[j]){
				int temp = burst_time[i];
				burst_time[i] = burst_time[j];
				burst_time[j] = temp;
				
				temp = process_id[i];
				process_id[i] = process_id[j];
				process_id[j] = temp;
				
				temp = arrival_time[i];
				arrival_time[i] = arrival_time[j];
				arrival_time[j] = temp;
			}
		}
	}
	
	j=0;
	for (i=1; i<5; i++){
		if (arrival_time[i] < arrival_time[j]){
			j=i;
		}
	}
	
	if (j!=0){
		int p_id = process_id[j];
		int arr_t =arrival_time[j];
		int bur_t = burst_time[j];
		for (i=j; i>0; i--){
			process_id[i] = process_id[i-1];
			arrival_time[i] = arrival_time[i-1];
			burst_time[i] = burst_time[i-1];
		}
		process_id[0] = p_id;
		arrival_time[0] = arr_t;
		burst_time[0] = bur_t;
	}
	
	// ------------------
	
	completion_time[0] = arrival_time[0] + burst_time[0];
	
	cout << "CPU scheduling"<< endl << endl << "Shortest Job First:" << endl;
	printf("%15s | %15s | %15s | %15s | %15s | %15s |", "Process-Id",
														"Arrival Time",
														"Burst Time",
														"Completion Time",
														"Turn Around T.",
														"Waiting Time");
														
	for(i=0; i<5; i++){
		
		if (i!=0){
			if (arrival_time[i] > completion_time[i-1]){
				int min_arr_time = arrival_time[i];
				int min_arr_time_index = i;
				j=i;
				while (arrival_time[j] > completion_time[i-1] && j<5){
					if (arrival_time[j] < min_arr_time){
						min_arr_time = arrival_time[j];
						min_arr_time_index = j;
					}
					j++;
				}
				
				if (j < 5) min_arr_time_index = j;
				
				int p_id = process_id[min_arr_time_index];
				int arr_t =arrival_time[min_arr_time_index];
				int bur_t = burst_time[min_arr_time_index];
				
				for (j=min_arr_time_index; j>i; j--){
					process_id[j] = process_id[j-1];
					arrival_time[j] = arrival_time[j-1];
					burst_time[j] = burst_time[j-1];
				}
				
				process_id[i] = p_id;
				arrival_time[i] = arr_t;
				burst_time[i] = bur_t;
			}
			
			if (arrival_time[i] > completion_time[i-1])
				completion_time[i] = burst_time[i] + arrival_time[i];
			else
				completion_time[i] = completion_time[i-1] + burst_time[i];
		}
		
		
		turn_around_time[i] = completion_time[i] - arrival_time[i];
		waiting_time[i] = turn_around_time[i] - burst_time[i];
		
		
		printf("\n%17d %17d %17d %17d %17d %17d\n", process_id[i],
													arrival_time[i],
													burst_time[i],
													completion_time[i],
													turn_around_time[i],
													waiting_time[i]);
													
		avg_tat += turn_around_time[i];
		avg_wt += waiting_time[i];
	}
	
	cout << endl << endl << "Gantt Chart:" << endl << " ";
	
	for(i=0; i<5; i++){
		
		if(i!=0){
			if(arrival_time[i] > completion_time[i-1])
				cout << " idle  | ";
			
		}
		cout << "    P" << process_id[i] << " |";	
	}
	
	cout << endl << arrival_time[0];
	
	for(i=0; i<5; i++){
		
		if(i!=0){
			if(arrival_time[i] > completion_time[i-1])
				printf("%7d  ", arrival_time[i]);
		}
		
		printf("%7d ", completion_time[i]);			
	}
	
	avg_tat = avg_tat/5;
	avg_wt = avg_wt/5;
	
	cout << endl << endl << "Average Turn Around Time: " << avg_tat;
	cout << endl << "Average Waiting Time: " << avg_wt;

}


#endif
