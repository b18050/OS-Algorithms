// first come first serve header

#ifndef FIRST_COME_FIRST_SERVE_H
#define FIRST_COME_FIRST_SERVE_H

#include<iostream>
#include<cstdio>

using namespace std;


void first_come_first_serve(){
	int process_id[] = {1, 2, 3, 4, 5},
		arrival_time[] = {1, 2, 17, 20, 30},
		burst_time[] = {10, 5, 20, 3, 11},
		completion_time[5] = {0},
		turn_around_time[5],
		waiting_time[5];
		
		
	int i;
	float avg_tat=0, avg_wt=0;
	
	completion_time[0] = arrival_time[0] + burst_time[0];
	
	cout << "CPU scheduling"<< endl << endl <<"First-Come-First-Serve:" << endl;
	printf("%15s | %15s | %15s | %15s | %15s | %15s |", "Process-Id",
														"Arrival Time",
														"Burst Time",
														"Completion Time",
														"Turn Around T.",
														"Waiting Time");
	
	for(i=0; i<5; i++){
		if(i!=0){
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
