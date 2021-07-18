from mondrian import mondrian
from read_adult_data import read_data 
import sys, copy, random

def get_result(data, k=10):
    print("K=%d" % k)
    data_back = copy.deepcopy(data)
    result, eval_result = mondrian(data, k)
    data = copy.deepcopy(data_back)
    print("NCP %0.2f" % eval_result[0] + "%")
    print("Running time %0.2f" % eval_result[1] + " seconds")

if __name__ == '__main__':
    k = int(input())
    DATA, INTUITIVE_ORDER = read_data()
    get_result(DATA, k)
