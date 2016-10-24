x=int(input())

y=[]
for m in range(x):
    y.append(int(input()))
y.sort()

for m in range(len(y)):
    print(y[m])
