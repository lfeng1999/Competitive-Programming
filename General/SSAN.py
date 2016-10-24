b=[int(str(u)+str(z)) for u in range(10) for z in range(u+1,10)]
c=[int(str(u)+str(v)+str(w)) for u in range(1,10) for v in range(u+1,10) for w in range(v+1,10)]
d=[int(str(u)+str(v)+str(w)+str(x)) for u in range(1,10) for v in range(u+1,10)
   for w in range(v+1,10) for x in range(w+1,10)]
e=[int(str(u)+str(v)+str(w)+str(x)+ str(y)) for u in range(1,10) for v in range(u+1,10)
   for w in range(v+1,10) for x in range(w+1,10)
   for y in range(x+1,10)]
x=[int(str(u)+str(v)+str(w)+str(x)+str(y)+str(z)) for u in range(1,10) for v in range(u+1,10) for w in range(v+1,10) for x in range(w+1,10) for y in range(x+1,10) for z in range(y+1,10)]
x=b+c+d+e+x
z=[(i+1)**2 for i in range(1000)]
real=[]
z.remove(1)
count=0
for m in range(len(x)):
    for n in z:
        if x[m-count]%n==0:
            x.remove(x[m-count])
            count+=1
x=list(map(str,x))
for m in x:
    num=0
    for n in m: num+=int(n)
    if int(num)%2==0:
        real.append(int(m))

ranges=[]
for k in range(5):
    x=input().split()
    ranges.append(list(map(int,x)))
for m in ranges:
    count=0
    for n in real:
        if n>=m[0] and n<=m[1]:
            count+=1
    print(count)
