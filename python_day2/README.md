# 서울시내 기온 변화 그래프 작성 프로그램

### 로봇게임단_수습단원_과제2_로봇학부_전서연

## 1. 프로젝트 소개
- 해당 프로그램은 지난 일주일 간의 서울 시내 시간대별 기온 변화 데이터를 바탕으로 csv 파일과 그래프를 제작합니다. 외부 라이브러리 'requests'로 외부 API에서 데이터를 가져온 후, csv 파일로 전처리 후 저장한 뒤, 'matplotlib'으로 그래프를 작성하여 시각화하기 위해 작성되었습니다.

## 2. 사용한 라이브러리
### **requests** (version: 2.34.2)
- Open-Meteo API에 요청을 보내 지난 7일간의 서울 시내 기온 데이터를 불러오기 위해 사용하였습니다.
- 보안 패치와 버그 수정을 받을 수 있으며 동시에 기능이 안정적으로 수행될 수 있는 최신 버전이 해당 프로그램에 적합하다 판단되어 2.34.2 버전을 사용하였습니다.

### **matplotlib** (version: 3.11.0)  
- 불러온 기온 데이터를 시간 흐름에 따른 선 그래프로 시각화하기 위해 matplotlib를 사용하였습니다.
- 해당 프로젝트에서 사용한 점 표시 기능 (scatter), 평균선 작성을 위한 기능 (axhline), 한글 깨짐을 방지하기 위해 필요한 한글 폰트 지정 기능 등이 안정적으로 지원되는 최신 버전인 3.11.0을 사용하였습니다.

## 3. 라이브러리 설치 방법
- 해당 프로젝트를 실행하기 위해 필요한 라이브러리를 한 번에 설치하는 코드입니다.
```
pip install -r requirements.txt
```
개별적으로 라이브러리를 설치할 경우 아래 코드를 참조하십시오.
```
pip install requests matplotlib
```

## 4. 실행 방법
- 아래 명령어로 프로그램을 시작합니다.
```
python main_2.py
```
실행할 경우,
- 서울시의 지난 일주일간 시간대별 기온 데이터를 API에서 가져옵니다.
- 'seoul_weather.csv' 파일로 전처리 과정을 거친 시간/ 기온 데이터를 저장합니다.
- 기온 데이터를 시각화한 기온 변화 그래프 창이 뜹니다. 최고, 최저 온도는 각각 빨간 점과 파란 점으로 표시하였으며, 평균 온도는 초록 점선으로 표시됩니다.

## 5. 코드 설명
### 한글 폰트 변경
```python
plt.rcParams['font.family'] = 'Malgun Gothic'
```
- 그래프 내 한글 깨짐 현상을 방지하기 위해 한글 폰트를 맑은 고딕으로 변경하였습니다.
### bring_data(url)
- 지정된 URL (Open-Meteo API)에 요청을 보내 데이터를 json 형태로 가져옵니다.
- 데이터를 가져오는데에 실패할 경우 오류 메세지를 출력하고 프로그램을 종료합니다.
```python
def bring_data(url):
    try:
        content= requests.get(url)
    except requests.exceptions.RequestException as e:
        print(f"데이터를 가져오는데에 실패했습니다: {e}")
        exit()
    data= content.json()
    return data
```

### make_csv(time_labels, temp_list)
- 전처리된 시간과 기온 데이터를 "seoul_weather.csv" 파일로 저장합니다.
```python
def make_csv(time_labels, temp_list):   
    with open("seoul_weather.csv","w", newline="", encoding="utf-8") as f:
        writer= csv.writer(f)
        writer.writerow(["time", "temperature"])
        for time, temp in zip(time_labels, temp_list):
            writer.writerow ([time, temp])
```

### graph_weather(time_labels, temp_list)
- 최고, 최저, 평균 온도를 구한 뒤, 최고, 최저 온도를 점으로 강조하기 위해 위치를 인덱스합니다.
- 최고, 최저 온도는 점으로 강조하고, 평균 온도는 가로선으로 강조하였습니다.
- 최고, 최저, 평균 온도는 범례로 그래프와 함께 표시하였습니다.
```python
def graph_weather(time_labels, temp_list):
    avg_temp = sum(temp_list) /len(temp_list)
    max_temp = max(temp_list)
    min_temp = min(temp_list)
    max_index = temp_list.index(max_temp)
    min_index = temp_list.index (min_temp)
    plt.plot(range(len(temp_list)), temp_list)
    plt.scatter(max_index, max_temp,color="red",zorder=5,label=f"최고 온도: {max_temp}°C")
    plt.scatter(min_index, min_temp,color="blue",zorder=5,label=f"최저 온도: {min_temp}°C")
    plt.axhline(y=avg_temp, color='green', linestyle='--', label=f'평균 온도: {avg_temp:.1f}°C')
    plt.xticks(range(len(temp_list)),time_labels,rotation=90, fontsize=6 ) 
    plt.legend()
    plt.show()
```

### main()
- 앞서 정의한 함수를 순차적으로 실행합니다.
- API에서 받은 시간 데이터 ('2026-07-14T00:00'의 형식)를 'T' 기준으로 분리하여 날짜가 바뀌는 시점에만 1회 날짜를 표시하고 그 외에는 시간만 표시할 수 있도록 time_label에 데이터를 저장하며 전처리 과정을 수행하였다.

```python
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
```


