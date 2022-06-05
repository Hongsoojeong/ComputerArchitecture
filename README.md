# ComputerArchitecture 12조
## 22-1학기 컴퓨터 구조 과목 기말프로젝트
### MIPS 시뮬레이터 구현하기

[공동 워크스페이스_노션](https://chestnut-raptorex-0b7.notion.site/9-dbb4d7240a6e44789969f3909aba4519)
## 프로그램 사용방법
<details>
<summary>명령어 종류</summary>
<div markdown="1">

+ l : Load program
  +  실행파일을 simulator 메모리에 올리는 명령어
  +  실행파일은 바이너파일(.bin) 형식
  
+ j : Jump program
  + 입력한 위치에 시뮬레이터 실행 준비

+ g : Go program
  + 앞서 l 명령어로 로드된 실행파일에 있는 명령어들을 모두 실행

+ s : Step program
  + 로드된 실행파일에 있는 명령어들을 한줄씩 실행
  
+ m : View memory
  + m <start> <end>
  + start~end 범위의 메모리 내용을 출력해준다
    
+ r: View register
  + 0 ~ 31 번째 register의 값을 출력해준다
    
+ x: Program exit
  + Simulator 프로그램을 종료해준다
  
+ sm : Set Memory
  + sm <location> <value> 
  + 메모리 특정 주소의 값을 설정해준다.
  
+ sr : Set Register
  + sr <register number> <value> 
  + 특정 레지스터의 값을 설정해준다.
  
+ help : Print Command List
  + 도움말 출력

</div>
</details>

