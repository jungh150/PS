from sys import stdin

y = 2014
m = 4
d = 2
isLeapYear = False

n = int(stdin.readline())

while n // 366 != 0:
    n -= 365
    y += 1
    if ((y % 4 == 0) and (y % 100 != 0)) or (y % 400 == 0):
        n -= 1
        if m != 2:
            if ((m < 8) and (m % 2 == 1)) or ((m > 7) and (m % 2 == 0)):
                if d == 32:
                    m += 1
                    d = 1
            else:
                if d == 31:
                    m += 1
                    d = 1
        if m == 13:
            y += 1
            m = 1

if ((y % 4 == 0) and (y % 100 != 0)) or (y % 400 == 0):
    isLeapYear = True

while n != 1:
    n -= 1
    d += 1
    if m == 2:
        if isLeapYear:
            if d == 30:
                m += 1
                d = 1
        else:
            if d == 29:
                m += 1
                d = 1
    elif ((m < 8) and (m % 2 == 1)) or ((m > 7) and (m % 2 == 0)):
        if d == 32:
            m += 1
            d = 1
    else:
        if d == 31:
            m += 1
            d = 1
    if m == 13:
        y += 1
        m = 1
        if ((y % 4 == 0) and (y % 100 != 0)) or (y % 400 == 0):
            isLeapYear = True
        else:
            isLeapYear = False

print(str(y) + "-" + format(m, '02') + "-" + format(d, '02'))