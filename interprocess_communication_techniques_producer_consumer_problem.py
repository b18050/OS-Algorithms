buffer_size = int(input("Enter Buffer Size: "))
buffer_ = []
b = 0

full = 0
empty = buffer_size
mutex = 1

def wait(w):
    return w-1

def signal(s):
    return s+1

def display_buffer():
    print("Buffer: ", end="")
    for x in buffer_:
        print(x, end="\t")
    print ("")

def produce():
    global mutex
    global empty
    global full
    global b
    if mutex == 1 and empty > 0:
        mutex = wait(mutex)
        empty = wait(empty)
        full = signal(full)

        b += 1
        print("Produced:", b)
        buffer_.append(b)
        mutex = signal(mutex)
    else:
        print("Buffer is full!")

    

def consume():
    global mutex
    global full
    global empty
    global b
    if mutex == 1 and full > 0:
        mutex = wait(mutex)
        full = wait(full)
        empty = signal(empty)

        x = buffer_.pop(0)
        print("Consumed:", x)
        mutex = signal(mutex)
    else:
        print("Buffer is empty!")
    



print("Enter:")
print("1: Producer")
print("2: Consumer")
while(True):
    choice = int(input(">> "))
    if choice == 1:
        produce()
        display_buffer()

    elif choice == 2:
        consume()
        display_buffer()

    else:
        print("\nEnter valid option.\n")

