print("\nDeadlock Avoidance: Banker's Algorithm")


avail_initial = [3,2,4]


# test case with impossible processe (P2)
# allocation = [
#     [1,0,1],
#     [0,0,1],
#     [0,0,0],
#     [0,0,0],

# ]

# max = [
#     [2,1,3],
#     [1,3,2],
#     [1,0,0],
#     [3,2,4],

# ]

# test case with no impossible processes
allocation = [
    [1,0,1],
    [0,1,0],
    [1,0,1],

]

max = [
    [2,1,3],
    [3,2,4],
    [1,0,0],


]

need = [ [max[i][j] - allocation[i][j] for j in range(len(max[i]))] for i in range(len(max)) ]


avail = [avail_initial[i]-sum( [allocation[j][i] for j in range(len(allocation))] ) for i in range(len(avail_initial))]
# for i in range(len(allocation)):
#     for j in range(len(allocation[i])):
#         avail[j] = avail_initial[j] - allocation[i][j]
print(avail)

process_doable = [ not any([max[i][j] > avail_initial[j]  for j in range(len(max[i]))]) for i in range(len(max))]

process_done = [not p for p in process_doable]

for i in range(len(process_doable)):
    if not process_doable[i]:
        print("P", i+1, " needs more resources then available! Freeing its allocated resources.", sep="")
        for j in range(len(avail)):
            avail[j] += allocation[i][j]
            allocation[i][j] = 0


print("\nExecuting other processes:")
print("Safe Sequence: ", end="")

while(not all(process_done)):
    process_to_complete_index = None
    for i in range(len(need)):

        if process_done[i]:
            continue

        do_this = True

        for j in range(len(need[i])):
            if need[i][j] > avail[j]:
                do_this = False
                break
        
        if do_this:
            process_to_complete_index = i
            break

    for i in range(len(avail)):
        avail[i] += allocation[process_to_complete_index][i]
        allocation[process_to_complete_index][i] = 0
        need[process_to_complete_index][i] = 0
        process_done[process_to_complete_index] = True
    
    print("P", process_to_complete_index+1, " | ", sep="", end="")

