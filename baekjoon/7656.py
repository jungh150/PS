import sys
import re
input = sys.stdin.readline

s = input()
sts = re.findall(r'[^.?]+[.?]?', s)

for st in sts:
    nst = st.strip()
    if len(nst) > 0 and nst[-1] == "?":
        print("Forty-two ", end = "")
        print(nst[5:-1], end = ".\n")