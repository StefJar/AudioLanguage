'''
Created on 08.12.2011

@author: StJ
'''
import math
import numpy

def normalizeAndConvertTo32BitFloat (x):
    scalor = 2. / numpy.max(x) - numpy.min(x)
    return numpy.array(numpy.multiply(x, scalor), dtype=numpy.float32)
    

def genSineSweep (fs, N, fstart):
    ts = 1./fs
    
    # start frequency
    f1 = fstart
    # end frequency is the nyquist frequency
    f2 = fs/2

    T = N * ts

    # some pre calcs
    w1 = 2 * math.pi * f1
    w2 = 2 * math.pi * f2

    lnScalor = math.log(w2/w1)
    k1 = w1 * T / lnScalor

    # calc

    # generate t for y(t)

    y = numpy.empty (N)
    t = 0
    for i in range(0,N):
        y[i] = numpy.sin(k1 * (math.exp(t/T*lnScalor)-1.))
        t += ts
    return normalizeAndConvertTo32BitFloat(y)

def genPhaseNoise (fs, N):
    phi = numpy.random.uniform(low=-1*numpy.pi, high=numpy.pi, size=N/2)
    Y = numpy.ones(N/2, dtype=complex)
    i = 0
    for p in phi:
        Y[i] = numpy.exp(1.j*p)
        i += 1
    Y[0] = 0. + 0.j
    y = numpy.fft.irfft(Y)
    return normalizeAndConvertTo32BitFloat(y)