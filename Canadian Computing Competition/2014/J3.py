Ant=100
Dav=100
scores=[]
num=int(input())
for m in range(num):
    scores.append(list(map(int,input().split())))
for m in scores:
    if m[1]>m[0]:
        Ant-=m[1]
    elif m[0]>m[1]:
        Dav-=m[0]
print(Ant)
print(Dav)
