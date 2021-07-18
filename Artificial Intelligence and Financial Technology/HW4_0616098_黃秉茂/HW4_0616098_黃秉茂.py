import math
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm 
import operator as op
from functools import reduce

def Discount(price, r, T):
	return price * np.exp(-r * T)

# Binomial Tree
# S0: 原始價值	K: 履約價	T: 到期年限	r: 無風險利率 vol: volatility	N: depth of tree
def BTcall(S0, K, T, r, vol, N):
	dt = T / N
	# u: 漲	d: 跌
	u = math.exp(vol * math.sqrt(dt))
	d = 1 / u
	# price
	priceT = np.zeros((N + 1, N + 1))
	priceT[0][0] = S0
	for col in range(N):
		# u 是往右推
		priceT[0][col + 1] = priceT[0][col] * u
		# d 是把所有的往右下推
		for row in range(col + 1):
			priceT[row + 1][col + 1] = priceT[row][col] * d
	# probability
	p = (math.exp(r * dt) - d) / (u - d)
	probT = np.zeros((N + 1, N + 1))
	probT[0][0] = 1
	for col in range(N):
		for row in range(col + 1):
			probT[row][col + 1] += probT[row][col] * p
			probT[row + 1][col + 1] += probT[row][col] * (1 - p)
	call = 0
	for row in range(N + 1):
		if (priceT[row][N] > K):
			call += (priceT[row][N] - K) * probT[row][N]
	# 還要再折現
	return Discount(call, r, T)

def ncr(n, r):
    r = min(r, n - r)
    numer = reduce(op.mul, range(n, n-r, -1), 1)
    denom = reduce(op.mul, range(1, r+1), 1)
    return numer // denom  # or / in Python 2

def BTcall_formula(S0, K, T, r, vol, N):
	dt = T / N
	u = math.exp(vol * math.sqrt(dt))
	d = 1 / u
	priceT = np.zeros((N + 1, N + 1))

	for col in range(N + 1):
		for row in range(col + 1):
			priceT[row][col] = S0 * (u ** (col - row)) * (d ** row)
	p = (math.exp(r * dt) - d) / (u - d)
	p_complement = 1 - p
	probT = np.zeros((N + 1, N + 1))
	for col in range(N + 1):
		for row in range(col + 1):
			probT[row][col] = 1 * ncr(col, row) * (p ** (col - row)) * (p_complement ** row)
	call = 0
	ST_premium = np.clip(priceT[:, N], K, None)
	call = np.dot(ST_premium - K, probT[:, N])
	return Discount(call, r, T)

def BTcall_formula_fast(S0, K, T, r, vol, N):
	dt = T / N
	u = math.exp(vol * math.sqrt(dt))
	d = 1 / u
	priceT = np.zeros(N + 1)
	for i in range(N + 1):
		priceT[i] = S0 * (u ** (N - i)) * (d ** i)
	p = (math.exp(r * dt) - d) / (u - d)
	p_complement = 1 - p
	probT = np.zeros(N + 1)
	for i in range(N + 1):
		probT[i] = 1 * ncr(N, i) * (p ** (N - i)) * (p_complement ** i)
	ST_premium = np.clip(priceT, K, None)
	call = np.dot(ST_premium - K, probT)
	return Discount(call, r, T)

# 股價從S0模擬N次到ST
def MCsim(S0, T, r, vol, N):
	dt = T / N
	ST = np.zeros((N + 1))
	ST[0] = S0
	for t in range(N):
		ST[t + 1] = ST[t] * math.exp((r - 0.5 * vol * vol) * dt + vol * np.random.normal() * math.sqrt(dt))
	return ST

def MCsim_multiple(S0, T, r, vol, N, number):
	dt = T / N
	ST = np.zeros((number, N + 1))
	ST[:, 0] = [S0] * number
	for t in range(N):
		# factor = [math.exp((r - 0.5 * vol * vol) * dt + vol * np.random.normal() * math.sqrt(dt)) for j in range(number)]
		factor = np.random.normal(size=number)
		factor = np.exp((r - 0.5 * vol * vol) * dt + vol * factor * np.sqrt(dt))
		ST[:, t + 1] = ST[:, t] * factor
	return ST

# n_term: 跑幾期，幾個收盤價		n_time: 跑幾次
def MCsim_EU_opt_call(S0, K, T, r, vol, n_term, n_time):
	call = 0
	for i in range(n_time):
		ST = MCsim(S0, T, r, vol, n_term)
		# ST[-1]: 到期那天的價值
		value = ST[-1]	
		if (value > K):
			call += (value - K) / n_time
	return Discount(call, r, T)

def MCsim_multiple_EU_opt_call(S0, K, T, r, vol, n_term, n_time):
	ST = MCsim_multiple(S0, T, r, vol, n_term, n_time)
	# ST[-1]: 到期那天的價值
	ST_premium = ST[:, -1]	
	ST_premium -= K
	ST_premium = ST_premium.clip(min=0)
	# call = np.sum(ST_premium) / n_time
	call = np.mean(ST_premium)
	return Discount(call, r, T)

def MCsim_multiple_EU_opt_ST_premium(S0, K, T, r, vol, n_term, n_time):
	ST = MCsim_multiple(S0, T, r, vol, n_term, n_time)
	# ST[-1]: 到期那天的價值
	ST_premium = ST[:, -1]	
	ST_premium -= K
	ST_premium = ST_premium.clip(min=0)
	# print(np.sum(ST_premium) / n_time)
	print(np.mean(ST_premium))
	return ST_premium

def MCsim_Asia_opt_call(S0, K, T, r, vol, n_term, n_time):
	call = 0
	for i in range(n_time):
		ST = MCsim(S0, T, r, vol, n_term)
		value = np.mean(ST)
		if (value > K):
			call += (value - K) / n_time
	return Discount(call, r, T)

def MCsim_multiple_Asia_opt_call(S0, K, T, r, vol, n_term, n_time):
	ST = MCsim_multiple(S0, T, r, vol, n_term, n_time)
	value = np.mean(ST, axis=1)	
	value_premium = value - K
	value_premium = value_premium.clip(min=0)
	# call = np.sum(ST_premium) / n_time
	call = np.mean(value_premium)
	return Discount(call, r, T)

def d1(S, K, r, T, vol):
	return (math.log(S / K) + (r + vol * vol / 2) * T) / (vol * math.sqrt(T))

def d2(S, K, r, T, vol):
	return d1(S, K, r, T, vol) - vol * math.sqrt(T)

# S: 現在的價值 K: 履約價 r: 無風險年利率 T: 還要多久會到到期日(年) vol: 波動率，對商品波動的預測
def bls_callprice(S, K, r, T, vol):
	D1 = d1(S, K, r, T, vol)
	D2 = d2(S, K, r, T, vol)
	call_price = S * norm.cdf(D1) - K * math.exp(-r * T) * norm.cdf(D2)
	return call_price

# Q1
print('----- Q1 -----')
Q1 = MCsim_multiple(50, 2, 0.08, 0.2, 100, 20000)
plt.ylabel('stock price')
for i in range(3):
	range_time = 200 * 10 ** i
	plt.title(f'Q1. Monte Carlo methods  first {range_time} times stock price distribution')
	plt.hist(Q1[0:range_time, -1], bins=80)
	plt.xlabel('number')
	plt.ylabel('stock price')
	plt.savefig(f'Q1_{range_time}.png')
	plt.show()

# Q2
print('----- Q2 -----')
Q2_1 = MCsim_multiple(50, 2, 0.08, 0.2, 100, 100000)
Q2_2 = MCsim_multiple(50, 2, 0.08, 0.4, 100, 100000)
Q2_index = np.arange(100000 + 1)
plt.title('Q2. red: vol = 0.2  green: vol = 0.4')
plt.xlabel('each simulation')
plt.ylabel('stock price')
plt.plot(Q2_index[1:], Q2_2[:, -1], 'g')
plt.plot(Q2_index[1:], Q2_1[:, -1], 'r')
plt.savefig(f'Q2.png')
plt.show()

# Q3
Q3_term = []
Q3_MC_100_error = []
Q3_MC_1000_error = []
Q3_MC_10000_error = []
print('----- Q3 -----')
for i in range(3):
	term = 100 * 10 ** i
	Q3_term.append(term)
	Q3_bls_callprice = bls_callprice(50, 40, 0.08, 2, 0.2)
	print('black-scholes model:', Q3_bls_callprice)
	Q3_ST_premium = MCsim_multiple_EU_opt_ST_premium(50, 40, 2, 0.08, 0.2, term, 10000)
	# Q3_MC_100 = np.sum(Q3_ST_premium[0:100]) / 100
	Q3_MC_100 = np.mean(Q3_ST_premium[0:100])
	print(f'Monte Carlo methods 切{term}期, 模擬前100次:', Q3_MC_100)
	# Q3_MC_1000 = np.sum(Q3_ST_premium[0:1000]) / 1000
	Q3_MC_1000 = np.mean(Q3_ST_premium[0:1000])
	print(f'Monte Carlo methods 切{term}期, 模擬前1000次:', Q3_MC_1000)
	# Q3_MC_10000 = np.sum(Q3_ST_premium[0:10000]) / 10000
	Q3_MC_10000 = np.mean(Q3_ST_premium[0:10000])
	print(f'Monte Carlo methods 切{term}期, 模擬前10000次:', Q3_MC_10000)
	Q3_MC_100_error.append(np.abs(Q3_bls_callprice - Q3_MC_100))
	print(f'Monte Carlo methods 切{term}期, 模擬前100次 與 black-scholes model 的絕對誤差:', Q3_MC_100_error[i])
	Q3_MC_1000_error.append(np.abs(Q3_bls_callprice - Q3_MC_1000))
	print(f'Monte Carlo methods 切{term}期, 模擬前1000次 與 black-scholes model 的絕對誤差:', Q3_MC_1000_error[i])
	Q3_MC_10000_error.append(np.abs(Q3_bls_callprice - Q3_MC_10000))
	print(f'Monte Carlo methods 切{term}期, 模擬前10000次 與 black-scholes model 的絕對誤差:', Q3_MC_10000_error[i])
plt.title('Q4. Abosolute error  red: first 100 times  green: first 1000 times  blue: first 10000 times')
plt.xlabel('the number of terms')
plt.ylabel('call price')
plt.plot(Q3_term, Q3_MC_100_error, 'r', Q3_term, Q3_MC_1000_error, 'g', Q3_term, Q3_MC_10000_error, 'b')
plt.savefig(f'Q3.png')
plt.show()

# Q4
print('----- Q4 -----')
Q4_BTcall = []
Q4_diff = []
Q4_term = []
Q4_bls_callprice = bls_callprice(50, 40, 0.08, 2, 0.2)
print('black-scholes model:', Q4_bls_callprice)
for i in range(4):
	Q4_n_term = 10 ** (i + 1)
	Q4_term.append(Q4_n_term)
	print(f'切{Q4_n_term}期:')
	Q4_BTcall.append(BTcall(50, 40, 2, 0.08, 0.2, Q4_n_term))
	print('Binomial Model:', Q4_BTcall[i])
	Q4_diff.append(np.abs(Q4_BTcall[i] - Q4_bls_callprice))
	print('Abosolute distance:', Q4_diff[i])
plt.title('Q4. Abosolute distance')
plt.xlabel('the number of terms')
plt.ylabel('call price')
plt.plot(Q4_term, Q4_diff, 'r')
plt.savefig(f'Q4.png')
plt.show()

# Q5
print('----- Q5 -----')
print(MCsim_multiple_Asia_opt_call(50, 40, 2, 0.08, 0.2, 1000, 1000))