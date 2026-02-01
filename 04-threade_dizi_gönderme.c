
//✅ Örnek Kod: Thread'e int dizisi gönderme
#include <windows.h>
#include <stdio.h>
#define BOYUT 5

DWORD WINAPI myThreadFunction(LPVOID lpParam) {
	int* numbers = (int*)lpParam;//gelen parametreyi int dizisine çeviriyoruz

		printf("Thread calisiyor.Gelen sayilar:\n");

	for (int i = 0; i < BOYUT; i++) {
		printf("Number %d: %d\n", i + 1, numbers[i]);

		}
	return 0;
}

int main() {
	HANDLE threadHandle;
	DWORD threadId;

	int veriler[BOYUT] = { 10,20,30,40,50 };

	threadHandle = CreateThread(NULL, 0, myThreadFunction, veriler, 0, &threadId);

	if (threadHandle == NULL) {
		printf("Thread olusturulmadı!\n");
		return 1;
	}
	WaitForSingleObject(threadHandle, INFINITE);

	CloseHandle(threadHandle);

	printf("Ana program sona erdi \n");
	return 0;
}



