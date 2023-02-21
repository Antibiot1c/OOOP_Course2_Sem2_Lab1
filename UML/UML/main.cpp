#include <iostream>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <chrono>
#include <mutex>
#include <future>
using namespace std;
using std::chrono::steady_clock;



enum edir {
	STOP = 0,
	LEFT = 1,
	UPLEFT = 2,
	DLEFT = 3,
	RIGHT = 4,
	UPRIGHT = 5,
	DRIGHT = 6
};


class Orb

{

private:
	int x, y;
	int OX, OY;
	edir direction;

public:

	Orb(int posX, int posY)
	{
		OX = posX;
		OY = posY;
		x = posX; y = posY;
		direction = STOP;
	}

	void reboot()
	{
		/// <summary>
		/// Restart
		/// </summary>
		x = OX; y = OY;
		direction = STOP;
	}

	void changedir(edir d)
	{
		/// <summary>
		/// Change dirrection
		/// </summary>
		/// <param name="d"></param>
		direction = d;
	}

	void randir()
	{
		/// <summary>
		/// Random dirrection
		/// </summary>
		direction = (edir)((rand() % 5) + 1);
	}

	inline int getX() {
		/// <summary>
		/// Get X position
		/// </summary>
		/// <returns></returns>
		return x;
	}

	inline int getY() {
		/// <summary>
		/// Get Y position
		/// </summary>
		/// <returns></returns>
		return y;
	}

	inline edir getdir() {
		/// <summary>
		/// Get dirrection
		/// </summary>
		/// <returns></returns>
		return direction;
	}

	void Move()
	{
		/// <summary>
		/// Move Orb
		/// </summary>
		switch (direction)
		{
		case STOP:
			break;

		case LEFT:
			x--;
			break;

		case RIGHT:
			x++;
			break;

		case UPLEFT:
			x--; y--;
			break;

		case DLEFT:
			x--; y++;
			break;

		case UPRIGHT:
			x++; y--;
			break;

		case DRIGHT:
			x++; y++;
			break;

		default:
			break;
		}
	}

	friend ostream& operator<<(ostream& o, Orb c)
	{
		o << "Orb [" << c.x << "," << c.y << "][" << c.direction << "]";
		return o;
	}
};

class Blade

{

private:

	int x, y;
	int OX, OY;

public:

	Blade()
	{
		x = y = 0;
	}

	Blade(int posX, int posY) : Blade()
	{
		OX = posX;
		OY = posY;
		x = posX;
		y = posY;

	}

	inline void reboot() {
		/// <summary>
		/// Restart
		/// </summary>
		x = OX; y = OY;
	}

	inline int getX() {
		/// <summary>
		/// Get X position
		/// </summary>
		/// <returns></returns>
		return x;
	}

	inline int getY() {
		/// <summary>
		/// Get Y position
		/// </summary>
		/// <returns></returns>
		return y;
	}

	inline void up() {
		/// <summary>
		/// Move Blade UP
		/// </summary>
		y--;
	}

	inline void down() {
		/// <summary>
		/// Move Blade DOWN
		/// </summary>
		y++;
	}

	friend ostream& operator<<(ostream& o, Blade c)
	{
		o << "Blade [" << c.x << "," << c.y << "]";
		return o;
	}
};

class GameController

{

private:

	/// <summary>
	/// Board parametrs
	/// </summary>
	int height, width;
	int resultA, resultB;
	bool exit;
	char upA, dA, upB, dB;
	Orb* orb;
	Blade* userA;
	Blade* userB;

public:

	~GameController()
	{
		delete orb, userA, userB;
	}

	GameController(int w, int h)
	{
		/// <summary>
		/// Here u can change presskeys and board color
		/// </summary>
		
		srand(time(NULL));

		exit = false;
		upA = 'e'; upB = 'u';       // User A 
		dA = 'd'; dB = 'j';			// User B 
		height = h; width = w;
		orb = new Orb(w / 2, h / 2);
		userA = new Blade(1, h / 2 - 3);
		userB = new Blade(w - 2, h / 2 - 3);
		resultA = resultB = 0;

		system("color 8E"); //Gray + Light Yellow
		
		

		//0 = Black       
		//1 = Blue       
		//2 = Green       A = Light Green
		//3 = Aqua        B = Light Aqua
		//4 = Red         C = Light Red
		//5 = Purple      D = Light Purple
		//6 = Yellow      E = Light Yellow
		//7 = White       F = Bright White
		//8 = Gray
		//9 = Light Blue
	}



	void Run()
	{
		/// <summary>
		/// Run Game
		/// </summary>
		while (!exit)
		{
			Input();
			Paint();
			Rules();
		}
	}

	void Input()
	{
		/// <summary>
		/// Game Mehanics
		/// </summary>
		
		orb->Move();


		int userAy = userA->getY();
		int userBy = userB->getY();
		int userAx = userA->getX();
		int userBx = userB->getX();
		int orbx = orb->getX();
		int orby = orb->getY();

		if (_kbhit())
		{
			char current = _getch();
			if (current == dA)
				if (userAy + 4 < height)
					userA->down();
			if (current == dB)
				if (userBy + 4 < height)
					userB->down();
			if (current == upA)
				if (userAy > 0)
					userA->up();
			if (current == upB)
				if (userBy > 0)
					userB->up();


			if (orb->getdir() == STOP)
				orb->randir();

			if (current == 'q')
				exit = true;
		}
	}

	void Paint()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int userAy = userA->getY();
				int userBy = userB->getY();
				int userAx = userA->getX();
				int userBx = userB->getX();
				int orbx = orb->getX();
				int orby = orb->getY();

				if (j == 0)
					cout << "\xB2";

				if (orbx == j && orby == i)
					cout << "O";

				else if (userAx == j && userAy == i)
					cout << "\xDB";

				else if (userBx == j && userBy == i)
					cout << "\xDB";

				else if (userBx == j && userBy + 1 == i)
					cout << "\xDB";

				else if (userBx == j && userBy + 2 == i)
					cout << "\xDB";

				else if (userBx == j && userBy + 3 == i)
					cout << "\xDB";

				else if (userAx == j && userAy + 1 == i)
					cout << "\xDB";

				else if (userAx == j && userAy + 2 == i)
					cout << "\xDB";

				else if (userAx == j && userAy + 3 == i)
					cout << "\xDB";

				else
					cout << " ";

				if (j == width - 1)
					cout << "\xB2";
			}

			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "result team A: " << resultA << endl << "result team B: " << resultB << endl;
	}


	void resultUp(Blade* user)
	{
		if (user == userA)
			resultA++;
		else if (user == userB)
			resultB++;


		userA->reboot();
		userB->reboot();
		orb->reboot();
	}

	void Rules()
	{
		//game rules


		int userAy = userA->getY();
		int userBy = userB->getY();
		int userAx = userA->getX();
		int userBx = userB->getX();
		int orbx = orb->getX();
		int orby = orb->getY();

		//left blade
		for (int i = 0; i < 4; i++)
			if (orbx == userAx + 1)
				if (orby == userAy + i)
					orb->changedir((edir)((rand() % 3) + 4));

		//right blade
		for (int i = 0; i < 4; i++)
			if (orbx == userBx - 1)
				if (orby == userBy + i)
					orb->changedir((edir)((rand() % 3) + 1));

		//down barrier
		if (orby == height - 1)
			orb->changedir(orb->getdir() == DRIGHT ? UPRIGHT : UPLEFT);

		//up barrier
		if (orby == 0)
			orb->changedir(orb->getdir() == UPRIGHT ? DRIGHT : DLEFT);

		//right barrier
		if (orbx == width - 1)
			resultUp(userA);

		//left barrier
		if (orbx == 0)
			resultUp(userB);
	}
};


class Timer
{
/// <summary>
/// Just timer
/// </summary>

private:
	std::mutex mtx;
	std::future<void> _ftr;

	bool _isRunning;
	bool _completed;
	void delay(const std::chrono::milliseconds& ms);

public:
	Timer() : _isRunning(false), _completed(false) {};

	bool isRunning();
	bool isCompleted();
	bool start(const std::chrono::milliseconds& ms);

};

void Timer::delay(const std::chrono::milliseconds& ms) {
	std::unique_lock<std::mutex> lck(mtx);
	_completed = false;

	_isRunning = true;

	lck.unlock();
	auto time_started = steady_clock::now();

	std::this_thread::sleep_for(ms);

	lck.lock();
	_isRunning = false;
	_completed = true;
}

bool Timer::isRunning() {
	std::unique_lock<std::mutex> lck(mtx);
	return _isRunning;
}

bool Timer::isCompleted() {
	std::unique_lock<std::mutex> lck(mtx);
	return _completed;
}

bool Timer::start(const std::chrono::milliseconds& ms) {
	if (isRunning()) {
		return false;
	}
	else {
		_ftr = std::async(&Timer::delay, this, ms);
		return true;
	}
}


int main()
{
	GameController c(50, 25); // game board size
	c.Run();
	return 0;


}