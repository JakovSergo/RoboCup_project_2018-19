import numpy as np
import constants


def koef_matrix_penrose_inverse(koef_matrix):
    return np.linalg.pinv(koef_matrix)


def drive(ax, ay, omega, speed_limit, penrose_inv):
    v = np.array([ax, ay, omega])
    weights = penrose_inv @ v
    return (constants.MAX_SPEED*speed_limit/np.max(np.abs(weights)) * weights).astype(np.float64)


print(drive(0, 0, 1, 1, koef_matrix_penrose_inverse(constants.KOEF_MATRIX)))
