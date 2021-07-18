# multiAgents.py
# --------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and child states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best
        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        The evaluation function takes in the current and proposed child
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        childGameState = currentGameState.getPacmanNextState(action)
        newPos = childGameState.getPacmanPosition()
        newFood = childGameState.getFood()
        newGhostStates = childGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        return childGameState.getScore()

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.getNextState(agentIndex, action):
        Returns the child game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        # Begin your code (Part 1)
        def minimax(currentGameState, depth, idx_agent):
            if currentGameState.isLose() or currentGameState.isWin():
                return self.evaluationFunction(currentGameState)
            legalMoves = currentGameState.getLegalActions(idx_agent)
            if len(legalMoves) == 0:
                return self.evaluationFunction(currentGameState)
            scores = []
            if idx_agent != 0:
                if idx_agent == gameState.getNumAgents() - 1:
                    if depth == self.depth:
                        for action in legalMoves:
                            childGameState = currentGameState.getNextState(idx_agent, action)
                            scores.append(self.evaluationFunction(childGameState))
                        return min(scores)
                    else:
                        for action in legalMoves:
                            childGameState = currentGameState.getNextState(idx_agent, action)
                            scores.append(minimax(childGameState, depth + 1, 0))
                        return min(scores)    
                else:
                    for action in legalMoves:
                        childGameState = currentGameState.getNextState(idx_agent, action)
                        scores.append(minimax(childGameState, depth, idx_agent + 1))
                    return min(scores)

            else:
                for action in legalMoves:
                    childGameState = currentGameState.getNextState(0, action)
                    scores.append(minimax(childGameState, depth, 1))
                return max(scores)    

        # Collect legal moves and child states
        legalMoves = gameState.getLegalActions()

        scores = []
        # Choose one of the best actions
        for action in legalMoves:
            childgameState = gameState.getNextState(0, action)
            scores.append(minimax(childgameState, 1, 1))
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        # Pick randomly among the best
        chosenIndex = random.choice(bestIndices) 
        return legalMoves[chosenIndex]
        util.raiseNotDefined()
        # End your code (Part 1)

class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        # Begin your code (Part 2)
        global bestActions
        bestActions = []

        def value(state, idx_agent, alpha, beta, depth):
            if idx_agent == state.getNumAgents():
                idx_agent = 0
                depth += 1   
            if state.isLose() or state.isWin():
                return self.evaluationFunction(state)
            legalMoves = state.getLegalActions(idx_agent)
            if len(legalMoves) == 0:
                return self.evaluationFunction(state)
            if idx_agent == 0:
                return max_value(state, idx_agent, alpha, beta, depth)
            else:
                return min_value(state, idx_agent, alpha, beta, depth)

        def max_value(state, idx_agent, alpha, beta, depth):
            v = float('-inf')
            legalMoves = state.getLegalActions(idx_agent)
            for action in legalMoves:
                successor = state.getNextState(idx_agent, action)
                if depth == 1:
                    global bestActions
                    successor_v = value(successor, idx_agent + 1, alpha, beta, depth)
                    if successor_v > v:
                        v = successor_v
                        bestActions = [action]
                    elif successor_v == v:
                        bestActions.append(action)
                else:
                    v = max(v, value(successor, idx_agent + 1, alpha, beta, depth))
                if v > beta:
                    return v
                alpha = max(alpha, v)
            return v 

        def min_value(state, idx_agent, alpha, beta, depth):
            v = float('inf')
            legalMoves = state.getLegalActions(idx_agent)
            for action in legalMoves:
                successor = state.getNextState(idx_agent, action)
                if depth == self.depth and idx_agent == state.getNumAgents() - 1:
                    v = min(v, self.evaluationFunction(successor))
                else:
                    v = min(v, value(successor, idx_agent + 1, alpha, beta, depth))
                if v < alpha:
                    return v
                beta = min(beta, v)
            return v 

        bestScore = value(gameState, 0, float('-inf'), float('inf'), 1)
        return random.choice(bestActions)
        util.raiseNotDefined()
        # End your code (Part 2)

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        # Begin your code (Part 3)
        def expectimax(currentGameState, depth, idx_agent):
            if currentGameState.isLose() or currentGameState.isWin():
                return self.evaluationFunction(currentGameState)
            legalMoves = currentGameState.getLegalActions(idx_agent)
            if len(legalMoves) == 0:
                return self.evaluationFunction(currentGameState)
            scores = []
            if idx_agent != 0:
                if idx_agent == gameState.getNumAgents() - 1:
                    if depth == self.depth:
                        scores = 0.0
                        for action in legalMoves:
                            childGameState = currentGameState.getNextState(idx_agent, action)
                            scores += self.evaluationFunction(childGameState)
                        return scores / len(legalMoves)
                    else:
                        scores = 0.0
                        for action in legalMoves:
                            childGameState = currentGameState.getNextState(idx_agent, action)
                            scores += expectimax(childGameState, depth + 1, 0)
                        return scores / len(legalMoves)
                else:
                    scores = 0.0
                    for action in legalMoves:
                        childGameState = currentGameState.getNextState(idx_agent, action)
                        scores += expectimax(childGameState, depth, idx_agent + 1)
                    return scores / len(legalMoves)

            else:
                for action in legalMoves:
                    childGameState = currentGameState.getNextState(0, action)
                    scores.append(expectimax(childGameState, depth, 1))
                return max(scores)  

        # Collect legal moves and child states
        legalMoves = gameState.getLegalActions()

        scores = []
        # Choose one of the best actions
        for action in legalMoves:
            childgameState = gameState.getNextState(0, action)
            scores.append(expectimax(childgameState, 1, 1))
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        # Pick randomly among the best
        chosenIndex = random.choice(bestIndices)
        return legalMoves[chosenIndex]
        util.raiseNotDefined()
        # End your code (Part 3)

def betterEvaluationFunction(currentGameState):
    """
    Your extreme evaluation function
    """
    # Begin your code (Part 4)
    original_score = currentGameState.getScore()
    food_score = currentGameState.getNumFood()
    pacman_pos = currentGameState.getPacmanPosition()
    n_ghost = currentGameState.getNumAgents() - 1
    total_distance = 1
    min_distance = 1000
    scared_time = 0
    for ghost_idx in range(n_ghost):
        ghost_pos = currentGameState.getGhostPosition(ghost_idx + 1)
        distance = (pacman_pos[0] - ghost_pos[0]) ** 2 + (pacman_pos[1] - ghost_pos[1]) ** 2
        if distance < min_distance:
            min_distance = distance
        total_distance += distance 
        ghost_state = currentGameState.getGhostState(ghost_idx + 1)
        scared_time = ghost_state.scaredTimer
    min_distance ** 0.5
    if min_distance * 1.2 > scared_time:
        scared_time = 0
    return original_score - food_score - scared_time * 4 * min_distance
    util.raiseNotDefined()
    # End your code (Part 4)

# Abbreviation
better = betterEvaluationFunction
