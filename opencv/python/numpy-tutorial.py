import time
import csv
import matplotlib.pyplot as plt
import numpy as np

# with open('test.csv',  'rb') as csvfile:
#     print(csvfile.read())
# f = np.genfromtxt('test.csv', delimiter=',', skip_header=1, \
#                   dtype="|S8,I,S,S", autostrip=True)
f = np.genfromtxt('test.csv', delimiter=',', skip_header=1, \
                  dtype=[("name",np.str_,32),("age",np.int),("birth",np.str,16),("occ",np.str,8)], \
                  autostrip=True)

# csv 파일 읽기
csvpath = '/Users/jhlee/prj/study/opencv/sampledata.csv'

# with open(csvpath,  'rb') as csvfile:
#     rows = csv.reader(csvfile, delimiter=',')
#     dewPoint = []
#     temperature = []
#     for index, row in enumerate(rows):
#         if index > 0:
#             dewPoint.append(row[5])
#             temperature.append(row[7])
#     print(dewPoint)
#     print(temperature)

# n = np.recfromcsv(csvpath, delimiter=',',  names=['station','date','time','weather','air_temperature','dew_point','sea_temperature','humidit"y','wind_direction','wind_speed','visibility','air pressure','wave_height','wave_period'])
# n = np.genfromtxt(csvpath, delimiter=',')
# n = np.loadtxt(csvpath, skiprows=1, usecols=(5, 7))


# station,date,time (UTC),weather,air temperature (degC),dew point (deg C),sea temperature (deg C),humidity (%),wind direction,wind speed (knots),visibility (nautical miles),air pressure (hPa),wave height (metres),wave period (seconds)
dt = [ \
       ('station', str), \
       ('date', str), \
       ('time', str), \
       ('weather', str), \
       ('air_temperature', float), \
       ('dew_point', float), \
       ('sea_temperature', str), \
       ('humidity', float), \
       ('wind_direction', float), \
       ('wind_speed', float), \
       ('visibility', float), \
       ('air_pressure', float), \
       ('wave_height', float), \
       ('wave_period', float), \
]

n = np.recfromcsv(csvpath, delimiter=',', dtype=dt)

# plt.plot(n.field(5), n.field(7))
# plt.show()

