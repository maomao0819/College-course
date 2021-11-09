/**
 * Framework for 2048 & 2048-like Games (C++ 11)
 * agent.h: Define the behavior of variants of agents including players and environments
 *
 * Author: Theory of Computer Games (TCG 2021)
 *         Computer Games and Intelligence (CGI) Lab, NYCU, Taiwan
 *         https://cgilab.nctu.edu.tw/
 */

#pragma once
#include <string>
#include <random>
#include <sstream>
#include <map>
#include <type_traits>
#include <algorithm>
#include "board.h"
#include "action.h"
#include "weight.h"
#include <fstream>

class agent {
public:
	agent(const std::string& args = "") {
		std::stringstream ss("name=unknown role=unknown " + args);
		for (std::string pair; ss >> pair; ) {
			std::string key = pair.substr(0, pair.find('='));
			std::string value = pair.substr(pair.find('=') + 1);
			meta[key] = { value };
		}
	}
	virtual ~agent() {}
	virtual void open_episode(const std::string& flag = "") {}
	virtual void close_episode(const std::string& flag = "") {}
	virtual action take_action(const board& b) { return action(); }
	virtual bool check_for_win(const board& b) { return false; }

public:
	virtual std::string property(const std::string& key) const { return meta.at(key); }
	virtual void notify(const std::string& msg) { meta[msg.substr(0, msg.find('='))] = { msg.substr(msg.find('=') + 1) }; }
	virtual std::string name() const { return property("name"); }
	virtual std::string role() const { return property("role"); }

protected:
	typedef std::string key;
	struct value {
		std::string value;
		operator std::string() const { return value; }
		template<typename numeric, typename = typename std::enable_if<std::is_arithmetic<numeric>::value, numeric>::type>
		operator numeric() const { return numeric(std::stod(value)); }
	};
	std::map<key, value> meta;
};

/**
 * base agent for agents with randomness
 */
class random_agent : public agent {
public:
	random_agent(const std::string& args = "") : agent(args) {
		if (meta.find("seed") != meta.end())
			engine.seed(int(meta["seed"]));
	}
	virtual ~random_agent() {}

protected:
	std::default_random_engine engine;
};

/**
 * base agent for agents with weight tables and a learning rate
 */
class weight_agent : public agent {
public:
	weight_agent(const std::string& args = "") : agent(args), alpha(0) {
		if (meta.find("init") != meta.end())
			init_weights(meta["init"]);
		if (meta.find("load") != meta.end())
			load_weights(meta["load"]);
		if (meta.find("alpha") != meta.end())
			alpha = float(meta["alpha"]);
	}
	virtual ~weight_agent() {
		if (meta.find("save") != meta.end())
			save_weights(meta["save"]);
	}

protected:
	virtual void init_weights(const std::string& info) {
//		net.emplace_back(65536); // create an empty weight table with size 65536
//		net.emplace_back(65536); // create an empty weight table with size 65536
	}
	virtual void load_weights(const std::string& path) {
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in.is_open()) std::exit(-1);
		uint32_t size;
		in.read(reinterpret_cast<char*>(&size), sizeof(size));
		net.resize(size);
		for (weight& w : net) in >> w;
		in.close();
	}
	virtual void save_weights(const std::string& path) {
		std::ofstream out(path, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!out.is_open()) std::exit(-1);
		uint32_t size = net.size();
		out.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (weight& w : net) out << w;
		out.close();
	}

protected:
	std::vector<weight> net;
	float alpha;
};

class player : public agent
{
public:
	player(const std::string &args = "") : agent("name=dummy role=player " + args), alpha(0), n_tile(25), tuple_size(4), tuple_number(8)
	{
		if (meta.find("tile") != meta.end())
			n_tile = int(meta["tile"]);
		if (meta.find("tuple_number") != meta.end())
		{
			int tn = int(meta["tuple_number"]);
			if (tn == 8 || tn == 9 || tn == 17)
				tuple_number = tn;
			else
			{
				printf("Haven't impliment %dxN-tuple network yet.\n", tn);
				printf("tuple_number must be 8, 9, or 17 ! Set tuple_number as the default value.\n\n");
			}
		}
		if (meta.find("tuple_size") != meta.end())
		{
			int ts = int(meta["tuple_size"]);
			if (tuple_number == 8 && ts == 5)
				tuple_size = 5;
			else if (ts != 4)
			{
				printf("Haven't impliment Nx%d-tuple network yet.\n", ts);
				printf("tuple_size must be 4 ! Set tuple_size as the default value.\n\n");
			}
		}
		if (meta.find("init") != meta.end())
			init_weights(meta["init"]);
		if (meta.find("load") != meta.end())
			load_weights(meta["load"]);
		if (meta.find("alpha") != meta.end())
			alpha = float(meta["alpha"]);
	}

	virtual ~player()
	{
		if (meta.find("save") != meta.end())
			save_weights(meta["save"]);
	}

	virtual action take_action(const board &before)
	{
		// random
		/*std::shuffle(opcode.begin(), opcode.end(), engine);
		for (int op : opcode)
		{
			board::reward reward = board(before).slide(op);
			if (reward != -1)
				return action::slide(op);
		}*/

		// greedy
		int best_op = -1;
		int best_reward = -1;
		// float best_value = -10000000;
		float best_value = -std::numeric_limits<float>::max();
		board best_after_state;
		for (int op : {0, 1, 2, 3})
		{
			board after = before;
			int reward = after.slide(op);
			// illegal move
			if (reward == -1)
				continue;
			float value = 0;
			if (tuple_number == 9)
				value = estimate_value_9x4(after);
			else if (tuple_number == 17)
				value = estimate_value_17x4(after);
			else
			{
				if (tuple_size == 5)
					value = estimate_value_8x5(after);
				else
					value = estimate_value_8x4(after);
			}
			if (reward + value > best_reward + best_value)
			{
				best_op = op;
				best_reward = reward;
				best_value = value;
				best_after_state = after;
			}
		}
		// legal move
		if (best_op != -1)
			history.push_back({best_reward, best_after_state}); 
		return action::slide(best_op);
	}

	virtual void open_episode(const std::string& flag = "")
	{
		history.clear();
	}

	virtual void close_episode(const std::string& flag = "")
	{
		if (history.empty())
			return;
		if (alpha == 0)
			return;
		if (tuple_number == 9)
			TD_backward_9x4();
		else if (tuple_number == 17)
			TD_backward_17x4();
		else
		{
			if (tuple_size == 5)
				TD_backward_8x5();
			else
				TD_backward_8x4();
		}
	}

	void TD_backward_8x4()
	{
		adjust_value_8x4(history[history.size() - 1].after, 0);
		for (int t = history.size() - 2; t >= 0; t--)
			adjust_value_8x4(history[t].after, history[t + 1].reward + estimate_value_8x4(history[t + 1].after));
	}

	void TD_backward_9x4()
	{
		adjust_value_9x4(history[history.size() - 1].after, 0);
		for (int t = history.size() - 2; t >= 0; t--)
			adjust_value_9x4(history[t].after, history[t + 1].reward + estimate_value_9x4(history[t + 1].after));
	}

	void TD_backward_17x4()
	{
		adjust_value_17x4(history[history.size() - 1].after, 0);
		for (int t = history.size() - 2; t >= 0; t--)
			adjust_value_17x4(history[t].after, history[t + 1].reward + estimate_value_17x4(history[t + 1].after));
	}

	void TD_backward_8x5()
	{
		adjust_value_8x5(history[history.size() - 1].after, 0);
		for (int t = history.size() - 2; t >= 0; t--)
			adjust_value_8x5(history[t].after, history[t + 1].reward + estimate_value_8x5(history[t + 1].after));
	}
	
	struct step_node 
	{
		int reward;
		board after;
	};
	std::vector<step_node> history;

	int extract_feature_Nx4(const board &after_state, int a, int b, int c, int d) const
	{
		// return after_state(a) * power(n_tile, (tuple_size - 1)) + after_state(b) * power(n_tile, (tuple_size - 2)) + after_state(c) * power(n_tile, (tuple_size - 3)) + after_state(d) * power(n_tile, (tuple_size - 4));
		return after_state(a) * n_tile * n_tile * n_tile + after_state(b) * n_tile * n_tile + after_state(c) * n_tile + after_state(d);
	}

	int extract_feature_Nx5(const board &after_state, int a, int b, int c, int d, int e) const
	{
		// return after_state(a) * power(n_tile, (tuple_size - 1)) + after_state(b) * power(n_tile, (tuple_size - 2)) + after_state(c) * power(n_tile, (tuple_size - 3)) + after_state(d) * power(n_tile, (tuple_size - 4)) + after_state(e) * power(n_tile, (tuple_size - 5));
		return after_state(a) * n_tile * n_tile * n_tile * n_tile + after_state(b) * n_tile * n_tile * n_tile + after_state(c) * n_tile * n_tile + after_state(d) * n_tile + after_state(e);
	}
	
	int power (int base, int exponent) const
	{
		// return std::pow(value, p);
		int pow = 1;
		int multi = base;
		while (exponent)
		{
			// if exponent is odd or even now
			if (exponent & 1)
				// if exponent is odd now
				pow *= multi;
			// square the base
			multi *= multi;
			// half the exponent
			exponent >>= 1;
		}
		return pow;
	}

	float estimate_value_8x4(const board& after_state) const
	{
		float value = 0;
		// row
		value += net[0][extract_feature_Nx4(after_state, 0, 1, 2, 3)];
		value += net[1][extract_feature_Nx4(after_state, 4, 5, 6, 7)];
		value += net[2][extract_feature_Nx4(after_state, 8, 9, 10, 11)];
		value += net[3][extract_feature_Nx4(after_state, 12, 13 ,14 ,15)];
		// column
		value += net[4][extract_feature_Nx4(after_state, 0, 4, 8, 12)];
		value += net[5][extract_feature_Nx4(after_state, 1, 5, 9, 13)];
		value += net[6][extract_feature_Nx4(after_state, 2, 6, 10, 14)];
		value += net[7][extract_feature_Nx4(after_state, 3, 7, 11, 15)];
		return value;
	}

	float estimate_value_9x4(const board& after_state) const
	{
		float value = 0;
		// block
		value += net[0][extract_feature_Nx4(after_state, 0, 1, 4, 5)];
		value += net[1][extract_feature_Nx4(after_state, 1, 2, 5, 6)];
		value += net[2][extract_feature_Nx4(after_state, 2, 3, 6, 7)];
		value += net[3][extract_feature_Nx4(after_state, 4, 5 ,8 ,9)];
		value += net[4][extract_feature_Nx4(after_state, 5, 6, 9, 10)];
		value += net[5][extract_feature_Nx4(after_state, 6, 7, 10, 11)];
		value += net[6][extract_feature_Nx4(after_state, 8, 9, 12, 13)];
		value += net[7][extract_feature_Nx4(after_state, 9, 10, 13, 14)];
		value += net[8][extract_feature_Nx4(after_state, 10, 11, 14, 15)];
		return value;
	}

	float estimate_value_17x4(const board& after_state) const
	{
		float value = 0;
		// row
                value += net[0][extract_feature_Nx4(after_state, 0, 1, 2, 3)];
                value += net[1][extract_feature_Nx4(after_state, 4, 5, 6, 7)];
                value += net[2][extract_feature_Nx4(after_state, 8, 9, 10, 11)];
                value += net[3][extract_feature_Nx4(after_state, 12, 13 ,14 ,15)];
		// column
		value += net[4][extract_feature_Nx4(after_state, 0, 4, 8, 12)];
                value += net[5][extract_feature_Nx4(after_state, 1, 5, 9, 13)];
                value += net[6][extract_feature_Nx4(after_state, 2, 6, 10, 14)];
                value += net[7][extract_feature_Nx4(after_state, 3, 7, 11, 15)];
                // block
		value += net[8][extract_feature_Nx4(after_state, 0, 1, 4, 5)];
                value += net[9][extract_feature_Nx4(after_state, 1, 2, 5, 6)];
                value += net[10][extract_feature_Nx4(after_state, 2, 3, 6, 7)];
                value += net[11][extract_feature_Nx4(after_state, 4, 5 ,8 ,9)];
                value += net[12][extract_feature_Nx4(after_state, 5, 6, 9, 10)];
                value += net[13][extract_feature_Nx4(after_state, 6, 7, 10, 11)];
                value += net[14][extract_feature_Nx4(after_state, 8, 9, 12, 13)];
                value += net[15][extract_feature_Nx4(after_state, 9, 10, 13, 14)];
                value += net[16][extract_feature_Nx4(after_state, 10, 11, 14, 15)];
		return value;
	}

	float estimate_value_8x5(const board& after_state) const
	{
		float value = 0;
		// corner L
		value += net[0][extract_feature_Nx5(after_state, 0, 1, 2, 4, 5)];
		value += net[1][extract_feature_Nx5(after_state, 1, 2, 3, 7, 11)];
		value += net[2][extract_feature_Nx5(after_state, 4, 8, 12, 13, 14)];
		value += net[3][extract_feature_Nx5(after_state, 13 ,14 ,15, 11, 7)];
		// middle +
		value += net[4][extract_feature_Nx5(after_state, 1, 4, 5, 6, 9)];
		value += net[5][extract_feature_Nx5(after_state, 2, 5, 6, 7, 10)];
		value += net[6][extract_feature_Nx5(after_state, 5, 8, 9, 10, 13)];
		value += net[7][extract_feature_Nx5(after_state, 6, 9, 10, 11, 14)];
		return value;
	}

	// train td	
	void adjust_value_8x4(const board& after, float target)
	{
		float current = estimate_value_8x4(after);
                float error = target - current;
                float adjust = alpha * error;
		
		// row
		net[0][extract_feature_Nx4(after, 0, 1, 2, 3)] += adjust;
		net[1][extract_feature_Nx4(after, 4, 5, 6, 7)] += adjust;
		net[2][extract_feature_Nx4(after, 8, 9, 10, 11)] += adjust;
		net[3][extract_feature_Nx4(after, 12, 13, 14, 15)] += adjust;
		// column
		net[4][extract_feature_Nx4(after, 0, 4, 8, 12)] += adjust;
		net[5][extract_feature_Nx4(after, 1, 5, 9, 13)] += adjust;
		net[6][extract_feature_Nx4(after, 2, 6, 10, 14)] += adjust;
		net[7][extract_feature_Nx4(after, 3, 7, 11, 15)] += adjust;
	}

	void adjust_value_9x4(const board& after, float target)
	{
		float current = estimate_value_9x4(after);
                float error = target - current;
                float adjust = alpha * error;

		// block
		net[0][extract_feature_Nx4(after, 0, 1, 4, 5)] += adjust;
		net[1][extract_feature_Nx4(after, 1, 2, 5, 6)] += adjust;
		net[2][extract_feature_Nx4(after, 2, 3, 6, 7)] += adjust;
		net[3][extract_feature_Nx4(after, 4, 5 ,8 ,9)] += adjust;
		net[4][extract_feature_Nx4(after, 5, 6, 9, 10)] += adjust;
		net[5][extract_feature_Nx4(after, 6, 7, 10, 11)] += adjust;
		net[6][extract_feature_Nx4(after, 8, 9, 12, 13)] += adjust;
		net[7][extract_feature_Nx4(after, 9, 10, 13, 14)] += adjust;
		net[8][extract_feature_Nx4(after, 10, 11, 14, 15)] += adjust;
	}

	void adjust_value_17x4(const board& after, float target)
	{
		float current = estimate_value_17x4(after);
                float error = target - current;
		float adjust = alpha * error;
		
		// row
                net[0][extract_feature_Nx4(after, 0, 1, 2, 3)] += adjust;
                net[1][extract_feature_Nx4(after, 4, 5, 6, 7)] += adjust;
                net[2][extract_feature_Nx4(after, 8, 9, 10, 11)] += adjust;
                net[3][extract_feature_Nx4(after, 12, 13 ,14 ,15)] += adjust;
		// column
		net[4][extract_feature_Nx4(after, 0, 4, 8, 12)] += adjust;
                net[5][extract_feature_Nx4(after, 1, 5, 9, 13)] += adjust;
                net[6][extract_feature_Nx4(after, 2, 6, 10, 14)] += adjust;
                net[7][extract_feature_Nx4(after, 3, 7, 11, 15)] += adjust;
                // block
		net[8][extract_feature_Nx4(after, 0, 1, 4, 5)] += adjust;
                net[9][extract_feature_Nx4(after, 1, 2, 5, 6)] += adjust;
                net[10][extract_feature_Nx4(after, 2, 3, 6, 7)] += adjust;
                net[11][extract_feature_Nx4(after, 4, 5 ,8 ,9)] += adjust;
                net[12][extract_feature_Nx4(after, 5, 6, 9, 10)] += adjust;
                net[13][extract_feature_Nx4(after, 6, 7, 10, 11)] += adjust;
                net[14][extract_feature_Nx4(after, 8, 9, 12, 13)] += adjust;
                net[15][extract_feature_Nx4(after, 9, 10, 13, 14)] += adjust;
                net[16][extract_feature_Nx4(after, 10, 11, 14, 15)] += adjust;
	}

	void adjust_value_8x5(const board& after, float target)
	{
		float current = estimate_value_8x5(after);
                float error = target - current;
                float adjust = alpha * error;
		// corner L
		net[0][extract_feature_Nx5(after, 0, 1, 2, 4, 5)] += adjust;
		net[1][extract_feature_Nx5(after, 1, 2, 3, 7, 11)] += adjust;
		net[2][extract_feature_Nx5(after, 4, 8, 12, 13, 14)] += adjust;
		net[3][extract_feature_Nx5(after, 13 ,14 ,15, 11, 7)] += adjust;
		// middle +
		net[4][extract_feature_Nx5(after, 1, 4, 5, 6, 9)] += adjust;
		net[5][extract_feature_Nx5(after, 2, 5, 6, 7, 10)] += adjust;
		net[6][extract_feature_Nx5(after, 5, 8, 9, 10, 13)] += adjust;
		net[7][extract_feature_Nx5(after, 6, 9, 10, 11, 14)] += adjust;
	}
		
protected : 
	virtual void init_weights(const std::string &info)
	{
		//		net.emplace_back(65536); // create an empty weight table with size 65536
		//		net.emplace_back(65536); // create an empty weight table with size 65536
		for (int i = 0; i < tuple_number; i++)
			net.emplace_back(power(n_tile, tuple_size));
			// net.emplace_back(n_tile * n_tile * n_tile * n_tile);
	}
	virtual void load_weights(const std::string &path)
	{
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (!in.is_open())
			std::exit(-1);
		uint32_t size;
		in.read(reinterpret_cast<char *>(&size), sizeof(size));
		net.resize(size);
		for (weight &w : net)
			in >> w;
		in.close();
	}
	virtual void save_weights(const std::string &path)
	{
		std::ofstream out(path, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!out.is_open())
			std::exit(-1);
		uint32_t size = net.size();
		out.write(reinterpret_cast<char *>(&size), sizeof(size));
		for (weight &w : net)
			out << w;
		out.close();
	}

protected:
	std::vector<weight> net;
	// learning rate
	float alpha;
	// the number of the probability of a tile
	int n_tile;
	// the number of the tiles in a tuple
	int tuple_size;
	// the number of the tuples
	int tuple_number;
};

/**
 * random environment
 * add a new random tile to an empty cell
 * 2-tile: 90%
 * 4-tile: 10%
 */
class rndenv : public random_agent {
public:
	rndenv(const std::string& args = "") : random_agent("name=random role=environment " + args),
		space({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }), popup(0, 9) {}

	virtual action take_action(const board& after) {
		std::shuffle(space.begin(), space.end(), engine);
		for (int pos : space) {
			if (after(pos) != 0) continue;
			board::cell tile = popup(engine) ? 1 : 2;
			return action::place(pos, tile);
		}
		return action();
	}

private:
	std::array<int, 16> space;
	std::uniform_int_distribution<int> popup;
};

/**
 * dummy player
 * select a legal action randomly
 */
class player_agent : public random_agent {
public:
	player_agent(const std::string &args = "") : random_agent("name=dummy role=player " + args),
												 opcode({0, 1, 2, 3}), args(args) {}

	virtual action take_action(const board& before) {
		std::shuffle(opcode.begin(), opcode.end(), engine);
		if (args == "greedy")
			return greedy_play(opcode, before);
		else 
			return random_play(opcode, before);
	}

	action random_play (std::array<int, 4> opcode, const board& before)
	{
		for (int op : opcode){
			board::reward reward = board(before).slide(op);
			if (reward != -1) return action::slide(op); 	
		}
		return action();
	}

	action greedy_play (std::array<int, 4> opcode, const board& before)
	{
		int best_op = -1;
		board::reward best_reward = -1;
		for (int op : opcode)
		{
			board::reward reward = board(before).slide(op);
			if (reward > best_reward)
			{
				best_op = op;
				best_reward = reward;
			}
		}
		if (best_op != -1)
			return action::slide(best_op);
		return action();
	}

private:
	std::array<int, 4> opcode;
	std::string args;
};
