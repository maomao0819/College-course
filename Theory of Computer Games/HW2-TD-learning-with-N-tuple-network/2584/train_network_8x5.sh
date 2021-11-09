#!/bin/bash
FILE=tuple_network/network_8x5/weights_8x5.bin
if [ ! -f "$FILE" ]; then
	./2584 --total=0 --play="init save=tuple_network/network_8x5/weights_8x5.bin  tuple_size=5" # generate a clean network
fi
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin save=tuple_network/network_8x5/weights_8x5.bin alpha=0.0125 tuple_size=5" | tee -a tuple_network/network_8x5/train_8x5.log
	./2584 --total=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin alpha=0 tuple_size=5" --save="tuple_network/network_8x5/stat_8x5.txt"
	tar zcvf tuple_network/network_8x5/weights_8x5.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_8x5/weights_8x5.bin tuple_network/network_8x5/train_8x5.log tuple_network/network_8x5/stat_8x5.txt
done
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin save=tuple_network/network_8x5/weights_8x5.bin alpha=0.01 tuple_size=5" | tee -a tuple_network/network_8x5/train_8x5.log
	./2584 --total=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin alpha=0 tuple_size=5" --save="tuple_network/network_8x5/stat_8x5.txt"
	tar zcvf tuple_network/network_8x5/weights_8x5.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_8x5/weights_8x5.bin tuple_network/network_8x5/train_8x5.log tuple_network/network_8x5/stat_8x5.txt
done
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin save=tuple_network/network_8x5/weights_8x5.bin alpha=0.005 tuple_size=5" | tee -a tuple_network/network_8x5/train_8x5.log
	./2584 --total=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin alpha=0 tuple_size=5" --save="tuple_network/network_8x5/stat_8x5.txt"
	tar zcvf tuple_network/network_8x5/weights_8x5.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_8x5/weights_8x5.bin tuple_network/network_8x5/train_8x5.log tuple_network/network_8x5/stat_8x5.txt
done
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin save=tuple_network/network_8x5/weights_8x5.bin alpha=0.0025 tuple_size=5" | tee -a tuple_network/network_8x5/train_8x5.log
	./2584 --total=1000 --play="load=tuple_network/network_8x5/weights_8x5.bin alpha=0 tuple_size=5" --save="tuple_network/network_8x5/stat_8x5.txt"
	tar zcvf tuple_network/network_8x5/weights_8x5.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_8x5/weights_8x5.bin tuple_network/network_8x5/train_8x5.log tuple_network/network_8x5/stat_8x5.txt
done
