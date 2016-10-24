num=int(input())

age=[]
for m in range(num):
    age.append(int(input()))

age.sort()
numt=int(input())
query=[]

for m in range(numt):
    query.append(int(input()))

for m in range(numt):
    print(age[query[m]-1])
