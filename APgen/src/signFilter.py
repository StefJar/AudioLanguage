'''
Created on 14.12.2011

@author: StJ
'''

import math
import numpy
import scipy
import scipy.signal


# a biquad filter class
#            z(0) + n1/n0*z(-1) + n2/n0*z(-2)
# H(z) = k * ---------------------------------  k = n0/d0
#            z(0) + d1/d0*z(-1) + d2/d0*z(-2)


# some basic filter functions and structs
#
# basic filter struct:
# filter= k, [n1,n2],[d1,d2]

def getFilter_LP (fs, fc):
    k=numpy.tan(numpy.pi*fc/fs)
    k2 = k * k;
    sqrtTwo = numpy.sqrt(2);
    dn = (1.+sqrtTwo*k+k2);
 
    n = [ k2/dn , 2.*k2/dn , k2/dn]
    d = [ 1 , (2.*(k2-1.))/dn, (1.-sqrtTwo*k+k2)/dn]
    return [n, d]

def getFilter_HP (fs, fc):
    k=numpy.tan(numpy.pi*fc/fs)
    k2 = k * k;
    sqrtTwo = numpy.sqrt(2);
    dn = (1.+sqrtTwo*k+k2);

    n = [ 1./dn , -2./dn , 1./dn]
    d = [ 1 , (2.*(k2-1.))/dn, (1.-sqrtTwo*k+k2)/dn]
    return [n, d]

def transformFilter (n , d):
    k = n[0] / d[0]
    d1 = d[1] / d[0]
    d2 = d[2] / d[0]
    n1 = n[1] / n[0]
    n2 = n[2] / n[0]
    return (k, (n1,n2),(d1,d2)), [0.0 , 0.0]

def transformFilterToDirectForm (flter):
    (k, (n1,n2),(d1,d2)) = flter
    N = numpy.array ([k, n1 * k, n2 * k])
    D = numpy.array ([1, d1 , d2])
    return N, D
    

def filterBQ (filter, S, x):
    [s1,s2] = S
    k, (n1,n2),(d1,d2)= filter

    td1 = - (d2 * s2 + d1 * s1 + x)
    y = n2 * s2 + n1 * s1 +  td1;
    y *= k;
    
    return y, td1, s1

def filterBQArray (fA,SA, x):
    i = 0
    xn = x
    for f in fA:
        y, SA[i][0],SA[i][1] = filterBQ(f,SA[i],xn)
        xn = y
        i += 1
    return y, SA

def createLP_Filter (fs, fc, num):
    n , d = getFilter_LP(fs, fc)
    i = 0
    fA = []
    sA = []
    while (i < num):
        f, s = transformFilter(n,d)
        fA.append(f)
        sA.append(s)
        i += 1
    return [fA, sA]

def createHP_Filter (fs, fc, num):
    n , d = getFilter_HP(fs, fc)
    i = 0
    fA = []
    sA = []
    while (i < num):
        f, s = transformFilter(n,d)
        fA.append(f)
        sA.append(s)
        i += 1
    return [fA, sA]

def createBP_Filter (fs, fhp, flp, num):
    L = createLP_Filter(fs,flp,num)
    H = createHP_Filter(fs,fhp,num)
    
    fA = H[0]
    fA.extend(L[0])
    
    sA = H[1]
    sA.extend(L[1])
    return [fA, sA]

# http://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.lfilter.html#scipy.signal.lfilter
def getFilter_lFilterInitCond (K):
    return numpy.array([0.0,0.0,0.0])


def scipyFilterSignal (x, K, zi):
    return scipy.signal.lfilter(K[0], K[1], x, -1, zi)

def scipyFilterBQArray (x, KA, ZA ):
    i = 0
    xn = x
    for n, d in KA:
        y, ZA[i] = scipy.signal.lfilter(n, d, x, zi=ZA[i])
        xn = y
        i += 1
    return y, ZA


class scipyBiquad (object):
    def __init__(self):
        self.d = numpy.zeros(3)
        self.n = numpy.zeros(3)
        self.zi = scipy.signal.lfilter_zi(b=self.d,a=self.n)
        self.dummyX = numpy.zeros(1)
        
    def initAsLP (self, fs, fc):
        [self.d, self.n] = getFilter_LP(fs, fc)

    def initAsHP (self, fs, fc):
        [self.d, self.n] = getFilter_HP(fs, fc)

    def filterSample (self, x):
        self.dummyX[0] = x
        (y, self.zi) = scipy.signal.lfilter(self.d, self.n, self.dummyX, zi=self.zi)
        return y[0]

    def filterSampleSet (self, xArray):
        (y, self.zi) = scipy.signal.lfilter(self.d, self.n, xArray, zi=self.zi)
        return y


# a filter bank
class scipyBiquadFilterBank(object):
    def __init__(self):
        self.FB = []
         
        
    def appendFBwithLP (self, fs, fc, nTimes):
        b = scipyBiquad()
        b.initAsLP(fs, fc)
        i = 0
        while (i < nTimes):
            self.FB.append(b)
            i += 1

    def appendFBwithHP (self, fs, fc, nTimes):
        b = scipyBiquad()
        b.initAsHP(fs, fc)
        i = 0
        while (i < nTimes):
            self.FB.append(b)
            i += 1
    
    def appendFBwithBP (self, fs, fHP, fLP, nTimes):
        b = scipyBiquad()
        b.initAsHP(fs, fHP)
        i = 0
        while (i < nTimes):
            self.FB.append(b)
            i += 1
        b.initAsLP(fs, fLP)
        i = 0
        while (i < nTimes):
            self.FB.append(b)
            i += 1
    
    def filterSample (self, x):
        y = x
        for b in self.FB:
            y = b.filterSample(y)
        return y

    def filterSampleArray (self, x):
        y = x
        for b in self.FB:
            y = b.filterSampleSet(y)
        return y

