def breakp(x,y):
    if x==1 or y==1:
        return max(x,y)-1
    elif max(x,y)%2==0:
        return breakp(max(x,y)/2,min(x,y))+breakp(max(x,y)/2,min(x,y))+1
    elif max(x,y)%2==1:
        return breakp((max(x,y)-1)/2,min(x,y))+breakp((max(x,y)+1)/2,min(x,y))+1

num=int(input())
testcase=[]
for m in range(num):
    testcase.append(input().split())

for m in testcase:
    print(int(breakp(int(m[0]),int(m[1]))))
