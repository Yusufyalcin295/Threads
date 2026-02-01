#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define thread_number 3

typedef struct {
	int id;
	char* message;

} threadVerisi;

DWORD WINAPI myThreadFunction(LPVOID lpParam) {
	threadVerisi* veri = (threadVerisi*)lpParam;
    
	printf("Thread %d calisiyor!:%s\n", veri->id, veri->message);
	return 0;

}
int main() {
	
	HANDLE threads[thread_number];
	threadVerisi* veriler[thread_number];

	//her thread için veri oluşturma
	int i;
	for (i = 0; i < thread_number; i++) {
		veriler[i] = (threadVerisi*)malloc(sizeof(threadVerisi));
		veriler[i]->id = i + 1;

		if (i == 0)  veriler[i]->message = "ilk gorev";
		else if (i == 1) veriler[i]->message = "ikinci gorev";
		else veriler[i]->message = "ucuncu gorev";



		//threadleri olusturma 
		threads[i] = CreateThread(NULL, 0, myThreadFunction, veriler[i], 0, NULL);

		if (threads[i] == NULL) {
			printf("Thread %d oluşturulamadı!\n", i);
		}
	}
	
	//threadlerin işlerinin bitmesini bekleme
	
	WaitForMultipleObjects(thread_number, threads, TRUE, INFINITE);
	/*
	* WaitForMultipleObjects(THREAD_SAYISI, threadler, TRUE, INFINITE);
	| Parametre           | Anlamı                                               |
| ------------------- | ---------------------------------------------------- |
| `THREAD_SAYISI` → 3 | Kaç thread varsa o kadar handle bekleyeceğiz         |
| `threadler`         | `HANDLE threadler[3]` dizisi — beklenen thread’ler   |
| `TRUE`              | Hepsi tamamlanana kadar bekle (biri değil, **tümü**) |
| `INFINITE`          | Süre sınırı yok, sonsuza kadar bekle                 |

	*/

	// Temizlik
	 
	for (int i = 0; i < thread_number; i++) {
		CloseHandle(threads[i]);
		free(veriler[i]);
		
	}

	printf("Tum thread'ler tamamlandi.\n");
	return 0;



}
