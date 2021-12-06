
#define SIZE 1000000
int v[SIZE] = { };
int summ=0;

void main (void) {
	int i;
	// fill array
	for (i = 0; i < SIZE; i++) {
		v[i] = i+1;
	}
	// summation
	for (i = 0; i < SIZE; i++) {
		summ+=v[i];
	}
}
