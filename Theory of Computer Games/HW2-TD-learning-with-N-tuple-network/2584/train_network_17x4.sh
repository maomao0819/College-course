#!/bin/bash
FILE=tuple_network/network_17x4/weights_17x4.bin
if [ ! -f "$FILE" ]; then
	./2584 --total=0 --play="init save=tuple_network/network_17x4/weights_17x4.bin  tuple_number=17" # generate a clean network
fi
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin save=tuple_network/network_17x4/weights_17x4.bin alpha=0.0125 tuple_number=17" | tee -a tuple_network/network_17x4/train_17x4.log
	./2584 --total=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin alpha=0 tuple_number=17" --save="tuple_network/network_17x4/stat_17x4.txt"
	tar zcvf tuple_network/network_17x4/weights_17x4.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_17x4/weights_17x4.bin tuple_network/network_17x4/train_17x4.log tuple_network/network_17x4/stat_17x4.txt
done
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin save=tuple_network/network_17x4/weights_17x4.bin alpha=0.01 tuple_number=17" | tee -a tuple_network/network_17x4/train_17x4.log
	./2584 --total=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin alpha=0 tuple_number=17" --save="tuple_network/network_17x4/stat_17x4.txt"
	tar zcvf tuple_network/network_17x4/weights_17x4.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_17x4/weights_17x4.bin tuple_network/network_17x4/train_17x4.log tuple_network/network_17x4/stat_17x4.txt
done
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin save=tuple_network/network_17x4/weights_17x4.bin alpha=0.005 tuple_number=17" | tee -a tuple_network/network_17x4/train_17x4.log
	./2584 --total=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin alpha=0 tuple_number=17" --save="tuple_network/network_17x4/stat_17x4.txt"
	tar zcvf tuple_network/network_17x4/weights_17x4.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_17x4/weights_17x4.bin tuple_network/network_17x4/train_17x4.log tuple_network/network_17x4/stat_17x4.txt
done
for i in {1..25}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin save=tuple_network/network_17x4/weights_17x4.bin alpha=0.0025 tuple_number=17" | tee -a tuple_network/network_17x4/train_17x4.log
	./2584 --total=1000 --play="load=tuple_network/network_17x4/weights_17x4.bin alpha=0 tuple_number=17" --save="tuple_network/network_17x4/stat_17x4.txt"
	tar zcvf tuple_network/network_17x4/weights_17x4.$(date +%Y%m%d-%H%M%S).tar.gz tuple_network/network_17x4/weights_17x4.bin tuple_network/network_17x4/train_17x4.log tuple_network/network_17x4/stat_17x4.txt
done
