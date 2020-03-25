disk_size = 200
track_requests = [176, 79, 34, 60, 92, 11, 41, 114]
head_position_initial = 50

def fcfs():
    head_position = head_position_initial
    no_of_seeks = 0

    for tr in track_requests:
        diff = abs(tr - head_position)
        head_position = tr
        no_of_seeks += diff
    
    print("Total no. of seek:", no_of_seeks)

    print("Seek Sequence:", end=" ")
    for tr in track_requests:
        print(tr, end="\t")



def scan(direction = "left"):
    head_position = head_position_initial

    left_list = []
    right_list = []

    if direction == "left":
        left_list.append(0)
    else:
        right_list.append(disk_size-1)

    for tr in track_requests:
        if tr <= head_position:
            left_list.append(tr)
        else:
            right_list.append(tr)

    left_list = sorted(left_list)[::-1]
    right_list = sorted(right_list)

    seek_sequence = []
    no_of_seeks = 0

    while(len(left_list) or len(right_list)):
        if direction == "left":
            if len(left_list):
                tr = left_list.pop(0)
                seek_sequence.append(tr)
                
                diff = abs(head_position - tr)
                no_of_seeks += diff

                head_position = tr
            
            if not len(left_list):
                direction = "right"

        if direction == "right":
            if len(right_list):
                tr = right_list.pop(0)
                seek_sequence.append(tr)

                diff = abs(head_position - tr)
                no_of_seeks += diff

                head_position = tr
            
            if not len(right_list):
                direction = "left"
    
    print("Total no. of seek:", no_of_seeks)

    print("Seek Sequence:", end=" ")
    for tr in seek_sequence:
        print(tr, end="\t")




def c_scan():
    head_position = head_position_initial

    left_list = []
    right_list = []

    left_list.append(0)
    right_list.append(disk_size-1)

    for tr in track_requests:
        if tr <= head_position:
            left_list.append(tr)
        else:
            right_list.append(tr)

    left_list = sorted(left_list)
    right_list = sorted(right_list)

    seek_sequence = []
    no_of_seeks = 0

    while(len(right_list)):
        tr = right_list.pop(0)
        seek_sequence.append(tr)

        diff = abs(head_position - tr)
        no_of_seeks += diff

        head_position = tr

    head_position = 0

    while(len(left_list)):
        tr = left_list.pop(0)
        seek_sequence.append(tr)

        diff = abs(head_position - tr)
        no_of_seeks += diff

        head_position = tr
    
    print("Total no. of seek:", no_of_seeks)

    print("Seek Sequence:", end=" ")
    for tr in seek_sequence:
        print(tr, end="\t")



print("Initial position of head:", head_position_initial, "\n")
print("Choose:")
print("1: FCFS")
print("2: SCAN")
print("3: C-SCAN")
while(True):
    choice = int(input(">> "))
    if choice == 1:
        fcfs()
    elif choice == 2:
        scan("left")
    elif choice == 3:
        c_scan()
    else:
        print("Please enter a valid input.", end="")
    
    print("\n", "_"*100, "\n")