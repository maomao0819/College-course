test_case = input()
for _ in range(int(test_case)):
	num_order = input()
	ask = [] 
	bid = []
	stock_price = '-'
	for _ in range(int(num_order)):
		order = input()
		order_list = order.split()
		if order_list[0][0] == 'b':
			bid.append([int(order_list[-1]), int(order_list[1])])
			bid.sort(reverse=True)
		elif order_list[0][0] == 's':			
			ask.append([int(order_list[-1]), int(order_list[1])])
			ask.sort()
		while len(bid) and len(ask) and bid[0][0] >= ask[0][0]:
			stock_price = ask[0][0]
			delta = min(ask[0][1], bid[0][1])
			ask[0][1] -= delta
			bid[0][1] -= delta
			if ask[0][1] == 0:
				ask.pop(0)
			if bid[0][1] == 0:
				bid.pop(0)
		bid_price = bid[0][0] if len(bid) else '-'
		ask_price = ask[0][0] if len(ask) else '-'
		print(ask_price, bid_price, stock_price)