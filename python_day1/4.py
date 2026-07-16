maze=[[1,1,1,1,1,1,1,1,1,1],[1,0,0,1,0,0,0,0,0,1],[1,0,0,1,1,1,0,0,0,1],
      [1,0,0,0,0,0,0,1,0,1],[1,0,0,0,0,0,0,1,0,1],[1,0,0,0,0,1,0,1,0,1],[1,0,0,0,0,1,2,1,0,1],
      [1,0,0,0,0,1,0,0,0,1],[1,0,0,0,0,0,0,0,0,1],[1,1,1,1,1,1,1,1,1,1]]

#입력된 미로를 출력하는 코드
for row in maze:
    for value in row:
        print(value, end=" ")
    print()

row, value= 1, 1

#이동 가능 여부를 확인하는 함수
def can_move_down (maze, row, value):
    return maze[row+1][value] !=1

def can_move_right(maze, row, value):
    return maze[row][value+1] !=1

while True:
    #시작 지점에 먹이가 있을 가능성을 고려함. 
    if maze[row][value] == 2:
        print("먹이 발견, 프로그램을 종료합니다.\n")
        maze[row][value]=9
        break
    #아래 if문에 maze[row][value]=9를 넣을 경우, 먹이를 확인하지 못한 상태에서 9로 변환됨. 해당 오류를 막기 위해 아래와 같은 위치에 배치함.
    maze[row][value]=9

    if can_move_right(maze, row, value):
        value+=1
    elif can_move_down(maze, row, value):
        row+=1
    else:
        print("더 이상 이동할 수 없습니다. 프로그램을 종료합니다.")
        break
#미로 속 개미의 이동경로를 보여주기 위해 출력하는 코드
for row in maze:
    for value in row:
        print(value, end=" ")
    print()