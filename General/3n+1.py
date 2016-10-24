n=int(input())
num=0

while n!=1:
    if n%2==0:
        n=n/2
    elif n%2==1:
        n=n*3+1
    num+=1
print(num)
