def hanoi(size,slot1,slot2,highest):
    if size==1:
        print(x[slot1]+x[slot2])
    else:
        hanoi(size-1,slot1,6-slot1-slot2,size-1)
        hanoi(1,slot1,slot2,size)
        hanoi(size-1,6-slot1-slot2,slot2,size-1)



stack=int(input())
x=dict()
x[1]='A'
x[2]='B'
x[3]='C'

hanoi(stack,1,3,stack)
