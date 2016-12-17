/*
* @file botTemplate.cpp
* @author Arun Tejasvi Chaganty <arunchaganty@gmail.com>
* @date 2010-02-04
* Template for users to create their own bots
*/

#include "Othello.h"
#include "OthelloBoard.h"
#include "OthelloPlayer.h"
#include <cstdlib>
using namespace std;
using namespace Desdemona;

class MyBot: public OthelloPlayer
{
    public:
        MyBot( Turn turn );

        virtual Move play( const OthelloBoard& board );
    private:
};

MyBot::MyBot( Turn turn )
    : OthelloPlayer( turn )
{
}
Turn global;
int score[10][10] = {
            {0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
            {0, 65, -3,  6,  4,  4,  6, -3, 65,  0},
            {0, -3, -29, 3,  1,  1,  3, -29,-3,  0},
            {0,  6,  3,  5,  3,  3,  5,  3,  6,  0},
            {0,  4,  1,  3,  1,  1,  3,  1,  4,  0},
            {0,  4,  1,  3,  1,  1,  3,  1,  4,  0},
            {0,  6,  3,  5,  3,  3,  5,  3,  6,  0},
            {0, -3, -29, 3,  1,  1,  3, -29,-3,  0},
            {0, 65, -3,  6,  4,  4,  6, -3, 65,  0},
            {0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
    };
int evaluation(const OthelloBoard & board){
    int mob = board.getValidMoves(global).size() - board.getValidMoves(other(global)).size(); 
    int Val = 0;
    for (int i = 0; i < 8; ++i)
     {
        for (int j = 0; j < 8; ++j)
         {
            if (board.get(i, j) == global)
                Val += score[i + 1][j + 1];
            else if (board.get(i, j) == other(global))
                Val -= score[i + 1][j + 1];
        }
    }
    return Val+mob;
}
int minimax(const OthelloBoard & board, int depth,bool isMaximizingPlayer)
{
    if(depth == 3){
        return evaluation(board);
    }
    if(isMaximizingPlayer){
        int bestval = -10000;
        list<Move> moves = board.getValidMoves(global);
        list<Move>::iterator it;
        for(it = moves.begin(); it!=moves.end();++it){
            OthelloBoard temp_board = board;
            temp_board.makeMove(global, *it);
            int value = minimax(temp_board, depth+1, false);
            bestval = max(bestval, value);
        }
        return bestval;
    }
    else{
        int bestval = 10000;
        list<Move> moves = board.getValidMoves(other(global));
        list<Move>::iterator it;
        for(it = moves.begin(); it!=moves.end();++it){
            OthelloBoard temp_board = board;
            temp_board.makeMove(other(global), *it);
            int value = minimax(temp_board, depth+1, true);
            bestval = min(bestval,value);
        }
        return bestval;
    }
}
Move MyBot::play( const OthelloBoard& board )
{
    global = turn;

    list<Move> moves = board.getValidMoves( turn );
    list<Move>::iterator it;
    int bestval = -10000;
    Move optimal = *(moves.begin());
    for(it = moves.begin();it!=moves.end();++it)
    {
        OthelloBoard temp_board = board;
        temp_board.makeMove(turn, *it);
        int value = minimax(temp_board, 1, false);
        if(value > bestval){
            bestval = value;
            optimal = *it;
        }
    }
    return optimal;
}

// The following lines are _very_ important to create a bot module for Desdemona

extern "C" {
    OthelloPlayer* createBot( Turn turn )
    {
        return new MyBot( turn );
    }

    void destroyBot( OthelloPlayer* bot )
    {
        delete bot;
    }
}

