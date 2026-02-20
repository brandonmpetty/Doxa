from .doxapy import *


def read_weights(file):
    with open(file) as f:
        return [float(x) for x in f.read().split()]
