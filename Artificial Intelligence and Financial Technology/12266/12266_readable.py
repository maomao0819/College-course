test_case = input()
for _ in range(int(test_case)):
	num_order = input()
	ask_order = [] 
	bid_order = []
	stock_price = '-'
	for _ in range(int(num_order)):
		order = input()
		order_list = order.split()
		if order_list[0] == 'buy':
			buy_price = int(order_list[-1])
			buy_share = int(order_list[1])
			bid_order.append([buy_price, buy_share])
			bid_order.sort(reverse=True)
		elif order_list[0] == 'sell':			
			sell_price = int(order_list[-1])
			sell_share = int(order_list[1])
			ask_order.append([sell_price, sell_share])
			ask_order.sort()
		while len(bid_order) and len(ask_order) and bid_order[0][0] >= ask_order[0][0]:
			stock_price = ask_order[0][0]
			bid_share = bid_order[0][1]
			ask_share = ask_order[0][1]
			num_deal = min(ask_share, bid_share)
			ask_order[0][1] -= num_deal
			bid_order[0][1] -= num_deal
			if ask_order[0][1] == 0:
				ask_order.pop(0)
			if bid_order[0][1] == 0:
				bid_order.pop(0)
		bid_price = bid_order[0][0] if len(bid_order) else '-'
		ask_price = ask_order[0][0] if len(ask_order) else '-'
		print(ask_price, bid_price, stock_price)