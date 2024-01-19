#!/bin/env python
# -*- coding: utf-8 -*-
"""
Plot Colorado data
"""
import os
import numpy as np
import matplotlib.pyplot as plt


def plot_colorado():
    """
    Plot Colorado data
    """
    # Load data
    data = np.genfromtxt('colorado_elev.csv', delimiter=',')

    # Plot
    plt.figure()
    plt.contourf(data) 
    plt.title('Colorado')
    plt.savefig('colorado.png')

if __name__ == "__main__":
    plot_colorado()