for qq in range(int(input())):

    mydict = {}
    text = input().split()
    cnt = 1
    while text!=[]:
        for x in text:
            if x in mydict:
                print(mydict[x], end = " ")
            else:
                print(x, end = " ")
                mydict[x] = cnt
                cnt+=1
        print()
        text = input().split()