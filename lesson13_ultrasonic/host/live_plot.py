#!/usr/bin/env python3

import json
import serial
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

plt.rcParams['xtick.major.pad']='17'
plt.rcParams["axes.axisbelow"] = False
matplotlib.rc('axes',edgecolor='w')
from matplotlib.animation import FuncAnimation

x_range = [-90, 90]
y_range = [0, 300]

def dress_axes(ax):
    ax.set_facecolor('w')
    ax.set_thetamin(x_range[0])
    ax.set_thetamax(x_range[1])
    ax.set_theta_zero_location("N")
    ax.set_rlim(y_range)


fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, polar=True)
xs = np.arange(x_range[0], x_range[1], dtype=np.float)
ys = np.zeros_like(xs, dtype=np.float)

dress_axes(ax)

line, = ax.plot(xs, ys)

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600)

# This function is called periodically from FuncAnimation
def animate(i, ys):
    jstr = ser.readline().strip(b'\r\n ')
    data = json.loads(jstr)
    print(data)
    ys[data['a'] - x_range[0]] = data['d']
    line.set_ydata(ys)

    return line,


if __name__ == '__main__' : 
    ani = FuncAnimation(fig, animate, fargs=(ys,), interval=50, blit=True)
    plt.show()
