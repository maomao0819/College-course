from numpy import array, dot
from qpsolvers import solve_qp
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import random
from functools import reduce
# M = array([[1., 2., 0.], [-8., 3., 2.], [0., 1., 1.]])
# P = dot(M.T, M)  # quick way to build a symmetric matrix
# q = dot(array([3., 2., 3.]), M).reshape((3,))
# G = array([[1., 2., 1.], [2., 0., 1.], [-1., 2., -1.]])
# h = array([3., 2., -2.]).reshape((3,))
# A = array([1., 1., 1.])
# b = array([1.])
# print('M ', np.shape(M))
# print('M ', np.shape(P))
# print('M ', np.shape(q))
# print('M ', np.shape(G))
# print('M ', np.shape(h))
# print('M ', np.shape(A))
# print('M ', np.shape(b))
# x = solve_qp(P, q, G, h, A, b)
# print("QP solution: x = {}".format(x))
print()
csv_file = "Stocks_ClosePrice.csv"
data = pd.read_csv(csv_file)
data.head()

return_data = data.iloc[1:, 6:11]
return_data.head()

mu = return_data.mean(axis=0)
cov = return_data.cov()

efficient_frontier_return_range = np.linspace(-0.001, 0.0015, 100)

def get_standard_deviation(weights):
    # return np.sqrt(np.matmul(np.matmul(weights, cov), weights))
    return np.sqrt(reduce(np.dot, [weights, cov, weights.T]))
# 
def get_return(weights):
    return np.sum(mu * weights)

M = array([[1., 2., 0.], [-8., 3., 2.], [0., 1., 1.]])
efficient_frontier_risk_list1 = []
# print(array([0] * 3).reshape((3, )))
# print(array([3., 2., 3.]).reshape((3,)))
mark = False
for i in efficient_frontier_return_range:
	P = np.array(cov * 2)
	q = array([1e-7] * 5).reshape((5, ))
	if mark == False:
		G = array([mu] * 5).reshape((-1, 5))
		h = array([i] * 5)
	if mark:
		G = array([-mu] * 5).reshape((-1, 5))
		h = array([-i] * 5)
	A = array([1] * 5)
	b = array([1])
	lb = array([-1] * 5)
	ub = array([1] * 5)
	w = solve_qp(P, q, G, h, A, b, lb, ub)
	if mark == False:
		if efficient_frontier_risk_list1:
			if get_standard_deviation(w) >= efficient_frontier_risk_list1[-1]:
				mark = True
				mvp_w = efficient_frontier_risk_list1[-1]
	efficient_frontier_risk_list1.append(get_standard_deviation(w))
print(mvp_w)
std = return_data.std()
plt.figure(figsize = (12, 6))
plt.title('Efficient Frontier (short sales are allowed)', fontsize=22, fontweight='bold')
# plt.scatter(mcStd_list, mcMu_list, color='b')
plt.scatter(std, mu, color='r', marker='*')
plt.plot(efficient_frontier_risk_list1, efficient_frontier_return_range, color='g', linewidth=1, marker='o')
plt.ylabel('Expected return (Mean)')
plt.xlabel('Risk (Std)')
plt.axis([0.016, 0.028, -0.002, 0.002])
plt.show()