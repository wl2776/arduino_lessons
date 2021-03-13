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

x_range = [0, 180]
y_range = [0, 300]

def dress_axes(ax):
    ax.set_facecolor('w')
    ax.set_thetamin(x_range[0])
    ax.set_thetamax(x_range[1])
    ax.set_theta_zero_location("E")
    ax.set_rlim(y_range)


fig = plt.figure()
ax = fig.add_subplot(1, 1, 1, polar=True)
xs = np.arange(x_range[0], x_range[1], dtype=np.float)
ys = np.ones_like(xs, dtype=np.float)

dress_axes(ax)

line, = ax.plot(xs, ys)

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600)

def animate(i, xs, ys):
    # jstr = '{{"a": {}, "d": 50}}'.format(i)
    jstr = ser.readline().strip(b'\r\n ')

    try:
        data = json.loads(jstr)
        print(data)
        index = data['a'] - x_range[0]
        ys[index] = data['d']
        xs[index] = data['a']
        line.set_ydata(ys)
        line.set_xdata(xs)
    except json.decoder.JSONDecodeError:
        pass
    except IndexError:
        pass
    except UnicodeDecodeError:
        pass
    ax.clear()
    dress_axes(ax)
    return line,


if __name__ == '__main__' : 
    ani = FuncAnimation(fig, animate, fargs=(xs, ys,), interval=100, blit=True)
    plt.show()
