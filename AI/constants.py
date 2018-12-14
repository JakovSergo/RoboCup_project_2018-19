import numpy as np
MAX_SPEED = 255
MASS = 0.685
RADIUS = 0.09
ALFA = [np.pi/4, np.pi/4 + np.pi/2, 5*np.pi/4, 7*np.pi/4]
I = MASS*RADIUS**2/2
a = -np.sin(ALFA)
b = np.cos(ALFA)
c = [MASS*RADIUS/I, MASS*RADIUS/I, MASS*RADIUS/I, MASS*RADIUS/I]
KOEF_MATRIX = np.array([a, b, c])
N = 100