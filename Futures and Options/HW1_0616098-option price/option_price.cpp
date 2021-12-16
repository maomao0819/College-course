#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

float dividend_yield = (float)0;
float calculate_up_state_size(float sigma, float time_stamp);
float calculate_down_state_size(float sigma, float time_stamp);
float calculate_up_move_probability(float return_rate, float dividend_yield, float time_stamp, float u, float d);
float exercise_value(float stock_price, int strike_price, int option_type);
float option_price_binomial_model_normal(float initial_stock_price, int strike_price, float return_rate, int n_term, float time_stamp, float u, float d, float p, int option_type);
float option_price_binomial_model_early(float initial_stock_price, int strike_price, float return_rate, int n_term, float time_stamp, float u, float d, float p, int option_type);
float normalCDF(float value);
float Black_Scholes_Model(float sigma, float maturity, float return_rate, float initial_stock_price, float strike_price, float dividend_yield, int option_type);
float n_choose_k(int n, int k);
int main ()
{
	float initial_stock_price = (float)50.0;
	float volatilaty = (float)0.3;
	int strike_price = 52;
	float maturity = (float)2.0;
	float interest_rate = (float)5 / 100;
	int n_time = 3;
	float time_stamp[n_time] = {(float)1 / 12, (float)1 / 52, (float)1 / 252};
	int n_term[n_time] = {0};

	// a
	cout << "(a) First compute the up step size u, the down step size d, and the probability of up "
		<< "move p under these three settings.\n";

	float u[n_time] = {0};
	float d[n_time] = {0};
	float p[n_time] = {0};

	for (int i = 0; i < n_time; i++)
	{
		n_term[i] = round(maturity * (1 / time_stamp[i]));
		u[i] = calculate_up_state_size(volatilaty, time_stamp[i]);
		d[i] = calculate_down_state_size(volatilaty, time_stamp[i]);
		p[i] = calculate_up_move_probability(interest_rate, 0, time_stamp[i], u[i], d[i]);
	}
	for (int i = 0; i < n_time; i++)
		cout << "When " << n_term[i] << " time steps, u = " << u[i] << ", d = " << d[i] << ", p = " << p[i] << ".\n";

    cout << "\n\n";

	// b
	cout << "(b) Use binomial model to compute the put option prices under these three settings. "
		<< "Report your results and compare them with that of the Black-Scholes formula. Briefly "
		<< "explain your findings.\n";

	int option_type = 2;
	float put_option_price_binomial_EU[n_time] = {0};
	float put_option_price_BS[n_time] = {0};
	for (int i = 0; i < n_time; i++)
	{
		cout << "When " << n_term[i] << " time steps:\n";
		put_option_price_binomial_EU[i] = option_price_binomial_model_normal(initial_stock_price, strike_price, interest_rate, n_term[i], time_stamp[i], u[i], d[i], p[i], option_type);
		put_option_price_BS[i] = Black_Scholes_Model(volatilaty, maturity, interest_rate, initial_stock_price, strike_price, 0, option_type);
		cout << "\tThe put option prices of the binomial model: " << put_option_price_binomial_EU[i] << "\n";
		cout << "\tThe put option prices of the Black-Scholes formula: " << put_option_price_BS[i] << "\n";
		cout << "\tThe difference between them: " << put_option_price_BS[i] - put_option_price_binomial_EU[i] << "\n";
	}

	cout << "\n\n";

	// c
	cout << "(c) Modify your program in (b) to compute the American put option values. Report your result.\n";

	float put_option_price_binomial_AM[n_time] = {0};
	// float put_option_price_BS[n_time] = {0};
	for (int i = 0; i < n_time; i++)
	{
		cout << "When " << n_term[i] << " time steps:\n";
		put_option_price_binomial_AM[i] = option_price_binomial_model_early(initial_stock_price, strike_price, interest_rate, n_term[i], time_stamp[i], u[i], d[i], p[i], option_type);
		// put_option_price_BS[i] = Black_Scholes_Model(volatilaty, maturity, interest_rate, initial_stock_price, strike_price, 0, option_type);
		cout << "\tThe put option prices of the binomial model: " << put_option_price_binomial_AM[i] << "\n";
		cout << "\tThe put option prices of the Black-Scholes formula: " << put_option_price_BS[i] << "\n";
		cout << "\tThe difference between them: " << put_option_price_BS[i] - put_option_price_binomial_AM[i] << "\n";
	}

	cout << "\n\n";

	// d
	cout << "(d) Change the number of time steps from 1 to 2 to 3 all the way to 252 to "
        << "calculate European put option prices. Plot your results as well as the Black-Scholes "
        << "closed form solution. Briefly explain your findings.\n";

    float put_binomial_EU[252] = {0};
    float put_BS[252] = {0};
	float put_BS_temp = Black_Scholes_Model(volatilaty, maturity, interest_rate, initial_stock_price, strike_price, 0, option_type);
	int time_steps[252] = {0};
	for (int time_step = 1; time_step <= 252; time_step++)
	{
		time_steps[time_step - 1] = time_step;
		float time_stamp = maturity / time_step;
		float u = calculate_up_state_size(volatilaty, time_stamp);
		float d = calculate_down_state_size(volatilaty, time_stamp);
		float p = calculate_up_move_probability(interest_rate, 0, time_stamp, u, d);
		put_binomial_EU[time_step - 1] = option_price_binomial_model_normal(initial_stock_price, strike_price, interest_rate, time_step, time_stamp, u, d, p, option_type);
		put_BS[time_step - 1] = put_BS_temp;
	}
	// plot(time_steps, put_binomial_EU);
	// plot(time_steps, put_BS);

	cout << "\n\n";

	// d
	cout << "Bonus For 6, 12, and 52 time steps, compute the terminal stock prices as well as "
        << "their corresponding probabilities. Plot the terminal stock price distribution. Briefly "
        << "explain your findings.\n";

    int time_steps_specific[3] = {6, 12, 52};
    for (int time_step_id = 0; time_step_id < 3; time_step_id++)
    {
        int time_step = time_steps_specific[time_step_id];
        cout << "When " << time_step << " time steps:\n";
        float time_stamp = maturity / time_step;
		float u = calculate_up_state_size(volatilaty, time_stamp);
		float d = calculate_down_state_size(volatilaty, time_stamp);
		float p = calculate_up_move_probability(interest_rate, 0, time_stamp, u, d);
		// terminal stock price
		float terminal_stock_price[time_step + 1];
		float probability[time_step + 1];
        for (int i = 0; i < time_step + 1; i++)
        {
            terminal_stock_price[i] = initial_stock_price * pow(u, (time_step - i)) * pow(d, i);
            probability[i] = n_choose_k(time_step, i) * pow(p, (time_step - i)) * pow((1 - p), i);
        }
        // plot(probability, terminal_stock_price);
    }
	return 0;
}

float calculate_up_state_size(float sigma, float time_stamp)
{
	return exp(sigma * sqrt(time_stamp));
}

float calculate_down_state_size(float sigma, float time_stamp)
{
	return exp(-sigma * sqrt(time_stamp));
}

float calculate_up_move_probability(float return_rate, float dividend_yield, float time_stamp, float u, float d)
{
	float a = exp((return_rate - dividend_yield) * time_stamp);
	return (a - d) / (u - d);
}

float exercise_value(float stock_price, int strike_price, int option_type)
{
    // call
    if (option_type == 1)
        return max(stock_price - strike_price, (float)0.0);
    // put
    else if (option_type == 2)
        return max(strike_price - stock_price, (float)0.0);
}

float option_price_binomial_model_normal(float initial_stock_price, int strike_price, float return_rate, int n_term, float time_stamp, float u, float d, float p, int option_type)
{
	float stock_price[n_term + 1][n_term + 1] = {0};
	float option_price_binomial[n_term + 1][n_term + 1] = {0};
	stock_price[0][0] = initial_stock_price;
	// stock price
	for (int term_id = 1; term_id < n_term + 1; term_id++)
        for (int i = 0; i <= term_id; i++)
            stock_price[i][term_id] = initial_stock_price * pow(u, (term_id - i)) * pow(d, i);

	// terminated option price
	for (int i = 0; i <= n_term; i++)
			option_price_binomial[i][n_term] = exercise_value(stock_price[i][n_term], strike_price, option_type);
	// option price
	for (int term_id = n_term - 1; term_id >= 0; term_id--)
		for (int i = 0; i <= term_id; i++)
			option_price_binomial[i][term_id] = (p * option_price_binomial[i][term_id + 1] + (1 - p) * option_price_binomial[i + 1][term_id + 1]) * exp(-return_rate * time_stamp);
	return option_price_binomial[0][0];
}

float option_price_binomial_model_early(float initial_stock_price, int strike_price, float return_rate, int n_term, float time_stamp, float u, float d, float p, int option_type)
{
	float stock_price[n_term + 1][n_term + 1] = {0};
	float option_price_binomial_normal[n_term + 1][n_term + 1] = {0};
	stock_price[0][0] = initial_stock_price;
	// stock price
	for (int term_id = 1; term_id < n_term + 1; term_id++)
		for (int i = 0; i <= term_id; i++)
			stock_price[i][term_id] = initial_stock_price * pow(u, (term_id - i)) * pow(d, i);
	// terminated option price
	for (int i = 0; i <= n_term; i++)
			option_price_binomial_normal[i][n_term] = exercise_value(stock_price[i][n_term], strike_price, option_type);
	// option price
	for (int term_id = n_term - 1; term_id >= 0; term_id--)
	{
		for (int i = 0; i <= term_id; i++)
		{
			option_price_binomial_normal[i][term_id] = (p * option_price_binomial_normal[i][term_id + 1] + (1 - p) * option_price_binomial_normal[i + 1][term_id + 1]) * exp(-return_rate * time_stamp);
			float option_price_binomial_exercise = exercise_value(stock_price[i][n_term], strike_price, option_type);
			if (option_price_binomial_exercise > option_price_binomial_normal[i][term_id])
				option_price_binomial_normal[i][term_id] = option_price_binomial_exercise;
		}
	}
	return option_price_binomial_normal[0][0];
}

float normalCDF(float value)
{
   return 0.5 * erfc(-value * M_SQRT1_2);
}

float Black_Scholes_Model(float sigma, float maturity, float return_rate, float initial_stock_price, float strike_price, float dividend_yield, int option_type)
{
	float d1 = (log(initial_stock_price / strike_price) + ((return_rate - dividend_yield) + sigma * sigma / 2) * maturity) / (sigma * sqrt(maturity));
	float d2 = (log(initial_stock_price / strike_price) + ((return_rate - dividend_yield) - sigma * sigma / 2) * maturity) / (sigma * sqrt(maturity));
	float N_d1 = normalCDF(d1);
	float N_d2 = normalCDF(d2);

	if (option_type == 1)
	{
		float BS_call = initial_stock_price * exp(-dividend_yield * maturity) * N_d1 - strike_price * exp(-return_rate * maturity) * N_d2;
		return BS_call;
	}
	else if (option_type == 2)
	{
		float BS_put = strike_price * exp(-return_rate * maturity) * (1 - N_d2) - initial_stock_price * exp(-dividend_yield * maturity) * (1 - N_d1);
		return BS_put;
	}
}

float n_choose_k(int n, int k)
{
    if (k > n / 2)
        k = n - k;
    if (k == 0)
        return 1;
    return float(n * n_choose_k(n - 1, k - 1)) / k;
}
