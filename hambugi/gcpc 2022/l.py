import sys

l,w,n = map(int,sys.stdin.readline().split())

def makeSq(a,b):
    alpha = 65
    for i in range(l//a):
        alphaList = ''
        for k in range(alpha, alpha+(w//b),1):
            alphaList += (chr(k)*b)
        for _ in range(a):
            print(alphaList)
        alpha += w//b

s = l*w/n
if s % 1 != 0 :
    print('IMPOSSIBLE')
else:
    s = int(s)
    for i in range(1,s+1):
        a = i
        b = s / a
        if b % 1 == 0 and l % a == 0 and w % b == 0 :
            makeSq(a,int(b))
            exit()