import numpy as np
import math
import pandas as pd
from sklearn import datasets
from sklearn.utils import shuffle
from sklearn.model_selection import KFold

def load_data():
	iris = datasets.load_iris()
	x = pd.DataFrame(iris['data'], columns=iris['feature_names'])
	y = pd.DataFrame(iris['target'], columns=['target_labels'])
	iris_data = pd.concat([x, y], axis=1)
	return iris_data

def data_preprocess_drop_label_2(iris_data):
	iris_data.drop(iris_data.loc[iris_data['target_labels'] == 2].index, inplace=True)
	return iris_data

def get_feature(iris_data):
	feature = np.array(iris_data.drop(iris_data.columns[-1], axis=1))
	return feature

def get_target(iris_data):
	target = np.array(iris_data[iris_data.columns[-1]])
	return target

def entropy(p1, n1):
	if (p1 == 0 and n1 == 0):
		return 1
	elif (p1 == 0 or n1 == 0):
		return 0
	else:  
		pp = p1 / (p1 + n1)
		np = n1 / (p1 + n1)
		return -pp * math.log2(pp) - np * math.log2(np)

def Imformation_Gain(p1, n1, p2, n2):
	num = p1 + n1 + p2 + n2
	num1 = p1 + n1
	num2 = p2 + n2
	return entropy(p1 + p2, n1 + n2) - num1 / num * entropy(p1, n1) - num2 / num * entropy(p2, n2)

def Decision_Tree(x_train, y_train):
	node = dict()
	node['data'] = range(len(y_train))
	Tree = []
	Tree.append(node)
	t = 0
	while t < len(Tree):
		# 資料編號，該node的所有data
		idx = Tree[t]['data']
		# 當該node的所有label都是0
		if sum(y_train[idx]) == 0:
			Tree[t]['leaf'] = 1
			Tree[t]['decision'] = 0
		# 當該node的所有label都是1
		if sum(y_train[idx]) == len(idx):
			Tree[t]['leaf'] = 1
			Tree[t]['decision'] = 1
		else:
			best_Information_Gain = 0
			# 4 columns
			# try 4 個 feature, node中該feature的所有可能
			# i: feature
			for i in range(x_train.shape[1]):
				# pool: 這個node的feature有的種類 取set，會把重複的刪掉
				pool = list(set(x_train[idx, i]))
				pool.sort()
				# j: 該node中該feature的可能、種類，切在哪
				for j in range(len(pool) - 1):
					# 想利用threshold變成二分，就可以用binary tree
					threshold = (pool[j] + pool[j + 1]) / 2
					# sample's index
					Group1 = []
					Group2 = []
					for k in idx:
						if x_train[k, i] <= threshold:
							Group1.append(k)
						else:
							Group2.append(k)
					p1 = sum(y_train[Group1] == 1)
					n1 = sum(y_train[Group1] == 0)
					p2 = sum(y_train[Group2] == 1)
					n2 = sum(y_train[Group2] == 0)
					this_Information_Gain = Imformation_Gain(p1, n1, p2, n2)
					if this_Information_Gain > best_Information_Gain:
						best_Information_Gain = this_Information_Gain
						best_Group1 = Group1
						best_Group2 = Group2
						best_threshold = threshold
						best_feature = i
			if best_Information_Gain > 0:
				Tree[t]['leaf'] = 0
				Tree[t]['select_feature'] = best_feature
				Tree[t]['threshold'] = best_threshold
				# child存child node的index
				Tree[t]['child'] = [len(Tree), len(Tree) + 1]
				node = dict()
				node['data'] = best_Group1
				Tree.append(node)
				node = dict()
				node['data'] = best_Group2
				Tree.append(node)
			# 最好的切法沒什麼information gain
			else:
				Tree[t]['leaf'] = 1
				# 1的數量 > 0的數量
				if sum(y_train[idx] == 1) > sum(y_train[idx] == 0):
					Tree[t]['decision'] = 1
				else:
					Tree[t]['decision'] = 0
		t += 1
	return Tree

def Decision_Tree_Error_Rate(x_train, y_train, x_test, y_test):
	Tree = Decision_Tree(x_train, y_train)
	n_wrong = 0
	for i in range(len(y_test)):
		test_feature = x_test[i, :]
		now = 0
		while Tree[now]['leaf'] == 0:
			best_feature = Tree[now]['select_feature']
			threshold = Tree[now]['threshold']
			if test_feature[best_feature] <= threshold:
				now = Tree[now]['child'][0]
			else:
				now = Tree[now]['child'][1]
		if y_test[i] != Tree[now]['decision']:
			n_wrong += 1
	error_rate = n_wrong / len(y_test)
	return error_rate

def main():
	
	iris_data = load_data()
	iris_data = data_preprocess_drop_label_2(iris_data)
	
	shuffle_data = True
	
	if shuffle_data == True:	
		iris_data = shuffle(iris_data)
	
	iris_x = get_feature(iris_data)
	iris_y = get_target(iris_data)
	
	k_fold_sklearn = False
	k_fold_manual = True

	# k-fold cross validation
	if k_fold_sklearn:
		error_rate_list = []
		kf = KFold(n_splits=10, shuffle=False)
		for train_index, test_index in kf.split(iris_x):
			iris_x_train = iris_x[train_index]
			iris_y_train = iris_y[train_index]
			iris_x_test = iris_x[test_index]
			iris_y_test = iris_y[test_index]
			error_rate = Decision_Tree_Error_Rate(iris_x_train, iris_y_train, iris_x_test, iris_y_test)		
			error_rate_list.append(error_rate)

		for set_id, error_rate in enumerate(error_rate_list):
			print(f'Set {set_id + 1}\'s error rate: {error_rate}')
		print('Average error rate:', np.mean(error_rate))

	if k_fold_manual:
		error_rate_list = []
		set_len = int(len(iris_x) // 10)
		for set_id in range(10):
			iris_x_train = np.concatenate((iris_x[0 : set_id * set_len], iris_x[(set_id + 1) * set_len :]), axis=0)
			iris_y_train = np.concatenate((iris_y[0 : set_id * set_len], iris_y[(set_id + 1) * set_len :]), axis=0)
			iris_x_test = iris_x[set_id * set_len : (set_id + 1) * set_len]
			iris_y_test = iris_y[set_id * set_len : (set_id + 1) * set_len]
			error_rate = Decision_Tree_Error_Rate(iris_x_train, iris_y_train, iris_x_test, iris_y_test)		
			error_rate_list.append(error_rate)

		for set_id, error_rate in enumerate(error_rate_list):
			print(f'Set {set_id + 1}\'s error rate: {error_rate}')
		print('Average error rate:', np.mean(error_rate))

if __name__ == "__main__":
	main()