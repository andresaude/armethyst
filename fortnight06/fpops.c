
#define SIZE 11

/*
 * Parabola: y = ax^2 + bx + c;
 * xc: Centro da parabola -> y' = 0 -> 2ax + b = 0 -> x = -b / 2a = xc
 * xc fica em v[SIZE / 2]; Logo, a abscissa x em v[0] é (xc - (SIZE/2))
 */

float v[SIZE] = {3.2, 0.5, 4.7, 0, 0, 0, 0, 0, 0, 0, 0};

void main (void) {
	int i;
	float a, b, c, x;
	a = v[0]; b = v[1]; c = v[2];
	x = (-b / (2*a)) - (SIZE / 2); // x em v[0], ver documentação acima
	for (i = 0; i < SIZE; i++) {
		v[i] = a*x*x + b*x + c;
		x+=1;
	}
}
