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

public:
	Game(std::shared_ptr<GamePlayer> player1, std::shared_ptr<GamePlayer> player2);
	virtual ~Game();

	void changeTurn();
	bool isWinner(std::shared_ptr<GamePlayer> player);
	std::shared_ptr<GamePlayer> getPlayer1();
	std::shared_ptr<GamePlayer> getPlayer2();
	void initGame();

	typedef boost::signals2::signal<void ()> StartGameType;
	StartGameType startGame;
	void playerPrepared();
private:
	std::shared_ptr<GamePlayer> player1_;
	std::shared_ptr<GamePlayer> player2_;
	int prepared_;
	std::mutex player_;
};

#endif /* GAME_H_ */
