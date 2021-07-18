#!/usr/bin/env python

# Generative Adversarial Networks (GAN) example in PyTorch. Tested with PyTorch 0.4.1, Python 3.6.7 (Nov 2018)
# See related blog post at https://medium.com/@devnag/generative-adversarial-networks-gans-in-50-lines-of-code-pytorch-e81b79659e3f#.sch4xgsa9

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from torch.autograd import Variable

matplotlib_is_available = True
try:
  from matplotlib import pyplot as plt
except ImportError:
  print("Will skip plotting; matplotlib is not available.")
  matplotlib_is_available = False

#Data params
#給定基礎資料的平均與標準差
data_mean = 4
data_stddev = 1.25

# ### Uncomment only one of these to define what data is actually sent to the Discriminator
#(name, preprocess, d_input_func) = ("Raw data", lambda data: data, lambda x: x)
#(name, preprocess, d_input_func) = ("Data and variances", lambda data: decorate_with_diffs(data, 2.0), lambda x: x * 2)
#(name, preprocess, d_input_func) = ("Data and diffs", lambda data: decorate_with_diffs(data, 1.0), lambda x: x * 2)
(name, preprocess, d_input_func) = ("Only 4 moments", lambda data: get_moments(data), lambda x: 4)

print("Using data [%s]" % (name))

#真實資料分布 Target Data(使用高斯分布)
def get_distribution_sampler(mu, sigma):
	return lambda n: torch.Tensor(np.random.normal(mu, sigma, (1, n)))  # Gaussian

#Generator輸入資料
def get_generator_input_sampler():
	return lambda m, n: torch.rand(m, n)  # Uniform-dist data into generator, _NOT_ Gaussian

#Generator Model
class Generator(nn.Module):
	# 定義 model 中需要的參數，weight、bias 等等
	def __init__(self, input_size, hidden_size, output_size, f):
		super(Generator, self).__init__()
		self.map1 = nn.Linear(input_size, hidden_size) #輸入層
		self.map2 = nn.Linear(hidden_size, hidden_size) #隱藏層
		self.map3 = nn.Linear(hidden_size, output_size) #輸出層
		self.f = f

	# 定義 model 接收 input 時，data 要怎麼傳遞、經過哪些 activation function 等等
	#Feedforward Network
	def forward(self, x):
		x = self.map1(x) #輸入層
		x = self.f(x)
		x = self.map2(x) #隱藏層
		x = self.f(x)
		x = self.map3(x) #輸出層
		return x

#Discriminator Model
class Discriminator(nn.Module):
	def __init__(self, input_size, hidden_size, output_size, f):
		super(Discriminator, self).__init__()
		self.map1 = nn.Linear(input_size, hidden_size) #輸入層
		self.map2 = nn.Linear(hidden_size, hidden_size) #隱藏層
		self.map3 = nn.Linear(hidden_size, output_size) #輸出層
		self.f = f

	#Feedforward Network
	def forward(self, x):
		x = self.f(self.map1(x))
		x = self.f(self.map2(x))
		x = self.f(self.map3(x)) 
		return x

#Load Data to List
def extract(v):
	return v.data.storage().tolist()

#Data Mean & Standard Deviation
def stats(d):
	return [np.mean(d), np.std(d)]

#
def get_moments(d):
	
	#平均
	mean = torch.mean(d)
	
	#偏移量
	diffs = d - mean
	
	#變異數
	var = torch.mean(torch.pow(diffs, 2.0))
	
	#標準差
	std = torch.pow(var, 0.5)
	
	#Z-score
	zscores = diffs / std
	
	#偏度
	skews = torch.mean(torch.pow(zscores, 3.0))
	
	#峰度
	kurtoses = torch.mean(torch.pow(zscores, 4.0)) - 3.0  # excess kurtosis, should be 0 for Gaussian
	
	#資料包含Mean、Standard Deviation、Skews、Kurtoses
	final = torch.cat((mean.reshape(1,), std.reshape(1,), skews.reshape(1,), kurtoses.reshape(1,)))
	return final

#def decorate_with_diffs(data, exponent, remove_raw_data=False):
#	mean = torch.mean(data.data, 1, keepdim=True)
#	mean_broadcast = torch.mul(torch.ones(data.size()), mean.tolist()[0][0])
#	diffs = torch.pow(data - Variable(mean_broadcast), exponent)

#	if remove_raw_data:
#		return torch.cat([diffs], 1)
#	else:
#		return torch.cat([data, diffs], 1)

#訓練過程
def train():
	# Model parameters
	g_input_size = 1	  # Random noise dimension coming into generator, per output vector
	g_hidden_size = 5	 # Generator complexity
	g_output_size = 1	 # Size of generated output vector
	d_input_size = 500	# Minibatch size - cardinality of distributions
	d_hidden_size = 10	# Discriminator complexity
	d_output_size = 1	 # Single dimension for 'real' vs. 'fake' classification
	minibatch_size = d_input_size

	d_learning_rate = 1e-3
	g_learning_rate = 1e-3
	sgd_momentum = 0.9

	num_epochs = 5000
	print_interval = 100
	d_steps = 20
	g_steps = 20

	dfe, dre, ge = 0, 0, 0
	d_real_data, d_fake_data, g_fake_data = None, None, None

	#Discriminator使用Sigmoid Function
	discriminator_activation_function = torch.sigmoid
	
	#Gnerator使用Tangent Hyperbolic Function
	generator_activation_function = torch.tanh

	#原始真實資料
	d_sampler = get_distribution_sampler(data_mean, data_stddev)
	
	#Generator原始輸入資料
	gi_sampler = get_generator_input_sampler()
	
	#Generator Model
	G = Generator(input_size=g_input_size,
				  hidden_size=g_hidden_size,
				  output_size=g_output_size,
				  f=generator_activation_function)

	#Discriminator Model
	D = Discriminator(input_size=d_input_func(d_input_size),
					  hidden_size=d_hidden_size,
					  output_size=d_output_size,
					  f=discriminator_activation_function)
	
	#Discriminator判斷真假資料
	criterion = nn.BCELoss()  # Binary cross entropy: http://pytorch.org/docs/nn.html#bceloss

	# stochastic gradient descent
	d_optimizer = optim.SGD(D.parameters(), lr=d_learning_rate, momentum=sgd_momentum)
	g_optimizer = optim.SGD(G.parameters(), lr=g_learning_rate, momentum=sgd_momentum)

	for epoch in range(num_epochs):
		for d_index in range(d_steps):
			
			#先訓練Discriminator在Real & Fake Data
			# 將參數梯度設為0
			D.zero_grad()

			#  1A: Train Discriminator on real
			d_real_data = Variable(d_sampler(d_input_size))
			d_real_decision = D(preprocess(d_real_data))
			d_real_error = criterion(d_real_decision, Variable(torch.ones([1,1])))  # ones = true
			# 反向傳播計算梯度
			d_real_error.backward() # compute/store gradients, but don't change params

			#  1B: Train Discriminator on fake
			d_gen_input = Variable(gi_sampler(minibatch_size, g_input_size))
			d_fake_data = G(d_gen_input).detach()  # detach to avoid training G on these labels
			d_fake_decision = D(preprocess(d_fake_data.t()))
			d_fake_error = criterion(d_fake_decision, Variable(torch.zeros([1,1])))  # zeros = fake
			# 計算梯度
			d_fake_error.backward()
			# 更新參數
			d_optimizer.step()	 # Only optimizes D's parameters; changes based on stored gradients from backward()
			dre, dfe = extract(d_real_error)[0], extract(d_fake_error)[0]

		for g_index in range(g_steps):
			#根據Discriminator的回饋來訓練Generator
			G.zero_grad()

			gen_input = Variable(gi_sampler(minibatch_size, g_input_size))
			g_fake_data = G(gen_input)
			dg_fake_decision = D(preprocess(g_fake_data.t()))
			g_error = criterion(dg_fake_decision, Variable(torch.ones([1,1])))  # Train G to pretend it's genuine

			g_error.backward()
			g_optimizer.step()  # Only optimizes G's parameters
			ge = extract(g_error)[0]

		if epoch % print_interval == 0:
			print("Epoch %s: D (%s real_err, %s fake_err) G (%s err); Real Dist (%s),  Fake Dist (%s) " %
				  (epoch, dre, dfe, ge, stats(extract(d_real_data)), stats(extract(d_fake_data))))
	
	#最後產生的圖會漸趨高斯分布
	if matplotlib_is_available:
		print("Plotting the generated distribution...")
		values = extract(g_fake_data)
		print(" Values: %s" % (str(values)))
		plt.hist(values, bins=50)
		plt.xlabel('Value')
		plt.ylabel('Count')
		plt.title('Histogram of Generated Distribution')
		plt.grid(True)
		plt.show()

train()