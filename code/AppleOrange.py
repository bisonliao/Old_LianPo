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

'''
这个题目是这样的：
爸爸往盘子里放苹果，儿子从盘子里取苹果吃；
妈妈往盘子里放橘子，女儿从盘子里取橘子吃；
盘子里只能放下一个水果，要么苹果，要么橘子
'''

qmutex = threading.Lock() #互斥访问盘子的锁
plate = list() #可以方一个物品的盘子
MAX_GOOD_NUM = 1
good_id = 1

emptySlot = threading.Semaphore(MAX_GOOD_NUM) # 空闲的盘子数量
appleNum = threading.Semaphore(0) # 盘子里苹果的数量
orangeNum = threading.Semaphore(0) # 盘子里橘子的数量

helpDict = {"apple": appleNum, "orange": orangeNum}




def parent(itemName:str):
    if itemName != "apple" and itemName != "orange":
        print(f"invalid argument {itemName}")
        return
    print(f"{threading.current_thread().name} start")
    global good_id
    while True:
        emptySlot.acquire()  # p操作， 有盘子空闲才生产水果
        time.sleep(1) # 生产水果

        qmutex.acquire()  # 互斥访问盘子
        addGood = False
        if len(plate) < MAX_GOOD_NUM:
            plate.append(f"{itemName}#{good_id} from {threading.current_thread().name} ")
            addGood = True
            good_id += 1
        qmutex.release()

        if addGood:
            helpDict[itemName].release()


def child(itemName:str):
    if itemName != "apple" and itemName != "orange":
        print(f"invalid argument {itemName}")
        return
    print(f"{threading.current_thread().name} start")

    while True:
        helpDict[itemName].acquire() # p操作，有存货才消费

        qmutex.acquire() # 互斥访问盘子
        delGood = False
        if len(plate) > 0:
            v = plate[0]
            plate.pop(0)
            print(f"consume {v} by {threading.current_thread().name}")
            delGood = True
        qmutex.release()

        if delGood:
            emptySlot.release() # v操作，通知生产者有空闲货架了

t1 = threading.Thread(target=parent, name='father', args=('apple',))
t2 = threading.Thread(target=parent, name='mother', args=('orange',))
t3 = threading.Thread(target=child, name='son', args=('apple',))
t4 = threading.Thread(target=child, name='daughter', args=('orange',))


t1.start()
t2.start()
t3.start()
t4.start()


t1.join()
t2.join()
t3.join()
t4.join()






