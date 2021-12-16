#include <vector>

typedef struct Point
{
	int x, y;
} Point;

bool did_snake_touched_prize(Point prize, Point snake_head);
bool generate_prize(Point &prize, std::vector<Point> snake, int width, int height);
void generate_snake_piece(std::vector<Point> &snake, std::stack<char> commands, int width, int height);
void handle_snake(std::vector<Point> &snake, std::stack<char> &command_stack, int width, int height);
void handle_snake_body_position(Point &body, char command, int width, int height);
void key_listening(std::stack<char> &commands);
void print_map(int height, int width, std::vector<Point> snake, Point prize);
