#include <iostream>
#include <stack>
#include <signal.h>
#include <unistd.h>
#include <vector>

#include "error-handling.h"
#include "random.h"
#include "snake.h"

#define CLOSE_KEY 27
#define SECOND 1000000

#define WIDTH 30
#define HEIGHT 10

using namespace std;

stack<char> command_stack;
vector<Point> snake;

Point prize;
bool can_generate_prize = true;
bool game_over = false;

void get_back_to_cooked_mode()
{
	system("stty cooked");
}

void program_error()
{
	error("Error", get_back_to_cooked_mode);
}

void handle_shutdown(int)
{
	program_error();
}

void print_game_screen()
{
	cout << "Press ESC to exit!" << endl;
	cout << "\"W\" -> UP\t\"S\" -> DOWN" << endl;
	cout << "\"A\" -> LEFT\t\"D\" -> RIGHT" << endl;

	print_map(HEIGHT, WIDTH, snake, prize);
}

int main()
{
	cout << "\033[1;37m";

	if (catch_signal(SIGINT, handle_shutdown) == -1)
	{
		program_error();
	}

	while (true)
	{
		system("clear");

		handle_snake(snake, command_stack, WIDTH, HEIGHT);

		if (!can_generate_prize)
		{
			can_generate_prize = did_snake_touched_prize(prize, snake[0]);
		}

		if (can_generate_prize && snake.size() != 0)
		{
			generate_snake_piece(snake, command_stack, WIDTH, HEIGHT);
		}
		else if (can_generate_prize)
		{
			snake.push_back({x : random_int(1, WIDTH - 2), y : random_int(1, HEIGHT - 2)});
		}

		while (can_generate_prize)
		{
			can_generate_prize = !generate_prize(prize, snake, WIDTH, HEIGHT);
		}

		print_game_screen();

		game_over = did_snake_touched_itself(snake);

		if (game_over)
		{
			break;
		}

		key_listening(command_stack);

		if (command_stack.top() == CLOSE_KEY)
		{
			break;
		}
	}

	cout << endl;

	if (game_over)
	{
		cout << "Game Over!";
	}
	else
	{
		cout << "Come back later!";
	}

	cout << endl;

	return 0;
}
