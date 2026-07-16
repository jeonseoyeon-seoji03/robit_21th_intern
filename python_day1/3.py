#if-elif문의 반복 대신, 함수와 딕셔너리를 이용하여 프로그래밍함.
#리스트의 메서드를 구현할 함수 정의
def list_append (list, parts):
    list.append(parts[1])

def list_insert (list, parts):
    list.insert(int(parts[1]),parts[2])
    
def list_remove (list, parts):
    try:
        list.remove(parts[1])
    except ValueError:
        print("존재하지 않는 값은 삭제할 수 없습니다.")
#존재하지 않는 값을 remove 할 때의 예외처리
 
def list_pop (list, parts):
    try:
        list.pop(int(parts[1]))
    except IndexError:
        print("인덱스 범위를 벗어났거나, 리스트가 비어있습니다.")
#리스트가 비어있거나, 인덱스 범위를 벗어난 경우의 예외처리

def len_print (list, parts):
    print(len(list))

def list_print (list, parts):
    print(list)

def list_clear (list, parts):
    list.clear()

n_list=[]
c_collect= {"append": list_append, "insert": list_insert, "remove": list_remove, 
                "pop": list_pop, "len": len_print, "print": list_print, "clear": list_clear }
#리스트의 메서드를 구현한 함수를 모아둔 딕셔너리    
while True:
    input_line = input()
    input_parts = input_line.split()
    command = input_parts[0]
#띄어쓰기 단위로 문자열을 분리하여 주어진 명령어를 수행하게끔 코딩함.
    if command in c_collect:
        c_collect[command](n_list, input_parts)
        #사용자가 입력한 명령어가 딕셔너리 내에 존재할 경우, 함수를 호출함
    else:
        print("명령어를 확인할 수 없습니다. 다시 입력하십시오.")
        #존재하지 않을 경우, 안내 문구를 출력함