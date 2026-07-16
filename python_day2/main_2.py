#matplotlib  3.11.0, requests 2.34.2
#위 라이브러리를 사용하여 시간대 별 기온을 csv 파일로 저장 후, 그래프를 작성하는 프로그램을 작성할 것이다.

import requests
import matplotlib.pyplot as plt
import csv
plt.rcParams['font.family'] = 'Malgun Gothic'
#그래프 속 한글이 깨지는 문제를 해결하기 위해 폰트를 지정함.

def bring_data(url):
    try:
        content= requests.get(url)
    except requests.exceptions.RequestException as e:
        print(f"데이터를 가져오는데에 실패했습니다: {e}")
        exit() #데이터를 가져오는데에 실패할 경우를 대비한 코드
    data= content.json() #받아온 content를 딕셔너리로 바꿈.
    return data

def make_csv(time_labels, temp_list):   
    with open("seoul_weather.csv","w", newline="", encoding="utf-8") as f:
        writer= csv.writer(f)
        writer.writerow(["time", "temperature"])
        for time, temp in zip(time_labels, temp_list):
            writer.writerow ([time, temp]) #파일 내에 시간과 기온 정보를 저장

def graph_weather(time_labels, temp_list):
    avg_temp = sum(temp_list) /len(temp_list)
    max_temp = max(temp_list)
    min_temp = min(temp_list)
    max_index = temp_list.index(max_temp)
    min_index = temp_list.index (min_temp) # 최고, 최저 온도에 점을 찍기 위해 위치를 인덱스함
    plt.plot(range(len(temp_list)), temp_list)
    plt.scatter(max_index, max_temp,color="red",zorder=5,label=f"최고 온도: {max_temp}°C")
    plt.scatter(min_index, min_temp,color="blue",zorder=5,label=f"최저 온도: {min_temp}°C")
    plt.axhline(y=avg_temp, color='green', linestyle='--', label=f'평균 온도: {avg_temp:.1f}°C')
    plt.xticks(range(len(temp_list)),time_labels,rotation=90, fontsize=6 ) #전체화면 기준 x축이 겹치지 않도록 코드를 작성함.
    plt.legend()
    plt.show()

def main():
    url="https://api.open-meteo.com/v1/forecast?latitude=37.57&longitude=126.98&hourly=temperature_2m&timezone=Asia%2FSeoul"
    data=bring_data(url)
    time_list=data["hourly"]["time"]
    temp_list=data["hourly"]["temperature_2m"]
    time_labels=[]
    prev_date = None
    for t in time_list:
        date_part, time_part = t.split("T") #시간 데이터가 T를 기준으로 날짜/ 시간으로 구별되므로 split를 이용하여 시간 데이터만 추출
        if date_part !=prev_date:
            time_labels.append(date_part[5:]+" "+time_part)
            prev_date=date_part # 그래프 x축에 날짜가 달라질 경우에만 날짜를 표기할 수 있도록 time_label에 데이터를 저장함.
        else: time_labels.append(time_part)
    make_csv(time_labels, temp_list)
    graph_weather(time_labels, temp_list)

if __name__ == "__main__":
    main()


