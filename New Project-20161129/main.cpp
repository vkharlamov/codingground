#include "string.h"
#include "stdio.h"
 
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
 
int main (void) {
const int N = 5;
const int M = 3;
	int arr [M];
	printf ("----- start ----\n");
	int i , j;
	for (i = 0; i < M; i++)
		arr [i] = i;
	int cnt_c  = 0;
	do {
 
		for (i = 0; i < M; i++)
			printf ("%d" , arr [i]);
		printf ("\n");
		cnt_c++;
 
		for ( j = M -1 ; j >=0 && arr [j] >= N - M + j; j--) ;
		if ( j >= 0){
			arr [j] ++;
			for (i = j + 1; i < M; i++)
				arr [i] = arr [i-1]  + 1;
		}
		else break;
 
	}while (true);
 
	printf ("cnt_c = %d", cnt_c);
}