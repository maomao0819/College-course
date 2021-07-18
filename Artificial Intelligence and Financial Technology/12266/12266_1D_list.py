test_case = input()
for _ in range(int(test_case)):
	num_order = input()
	ask = [] 
	bid = []
	for _ in range(int(num_order)):
		statement = input()
		statement_array = statement.split(' ')
		if statement_array[0] == 'buy':
			for _ in range(int(statement_array[1])):
				bid.append(int(statement_array[4]))
			bid.sort(reverse=True)
		elif statement_array[0] == 'sell':			
			for _ in range(int(statement_array[1])):
				ask.append(int(statement_array[4]))
			ask.sort()
		stock_price = '-'
		while len(bid) and len(ask) and bid[0] >= ask[0]:
			if stock_price == '-':
				stock_price = ask[0]
			bid.pop(0)
			ask.pop(0)
		bid_price = bid[0] if len(bid) else '-'
		ask_price = ask[0] if len(ask) else '-'
		print(f'{ask_price} {bid_price} {stock_price}')