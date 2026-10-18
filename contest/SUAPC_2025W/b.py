import sys

my_stack = []
result_cnt = 0
N = int(sys.stdin.readline())
skeep_list = list(sys.stdin.readline())[:-1]

def is_this_skeep():
    #print(my_stack)#####################
    if not my_stack[-5] == "s":
        return False
    if not ( my_stack[-4] == "k" or my_stack[-4] == "*"):
        return False
    if not ( my_stack[-3] == "e" or my_stack[-3] == "*"):
        return False
    if not ( my_stack[-2] == "e" or my_stack[-2] == "*"):
        return False
    if not ( my_stack[-1] == "p" or my_stack[-1] == "*"):
        return False
    return True

def see_top_5():
    global result_cnt
    if len(my_stack) < 5 :
        return

    if is_this_skeep() :
        result_cnt += 1
        my_stack.pop()
        my_stack.pop()
        my_stack.pop()
        my_stack.pop()
        my_stack.pop()
        my_stack.append("*")
        see_top_5()

for i in range(len(skeep_list)):
    #print(my_stack)#####################

    my_stack.append(skeep_list[i])
    
    if len(my_stack) >= 5 :
        see_top_5()
    
# while len(my_stack) >= 5 :
#     print(my_stack)#####################

#     see_top_5()

print(result_cnt)