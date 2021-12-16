#include <iostream>
#include <map>
#include <stack>
#include <vector>

#include "snake.h"
#include "random.h"

using namespace std;

bool did_snake_touched_itself(std::vector<Point> snake)
{
	for (int i = 1; i < snake.size(); i++)
	{
		if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
		{
			return true;
		}
	}

	return false;
}

bool did_snake_touched_prize(Point prize, Point snake_head)
{
	if (snake_head.x == prize.x && snake_head.y == prize.y)
	{
		return true;
	}

	return false;
}

bool generate_prize(Point &prize, vector<Point> snake, int width, int height)
{
	prize.x = random_int(1, width - 2);
	prize.y = random_int(1, height - 2);

	for (int i = 0; i < snake.size(); i++)
	{
		if (snake[i].x == prize.x && snake[i].y == prize.y)
		{
			return false;
		}
	}

	return true;
}

void generate_snake_piece(vector<Point> &snake, stack<char> commands, int width, int height)
{
	Point tail = snake[snake.size() - 1];

	map<int, Point> possibilities;

	char last_command;

	while (!commands.empty())
	{
		last_command = commands.top();
		commands.pop();
	}

	if (last_command == 'w' || last_command == 'W')
	{
		possibilities.insert(pair<int, Point>(2, {x : tail.x, y : tail.y + 1}));
	}
	if (last_command == 's' || last_command == 'S')
	{
		possibilities.insert(pair<int, Point>(3, {x : tail.x, y : tail.y - 1}));
	}
	if (last_command == 'a' || last_command == 'A')
	{
		possibilities.insert(pair<int, Point>(0, {x : tail.x + 1, y : tail.y}));
	}
	if (last_command == 'd' || last_command == 'D')
	{
		possibilities.insert(pair<int, Point>(1, {x : tail.x - 1, y : tail.y}));
	}

	snake.push_back(possibilities.begin()->second);
}

void handle_snake(vector<Point> &snake, stack<char> &command_stack, int width, int height)
{
	stack<char> temp_command_stack;

	for (int i = 0; i < snake.size(); i++)
	{
		char command = command_stack.top();
		temp_command_stack.push(command);
		handle_snake_body_position(snake[i], command, width, height);
		if (command_stack.size() > 1)
		{
			command_stack.pop();
		}
	}

	while (!command_stack.empty())
	{
		command_stack.pop();
	}

	while (!temp_command_stack.empty())
	{
		command_stack.push(temp_command_stack.top());
		temp_command_stack.pop();
	}
}

void handle_snake_body_position(Point &body, char command, int width, int height)
{
	if (command == 'a' || command == 'A')
	{
		if (body.x > 1)
		{
			body.x--;
		}
		else
		{
			body.x = width - 2;
		}
	}

	if (command == 'd' || command == 'D')
	{
		if (body.x < width - 2)
		{
			body.x++;
		}
		else
		{
			body.x = 1;
		}
	}

	if (command == 's' || command == 'S')
	{
		if (body.y < height - 2)
		{
			body.y++;
		}
		else
		{
			body.y = 1;
		}
	}

	if (command == 'w' || command == 'W')
	{
		if (body.y > 1)
		{
			body.y--;
		}
		else
		{
			body.y = height - 2;
		}
	}
}

void key_listening(stack<char> &commands)
{
	char pressed_key;

	system("stty raw");
	cin.get(pressed_key);
	system("stty cooked");

	commands.push(pressed_key);
}

void print_map(int height, int width, vector<Point> snake, Point prize)
{
	bool touched = did_snake_touched_itself(snake);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int printed_snake = 0;

			for (int k = 0; k < snake.size(); k++)
			{
				if (snake[k].x == j && snake[k].y == i)
				{

					if (k == 0)
					{
						cout << "\033[1;31m";

						if (touched)
						{
							cout << "\033[47m";
						}
					}

					cout << "O";
					if (k == 0)
					{
						cout << "\033[1;37m";

						if (touched)
						{
							cout << "\033[40m";
						}
					}
					printed_snake++;
					break;
				}
			}

			if (printed_snake)
			{
				continue;
			}

			if (i == 0 || i == height - 1)
			{
				cout << "-";
			}
			else if (j == 0 || j == width - 1)
			{
				cout << "|";
			}
			else if (prize.x == j && prize.y == i)
			{
				cout << "+";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}

	cout << endl;
}
