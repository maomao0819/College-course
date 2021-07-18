import random
import string
import time
import hashlib
import requests
import threading
import multiprocessing
from lxml.html import fromstring

finish_A = False

def get_random_string(N=5):
	letter = string.ascii_letters + string.digits + string.punctuation
	return ''.join(random.choice(letter) for _ in range(N))

def get_hash_value(str_C, str_S):
	SHA256 = hashlib.sha256()
	SHA256.update(str_C.encode("utf-8"))
	SHA256.update(str_S.encode("utf-8"))
	hash_value = SHA256.hexdigest()
	return hash_value

def Workload_A_thread(i, str_S):
	while True:
		str_C = get_random_string(5)
		hash_value = get_hash_value(str_C, str_S)
		hash_value_first_5_letter = hash_value[:5]
		global finish_A
		if hash_value_first_5_letter == '00000':
			print(str_C + str_S)
			finish_A = True
			break
		if finish_A == True:
			break

def Workload_A_process(idx, str_S, quit, foundit):
	while not quit.is_set():
		str_C = get_random_string(5)
		hash_value = get_hash_value(str_C, str_S)
		hash_value_first_5_letter = hash_value[:5]
		if hash_value_first_5_letter == '00000':
			print(str_C + str_S)
			check = True
			if check:
				SHA256 = hashlib.sha256()
				SHA256.update(str_C.encode("utf-8"))
				SHA256.update(str_S.encode("utf-8"))
				hash_value = SHA256.hexdigest()
				print(hash_value[:5])
			foundit.set()
			break

def Workload_B():
	URL = 'http://www.imdb.com/title/tt0108778/'
	r = requests.get(URL, auth=('user', 'pass'))
	if r.status_code == requests.codes.ok:
		content = fromstring(r.content)
		title = content.findtext('.//title')
		print(title)

def generate_thread(task_type, n_thread=0, n_instance=0):	
	if task_type == '1':
		str_S_list = [input() for _ in range(n_instance)]
		global finish_A
		for instance_idx in range(n_instance):
			str_S = str_S_list[instance_idx]
			finish_A = False
			start_time = time.perf_counter()
			thread_list = []
			for thread_idx in range(n_thread):
				thread = threading.Thread(target=Workload_A_thread, args=(thread_idx, str_S))
				thread_list.append(thread)
			for thread in thread_list:
				thread.start()
			for thread in thread_list:
				thread.join()	
			print(time.perf_counter() - start_time)
	elif task_type == '2':
		URL_list = [input() for _ in range(n_instance)]

def generate_process(task_type, n_process=0, n_instance=0):
	if task_type == '1':
		str_S_list = [input() for _ in range(n_instance)]
		for instance_idx in range(n_instance):
			str_S = str_S_list[instance_idx]
			start_time = time.perf_counter()
			quit = multiprocessing.Event()
			foundit = multiprocessing.Event()
			process_list = []
			for process_idx in range(n_process):
				process = multiprocessing.Process(target=Workload_A_process, args=(process_idx, str_S, quit, foundit))
				process.start()
			foundit.wait()
			quit.set()
			print(time.perf_counter() - start_time)
	elif task_type == '2':
		URL_list = [input() for _ in range(n_instance)]

def main():
	# 1: Workload_A()	2: Workload_B()
	task_type = input()
	# 1: multithread	2: multiprocess		3: coroutine
	execute_way = input()
	n_instance = int(input())

	if execute_way[0] == '1':
		n_thread = int(execute_way.split()[-1])
		generate_thread(task_type=task_type, n_thread=n_thread, n_instance=n_instance)
	elif execute_way[0] == '2':
		n_process = int(execute_way.split()[-1])
		generate_process(task_type=task_type, n_process=n_process, n_instance=n_instance)

if __name__ == '__main__':
	main()