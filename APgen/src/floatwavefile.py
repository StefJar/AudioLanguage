'''
Created on 27.09.2011

@author: Stefan Jaritz

@content:

a simple extension of the wavfile modul at scipy
to read/write wav file containing float values

annotation:
the orginal wavfile from scipy/wave modul is
only able to handle PCM(integer) data
if numpy.float32 dataarrays are used it won't fail
but the data get corrupted

this module is a reverse engineered of the common
version from scipy

good luck and happy coding!
'''
import numpy
from numpy.compat import asbytes
import struct
import warnings

from scipy.io import wavfile

#define for the format id
_WAVfloatFormatID = 3
#_WAVfloatFormatSize = 32


def _read_float_data_chunk(fid, noc, bits):
    # 1. get size
    if wavfile._big_endian:
        fmt = '>i'
    else:
        fmt = '<i'
    size = struct.unpack(fmt,fid.read(4))[0]

    # 2. read the data
    amount = size / 4
    data = numpy.fromfile(fid, dtype=numpy.float32, count=amount)
    if noc > 1:
        data = data.reshape(-1,noc)
    return data

# assumes file pointer is immediately
#  after the 'fmt ' id
def _read_float_fmt_chunk(fid):
    if wavfile._big_endian:
        fmt = '>'
    else:
        fmt = '<'
    res = struct.unpack(fmt+'ihHIIHH',fid.read(20))
    size, comp, noc, rate, sbytes, ba, bits = res
    return size, comp, noc, rate, sbytes, ba, bits


# open a wave-file
def readFloatWAV(file):
    """
    Return the sample rate (in samples/sec) and data from a WAV file

    Parameters
    ----------
    file : file
        Input wav file.

    Returns
    -------
    rate : int
        Sample rate of wav file
    data : numpy array
        Data read from wav file

    Notes
    -----

    * The file can be an open file or a filename.

    * The returned sample rate is a Python integer
    * The data is returned as a numpy array with a
      data-type determined from the file.

    """
    if hasattr(file,'read'):
        fid = file
    else:
        fid = open(file, 'rb')

    fsize = wavfile._read_riff_chunk(fid)
    noc = 1
    bits = 8
    while (fid.tell() < fsize):
        # read the next chunk
        chunk_id = fid.read(4)
        if chunk_id == asbytes('fmt '):
            size, comp, noc, rate, sbytes, ba, bits = _read_float_fmt_chunk(fid)
        elif chunk_id == asbytes('data'):
            data = _read_float_data_chunk(fid, noc, bits)
        else:
            # skip chunk
            warnings.warn("chunk not understood", wavfile.WavFileWarning)
            data = fid.read(4)
            if wavfile._big_endian:
                fmt = '>i'
            else:
                fmt = '<i'
            size = struct.unpack(fmt, data)[0]
            fid.seek(size, 1)
    fid.close()
    return rate, data

# Write a wave-file
# sample rate, data
def writeFloatWAV(filename, rate, data):
    """
    Write a numpy array as a WAV file

    Parameters
    ----------
    filename : file
        The name of the file to write (will be over-written).
    rate : int
        The sample rate (in samples/sec).
    data : ndarray
        A 1-D or 2-D numpy array of integer data-type.

    Notes
    -----
    * Writes a simple uncompressed WAV file.
    * The bits-per-sample will be determined by the data-type.
    * To write multiple-channels, use a 2-D array of shape
      (Nsamples, Nchannels).

    """
    fid = open(filename, 'wb')
    fid.write(asbytes('RIFF'))
    fid.write(asbytes('\x00\x00\x00\x00'))
    fid.write(asbytes('WAVE'))
    # fmt chunk
    fid.write(asbytes('fmt '))
    if data.ndim == 1:
        noc = 1
    else:
        noc = data.shape[1]
    bits = data.dtype.itemsize * 8
    sbytes = rate*(bits // 8)*noc
    ba = noc * (bits // 8)
    fid.write(struct.pack('<ihHIIHH', 16, _WAVfloatFormatID, noc, rate, sbytes, ba, bits))
    # data chunk
    fid.write(asbytes('data'))
    # save size of the float array
    datacount = len (data) * 4
    fid.write(struct.pack('<i', datacount))
    # write data to file
    data.tofile(fid)
    # Determine file size and place it in correct
    # position at start of the file.
    size = fid.tell()
    fid.seek(4)
    fid.write(struct.pack('<i', size-8))
    fid.close()