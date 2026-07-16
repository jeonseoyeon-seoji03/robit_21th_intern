#과제 1_ 추가 구현 파일입니다.
import csv 
import json

try:
    with open ("students.csv", "r", newline="", encoding="cp949") as file:
        reader = csv.DictReader(file) # 하위 폴더인 0714에 속한 students의 내용을 읽고자 함.
        #DictReader는 첫 줄을 헤더로 인식하므로 main_1_1에서 사용한 next(header)를 사용하지 않는다.
        clear_students=[] #유효한 행의 정보를 담을 리스트를 만든다.
        for row in reader:
            name=row["name"] 
            score_str=row["score"]
            try:
                clear_score= int (score_str) #점수가 숫자인지 확인

            except ValueError:
                print(f"{name}: {score_str}가 숫자로 변환되지 못했습니다.")
                continue
            else:
                if not (0<= clear_score <=100):
                    print(f"{clear_score}(은)는 허용 범위를 벗어난 점수입니다.")
                    continue #int로 바뀐 점수가 범위 내에 위치하는지 확인
            clear_students.append({"name": name, "score": clear_score}) #유효한 행의 정보를 리스트에 추가한다. 
            #main_1_1에서는 튜플로 저장했으나, 2에서는 딕셔너리로 저장하여 편의성을 증가시키고자한다.

except FileNotFoundError:
    print("파일을 찾을 수 없습니다.")
    exit() #파일을 찾을 수 없는 경우, 다음 코드가 진행되며 오류가 발생하는 문제를 해결하기 위해 작성함.


with open("clean_students2.csv","w", newline="", encoding="utf-8") as f:
    writer= csv.DictWriter(f,fieldnames=["name","score"])
    writer.writeheader()
    writer.writerows (clear_students)

scores= []
for student in clear_students:
    scores.append(student["score"])

if not scores: 
    print("유효한 숫자가 존재하지 않습니다.")
    exit() #유효한 행이 존재하지 않을 때 다음 코드가 진행되며 ZerodivisionError가 발생하는 문제를 해결하기 위해 작성함.
else:
    summary={"people":len(clear_students),
        "average":sum(scores)/len(clear_students),
        "max": max(scores)}
    #json 파일에 넣을 딕셔너리를 만듦.
    with open ("summary2.json", "w",encoding="utf-8") as fi:
        json.dump (summary, fi, ensure_ascii=False, indent=2)
        #인원수, 평균, 최고점을 json 파일에 작성함.