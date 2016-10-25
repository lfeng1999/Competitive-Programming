n = int(input())
x = int(input())
c = 0
r = 0
while True:
    c += n
    if n+r < x:
         break
    n,r = (n+r)//x,(n+r)%x
    
print(c)