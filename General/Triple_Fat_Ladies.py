t=int(input())

for m in range(t):
    k=int(input())
    while True:
        k+=1
        n=k**3
        if n%1000==888:
            print(k)
            break
    
