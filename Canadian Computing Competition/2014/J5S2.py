num=int(input())
class1=input().split()
class2=input().split()
pairs=[]
pair='good'
for m in range(num):
    pairs.append([class1[m],class2[m]])
pairs.sort()

for m in pairs:
    m.reverse()
    if pairs.count(m)!=2:
        pair='bad'
    m.reverse()
print(pair)
