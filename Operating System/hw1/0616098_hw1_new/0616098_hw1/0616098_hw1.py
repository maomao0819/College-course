import time
import threading
import queue
import random
import string
import hashlib
import requests
import multiprocessing
from lxml.html import fromstring
import asyncio

def get_random_string(N=5):
    letter = string.ascii_letters + string.digits + string.punctuation
    return ''.join(random.choice(letter) for _ in range(N))

def get_hash_value(str_C, str_S):
    SHA256 = hashlib.sha256()
    # SHA256.update(b'{str_C})
    SHA256.update(str_C.encode("utf-8"))
    SHA256.update(str_S.encode("utf-8"))
    hash_value = SHA256.hexdigest()
    return hash_value

def Workload_A(str_S):
    while True:
        str_C = get_random_string(5)
        hash_value = get_hash_value(str_C, str_S)
        hash_value_first_5_letter = hash_value[:5]
        if hash_value_first_5_letter == '00000':
            print(str_C + str_S)
            break

def Workload_B(URL):
    # r = requests.head(URL)
    r = requests.get(URL, auth=('user', 'pass'))
    if r.status_code == requests.codes.ok:
        content = fromstring(r.content)
        title = content.findtext('.//title')
        print(title)

# Worker 類別，負責處理資料
class worker_thread_A(threading.Thread):
    def __init__(self, queue):
        threading.Thread.__init__(self)
        self.queue = queue

    def run(self):
        while self.queue.qsize() > 0:
            # 取得新的資料
            str_S = self.queue.get()
            # 處理資料
            Workload_A(str_S)

class worker_thread_B(threading.Thread):
    def __init__(self, queue):
        threading.Thread.__init__(self)
        self.queue = queue

    def run(self):
        while self.queue.qsize() > 0:
            # 取得新的資料
            URL = self.queue.get()
            # 處理資料
            Workload_B(URL)

def generate_thread(task_type, n_thread, n_instance):
    # 建立佇列
    input_queue = queue.Queue()
    # 將資料放入佇列
    for _ in range(n_instance):
        input_queue.put(input())
    # 建立兩個 Worker
    worker_list = []

    if task_type == '1':
        for _ in range(n_thread):
            worker = worker_thread_A(input_queue)
            worker_list.append(worker)
    elif task_type == '2':
        for _ in range(n_thread):
            worker = worker_thread_B(input_queue)
            worker_list.append(worker)
    
    start_time = time.perf_counter()
    for i in range(n_thread):
    # 讓 Worker 開始處理資料
        worker_list[i].start()

    # 等待所有 Worker 結束
    for i in range(n_thread):
    # 讓 Worker 開始處理資料
        worker_list[i].join()
    print(time.perf_counter() - start_time)

def process_A(queue):
    while True:
        # 取得新的資料
        item = queue.get(block=True) #block=True means make a blocking call to wait for items in queue
        if item is None:
            break
        # 處理資料
        str_S = item
        Workload_A(str_S)

def process_B(queue):
    while True:
        # 取得新的資料
        item = queue.get(block=True) #block=True means make a blocking call to wait for items in queue
        if item is None:
            break
        # 處理資料
        URL = item
        Workload_B(URL)
    
def generate_process(task_type, n_process, n_instance):
    # 建立佇列
    input_queue = multiprocessing.Queue()
    # 將資料放入佇列
    for _ in range(n_instance):
        input_queue.put(input())
    for _ in range(n_process):
        input_queue.put(None)
    start_time = time.perf_counter()
    if task_type == '1':
        pool = multiprocessing.Pool(n_process, process_A, (input_queue, ))
    elif task_type == '2':
        pool = multiprocessing.Pool(n_process, process_B, (input_queue, ))
    
    # prevent adding anything more to the queue and wait for queue to empty
    input_queue.close()
    input_queue.join_thread()

    # prevent adding anything more to the process pool and wait for all processes to finish
    pool.close()
    pool.join()
    print(time.perf_counter() - start_time)

async def async_Workload_A(str_S):
    await asyncio.sleep(0.001)
    Workload_A(str_S)

async def async_Workload_B(URL):
    await asyncio.sleep(0.001)
    Workload_B(URL)

loop = asyncio.get_event_loop() #建立一個Event Loop

def generate_coroutine(task_type, n_instance):
    # 建立佇列
    input_queue = queue.Queue()
    # 將資料放入佇列
    for _ in range(n_instance):
        input_queue.put(input())

    coroutines = []
    if task_type == '1':
        while input_queue.qsize() > 0:
            str_S = input_queue.get()
            task = loop.create_task(async_Workload_A(str_S))
            coroutines.append(task)
            
    elif task_type == '2':
        while input_queue.qsize() > 0:
            URL = input_queue.get()
            task = loop.create_task(async_Workload_B(URL))
            coroutines.append(task)

    start_time = time.perf_counter()
    loop.run_until_complete(asyncio.wait(coroutines))
    print(time.perf_counter() - start_time)

def multi_task(task_type, n_thread=0, n_process=0, n_instance=0):
    if n_thread > 0:
        generate_thread(task_type=task_type, n_thread=n_thread, n_instance=n_instance)
    elif n_process > 0:
        generate_process(task_type=task_type, n_process=n_process, n_instance=n_instance)
    else:
        generate_coroutine(task_type=task_type, n_instance=n_instance)

def main():
    # 1: Workload_A()   2: Workload_B()
    task_type = input()
    # 1: multithread    2: multiprocess     3: coroutine
    execute_way = input()
    n_instance = int(input())

    n_thread = 0
    n_process = 0
    if execute_way[0] == '1':
        n_thread = int(execute_way.split()[-1])
    elif execute_way[0] == '2':
        n_process = int(execute_way.split()[-1])
    multi_task(task_type=task_type, n_thread=n_thread, n_process=n_process, n_instance=n_instance)

if __name__ == '__main__':
    main()