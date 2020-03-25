pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]

capacity = 4


def fifo():
    print("FIFO:\n")
    cache_block = []

    page_faults = 0

    for p in pages:
        print("Finding", p, ": ", end="")
        if p not in cache_block:
            print("Miss\t Cache: ", end=" ")
            page_faults += 1
            if len(cache_block) < capacity:
                cache_block.append(p)
            else:
                cache_block.pop(0)
                cache_block.append(p)
        else:
            print ("Hit \t Cache: ", end=" ")
        
        for q in cache_block:
            print(q, end="\t")
        print("")

    print("No. of Page Faults:", page_faults)



def lru():
    print("LRU:\n")
    cache_block = []

    page_faults = 0

    for p in pages:
        print("Finding", p, ": ", end="")
        if p not in cache_block:
            print("Miss\t Cache: ", end=" ")
            page_faults += 1
            if len(cache_block) < capacity:
                cache_block.insert(0, p)
            else:
                cache_block.pop()
                cache_block.insert(0, p)
        else:
            cache_block.remove(p)
            cache_block.insert(0, p)
            print ("Hit \t Cache: ", end=" ")
        
        for q in cache_block:
            print(q, end="\t")
        print("")

    print("No. of Page Faults:", page_faults)

def lfu():
    print("LFU:\n")
    cache_block = []
    freq = dict()
    
    page_faults = 0

    for p in pages:
        print("Finding", p, ": ", end="")
        freq.setdefault(p, 0)

        if p not in cache_block:
            print("Miss\t Cache: ", end=" ")
            page_faults += 1
            if len(cache_block) < capacity:
                freq[p] += 1
                cache_block.append(p)
            else:
                lf = cache_block[0]
                for p_cb in cache_block:
                    if freq[p_cb] < freq[lf]:
                        lf = p_cb
                
                cache_block.remove(lf)
                freq[lf] = 0
                cache_block.append(p)
                freq[p] += 1
        else:
            freq[p] += 1
            print ("Hit \t Cache: ", end=" ")
        
        for q in cache_block:
            print(q, end="\t")
        print("")
    
    print("No. of Page Faults:", page_faults)



print ("Choose:")
print("1. FIFO")
print("2. LRU")
print("3. LFU")

while(True):
    choice = int(input(">> "))

    if choice == 1:
        fifo()
    elif choice == 2:
        lru()
    elif choice == 3:
        lfu()
    else:
        print("Invalid input!")
    
    print("\n", "_"*100, "\n")
