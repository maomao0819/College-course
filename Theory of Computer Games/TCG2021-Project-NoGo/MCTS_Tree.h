#ifndef MCTS_TREE
#define MCTS_TREE

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <map>
#include <type_traits>
#include <algorithm>
#include "board.h"
#include "action.h"
#include <fstream>

class MCTS_node
{
public:
	// Costructors
	// MCTS_node();
	// MCTS_node(const board& b);
	MCTS_node(const board &b = board(), board::piece_type who = board::black, action::place apply_move = action(), 
		unsigned n_win = 0, unsigned n_visit = 0);
	MCTS_node &operator=(const MCTS_node &M) = default;

	// Default destructor
	~MCTS_node() = default;

	// Getters
	board get_state() const;
	const MCTS_node *get_parent() const;
	MCTS_node *get_parent();
	std::vector<MCTS_node *> get_children() const;
	std::vector<action::place> get_moves() const;
	board::piece_type get_player() const;
	action::place get_applied_move() const;
	unsigned get_n_wins() const;
	unsigned get_n_visits() const;

	// Copy assignment and costructors are prevented
	// Neither of the two are used; moreover while deep-copying would be inconvenient
	// (as it would mean to copy the whole branch below the node), shallow-copying would
	// be risky in that it may break synchrony between children and available moves
	// MCTS_node& operator = (const MCTS_node&) = delete;
	// MCTS_node(const MCTS_node&) = delete;

	//  Update the score and the visits of the node
	void update(unsigned result);					   // Only one visit, by default
	void update(unsigned result, unsigned new_visits); // More than one visit

	// True if all moves have been tried (vector of moves is empty)
	bool is_all_moves_tried() const;

	// True if the node has children (vector of children not null)
	bool has_children() const;

	// Adds a new child, built applying the input move to the current game state
	MCTS_node *make_child(const action::place &move);

	// Print info (DEBUG)
	void print_node() const;
	board::piece_type change_player(board::piece_type who);

private:
	std::vector<action::place> generate_possible_moves(const board &state, board::piece_type player);
	// Deletes the input move from the vector of available moves
	void erase_move(const action::place &move);

	board state;
	MCTS_node *parent = NULL;
	std::vector<MCTS_node *> children;
	std::vector<action::place> possible_moves;
	board::piece_type player = board::black;
	action::place applied_move = action();
	unsigned n_wins = 0;
	unsigned n_visits = 0;
};

class MCTS_tree : public MCTS_node
{
public:
	// Costructors
	// MCTS_tree();
	MCTS_tree(const board &b, board::piece_type player = board::black, double UCB_c = 1.0, unsigned n_round = 100, unsigned timeout = 0);
	MCTS_tree &operator=(const MCTS_tree &M) = default;

	// Default destructor
	~MCTS_tree() = default;

	void UCT_search();
	void UCT_search(unsigned n_round);
	action::place best_move();

private:
	double calculate_UCB(MCTS_node *n);
	MCTS_node *best_child(MCTS_node *n);
	MCTS_node *selection();
	MCTS_node *expansion(MCTS_node *n);
	MCTS_node *simulation(MCTS_node *n);
	board::reward check_result(MCTS_node *leqf);
	void backpropagation(MCTS_node *leaf, board::reward result, MCTS_node *expansion_node);

	double UCB_constant = 1.0;
	MCTS_node *root;
	unsigned n_round = 100;
	unsigned timeout = 0;
};

#endif