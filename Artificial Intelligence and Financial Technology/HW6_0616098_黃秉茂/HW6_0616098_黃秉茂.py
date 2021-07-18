import numpy as np
import collections
from sklearn import datasets
import matplotlib.pyplot as plt
import math
import random
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score

# load data
iris = datasets.load_iris()
X = iris.data
Y = iris.target

# Kmeans
def Kmeans(sample, K, max_iter):
	# N data
	N = sample.shape[0]
	# D dimension
	D = sample.shape[1]
	# 可寫可不寫 存K個center的座標
	C = np.zeros((K, D))
	# N個sample的label
	L = np.zeros((N, 1))
	# label last time, 用來看跟上次的label一樣不一樣
	L_last = np.zeros((N, 1))
	# distance
	dist = np.zeros((N, K))
	# 隨機找出K個中心點，從range(N)中抽取K個出來
	center_idx = random.sample(range(N), K)
	# center
	C = sample[center_idx, :]
	iteration = 0
	while(iteration < max_iter):
		for i in range(K):
			# 做sample(各點)與center(K個中心點)的距離
			# np.tile: copy, 將center往下copyN次往右copy1次
			# np.sum(axis=1): 做列的總和
			dist[:, i] = np.sqrt(np.sum((sample - np.tile(C[i, :], (N, 1))) ** 2, 1))
		# 哪個位置最小, 0 ~ K - 1
		L = np.argmin(dist, 1)
		# 收斂了
		if np.array_equal(L, L_last):
			break
		L_last = L
		for i in range(K):
			# 回傳True的index
			center_idx = np.nonzero(L == i)[0]
			# 沒東西的話sum, mean會出錯
			if len(center_idx) > 0:
				# 將群的重心當成新群的中心
				# np.mean(axis=0): 做行的平均
				C[i, :] = np.mean(sample[center_idx, :], 0)
		iteration += 1
	return C, L

def label_ascend(Group_label):
	index_mean = []
	Group_clustered_idx = []
	Group_clustered_idx.append(np.nonzero(Group_label == 0)[0])
	index_mean.append(np.mean(Group_clustered_idx[0]))
	Group_clustered_idx.append(np.nonzero(Group_label == 1)[0])
	index_mean.append(np.mean(Group_clustered_idx[1]))
	Group_clustered_idx.append(np.nonzero(Group_label == 2)[0])
	index_mean.append(np.mean(Group_clustered_idx[2]))
	label_0_group_idx = np.argmin(index_mean)
	Group_label[Group_clustered_idx[label_0_group_idx]] = 0
	label_2_group_idx = np.argmax(index_mean)
	Group_label[Group_clustered_idx[label_2_group_idx]] = 2
	label_1_group_idx = [i for i in range(3)]
	label_1_group_idx.remove(label_0_group_idx)
	label_1_group_idx.remove(label_2_group_idx)
	Group_label[Group_clustered_idx[label_1_group_idx[0]]] = 1
	return Group_label

data_preprocess = ['未經標準化', 'standard score', 'scaling']
accuracy_list = []
precision_list = []
recall_list = []
f1_list = []

# 未經標準化
print('未經標準化:')
Group_center, Group_label = Kmeans(X, 3, 1000)
Group_label = label_ascend(Group_label)
accuracy_list.append(accuracy_score(Y, Group_label))
print('accuracy:', accuracy_list[-1])
precision_list.append(precision_score(Y, Group_label, average='weighted'))
print('precision:', precision_list[-1])
recall_list.append(recall_score(Y, Group_label, average='weighted'))
print('recall:', recall_list[-1])
f1_list.append(f1_score(Y, Group_label, average='weighted'))
print('f1 score:', f1_list[-1])
print('------------------------------------------------------')

# standard score
print('standard score:')
std_X = ((X - np.mean(X, axis=0)) / np.std(X, axis=0))
Group_center, Group_label = Kmeans(std_X, 3, 1000)
Group_label = label_ascend(Group_label)
accuracy_list.append(accuracy_score(Y, Group_label))
print('accuracy:', accuracy_list[-1])
precision_list.append(precision_score(Y, Group_label, average='weighted'))
print('precision:', precision_list[-1])
recall_list.append(recall_score(Y, Group_label, average='weighted'))
print('recall:', recall_list[-1])
f1_list.append(f1_score(Y, Group_label, average='weighted'))
print('f1 score:', f1_list[-1])
print('------------------------------------------------------')

# scaling
print('scaling:')
scaling_X = ((X - np.amin(X, axis=0)) / (np.amax(X, axis=0) - np.amin(X, axis=0)))
Group_center, Group_label = Kmeans(scaling_X, 3, 1000)
Group_label = label_ascend(Group_label)
accuracy_list.append(accuracy_score(Y, Group_label))
print('accuracy:', accuracy_list[-1])
precision_list.append(precision_score(Y, Group_label, average='weighted'))
print('precision:', precision_list[-1])
recall_list.append(recall_score(Y, Group_label, average='weighted'))
print('recall:', recall_list[-1])
f1_list.append(f1_score(Y, Group_label, average='weighted'))
print('f1 score:', f1_list[-1])
print('------------------------------------------------------')

optimize_data_preprocess = data_preprocess[np.amax([np.argmax(accuracy_list), np.argmax(precision_list), np.argmax(recall_list), np.argmax(f1_list)])]
print(optimize_data_preprocess, 'is the best data preprocess\n')

# KNN
# test先找到N個和他最近的training data，，然後分類為K個中出現最多的label
def KNN(test, train, train_target, K):
	# N data
	N = train.shape[0]
	# 做test與train的距離
	# np.tile: copy, 將center往下copyN次往右copy1次
	# np.sum(axis=1): 做列的總和	
	dist = np.sum((train - np.tile(test, (N, 1))) ** 2, 1)
	# 最像的K個
	# 每個距離的排序，用距離當作sort的基準，distance小的排前面
	idx = sorted(range(len(dist)), key = lambda i:dist[i])[0: K]
	# 把target拿出來看哪個出現的最多
	return collections.Counter(train_target[idx]).most_common(1)[0][0]

confusion_matrix_10 = np.zeros((3, 3))
confusion_matrix_1 = np.zeros((3, 3))

for i in range(150):
	train_x = np.concatenate((X[0:i], X[i + 1:]), axis=0)
	train_y = np.concatenate((Y[0:i], Y[i+1:]), axis=0)
	test_x = X[i]
	test_y = Y[i]
	prdict_1 = KNN(test_x, train_x, train_y, 1)
	prdict_10 = KNN(test_x, train_x, train_y, 10)
	confusion_matrix_1[prdict_1][test_y] += 1
	confusion_matrix_10[prdict_10][test_y] += 1

print('1-NN confusion matrix:')
print(confusion_matrix_1)
print('------------------------------------------------------')
print('10-NN confusion matrix:')
print(confusion_matrix_10)