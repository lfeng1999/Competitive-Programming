num=int(input())
rope=[]
for m in range(num):
    rope.append(list(input()))
for m in rope:
    for n in range(m.count(" ")):
        m.remove(" ")
rope.reverse()
end=""
for m in range(len(rope)):
    if m%2==1:
        rope[m].reverse()
    for k in rope[m]:
        end+=k
print(end)
