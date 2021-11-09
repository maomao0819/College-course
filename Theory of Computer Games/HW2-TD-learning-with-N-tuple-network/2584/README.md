# 2048-Framework

Framework for 2584 & 2584-like Games (C++ 11)

## Basic Usage

To make the sample program:
```bash
make # see makefile for details
```

To run the sample program:
```bash
./2584 # by default the program runs 1000 games
```

To specify the total games to run:
```bash
./2584 --total=100000
```

To display the statistic every 1000 episodes:
```bash
./2584 --total=100000 --block=1000 --limit=1000
```

To specify the total games to run, and seed the environment:
```bash
./2584 --total=100000 --evil="seed=12345" # need to inherit from random_agent
```

To save the statistic result to a file:
```bash
./2584 --save=stat.txt
```

To load and review the statistic result from a file:
```bash
./2584 --load=stat.txt
```

To play with certain agent:
```bash
./2584 --play=greedy
```

## Advanced Usage

To initialize the network, train the network for 100000 games, and save the weights to a file:
```bash
./2584 --total=100000 --block=1000 --limit=1000 --play="init save=weights.bin" # need to inherit from weight_agent
```

To load the weights from a file, train the network for 100000 games, and save the weights:
```bash
./2584 --total=100000 --block=1000 --limit=1000 --play="load=weights.bin save=weights.bin" # need to inherit from weight_agent
```

To train the network for 1000 games, with a specific learning rate:
```bash
./2584 --total=1000 --play="init alpha=0.0025" # need to inherit from weight_agent
```

To train the network for 1000 games, with the specific number of the possible tile types:
```bash
./2584 --total=1000 --play="n_tile=25" 
```

To train the network for 1000 games, with a specific MxN tuple network:
```bash
./2584 --total=1000 --play="tuple_number=9 tuple_size=4" # tuple_number is available with 8, 9, and 17 and tuple_size is only available with 4 and 5(when tuple_number is 8)
```

To train the network for 10000 games, with a specific learning rate, the specific number of the possible tile types, and with a specific MxN tuple network:
```bash
./2584 --total=10000 --block=1000 --limit=1000 --play="init alpha=0.0125 n_tile=25 tuple_number=17 tuple_size=4" # need to inherit from weight_agent
```

To load the weights from a file, test the network for 1000 games, and save the statistic:
```bash
./2584 --total=1000 --play="load=weights.bin alpha=0" --save="stat.txt" # need to inherit from weight_agent
```

To perform a long training with periodic evaluations and network snapshots:
```bash
./2584 --total=0 --play="init save=weights.bin" # generate a clean network
for i in {1..100}; do
	./2584 --total=100000 --block=1000 --limit=1000 --play="load=weights.bin save=weights.bin alpha=0.0025" | tee -a train.log
	./2584 --total=1000 --play="load=weights.bin alpha=0" --save="stat.txt"
	tar zcvf weights.$(date +%Y%m%d-%H%M%S).tar.gz weights.bin train.log stat.txt
done
```

## Author

[Computer Games and Intelligence (CGI) Lab](https://cgilab.nctu.edu.tw/), NYCU, Taiwan
