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

n_ticks = 20
big_angle = 180/n_ticks  # How we split our polar space

inner=10
outer=30

x_len = 200         # Number of points to display
y_range = [0, 100]  # Range of possible Y values to display


def dress_axes(ax):
    ax.set_facecolor('w')
    ax.set_theta_zero_location("N")
    ax.set_theta_direction(-1)
    # Here is how we position the months labels

    middles = np.arange(big_angle/2, 180, big_angle)*np.pi/180
    ax.set_xticks(middles)
    ax.set_xticklabels(middles)


# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = list(range(0, 200))
ys = [0] * x_len
ax.set_ylim(y_range)

line, = ax.plot(xs, ys)

ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600)

# This function is called periodically from FuncAnimation
def animate(i, ys):
    jstr = ser.readline().strip(b'\r\n ')
    data = json.loads(jstr)
    print(data)
    distance = data['d']

    # Add y to list
    ys.append(distance)

    # Limit y list to set number of items
    ys = ys[-x_len:]

    # Update line with new Y values
    line.set_ydata(ys)

    return line,


if __name__ == '__main__' : 
    ani = FuncAnimation(fig, animate, fargs=(ys,), interval=50, blit=True)
    plt.show()
