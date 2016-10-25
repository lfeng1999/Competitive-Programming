def play1(money,count1):
    if count1==35:
        money+=30
    count
    return money
def play2(money,count1):
    if count1==100:
        money+=60
    return money
def play1(money,count1):
    if count1==10:
        money+=9
    return money
        


money=int(input())
count=[]
for m in range(3):
    count.append(int(input()))

times=0
while money!=0:
    if money!=0:
        money-=1
        count[0]+=1
        times+=1
        if count[0]==35:
            count[0]=0
            money+=30
    if money!=0:
        money-=1
        count[1]+=1
        times+=1
        if count[1]==100:
            count[1]=0
            money+=60
    if money!=0:
        money-=1
        count[2]+=1
        times+=1
        if count[2]==10:
            count[2]=0
            money+=9
print("Martha plays "+str(times)+" times before going broke.")
