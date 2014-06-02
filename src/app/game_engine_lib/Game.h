/*
 * Game.h
 *
 *  Created on: May 31, 2014
 *      Author: paulina
 */

#ifndef GAME_H_
#define GAME_H_
#include <mutex>
#include <memory>
#include <boost/signals2/signal.hpp>


class GamePlayer;

class Game {
	typedef std::shared_ptr<GamePlayer> PlayerPtr;
public:
	Game(PlayerPtr player1, PlayerPtr player2);
	virtual ~Game() = default;

	void changeTurn();
	bool isWinner(PlayerPtr player);
	PlayerPtr getPlayer1();
	PlayerPtr getPlayer2();
	void initGame();

	typedef boost::signals2::signal<void ()> StartGameType;
	StartGameType startGame;
	void playerPrepared();
private:
	PlayerPtr player1_;
	PlayerPtr player2_;
	int prepared_;
	std::mutex player_;
};

#endif /* GAME_H_ */
