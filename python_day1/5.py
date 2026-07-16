def compress(text):
    te_len=len(text)
    result = ""
    count = 1
    for i in range (1, te_len):
        if text[i] == text [i-1]:
            count+=1
            #같은 문자가 반복되는 횟수 측정
        else:
         result= result+ text[i-1]+str(count)
         count = 1
         #문자+문자가 반복된 횟수를 결과값에 포함시키는 코드
    result= result + text[-1]+str(count)
    #마지막 문자가 반복된 횟수가 반복문 내에서 결과값에 포함되지 않는 것을 보완하는 코드
    if len(result)> te_len: 
        return text
    #압축 결과가 원본보다 길어질 경우 원본을 반환하는 코드
    else:
        return result

def is_valid_code(code):
    c_len= len(code)
    if code =="":
        return False
    i=0
    while i < c_len:
        if not code[i].isalpha():
            return False
        i+=1
        num=""
        #첫 글자가 알파벳이 아닌 경우 False를 반환

        while i < c_len and code[i].isdigit():
            num= num + code[i]
            i+=1
            
        if num == "":
            return False
            #이어지는 글자가 숫자가 아닌 경우 false 반환
        elif int(num) < 1:
            return False
            #두번째 글자가 숫자이지만 1 이상이 아닐 경우 false 반환
    return True

def decompress(code):
    if not is_valid_code(code):
        return "ERROR"
    # decompress의 실행 전 검증 역할로 구현함.
    result = ""
    i=0
    c_len= len(code)
    while i < c_len:
        letter=code[i]
        i+=1
        num= ""
        while i<c_len and code[i].isdigit():
            num=num+code[i]
            i+=1
        count = int(num)
        result = result+letter*count
        #code속 숫자를 int로 변환하여 원래 문자열로 복원시키는 코드.
    return result

print(compress("aaabbccccd"))
print(decompress("a3b2c4d1"))
print(decompress("a0"))
print(decompress("3a"))
print(decompress("ab3"))
print(compress("abcde"))