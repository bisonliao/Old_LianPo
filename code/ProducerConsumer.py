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


qmutex = threading.Lock()
qgoods = list()
MAX_GOOD_NUM = 4

emptySlot = threading.Semaphore(MAX_GOOD_NUM) # 空闲的仓库货架数量
itemNum = threading.Semaphore(0) # 仓库里存货的数量


def producer():
    good_id = 1
    while True:
        emptySlot.acquire()  # p操作， 有空闲货架才生产
        time.sleep(1) # 生产

        qmutex.acquire()  # 互斥访问仓库
        addGood = False
        if len(qgoods) < MAX_GOOD_NUM:
            qgoods.append(good_id)
            addGood = True
            good_id += 1
        qmutex.release()

        if addGood:
            itemNum.release() # v操作,通知消费者有存货可消费

def consumer():
    while True:
        itemNum.acquire() # p操作，有存货才消费

        qmutex.acquire() # 互斥访问仓库
        delGood = False
        if len(qgoods) > 0:
            v = qgoods[0]
            qgoods.pop(0)
            print("consume good#", v)
            delGood = True
        qmutex.release()

        if delGood:
            emptySlot.release() # v操作，通知生产者有空闲货架了

t1 = threading.Thread(target=producer, name='producer')
t2 = threading.Thread(target=consumer, name='consumer')

t1.start()
t2.start()

t1.join()
t2.join()





