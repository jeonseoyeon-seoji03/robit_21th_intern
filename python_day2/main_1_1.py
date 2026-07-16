import csv 
import json

try:
    with open ("students.csv", "r", newline="", encoding="cp949") as file:
        reader = csv.reader(file) # 하위 폴더인 0714에 속한 students의 내용을 읽고자 함.
        header = next(reader) # 첫 행을 건너뛴다.
        clear_students=[] #유효한 행의 정보를 담을 리스트를 만든다.
        for row in reader:
            name, score_str = row
            try:
                clear_score= int (score_str) #점수가 숫자인지 확인

            except ValueError:
                print(f"{name}: {score_str}가 숫자로 변환되지 못했습니다.")
                continue
            else:
                if not (0<= clear_score <=100):
                    print(f"{clear_score}(은)는 허용 범위를 벗어난 점수입니다.")
                    continue #int로 바뀐 점수가 범위 내에 위치하는지 확인
            clear_students.append((name, clear_score)) #유효한 행의 정보를 리스트에 추가한다.

except FileNotFoundError:
    print("파일을 찾을 수 없습니다.")
    exit() #파일을 찾을 수 없는 경우, 다음 코드가 진행되며 오류가 발생하는 문제를 해결하기 위해 작성함.


with open("clean_students.csv","w", newline="", encoding="utf-8") as f:
    writer= csv.writer(f)
    writer.writerow(["name", "score"])
    writer.writerows (clear_students)

scores= []
for name, score in clear_students:
    scores.append(score)

if not scores: 
    print("유효한 숫자가 존재하지 않습니다.")
    exit() #유효한 행이 존재하지 않을 때 다음 코드가 진행되며 ZerodivisionError가 발생하는 문제를 해결하기 위해 작성함.
else:
    summary={"people":len(clear_students),
        "average":sum(scores)/len(clear_students),
        "max": max(scores)}
    #json 파일에 넣을 딕셔너리를 만듦.
    with open ("summary.json", "w",encoding="utf-8") as fi:
        json.dump (summary, fi, ensure_ascii=False, indent=2)
        #인원수, 평균, 최고점을 json 파일에 작성함.



