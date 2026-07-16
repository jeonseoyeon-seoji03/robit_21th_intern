robot_status = [{"name" : "mobliebot", "battery": 82, "position": (1.2, 0.5),"distance": 0.8},
                {"name" : "drone", "battery": 18, "position": (0.3, 1.5),"distance": 0.4},
                {"name" : "manipulator", "battery": 45, "position": (2.0, 1.0),"distance": 1.2},]
#함수를 이용하여 기능별로 코드를 분류함.
def robot_name (i):
    ro_name = robot_status[i]["name"]
    print(f"[{ro_name}]")

#상태 분류 또한 함수 안에서 진행함.
def battery_status (i):
    battery = robot_status[i]["battery"]
    if (battery >= 60):
        battery_left= "배터리 충분"
    elif (battery >=20):
        battery_left= "배터리 주의"
    else:
        battery_left= "충전 필요"
    print(f"배터리: {battery_left}")

def position_unpacking(i):
 x,y=robot_status[i]["position"]
 print(f"위치: x={x}, y={y}")

def forward_status(i):
    dist=robot_status[i]["distance"]
    if (dist >= 0.5):
        dist_status= "전진 가능"
    else:
        dist_status= "장애물 감지"
    print(f"상태: {dist_status}\n")

#반복문과 함수를 사용하여 결과값을 출력함.
for i in range (3):
    robot_name (i)
    battery_status (i)
    position_unpacking(i)
    forward_status(i)