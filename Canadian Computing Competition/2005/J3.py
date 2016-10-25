turns=[]
dest=[]
while True:
    Nturn=input()
    if Nturn=='R':
        Nturn='LEFT'
    if Nturn=='L':
        Nturn='RIGHT'
    turns=[Nturn]+turns
    Ndest=input()
    dest=dest+[Ndest]
    if Ndest=='SCHOOL':
        break
dest.reverse()
for a in range(len(turns)-1):
    print('Turn',turns[a],'onto',dest[a+1],'street.')
print('Turn',turns[a+1],'into your HOME.')
    
