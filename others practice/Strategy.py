class Strategy():
    # option setting needed
    def __setitem__(self, key, value):
        self.options[key] = value

    # option setting needed
    def __getitem__(self, key):
        return self.options.get(key, '')

    def __init__(self):
        # strategy property
        self.subscribedBooks = {
            'Bitfinex': {
                'pairs': ['ETH-USDT'],
            },
        }
        self.period = 10 * 60
        self.options = {}

        # user defined class attribute
        self.close_price_trace = np.array([])
        self.gird_start_price = self.close_price_trace[0]
        self.UP = 1
        self.DOWN = 2

    def price_across(self, uperenct = 0.05, dperenct = 0.05):
        self.length = len(self.close_price_trace)
        for i in range (self.length):
            if self.length == 1:
              return None
            elif (self.close_price_trace[i]/self.gird_start_price)-1  >= uperenct :
              self.gird_start_price = self.close_price_trace[i]
              return self.UP
            elif  1- (self.close_price_trace[i]/self.gird_start_price) <= dperenct :
              self.gird_start_price = self.close_price_trace[i]
              return self.DOWN 
            return None
     
     #強制增加
    def on_order_state_change(self, order):
        Log("on order state change message: " + str(order) + " order price: " + str(order["price"]))


    # called every self.period
    def trade(self, information):
        exchange = list(information['candles'])[0]
        pair = list(information['candles'][exchange])[0]
        target_currency = pair.split('-')[0]  #ETH
        base_currency = pair.split('-')[1]  #USDT
        base_currency_amount = self['assets'][exchange][base_currency] 
        target_currency_amount = self['assets'][exchange][target_currency] 
        
        price_across = self.price_across()
        # add latest price into trace
        close_price = information['candles'][exchange][pair][0]['close']
        self.close_price_trace = np.append(self.close_price_trace,  [float(close_price)])

       # price up and sell 
        if price_across == self.UP:
            Log('selling 1 unit of ' + str(target_currency))
            return [
                {
                    'exchange': exchange,
                    'amount': -1,
                    'price': -1,
                    'type': 'MARKET',
                    'pair': pair,
                }
            ]
        # peice down and buy 
        elif price_across == self.DOWN:
            Log('buying: ' + str(self['assets'][exchange][base_currency]))
            return [
                {
                    'exchange': exchange,
                    'amount': 1.1,
                    'price': -1,
                    'type': 'MARKET',
                    'pair': pair,
                }
            ]
        return []