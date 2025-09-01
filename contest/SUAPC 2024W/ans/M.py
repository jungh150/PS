n=int(input())
arr_list=input()
track=input()
res=0

for i in arr_list:
    if i == track:
        res+=1

print(res)