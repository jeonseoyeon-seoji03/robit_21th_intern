def add_log(robot_name, battery, logs=None):
    if logs is None:
        logs=[]
    #리스트인 logs는 가변함. 원래 코드와 같이 매개변수란에 logs=[]이 존재할 경우, 첫번째 함수 호출 시에만 빈 리스트가 생성됨.
    #첫번째 함수 실행 이후 변형된 리스트가 다음번 호출에도 재사용되어 로그가 누적되는 문제가 발생하게 됨.
    #따라서, 매개변수란에는 logs를 두되, 인자를 넘기지 않는 경우 초기화될 수 있도록 위와 같이 수정함.

    log = robot_name + " battery: " + str(battery)
    #log의 타입은 str이므로 int 형태인 battery의 값을 str형으로 바꾸어야 함.
    logs.append(log)
    return logs
print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))