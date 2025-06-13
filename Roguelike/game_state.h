#ifndef GAME_STATE_H
#define GAME_STATE_H

class Cursor;
class Player;

struct GameState
{
public:
	bool cursorMode = false;
	std::shared_ptr<Cursor> cursor;
	std::shared_ptr<Player> player;
};

#endif // GAME_STATE_H