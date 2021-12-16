import numpy as np
import math
import matplotlib.pyplot as plt
from scipy.stats import norm


def calculate_up_state_size(sigma, time_stamp):
	return math.exp(sigma * math.sqrt(time_stamp))

def calculate_down_state_size(sigma, time_stamp):
	return math.exp(-sigma * math.sqrt(time_stamp))

def calculate_up_move_probability(return_rate, dividend_yield, time_stamp, u, d):
	a = math.exp((return_rate - dividend_yield) * time_stamp)
	return (a - d) / (u - d)

def exercise_value(stock_price, strike_price, option_type):
	# call
	if option_type == 1:
		return max(stock_price - strike_price, 0)
	# put
	elif option_type == 2:
		return max(strike_price - stock_price, 0)

def option_price_binomial_model_normal(initial_stock_price, strike_price, return_rate, n_term, time_stamp, u, d, p, option_type):
	stock_price = np.zeros((n_term + 1, n_term + 1))
	option_price_binomial = np.zeros((n_term + 1, n_term + 1))
	stock_price[0, 0] = initial_stock_price
	# stock price
	for term_id in range(1, n_term + 1):
		for i in range(term_id + 1):
			stock_price[i, term_id] = initial_stock_price * math.pow(u, (term_id - i)) * math.pow(d, i)

	# terminated option price
	for i in range(term_id + 1):
			option_price_binomial[i, n_term] = exercise_value(stock_price[i, n_term], strike_price, option_type)
	# option price
	for term_id in range(n_term - 1, 0 - 1, -1):
		for i in range(term_id + 1):
			option_price_binomial[i, term_id] = (p * option_price_binomial[i, term_id + 1] + (1 - p) * option_price_binomial[i + 1, term_id + 1]) * math.exp(-return_rate * time_stamp)
	return option_price_binomial[0, 0]

def option_price_binomial_model_early(initial_stock_price, strike_price, return_rate, n_term, time_stamp, u, d, p, option_type):
	stock_price = np.zeros((n_term + 1, n_term + 1))
	option_price_binomial_normal = np.zeros((n_term + 1, n_term + 1))
	stock_price[0, 0] = initial_stock_price
	# stock price
	for term_id in range(1, n_term + 1):
		for i in range(term_id + 1):
			stock_price[i, term_id] = initial_stock_price * math.pow(u, (term_id - i)) * math.pow(d, i)
	# terminated option price
	for i in range(term_id + 1):
			option_price_binomial_normal[i, n_term] = exercise_value(stock_price[i, n_term], strike_price, option_type)
	# option price
	for term_id in range(n_term - 1, 0 - 1, -1):
		for i in range(term_id + 1):
			option_price_binomial_normal[i, term_id] = (p * option_price_binomial_normal[i, term_id + 1] + (1 - p) * option_price_binomial_normal[i + 1, term_id + 1]) * math.exp(-return_rate * time_stamp)
			option_price_binomial_exercise = exercise_value(stock_price[i, n_term], strike_price, option_type)
			if option_price_binomial_exercise > option_price_binomial_normal[i, term_id]:
				option_price_binomial_normal[i, term_id] = option_price_binomial_exercise
	return option_price_binomial_normal[0, 0]

def Black_Scholes_Model(sigma, maturity, return_rate, initial_stock_price, strike_price, dividend_yield, option_type):
	d1 = (math.log(initial_stock_price / strike_price) + ((return_rate - dividend_yield) + sigma * sigma / 2) * maturity) / (sigma * math.sqrt(maturity))
	d2 = (math.log(initial_stock_price / strike_price) + ((return_rate - dividend_yield) - sigma * sigma / 2) * maturity) / (sigma * math.sqrt(maturity))
	N_d1 = norm.cdf(d1)
	N_d2 = norm.cdf(d2)
	if option_type == 1:
		BS_call = initial_stock_price * math.exp(-dividend_yield * maturity) * N_d1 - strike_price * math.exp(-return_rate * maturity) * N_d2
		return BS_call
	elif option_type == 2:
		BS_put = strike_price * math.exp(-return_rate * maturity) * (1 - N_d2) - initial_stock_price * math.exp(-dividend_yield * maturity) * (1 - N_d1)
		return BS_put

def n_choose_k(n, k):
	if k > n / 2:
		k = n - k;
	if k == 0:
		return 1
	return float(n * n_choose_k(n - 1, k - 1)) / k;

if __name__ == '__main__':
	initial_stock_price = 50.0
	volatilaty = 0.3
	strike_price = 52
	maturity = 2.0
	interest_rate = 5 / 100
	n_time = 3
	time_stamp = np.zeros(n_time, dtype=np.int)
	time_stamp = [1 / 12, 1 / 52, 1 / 252]
	n_term = np.zeros(n_time)
	dividend_yield = 0
	# a
	print("(a) First compute the up step size u, the down step size d, and the probability of up ", end='')
	print("move p under these three settings.\n")
	u = np.zeros(n_time)
	d = np.zeros(n_time)
	p = np.zeros(n_time)

	for i in range(n_time):
		n_term[i] = int(maturity * (1 / time_stamp[i]))
		u[i] = calculate_up_state_size(volatilaty, time_stamp[i])
		d[i] = calculate_down_state_size(volatilaty, time_stamp[i])
		p[i] = calculate_up_move_probability(interest_rate, 0, time_stamp[i], u[i], d[i])
	for i in range(n_time):
		print("When " + str(int(n_term[i])) + " time steps, u = " + str(u[i]) + ", d = " + str(d[i]) + ", p = " + str(p[i]) + ".\n")

	print("\n\n")

	# b
	print("(b) Use binomial model to compute the put option prices under these three settings. ", end='')
	print("Report your results and compare them with that of the Black-Scholes formula. Briefly ", end='')
	print("move p under these three settings.\n")

	option_type = 2
	put_option_price_binomial_EU = np.zeros(n_time)
	put_option_price_BS = np.zeros(n_time)
	for i in range(n_time):
		print("When " + str(int(n_term[i])) + " time steps:\n")
		put_option_price_binomial_EU[i] = option_price_binomial_model_normal(initial_stock_price, strike_price, interest_rate, int(n_term[i]), time_stamp[i], u[i], d[i], p[i], option_type)
		put_option_price_BS[i] = Black_Scholes_Model(volatilaty, maturity, interest_rate, initial_stock_price, strike_price, 0, option_type)
		print("\tThe put option prices of the binomial model: " + str(put_option_price_binomial_EU[i]) + "\n")
		print("\tThe put option prices of the Black-Scholes formula: " + str(put_option_price_BS[i]) + "\n")
		print("\tThe difference between them: " + str(put_option_price_BS[i] - put_option_price_binomial_EU[i]) + "\n")

	print("\n\n")

	# c
	print("(c) Modify your program in (b) to compute the American put option values. Report your result.\n")

	put_option_price_binomial_AM = np.zeros(n_time)
	# put_option_price_BS[n_time] =
	for i in range(n_time):
		print("When " + str(int(n_term[i])) + " time steps:\n")
		put_option_price_binomial_AM[i] = option_price_binomial_model_early(initial_stock_price, strike_price, interest_rate, int(n_term[i]), time_stamp[i], u[i], d[i], p[i], option_type)
		# put_option_price_BS[i] = Black_Scholes_Model(volatilaty, maturity, interest_rate, initial_stock_price, strike_price, 0, option_type)
		print("\tThe put option prices of the binomial model: " + str(put_option_price_binomial_AM[i]) + "\n")
		print("\tThe put option prices of the Black-Scholes formula: " + str(put_option_price_BS[i]) + "\n")
		print("\tThe difference between them: " + str(put_option_price_BS[i] - put_option_price_binomial_AM[i]) + "\n")

	print("\n\n")

	# d
	print("(d) Change the number of time steps from 1 to 2 to 3 all the way to 252 to ", end='')
	print("calculate European put option prices. Plot your results as well as the Black-Scholes ", end='')
	print("closed form solution. Briefly math.explain your findings.\n")
	put_binomial_EU = np.zeros(252)
	put_BS = np.zeros(252)
	put_BS_temp = Black_Scholes_Model(volatilaty, maturity, interest_rate, initial_stock_price, strike_price, 0, option_type)
	time_steps = np.zeros(252)
	for time_step in range(1, 252 + 1):
		time_steps[time_step - 1] = time_step
		time_stamp = maturity / time_step
		u = calculate_up_state_size(volatilaty, time_stamp)
		d = calculate_down_state_size(volatilaty, time_stamp)
		p = calculate_up_move_probability(interest_rate, 0, time_stamp, u, d)
		put_binomial_EU[time_step - 1] = option_price_binomial_model_normal(initial_stock_price, strike_price, interest_rate, time_step, time_stamp, u, d, p, option_type)
		put_BS[time_step - 1] = put_BS_temp

	plt.title('green: binomial EU red: Black Scholes')
	plt.xlabel('time steps')
	plt.ylabel('put option price')
	plt.plot(time_steps, put_binomial_EU, 'g')
	plt.plot(time_steps, put_BS, 'r')
	plt.savefig(f'd.png')
	plt.show()

	print("\n\n")

	# bonus
	print("Bonus For 6, 12, and 52 time steps, compute the terminal stock prices as well as ", end='')
	print("their corresponding probabilities. Plot the terminal stock price distribution. Briefly ", end='')
	print("math.explain your findings.\n")

	time_steps_specific = np.zeros(3)
	time_steps_specific = [6, 12, 52]
	for time_step_id in range(3):
		time_step = time_steps_specific[time_step_id]
		print("When " + str(time_step) + " time steps:\n")
		time_stamp = maturity / time_step
		u = calculate_up_state_size(volatilaty, time_stamp)
		d = calculate_down_state_size(volatilaty, time_stamp)
		p = calculate_up_move_probability(interest_rate, 0, time_stamp, u, d)
		# terminal stock price
		terminal_stock_price = np.zeros(time_step + 1)
		probability = np.zeros(time_step + 1)
		for i in range(time_step + 1):
			terminal_stock_price[i] = initial_stock_price * math.pow(u, (time_step - i)) * math.pow(d, i)
			probability[i] = n_choose_k(time_step, i) * math.pow(p, (time_step - i)) * math.pow((1 - p), i)
		plt.title(f'{time_step} time steps probability distribution')
		plt.xlabel('terminal stock price')
		plt.ylabel('probability')
		plt.plot(terminal_stock_price, probability)
		plt.savefig(f'bonus_{time_step}.png')
		plt.show()