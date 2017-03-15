'''
Created on 05.10.2011

@author: StJ
'''
import scipy
import numpy
import matplotlib.pyplot as plt


def poltBode (AmplitudeSubPlotNumber, PhaseSubPlotNumber, ComplexVal, N, xScalor, color, lw, alphaCh, legendLabel):
    A = abs (ComplexVal)
    A = 20 * numpy.log10(A)
    p = numpy.angle(ComplexVal)
    xAxis = numpy.linspace(0, N, len(A))
    xAxis *= xScalor
    xAxis = numpy.log10(xAxis)
           
    plt.subplot(AmplitudeSubPlotNumber)
    plt.plot(xAxis, A, lw=lw, color=color,alpha=alphaCh,label=legendLabel)
    plt.xlabel('log frequency')
    plt.ylabel('magnitude in dB')
    plt.legend(loc=0)
    
    plt.subplot(PhaseSubPlotNumber)
    plt.plot(xAxis, p, lw=lw, color=color, alpha=alphaCh,label=legendLabel)
    plt.xlabel('log frequency')
    plt.ylabel('phase in rad')
    plt.legend(loc=0)

