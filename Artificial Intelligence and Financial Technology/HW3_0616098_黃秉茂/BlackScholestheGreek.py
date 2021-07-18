import math
from scipy.stats import norm 
import numpy as np
import matplotlib.pyplot as plt

def total_contract_value(S, contract_multiplier):
	return S * contract_multiplier

def leverage(S, contract_multiplier, the_least_money_in_account_to_buy_a_position):
	return total_contract_value(S, contract_multiplier) / the_least_money_in_account_to_buy_a_position

def index_margin_call(S, the_least_money_in_account_to_buy_a_position, the_least_money_in_account, contract_multiplier):
	return S - (the_least_money_in_account_to_buy_a_position - the_least_money_in_account) / contract_multiplier

def premium_call(call, contract_multiplier):
	return call * contract_multiplier

def out_of_the_money_for_short_call(K, S, contract_multiplier):
	return max((K - S) * contract_multiplier, 0)

def margin_call(call, K, S, contract_multiplier, A, B):
	return call * contract_multiplier + max(A - out_of_the_money_for_short_call(K, S, contract_multiplier), B)

def put_call_parity_call(call, K, r, T):
	return call + K * math.exp(-r * T)

def put_call_parity_put(put, S):
	return put + S

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

def bls_putprice(S, K, r, T, vol):
	D1 = d1(S, K, r, T, vol)
	D2 = d2(S, K, r, T, vol)
	put_price = K * math.exp(-r * T) * norm.cdf(-D2) - S * norm.cdf(-D1)
	return put_price

# 透過try and error慢慢逼近估出vol
def BisectionBLS(S, K, r, T, call_price):
	# vol的左界
	left = 0.00001
	# vol的右界
	right = 1
	#					confidence
	while (right - left) > 0.000001:
		middle = (left + right) / 2
		if bls_callprice(S, K, r, T, middle) > call_price:
			right = middle
		else:
			left = middle
	return (left + right) / 2

def delta_formula(S, K, r, T, vol):
	return norm.cdf(d1(S, K, r, T, vol))

print(bls_callprice(50, 40, 0.08, 2, 0.2))

S0 = np.arange(1, 100, 0.1)
y = np.zeros(len(S0))

for i in range(len(S0)):
	y[i] = bls_callprice(S0[i], 40, 0.08, 2, 0.2)

# plt.plot(S0, y)
# plt.show()

dx = 0.000001
delta = (bls_callprice(50 + dx, 40, 0.08, 2, 0.2) - bls_callprice(50 - dx, 40, 0.08, 2, 0.2)) / (2 * dx)
vega = (bls_callprice(50, 40, 0.08, 2, 0.2 + dx) - bls_callprice(50, 40, 0.08, 2, 0.2 - dx)) / (2 * dx)
theta = (bls_callprice(50, 40, 0.08, 2 - dx, 0.2) - bls_callprice(50, 40, 0.08, 2 + dx, 0.2)) / (2 * dx)
rho = (bls_callprice(50, 40, 0.08 + dx, 2, 0.2) - bls_callprice(50, 40, 0.08 - dx, 2, 0.2)) / (2 * dx)
print("delta =", delta)
print("vega =", vega)
print("theta =", theta)
print("rho =", rho)

vol = BisectionBLS(50, 40, 0.08, 2, 20)
print("vol =", vol)
print()
print('Q1')
print('total_contract_value:', total_contract_value(S=12947, contract_multiplier=200))
print('leverage:', leverage(S=12947, contract_multiplier=200, the_least_money_in_account_to_buy_a_position=148000))
print('index:', index_margin_call(S=12947, the_least_money_in_account_to_buy_a_position=148000, the_least_money_in_account=113000, contract_multiplier=200))
print('total_contract_value:', total_contract_value(S=12947, contract_multiplier=50))
print('leverage:', leverage(S=12947, contract_multiplier=50, the_least_money_in_account_to_buy_a_position=37000))
print('index:', index_margin_call(S=12947, the_least_money_in_account_to_buy_a_position=37000, the_least_money_in_account=28250, contract_multiplier=50))
print('premium_call:', premium_call(call=149, contract_multiplier=50))
print('margin_call:', margin_call(call=149, K=12900, S=12947, contract_multiplier=50, A=41000, B=21000))

print('Q2')
print('call_12900:', put_call_parity_call(call=149, K=12900, r=0.00755, T= 8 / 365))
print('put_12900:', put_call_parity_put(put=106, S=12947.13))
print('call_13000:', put_call_parity_call(call=95, K=13000, r=0.00755, T= 8 / 365))
print('put_13000:', put_call_parity_put(put=153, S=12947.13))

print('Q3')
vol_12900 = BisectionBLS(12947.13, 12900, 0.00755, 8 / 365, 149)
print(vol_12900)
print(bls_putprice(12947.13, 12900, 0.00755, 8 / 365, vol_12900))
print(bls_callprice(12947.13, 13000, 0.00755, 8 / 365, vol_12900))
print(bls_putprice(12947.13, 13000, 0.00755, 8 / 365, vol_12900))

delta_12900_formula = delta_formula(12947.13, 12900, 0.00755, 8 / 365, vol_12900)
print('delta_12900_formula:', delta_12900_formula)
dx = 0.000001
delta_12900_difference = (bls_callprice(12947.13 + dx, 12900, 0.00755, 8 / 365, vol_12900) - bls_callprice(12947.13 - dx, 12900, 0.00755, 8 / 365, vol_12900)) / (2 * dx)
print('delta_12900_difference:', delta_12900_difference)