#plt.plot()	update graph data/state
#plt.ion()	enable live interactive plotting mode
#plt.pause()	allow GUI/backend/OS to render & refresh graph continuously
#plt.show()	open graph in blocking mode

import serial
import csv
from datetime import datetime
import matplotlib.pyplot as plt
from collections import deque
import time
import os

#limited array to avoid lag while plotting graph
x = deque(maxlen=100)   # latest 100 samples
y = deque(maxlen=100)



file = open("sensor_dataloggs.csv", "a", newline='')
writer = csv.writer(file)
if os.path.getsize("sensor_dataloggs.csv") == 0:
    writer.writerow(["Distance","Date","Time"])

#setting up port to read data
arduino = serial.Serial("COM5", 9600, timeout=1)

#waiting 2 sec to avoid error bits
time.sleep(2)

#reset buffer space
arduino.reset_input_buffer()

#store the time when python starts taking readings (in seco.) 
start_time = time.time()

#enabling interactive mode
plt.ion()


while True:
    #gather readable data
    data = arduino.readline().decode(errors="ignore").strip()
    
    #process loop 
    if data:
        
        #handling conversion exception
        try:
            distance = float(data)
        except ValueError:
            continue

        current_time = datetime.now().strftime("%H:%M:%S")
        current_date = datetime.now().strftime("%d/%m/%Y")
        
        #elapsed in time seconds
        elapsed = time.time()-start_time
        
        #save to csv
        writer.writerow([distance, current_date, current_time])
        file.flush()
        
        #kinda serial monitor
        print("distance", distance,
              "elapsed", round(elapsed,2),"sec",
              "current_time", current_time,
              "current_date", current_date)
        

        #decision logic
        if distance < 10:
            print("warning: object very close")
        elif distance < 25:
            print("object nearby")
        else:
            print("area clear")
        
        
        x.append(elapsed)
        y.append(distance)
        
        #clear prvs graph 
        plt.clf()

        #draw graph
        plt.plot(x, y)

        #labbeling
        plt.xlabel("time in sec")
        plt.ylabel("distance in cm")
        plt.title("Real-Time telemetry")

        #appearance
        plt.tight_layout()

        #give gui event loop specified time to update and redraw graph 
        plt.pause(0.01)