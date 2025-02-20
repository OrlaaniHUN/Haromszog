#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "Base.h"

int main()
{
	char table[t_size][t_size];
	Triangle triangle = gen_triangle();
	Circle circle = gen_circle();

	while (true)
	{
		system("cls");
		fill_table(table, '.');
		draw_triangle(table, triangle);
		draw_line(table, triangle.A, triangle.B, 's');
		draw_line(table, triangle.B, triangle.C, 'o');
		draw_line(table, triangle.C, triangle.A, 'x');
		draw_circle(table, circle);
		render(table);
		Sleep(500);
		rotate_triangle(triangle);
	}

	
}


void render(char table[t_size][t_size]) {
	std::string line;
	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			line = line + table[i][j] + table[i][j];
		}
		std::cout << line << "\n";
		line.clear();
	}
}

void char_on_table(char table[t_size][t_size], int x, int y, char c) {
	table[x + offset][y+offset] = c;
}

void fill_table(char table[t_size][t_size], char c) {
	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			table[i][j] = c;
		}
	}
}

void draw_line(char table[t_size][t_size], Point A, Point B, char c) {
	//Bresenham' line drawing algorithm

	/*int x1 = int(A.x);
	int	y1 = int(A.y);
	int x2 = int(B.x);
	int y2 = int(B.y);

	float dx = x2 - x1;
	float dy = y2 - y1;

	float step = max(abs(dx), abs(dy));

	if (step != 0) {
		float stepx = dx / step;
		float stepy = dy / step;
		for (int i = 0; i < step+1; i++)
		{
			char_on_table(table, int(x1 + i * stepx), int(y1 + i * stepy), c);
		}
	}*/

	//gpts' version
	/*int x1 = int(A.x), y1 = int(A.y);
	int x2 = int(B.x), y2 = int(B.y);
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	int offset = 15; // Adjusting for display
	while (true) {
		table[x1 + offset][y1 + offset] = 'N';

		if (x1 == x2 && y1 == y2) break;

		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x1 += sx; }
		if (e2 < dx) { err += dx; y1 += sy; }
	}*/


	Point vec(B.x - A.x, B.y - A.y);
	int offset = 15;
	for (float i = 1; i < 18; i++)
	{
		char_on_table(table, int(round(A.x + (vec.x / 18) * i)), int(round(A.y + (vec.y / 18) * i)), c);
	}

}

void draw_triangle(char table[t_size][t_size], Triangle triangle) {
	char_on_table(table, int(triangle.A.x), int(triangle.A.y), 'N');
	char_on_table(table, int(triangle.B.x), int(triangle.B.y), 'N');
	char_on_table(table, int(triangle.C.x), int(triangle.C.y), 'N');
}

void rotate_triangle(Triangle& triangle) {
	triangle.A = rotate_vector(triangle.A, 10);
	triangle.B = rotate_vector(triangle.A, 120);
	triangle.C = rotate_vector(triangle.B, 120);
}

void draw_circle(char table[t_size][t_size],Circle circle) {
	Point v = Point(circle.p.x, circle.p.y + circle.r);
	for (int i = 0; i < 72; i++)
	{
		char_on_table(table, int(round(v.x)), int(round(v.y)), 'O');
		v = rotate_vector(v, 5);
	}
}

Triangle gen_triangle() {
	//PQ => (x2-x1,y2-y1)
	Point A_vec(0, 10);
	Point B_vec = rotate_vector(A_vec, 120);
	Point C_vec = rotate_vector(B_vec, 120);
	Triangle triangle(A_vec,B_vec,C_vec);
	return triangle;
}

Circle gen_circle() {
	Point p(0, 2);
	Circle circle(p, 10);
	return circle;
}

Point rotate_vector(Point A, double angle) {
	double rad = angle * M_PI / 180.0;
	double cos_theta = cos(rad);
	double sin_theta = sin(rad);
	double x_new = A.x * cos_theta - A.y * sin_theta;
	double y_new = A.x * sin_theta + A.y * cos_theta;

	return Point(x_new, y_new);
}