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
场景就是：n个哲学家围坐一桌，每个哲学家之间有一只筷子，哲学家要么思考要么吃饭。哲学家只有拿到自己左右两边的两支筷子才能吃饭
'''

PHILOSOPHER_NUM = 15
chopsticks = [ threading.Semaphore(1) for _ in range(PHILOSOPHER_NUM)]


def philosopher(i:int):
    # 通过打破不剥夺条件，防止死锁。一旦右边筷子拿不到，就释放左边的筷子
    while True:
        left = i
        right = (i+1) % PHILOSOPHER_NUM
        chopsticks[left].acquire()
        if not chopsticks[right].acquire(blocking=False):
            chopsticks[left].release()
            continue
        print(f"philosopher#{i} is eating...")
        time.sleep(2)

        chopsticks[right].release()
        chopsticks[left].release()
        time.sleep(1) # thinking...

def philosopher_v2(i:int):
    while True:
        #确保先申请小编号资源，再申请大编号资源，打破循环等待条件，避免死锁
        if i+1 == PHILOSOPHER_NUM:
            first = (i+1) % PHILOSOPHER_NUM
            second = i
        else:
            first = i
            second = (i+1) % PHILOSOPHER_NUM
        chopsticks[first].acquire()
        chopsticks[second].acquire()
        print(f"philosopher#{i} is eating...")
        time.sleep(2)

        chopsticks[second].release()
        chopsticks[first].release()
        time.sleep(1) # thinking...

phis = [threading.Thread(target=philosopher_v2, args=(j,)) for j in range(PHILOSOPHER_NUM)]

[phis[j].start() for j in range(PHILOSOPHER_NUM)]
[phis[j].join() for j in range(PHILOSOPHER_NUM)]
