#ifndef BASE_H
#define BASE_H

const int t_size = 31;
const int offset = 15;

struct Point {
	float x;
	float y;
	Point(float x, float y) : x(x), y(y) {}
};

struct Triangle {
	Point A;
	Point B;
	Point C;
	Triangle(Point A, Point B, Point C) : A(A), B(B), C(C) {}
	bool check_inside(Point P) {
		return false;
	}
};

struct Circle {
	Point p;
	float r;

	Circle(Point p, float r) : p(p), r(r) {}
};

void render(char table[t_size][t_size]);
void char_on_table(char table[t_size][t_size], int x, int y, char c);
void fill_table(char table[t_size][t_size], char c);
void draw_line(char table[t_size][t_size], Point A, Point B, char c);
void draw_triangle(char table[t_size][t_size], Triangle triangle);
void rotate_triangle(Triangle& triangle);
void draw_circle(char table[t_size][t_size], Circle circle);
Triangle gen_triangle();
Circle gen_circle();
Point rotate_vector(Point A, double angle);

#endif // BASE_H

