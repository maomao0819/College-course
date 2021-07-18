import numpy as np
import matplotlib.pyplot as plt

# K: 履約價	call: call price, 付的權利金, 成交價		ST: 到期的
# 這口交易的獲利曲線
def callr(K, call):
	ST = np.arange(11500,13500 + 1)
	return np.maximum(ST - K, 0) - call

def putr(K, put):
	ST = np.arange(11500,13500 + 1)
	return np.maximum(K - ST, 0) - put

x1 = np.arange(11500, 13500 + 1)
# y1 r 12500
# y2 g 13000
# y3 b bull spred
y1 = callr(12500, 348)
y2 = -callr(13000, 60)
y3 = y1 + y2
plt.plot(x1, y1, 'r', [x1[0], x1[-1]], [0, 0], '--k')
plt.plot(x1, y1, 'r', x1, y2, 'g', x1, y3, 'b', [x1[0], x1[-1]], [0, 0], '--k')

x1 = np.arange(11500, 13500 + 1)
# y1 r 12500
# y2 g 13000
# y3 b bull spred
y1 = putr(12500, 65)
y2 = putr(12900, 215)
y3 = putr(12700, 118)
y3 = y1 + y2
plt.plot(x1, y1 + y2 - y3 * 2, 'r', [x1[0], x1[-1]], [0, 0], '--k')












