#!/usr/bin/env python3

import json
import serial
import numpy as np

import matplotlib
matplotlib.rc('axes',edgecolor='w')

import matplotlib.pyplot as plt
plt.rcParams['xtick.major.pad']='17'
plt.rcParams["axes.axisbelow"] = False

from matplotlib.animation import FuncAnimation

x_range = [0, 180]
y_range = [0, 100]

def dress_axes(ax):
    ax.set_facecolor('w')
    ax.set_xlim(x_range)
    ax.set_ylim(y_range)
    ax.set_thetamin(x_range[0])
    ax.set_thetamax(x_range[1])
    ax.set_theta_zero_location("E")
    ax.set_rlim(y_range)


def animate(i, xs, ys, ser):
    # jstr = '{{"a": {}, "d": 50}}'.format(i)
    jstr = ser.readline().strip(b'\r\n ')

    try:
        data = json.loads(jstr)
        print(data)
        index = data['a'] - x_range[0]
        ys[index] = data['d']
        xs[index] = data['a'] * np.pi / 180
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

    fig = plt.figure()
    ax = fig.add_subplot(1, 1, 1, polar=True)
    xs = np.arange(x_range[0], x_range[1], dtype=np.float) * np.pi / 180.
    ys = np.ones_like(xs, dtype=np.float)

    dress_axes(ax)

    line, = ax.plot(xs, ys, 'ro--')

    ser = serial.Serial(port='/dev/ttyUSB0', baudrate=115200)

    ani = FuncAnimation(fig, animate, fargs=(xs, ys, ser, ), interval=0, blit=True)
    plt.show()
