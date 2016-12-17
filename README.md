# Othello-Game-alpha-Beta-pruning-


Alpha-Beta pruning is not actually a new algorithm, rather an optimization technique for minimax algorithm. It reduces the computation time by a huge factor. This allows us to search much faster and even go into deeper levels in the game tree. It cuts off branches in the game tree which need not be searched because there already exists a better move available. It is called Alpha-Beta pruning because it passes 2 extra parameters in the minimax function, namely alpha and beta.

Let’s define the parameters alpha and beta.
Alpha is the best value that the maximizer currently can guarantee at that level or above.
Beta is the best value that the minimizer currently can guarantee at that level or above.

Pseudocode :

function minimax(node, depth, isMaximizingPlayer, alpha, beta):

    if node is a leaf node :
        return value of the node
    
    if isMaximizingPlayer :
        bestVal = -INFINITY 
        for each child node :
            value = minimax(node, depth+1, false, alpha, beta)
            bestVal = max( bestVal, value) 
            alpha = max( alpha, bestVal)
            if beta <= alpha:
                break
        return bestVal

    else :
        bestVal = +INFINITY 
        for each child node :
            value = minimax(node, depth+1, true, alpha, beta)
            bestVal = min( bestVal, value) 
            beta = min( beta, bestVal)
            if beta <= alpha:
                break
        return bestVal
        
        
        
        
        This heuristic function is actually a collection of several heuristics and calculates the utility value of a board position by assigning different weights to those heuristics. These heuristics take into account the mobility, coin parity, stability and corners-captured aspects of a board configuration. Each heuristic scales its return value from -100 to 100. These values are weighed appropriately to play an optimal game. The various heuristics include:


1. Coin Parity


This component of the utility function captures the difference in coins between the max player and the min player. The return value is determined as follows :


Coin Parity Heuristic Value =
	100 * (Max Player Coins - Min Player Coins ) / (Max Player Coins + Min Player Coins)
	
	
	
2. Mobility

It attempts to capture the relative difference between the number of possible moves for the max and the min players, with the intent of restricting the opponent’s mobility and increasing one’s own mobility. This value is calculated as follows :


if ( Max Player Moves + Min Player Moves != 0)
	Mobility Heuristic Value =
		100 * (Max Player Moves - Min Player Moves) / (Max Player Moves + Min Player Moves)
else
	Mobility Heuristic Value = 0
	
	
	
3. Corners Captured

Corners hold special importance because once captured, they cannot be flanked by the opponent. They also allow a player to build coins around them and provide stability to the player’s coins. This value is captured as follows :


if ( Max Player Corners + Min Player Corners != 0)
	Corner Heuristic Value =
		100 * (Max Player Corners - Min Player Corners) / (Max Player Corners + Min Player Corners)
else
	Corner Heuristic Value = 0
	
	
	
4. Stability


The stability measure of a coin is a quantitative representation of how vulnerable it is to being flanked. Coins can be classified as belonging to one of three categories: (i) stable, (ii) semi-stable and (iii) unstable.

Stable coins are coins which cannot be flanked at any point of time in the game from the given state. Unstable coins are those that could be flanked in the very next move. Semi-stable coins are those that could potentially be flanked at some point in the future, but they do not face the danger of being flanked immediately in the next move. Corners are always stable in nature, and by building upon corners, more coins become stable in the region.

Weights are associated to each of the three categories, and summed to give rise to a final stability value for the player. Typical weights could be 1 for stable coins, -1 for unstable coins and 0 for semi-stable coins.

The stability value is calculated as follows :


if ( Max Player Stability Value + Min Player Stability Value != 0)
	Stability  Heuristic Value =
		100 * (Max Player Stability Value - Min Player Stability Value) / (Max Player Stability Value + Min Player Stability Value)
else
	Stability Heuristic Value = 0
  
  
