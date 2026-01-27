#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


typedef struct {
	int number;
	char* message;

}threadVerisi;

DWORD WINAPI mySquareFunction(LPVOID lpParam) {

	threadVerisi* veri = (threadVerisi*)lpParam;
	
	printf("Message:%s ", veri->message);
	printf("\nSquare of the %d:%d\n", veri->number, veri->number * veri->number); 
	
}

int main() {

	HANDLE threadHandle;
	DWORD threadId;

	//struct oluşturma

	threadVerisi* veri = (threadVerisi*)malloc(sizeof(threadVerisi));
	veri->message = "Thread calisiyor,islem yapiliyor!";
	veri->number = 10;

	//thread yaratma

	threadHandle = CreateThread(NULL, 0, mySquareFunction, veri, 0, &threadId);

	//thread yaratılmadıysa mesaj 
	if (threadHandle == NULL) {
		printf("Thread olusturulamadi\n");
		free(veri);
		return 1;
	}

	WaitForSingleObject(threadHandle, INFINITE);

	CloseHandle(threadHandle);
	free(veri);

	printf("PROGRAM KAPATILIYOR\n");
	

}