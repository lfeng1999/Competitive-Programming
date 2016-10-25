a=int(input())
b=int(input())
norm=int(input())

if a>norm:
    print("Bob overdoses on day 1.")
elif (a/2)+b>norm:
    print("Bob overdoses on day 2.")
else:
    print("Bob never overdoses.")