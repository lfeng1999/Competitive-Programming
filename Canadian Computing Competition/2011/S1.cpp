N=int(input())
T=0
S=0
for i in range(N):
    k=input()
    T+=k.count('t')
    T+=k.count('T')
    S+=k.count('s')
    S+=k.count('S')
if (T>S):
    print("English")
else:
    print("French")