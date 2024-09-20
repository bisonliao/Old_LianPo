import numpy as np
import cupy as cp
import datetime
import time
import torch

import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
import math

def create_lps(pattern:str):
    lps = [0] * len(pattern)
    for i in range(1, len(pattern)):
        subs = pattern[0:i+1]
        prefix=list()
        suffix=list()
        for j in range(len(subs)-1):
            prefix.append(subs[0:j+1])
            suffix.append(subs[-j-1:])
        for j in range(len(prefix)):
            if (prefix[j]==suffix[j]):
                lps[i] = len(prefix[j])

    return lps



s = "ababa"
print(create_lps(s), compute_lps(s))
s = "abcabcd"
print(create_lps(s), compute_lps(s))


def kmp_search(text, pattern):
    lps = create_lps(pattern)
    cmp_cnt = 0
    i = 0  # index for text
    j = 0  # index for pattern

    while i < len(text):
        if pattern[j] == text[i]:
            cmp_cnt += 1
            i += 1
            j += 1

        if j == len(pattern):
            print(f"Pattern found at index {i - j}", cmp_cnt)
            j = lps[j - 1]
        elif i < len(text) and pattern[j] != text[i]:
            cmp_cnt += 1
            if j != 0:
                j = lps[j - 1]
            else:
                i += 1


# Example usage
text = "ABABDABACDABABCABAB"
pattern = "ABABCABAB"
kmp_search(text, pattern)





