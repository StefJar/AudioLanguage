'''
Created on 25.06.2012

@author: StJ
'''

import socket
import sys
import logging


# conventions for that module
# lg - logger
# h - hostname/address
# p - port
# sa - service address
# s - socket

# creates a socket witch waits for a connection
def createSocket_Master (lg, h, p, listenFlag=True):
    if h == None:
        h = socket.gethostbyname(socket.gethostname())
    lg.info('try to create socket master='+str(h)+' port='+str(p))    
    s = None
    for res in socket.getaddrinfo(h, p, socket.AF_UNSPEC, socket.SOCK_STREAM, socket.IPPROTO_TCP , socket.AI_PASSIVE):
        af, socktype, proto, canonname, sa = res
        lg.info('try to create socket '+str(res))
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error, msg:
            s = None
            lg.info('create socket failed because of :' + str(msg))
            continue
        try: 
            s.bind(sa)
            if listenFlag == True:
                s.listen(1)
        except socket.error, msg:
            s.close()
            lg.info('binding socket failed because of:' + str(msg))
            s = None
            continue
        break
    if s is None:
        lg.error('create socket failed')
        return (False, None, None)
    return (True, s, sa)

# creates a socket witch attempt to connect to a master
def createSocket_Slave (lg, h, p, connectFlag = True):
    if h == None:
        h = socket.gethostbyname(socket.gethostname())    
    lg.info('try to create socket slave='+str(h)+' port='+str(p))
    s = None
    for res in socket.getaddrinfo(h, p, socket.AF_UNSPEC, socket.SOCK_STREAM, socket.IPPROTO_TCP , socket.AI_PASSIVE):
        af, socktype, proto, canonname, sa = res
        lg.info('try to create socket '+str(res))
        try:
            s = socket.socket(af, socktype, proto)
        except socket.error, msg:
            s = None
            lg.info('create socket failed because of :' + str(msg))
            continue
        # connect only if flag is set 
        if connectFlag == True:
            try: 
                s.connect(sa)
            except socket.error, msg:
                s.close()
                lg.info('connecting socket failed because of:' + str(msg))
                s = None
                continue
            break
    if s is None:
        lg.error('open socket failed')
        return (False, None, None)
    return (True, s, sa)