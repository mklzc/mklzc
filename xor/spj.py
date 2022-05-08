with open('xor.out') as my_object, open('xor3.out') as ans_object, open('xor3.in') as input_object:
    row = 0
    for my_line, ans_line in zip(my_object, ans_object):
        row += 1
        # print(row)
        if my_line != ans_line:
            if my_line == "Yes" or my_line == "No":
                print(my_line + ' ' + ans_line + ' in ' + str(row))
                
    