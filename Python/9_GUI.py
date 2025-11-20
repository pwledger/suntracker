import serial
import tkinter as tk
import time
import customtkinter as ctk                     # Custom 가능한 tkinter 사용.

ser = serial.Serial('COM3', 9600, timeout=1)    # serial통신 설정

### 전역변수 및 변수저장 목적으로 생성 ###
root = None                                     
frame = None
temp_volt = None
temp_watt = None
volt = 0

### 아두이노에서 전압값을 읽어오고, 전력값을 계산 ###
def poll():   
    global root
    global temp_volt
    global volt

    # Update labels to display voltage values
    try:
        val = ser.readline()                    # 전압값 읽어옴(byte단위)
        val_str = val.decode()                  # DATA DECODE해서 전압값 가져옴(byte -> 문자열)
        val_float = float(val_str)              # val_str에 저장된 전압값은 문자열이므로 float형식으로 변환.
        temp_volt.set(val_float)                # temp_volt에 val_float값을 저장.
        temp_watt.set(round((val_float*val_float/10),3))    # p = v^2 / R를 이용하여 전압값을 계산.
        volt = temp_volt.get()                         # 실수형 전압 가져오기 위해 사용(게이지바에서 실수형 DATATYPE필요함)

    except:
        pass

    # Schedule the poll() function for another 500 ms from now
    root.after(200, poll)                   

root = ctk.CTk()    
root.title("신재생에너지 키트")     # 상단 title
frame = ctk.CTkFrame(master = root,width = 1200, height = 700, fg_color='#3a4048')
frame.pack(fill=ctk.BOTH, expand=1)     #pack함수의 fill을 both(x,y)로하여, 윈도우 사이즈를 변경해도 위젯의 상대적위치가 변하지 않는다.

exit_image=tk.PhotoImage(file="off.png")     # 종료 이미지 로고 
exit_image=exit_image.subsample(8,8)         # 이미지 로고 크기조정가능
temp_volt = tk.DoubleVar()      # 전압(아래LABEL에서 사용 예정)         실수형 변수 datatype
temp_watt = tk.DoubleVar()      # 전력(아래LABEL에서 사용 예정)         실수형 변수 datatype

### 전압 라벨 ###
label_temp = ctk.CTkLabel(master = root,                
                          text = "전압 (V)", width = 500, height = 180, 
                          fg_color= '#121820', bg_color= '#3a4048', font = ("HY헤드라인M",80), 
                          text_color='white', corner_radius= 8)
### 전압 데이터 출력 라벨 ###
label_volt = ctk.CTkLabel(master = root,                
                          textvariable = temp_volt, width = 500, height = 100, 
                          font = ("HY헤드라인M", 80), text_color = '#e5e500',
                          bg_color = '#3a4048', fg_color = '#121820', corner_radius = 8)
### 전력 라벨 ###
label_tracker = ctk.CTkLabel(master = root,                 
                             text = "전력 (mW)", width = 500, height = 180, 
                             fg_color = '#121820', bg_color = '#3a4048', font = ("HY헤드라인M",80),
                             text_color ='white', corner_radius= 8)
### 전력 데이터 출력 라벨 ###
label_watt = ctk.CTkLabel(master = root,            
                          textvariable = temp_watt, width = 500, height = 100, 
                          font = ("HY헤드라인M", 80), text_color = '#e5e500', bg_color= '#3a4048',
                          fg_color = '#121820', corner_radius = 8)
### 종료 버튼 ###
btn_quit = ctk.CTkButton(master = root,                   
                         width = 150, height = 100, image = exit_image, 
                         hover_color = 'red',            # 마우스 커서 갖다대면 빨간색으로 변함
                         text = "", border_width = 0, corner_radius = 8,
                         fg_color = 'white', bg_color = '#3a4048', command = root.destroy)
# 프로그래스바 생성
progressbar = ctk.CTkProgressBar(master = root, width = 500, height = 70, bg_color = '#3a4048',
                                 fg_color = 'white', progress_color = 'green')       

#### 게이지바 상승 코드 ####
def gaugebar():         
    global root         
    global volt

    percent = volt/6      #전압값이 6v일때 1로하여 gaugebar의 percent계산.

    if percent >= 1:
        percent = 1
    progressbar.set(percent)
    
    if percent < 0.2:       
        progressbar.configure(progress_color='red')
    elif percent < 0.6:
        progressbar.configure(progress_color='green')
    else:
        progressbar.configure(progress_color='blue')

    root.after(200, gaugebar)      # 0.2초 단위마다 함수 재실행
    root.update_idletasks          # 현재 출력된 gui window에서 새로고침.
#########################
gaugebar()                          # 게이지바 함수 실행

# 각 widget 위치 설정
progressbar.place(relx=0.05, rely=0.75)        
label_temp.place(relx = 0.05, rely =0.1)
label_volt.place(relx = 0.05, rely = 0.4) 
label_tracker.place(relx = 0.5, rely =0.1)
label_watt.place(relx = 0.5, rely = 0.4)
btn_quit.place(relx=0.75, rely=0.7)

root.after(200, poll)                   

root.mainloop()                         # GUI를 실행