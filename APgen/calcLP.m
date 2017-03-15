function [dfilt] = calcLP (fs, fg)
    k=tan(pi*fg/fs);
    k2 = k * k;
    sqrtTwo = sqrt(2);
    dn = (1+sqrtTwo*k+k2);
    
    n0=k2/dn;
    n1=2*k2/dn;
    n2=k2/dn;
    d0=1;
    d1=(2*(k2-1))/dn;
    d2=(1-sqrtTwo*k+k2)/dn;
    dfilt = [n0,n1,n2;d0,d1,d2];