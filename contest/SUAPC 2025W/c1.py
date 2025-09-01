import sys

n = int(sys.stdin.readline())
fir_roads = list(map(int,sys.stdin.readline().split()))
roads = fir_roads[1:] # 0 제외
k = int(sys.stdin.readline())
fir_keys = sys.stdin.readline()
keys = fir_keys.split("J")

if fir_roads[0] != 0 :
    print("NO")
    exit()
if ("J" not in fir_keys) and (0 != len(roads)):
    print("NO")
    exit()


keys[-1] = keys[-1][:-1]
if keys[-1] == '':
    keys.pop()
#print(keys)##############

key_moves = []
for key in keys:
    reresult = []
    key_move = 0

    for letter in key:
        if letter == "D":
            reresult.append(-1)
        if letter == "A":
            key_move = key_move + 1

    reresult.append((key_move))
    key_moves.append(reresult)

# real_key = key_moves #얕은복사
if fir_keys[-2] != "J":
    last_chance = [max(key_moves[0]) + max(key_moves[-1])]
    if (-1 in key_moves[0]) or (-1 in key_moves[-1]):
        last_chance.append(-1)
    key_moves[-1] = last_chance


#print(key_moves)###############

def is_alive(now, keyNum):
    #print(now,key_moves[keyNum] )###############
    if now >= 0 :
        if max(key_moves[keyNum]) >= now :
            return True
        return False
    if (now in key_moves[keyNum]):
        return True
    return False
    

key_num = 0
for road in roads:
    if not is_alive(road, key_num):
        print("NO")
        exit()

    if len(key_moves) == 1:
        key_num = 0
    else:
        if fir_keys[-2] != "J":
            if len(key_moves)-1 == key_num:
                key_num = 1
            else:
                key_num += 1
        else:
            if len(key_moves)-1 == key_num:
                key_num = 0
            else:
                key_num += 1


print("YES")
