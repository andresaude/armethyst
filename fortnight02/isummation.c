
#define SIZE 10
int v[SIZE] = {5,2,9,6,3,10,7,4,1,8};
int summ;

void main (void) {
	int i;
	summ = 0;
	for (i = 0; i < SIZE; i++) {
		summ+=v[i];
	}
}
