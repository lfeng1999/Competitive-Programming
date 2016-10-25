numbers=[]
for m in range(10):
    x=int(input())
    x=x%42
    numbers.append(x)
print(len(list(set(numbers))))