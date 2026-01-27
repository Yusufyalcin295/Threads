#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

typedef struct {
	int* sayilar;
	int boyut;
	char* mesaj;
}ThreadVerisi;

//thread fonksiyonu

DWORD WINAPI myThreadFunction(LPVOID lpParam) {
	ThreadVerisi* veri = (ThreadVerisi*)lpParam;

	printf("Thread calisiyor.Mesaj:%s\n", veri->mesaj);
	printf("Gelen sayilar:\n");

	for (int i = 0; i < veri->boyut; i++) {
		printf("Sayi %d=%d\n", i + 1, veri->sayilar[i]);

	}
	return 0;
}
int main() {
	HANDLE threadHandle;
	DWORD threadId;

	//sayilar dizisi
	int* dizi = malloc(sizeof(int) * 4);
	dizi[0] = 5;
	dizi[1] = 15;
	dizi[2] = 25;
	dizi[3] = 35;

	//yapıyı doldurma
	ThreadVerisi veri;
	veri.sayilar = dizi;
	veri.boyut = 4;
	veri.mesaj = "Sayilari isliyorum...";

	//thread oluşturma
	threadHandle = CreateThread(NULL, 0, myThreadFunction, &veri, 0, &threadId);

	if (threadHandle == NULL) {
		printf("Thread olusturulmadi!\n");
		free(dizi);
		return 1;
	}
	WaitForSingleObject(threadHandle, INFINITE);
	CloseHandle(threadHandle);

	free(dizi);
	printf("Ana program sona erdi.\n");
	return 0;
}
