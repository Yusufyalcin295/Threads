
//HAZIR DİZİ İLE İŞLEM 

/*
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX_SIZE 100
#define thread_numbers 3

typedef struct {
	int id;
	int* numbers;
	int size;

}threadVerisi;

DWORD WINAPI  myThreadFunction(LPVOID lpParam) {

	threadVerisi* veri = (threadVerisi*)lpParam;

	int sum = 0;

	for (int i = 0; i < veri->size; i++) {
		
		sum += veri->numbers[i];
 
	}
	double average = (double)sum / veri->size;
	printf("Thread %d is run ! Average:%.2f \n", veri->id, average);

	return 0;
 }

int main() {

	HANDLE  threads[thread_numbers];
	threadVerisi* veriler[thread_numbers];

	int arrays[thread_numbers][5] = { {10,20,30,40,50 }, { 12,14,16,18,20 }, { 0,18,16,34,48 } };

	

	for (int i = 0; i < thread_numbers; i++) {

		veriler[i] = (threadVerisi*)malloc(sizeof(threadVerisi));
		veriler[i]->id = i + 1;
		veriler[i]->numbers = arrays[i];
		veriler[i]->size = 5;
		
		threads[i] = CreateThread(NULL, 0, myThreadFunction, veriler[i], 0, NULL);

		if (threads[i] == NULL) {
			printf("THREAD %d OLUSTURULMADI\n",i);
		}


	}		

	WaitForMultipleObjects(thread_numbers, threads, TRUE, INFINITE);

	for (int i = 0; i < thread_numbers; i++) {
		CloseHandle(threads[i]);
		free(veriler[i]);

	}

	printf("PROGRAM SONA ERDI!\n");


	return 0;
}
*/

//KULLANICIDAN ALININAN BOYUT İLE OLUŞTURULAN DİZİYLE İŞLEM 

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define thread_numbers 3

typedef struct {
	int id;
	int* numbers;
	int size;
	double average;

}threadVerisi;

DWORD WINAPI myThreadFunction(LPVOID lpParam) {
	threadVerisi* veri = (threadVerisi*)lpParam;
	int sum=0;

	for (int i = 0; i <veri->size; i++) {

		sum += veri->numbers[i];
	}
	veri-> average = (double)sum / veri->size;

	//printf("Thrad %d is run! average is:%.2f", veri->id, average);

	return 0;

}

int main() {

	HANDLE threads[thread_numbers];
	threadVerisi* veriler[thread_numbers];

	for (int i = 0; i < thread_numbers; i++) {
	
		veriler[i] = (threadVerisi*)malloc(sizeof(threadVerisi));
		veriler[i]->id = i + 1;

		printf("Enter numbers for thread %d:\n" , i + 1);
		scanf_s("%d", &veriler[i]->size);

		veriler[i]->numbers = (int*)malloc(sizeof(int) * veriler[i]->size);
		
		printf("Enter %d numbers for thread %d :", veriler[i]->size, i + 1);

		for (int j = 0; j < veriler[i]->size; j++) {

			printf("[%d]:", j + 1);
			scanf_s("%d", &veriler[i]->numbers[j]);

		}


		threads[i] = CreateThread(NULL, 0, myThreadFunction, veriler[i], 0, NULL);


		if (threads[i] == NULL) {
			printf("Thread %d is not created!\n");
		}
	

	}

	WaitForMultipleObjects(thread_numbers, threads, TRUE, INFINITE);


	for (int i = 0; i < thread_numbers; i++) {
		printf("Average of thread %d is:%.2f\n", veriler[i]->id, veriler[i]->average);

	}

	for (int i = 0; i < thread_numbers; i++) {

		CloseHandle(threads[i]);
		free(veriler[i]->numbers);
		free(veriler[i]);


	}
	

	printf("\nAll threads is completed their jobs , program is terminated");

	return 0;
}