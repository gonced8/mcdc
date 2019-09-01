#include "bubblesort.h"


void bubble_sort(Element *list, unsigned int n){
	unsigned int newn;
	unsigned int i;
	Element aux;

	do{
		newn = 0;
		for(i=1; i<n; i++){
			if (list[i-1] > list[i]) {
				aux = list[i-1];
				list[i-1] = list[i];
				list[i] = aux;
				newn = i;
			}
		}
		n = newn;
	}while (n > 1);
}
