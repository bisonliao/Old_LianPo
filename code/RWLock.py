import numpy as np
import cupy as cp
import datetime
import time
import torch

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import math
import threading
import time

class RWLock:
    def __init__(self):
        self.readerCounter = 0
        self.readerCounterMutex = threading.Lock()

        self.antiWriteStarve = threading.Lock()
        self.lock = threading.Lock()

    def rlock(self):
        self.antiWriteStarve.acquire()
        self.readerCounterMutex.acquire()
        if self.readerCounter == 0:
            self.lock.acquire()
        self.readerCounter += 1
        self.readerCounterMutex.release()
        self.antiWriteStarve.release()

    def release_rlock(self):
        self.readerCounterMutex.acquire()
        if self.readerCounter >= 0:
            self.readerCounter -= 1
        if self.readerCounter == 0:
            self.lock.release()
        self.readerCounterMutex.release()

    def wlock(self):
        self.antiWriteStarve.acquire()
        self.lock.acquire()
        self.antiWriteStarve.release()


    def release_wlock(self):
        self.lock.release()

rwlock = RWLock()

def reader():
    while True:
        rwlock.rlock()
        print(f"{threading.current_thread().name} is reading...")
        time.sleep(1)
        print(f"{threading.current_thread().name} done")
        rwlock.release_rlock()

def writer():
    while True:
        rwlock.wlock()
        print(f"{threading.current_thread().name} is writing...")
        time.sleep(2)
        print(f"{threading.current_thread().name} done")
        rwlock.release_wlock()






t1 = threading.Thread(target=writer, name='writer-1')
t2 = threading.Thread(target=writer, name='writer-2')
t3 = threading.Thread(target=reader, name='reader-1')
t4 = threading.Thread(target=reader, name='reader-2')



t1.start()
t2.start()
t3.start()
t4.start()


t1.join()
t2.join()
t3.join()
t4.join()


