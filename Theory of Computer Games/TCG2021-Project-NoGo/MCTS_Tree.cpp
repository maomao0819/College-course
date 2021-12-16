#include "MCTS_Tree.h"

/* - - - - - - - - - - - - - - - - - */
// 			   MCTS_node             //
/* - - - - - - - - - - - - - - - - - */

// Costructors

// MCTS_node::MCTS_node() : state(board()), parent(NULL), player(board::black), applied_move(action()), n_wins(0), n_visits(0)
// {
// 	possible_moves = generate_possible_moves(state, player);
// }

/*MCTS_node::MCTS_node(const board &b) : state(b), parent(NULL), player(board::empty), n_wins(0), n_visits(0)
{
	possible_moves = generate_possible_moves(state, player);
}*/

MCTS_node::MCTS_node(const board &b = board(), board::piece_type who = board::black, action::place apply_move = action(), 
	unsigned n_win = 0, unsigned n_visit = 0) : state(b), parent(NULL), player(who), applied_move(apply_move), 
	n_wins(n_win), n_visits(n_visit)
{
	possible_moves = generate_possible_moves(state, player);
}

std::vector<action::place> MCTS_node::generate_possible_moves(const board &state, board::piece_type player)
{
	std::default_random_engine engine;
	std::vector<action::place> space(board::size_x * board::size_y);
	for (size_t i = 0; i < space.size(); i++)
		space[i] = action::place(i, player);
	std::shuffle(space.begin(), space.end(), engine);
	board after = state;
	for (const action::place &move : space)
	{
		after = state;
		if (move.apply(after) == board::legal)
			possible_moves.emplace_back(move);
	}
}

// Getters
board MCTS_node::get_state() const { return state; }
const MCTS_node *MCTS_node::get_parent() const { return parent; }
MCTS_node *MCTS_node::get_parent() { return parent; }
std::vector<MCTS_node *> MCTS_node::get_children() const { return children; }
std::vector<action::place> MCTS_node::get_moves() const { return possible_moves; }
board::piece_type MCTS_node::get_player() const { return player; }
action::place MCTS_node::get_applied_move() const { return applied_move; }
unsigned MCTS_node::get_n_wins() const { return n_wins; }
unsigned MCTS_node::get_n_visits() const { return n_visits; }

//  Update the score and the visits of the node
void MCTS_node::update(unsigned result) // Only one visit, by default
{
	n_wins += result;
	n_visits += 1;
}

void MCTS_node::update(unsigned result, unsigned new_visits) // More than one visit
{
	n_wins += result;
	n_visits += new_visits;
}

// True if all moves have been tried (vector of moves is empty)
bool MCTS_node::is_all_moves_tried() const { return possible_moves.empty(); }

// True if the node has children (vector of children not null)
bool MCTS_node::has_children() const { return !(children.empty()); }

MCTS_node *MCTS_node::make_child(const action::place &move)
{
	board after = state;
	if (move.apply(after) == board::legal)
	{
		// MCTS_node child();
		MCTS_node *child = new MCTS_node(after, change_player(player), move);
		child->parent = this;
		children.emplace_back(child);
		erase_move(move);
		return children[children.size() - 1];
	}
}

board::piece_type MCTS_node::change_player(board::piece_type who)
{
	if (who == board::white)
		return board::black;
	else if (who == board::black)
		return board::white;
}

void MCTS_node::erase_move(const action::place &move)
{
	for (auto it = possible_moves.begin(); it != possible_moves.end(); ++it)
	{
		if ((*it) == move)
		{
			possible_moves.erase(it);
			return;
		}
	}
}

void MCTS_node::print_node() const
{
	std::cout << "Player: " << player << " | W/V: " << n_wins << "/" << n_visits << " #child: " << children.size() 
		<< " #moves: " << possible_moves.size() << std::endl;
}

/* - - - - - - - - - - - - - - - - - */
// 			   MCTS_tree             //
/* - - - - - - - - - - - - - - - - - */

// Costructors
// MCTS_tree::MCTS_tree() : UCB_constant(1.0), n_round(100), timeout(0)
// {
// 	board state = board();
// 	// MCTS_node n(state);
// 	root = new MCTS_node(state);
// }

MCTS_tree::MCTS_tree(const board &b = board(), board::piece_type p = board::black, double UCB_c = 1.0, unsigned n_round = 100, 
	unsigned timeout = 0) : UCB_constant(UCB_c), n_round(n_round), timeout(timeout)
{
	root = new MCTS_node(b, p);
}

double MCTS_tree::calculate_UCB(MCTS_node *n)
{
	unsigned n_win = n->get_n_wins();
	unsigned n_visit = n->get_n_visits();
	double average = n_win / n_visit;
	double explore = UCB_constant * sqrt(log(n_visit) / n_win);
	return average + explore;
}

MCTS_node *MCTS_tree::best_child(MCTS_node *n)
{
	double best_UCB = 0.0;
	double current_UCB = 0.0;
	MCTS_node *best_child = NULL;
	if (n->has_children())
	{
		std::vector<MCTS_node *> children = n->get_children();
		for (auto child = children.begin(); child != children.end(); ++child)
		{
			current_UCB = calculate_UCB(*child);
			if (current_UCB > best_UCB)
			{
				best_UCB = current_UCB;
				best_child = *child;
			}
		}
	}
	return best_child;
}

MCTS_node *MCTS_tree::selection()
{
	MCTS_node *select_node = root;
	while (select_node->has_children() && select_node->is_all_moves_tried())
		select_node = best_child(select_node);
	return select_node;
}

MCTS_node *MCTS_tree::expansion(MCTS_node *n)
{
	MCTS_node *current = n->make_child(n->get_moves()[0]);
	return current;
}

MCTS_node *MCTS_tree::simulation(MCTS_node *n)
{
	bool is_leaf = false;
	while (!is_leaf)
	{
		is_leaf = true;
		board state = n->get_state();
		std::default_random_engine engine;
		std::vector<action::place> space(board::size_x * board::size_y);
		for (size_t i = 0; i < space.size(); i++)
			space[i] = action::place(i, n->get_player());
		std::shuffle(space.begin(), space.end(), engine);
		board after = state;
		for (const action::place &move : space)
		{
			after = state;
			if (move.apply(after) == board::legal)
			{
				is_leaf = false;
				n = new MCTS_node(after, n->change_player(n->get_player())); 
				break;
			}
		}
	}
	return n;
}

board::reward MCTS_tree::check_result(MCTS_node *leaf)
{
	if (leaf->get_player() == root->get_player())
		return 1;
	else
		return 0;
}

void MCTS_tree::backpropagation(MCTS_node *leaf, board::reward result, MCTS_node *expansion_node)
{
	bool is_simulation = true;
	MCTS_node *temp = leaf;
	while (leaf != root)
	{
		if (leaf == expansion_node)
			is_simulation = false;
		if (is_simulation)
		{
			temp = leaf;
			leaf = leaf->get_parent();
			delete temp;
		}
		else
		{
			leaf->update(result);
			leaf = leaf->get_parent();
		}
	}
}

void MCTS_tree::UCT_search()
{
	UCT_search(n_round);
}

void MCTS_tree::UCT_search(unsigned n_round)
{
	while (n_round--)
	{
		MCTS_node *select_node = selection();
		MCTS_node *expansion_node = expansion(select_node);
		MCTS_node *simulation_node = expansion_node;
		MCTS_node *leaf_node = simulation(simulation_node);
		board::reward result = check_result(leaf_node);
		backpropagation(leaf_node, result, expansion_node);
	}
}

action::place MCTS_tree::best_move() 
{ 
	if (root->has_children())
		return best_child(root)->get_applied_move(); 
	else
		return action();
}