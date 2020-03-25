// Algorithm reference: https://www.geeksforgeeks.org/program-first-fit-algorithm-memory-management/

#include<iostream>

using namespace std;

void worst_fit(int&, int*, int*, int&, int*, int*);
void best_fit(int&, int*, int*, int&, int*, int*);
void first_fit(int&, int*, int*, int&, int*, int*);

void print_input(int&, int*, int*, int&, int*, int*);
void sort_2_arrays(int&, int*, int*);


int main(){
	
//	test case - 1
//	int block_ids[] = {1, 2, 3, 4, 5};
//	int block_sizes[] = {100, 500, 200, 300, 600};
//	
//	int process_ids[] = {1, 2, 3, 4};
//	int process_requirements[] = {212, 417, 112, 426};
	
	
//	test case - 2
	int block_ids[] = {1, 2, 3, 4, 5, 6, 7};
	int block_sizes[] = {342, 876, 543, 798, 624, 141, 124};
	
	int process_ids[] = {1, 2, 3, 4, 5};
	int process_requirements[] = {232, 980, 832, 123, 511};
	
	
	int nb_blocks = sizeof(block_ids)/sizeof(int);
	int nb_processes = sizeof(process_ids)/sizeof(int);
	
	print_input(nb_blocks, block_ids, block_sizes, nb_processes, process_ids, process_requirements);
	
	
	char choice;
	
	cout << "Contiguous Memory Allocation Techniques:" << endl;
	cout << "Choose: " << endl;
	cout << "a. Worst Fit" << endl << "b. Best Fit" << endl << "c. First Fit" << endl;
	
	while(true){
		cout << ">> ";
		cin >> choice;
		
		switch(choice){
			case 'a' :
				worst_fit(nb_blocks, block_ids, block_sizes, nb_processes, process_ids, process_requirements);
				break;
				
			case 'b' :
				best_fit(nb_blocks, block_ids, block_sizes, nb_processes, process_ids, process_requirements);
				break;
				
			case 'c' :
				first_fit(nb_blocks, block_ids, block_sizes, nb_processes, process_ids, process_requirements);
				break;
				
			default :
				cout << "\nPlease choose from (a, b, c)\n";
		}
	}
	
	
	return 0;
}


void print_input(int& nb_blocks, int* block_ids, int* block_sizes, int& nb_processes, int* process_ids, int* process_requirements){
	cout << "Input:\n\n";
	
	cout << "Blocks Information:\n";
	printf("%17s |%17s |\n", "Block Id", "Block Size");
	for (int i=0; i<nb_blocks; i++){
		printf("%17d |%17d |\n", block_ids[i], block_sizes[i]);
	}
	
	cout << "\n\nProcesses Information:\n";
	printf("%17s |%17s |\n", "Process Id", "Process Req.");
	for (int i=0; i<nb_processes; i++){
		printf("%17d |%17d |\n", process_ids[i], process_requirements[i]);
	}
	
	cout << endl << "----------------------------------------------------------------------" << endl << endl;
}


void sort_2_arrays(int& array_size, int* array_1, int* array_2){
	for(int i=0; i<array_size; i++)
		for(int j=1; j<array_size-i; j++)
			if(array_2[j-1] > array_2[j]){
				int temp = array_2[j];
				array_2[j] = array_2[j-1];
				array_2[j-1] = temp;
				
				temp = array_1[j];
				array_1[j] = array_1[j-1];
				array_1[j-1] = temp;
			}
}



void worst_fit(int& nb_blocks, int* block_ids, int* block_sizes, int& nb_processes, int* process_ids, int* process_requirements){
	
	int* block_remaining = new int[nb_blocks];
	int* block_ids_copy = new int[nb_blocks];
	int* process_allocation = new int[nb_processes];
	
	for(int i=0; i<nb_blocks; i++){
		block_remaining[i] = block_sizes[i];
		block_ids_copy[i] = block_ids[i];
	}
	
	
	cout << "\n\nWorst Fit:\n";
	printf("%17s |%17s |%17s |%17s |\n", "Process Id", "Process Req.", "Allocated Block", "Block Rem.");
	
	for (int i=0; i<nb_processes; i++){
		sort_2_arrays(nb_blocks, block_ids_copy, block_remaining);
		
		
		process_allocation[i] = -1;
		int j;
		for(j=nb_blocks-1; j>=0; j--)
			if (process_requirements[i] <= block_remaining[j]){
				process_allocation[i] = block_ids_copy[j];
				block_remaining[j] -= process_requirements[i];
				break;
			}
		
		if (process_allocation[i] == -1)
			printf("%17d |%17d |%17s |%17s |\n", process_ids[i], process_requirements[i], "Not Allocated", "----");
		else
			printf("%17d |%17d |%17d |%17d |\n", process_ids[i], process_requirements[i], process_allocation[i], block_remaining[j]);
	}
	
	cout << "\n\n";
	
}



void best_fit(int& nb_blocks, int* block_ids, int* block_sizes, int& nb_processes, int* process_ids, int* process_requirements){
	
	int* block_remaining = new int[nb_blocks];
	int* block_ids_copy = new int[nb_blocks];
	int* process_allocation = new int[nb_processes];
	
	for(int i=0; i<nb_blocks; i++){
		block_remaining[i] = block_sizes[i];
		block_ids_copy[i] = block_ids[i];
	}
	
	
	cout << "\n\nBest Fit:\n";
	printf("%17s |%17s |%17s |%17s |\n", "Process Id", "Process Req.", "Allocated Block", "Block Rem.");
	
	for (int i=0; i<nb_processes; i++){
		sort_2_arrays(nb_blocks, block_ids_copy, block_remaining);
		
//		cout << "-----------------------------------------------"<<endl;
//		for(int j=0; j<nb_blocks; j++){
//			cout << block_remaining[j] << endl;
//		}
//		cout << "-----------------------------------------------"<<endl;
		
		process_allocation[i] = -1;
		int j;
		for(j=0; j<nb_blocks; j++)
			if (process_requirements[i] <= block_remaining[j]){
				process_allocation[i] = block_ids_copy[j];
				block_remaining[j] -= process_requirements[i];
				break;
			}
		
		if (process_allocation[i] == -1)
			printf("%17d |%17d |%17s |%17s |\n", process_ids[i], process_requirements[i], "Not Allocated", "----");
		else
			printf("%17d |%17d |%17d |%17d |\n", process_ids[i], process_requirements[i], process_allocation[i], block_remaining[j]);
	}
	
	cout << "\n\n";
					
}



void first_fit(int& nb_blocks, int* block_ids, int* block_sizes, int& nb_processes, int* process_ids, int* process_requirements){
	
	int* block_remaining = new int[nb_blocks];
	int* process_allocation = new int[nb_processes];
	
	for(int i=0; i<nb_blocks; i++){
		block_remaining[i] = block_sizes[i];
	}
	
	
	cout << "\n\nFirst Fit:\n";
	printf("%17s |%17s |%17s |%17s |\n", "Process Id", "Process Req.", "Allocated Block", "Block Rem.");
	
	for (int i=0; i<nb_processes; i++){
		process_allocation[i] = -1;
		
		int j;
		for(j=0; j<nb_blocks; j++)
			if (process_requirements[i] <= block_remaining[j]){
				process_allocation[i] = block_ids[j];
				block_remaining[j] -= process_requirements[i];
				break;
			}
		
		if (process_allocation[i] == -1)
			printf("%17d |%17d |%17s |%17s |\n", process_ids[i], process_requirements[i], "Not Allocated", "----");
		else
			printf("%17d |%17d |%17d |%17d |\n", process_ids[i], process_requirements[i], process_allocation[i], block_remaining[j]);
	}
	
	cout << "\n\n";
						
		
	
}


