function [filter] = normFilterCoeff (dF)
    filter = dF / dF(2,1);