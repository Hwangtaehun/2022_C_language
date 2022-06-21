#include <stdio.h>

void Swap(int num1, int num2);

int main() {
	int a = 55, b = 33;
	printf("main에서 Swap()실행 전 : a = %d. b = %d\n", a, b);
	Swap(a, b);
	printf("main에서 Swap()실행 후 : a = %d. b = %d\n", a, b);
	return 0;
}

void Swap(int num1, int num2) 
{
	int temp;
	printf("Swap에서 교환 전: num1 = %d, num2 = %d\n", num1, num2);

	temp = num1;
	num1 = num2;
	num2 = temp;

	printf("Swap에서 교환 후: num1 = %d, num2 = %d\n", num1, num2);

}