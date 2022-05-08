from operator import xor

st = 0

with open('xor.out') as my_object, open('xor4.out') as ans_object, open('xor3.in') as input_object:
    row = 0
    no_num = 0
    for my_line, ans_line in zip(my_object, ans_object):
        row += 1
        if my_line[0] == 'N': no_num += 1
        if my_line != ans_line:
            if my_line[0] == "Y" or my_line[0] == "N":
                print('MY: ' + my_line + ' ANS: ' + ans_line + ' in ' + str(row))
                st = 1
            # else:
            #     input_row = 0
            #     wr = 0
                # for line in input_object:
                #     input_row += 1
                #     if input_row == 0: 
                #         continue
                #     else:
                #         ws = str(line).split()
                #         res = str(my_line + ' 0 0').split()
                #         Ans = 0
                        # for i in range(int(ws[0]), int(ws[1]) + 1):
                        #     Ans = Ans ^ int(res[i - 1])
                        # if Ans != int(ws[-1]):
                        #     # print(Ans, ws[0], ws[1], ws[-1])
                        #     wr += 1
                # print(wr, no_num)
    if st == 0:
        print("OK")