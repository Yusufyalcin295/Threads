
// Hedef: Thread’ler arasında ortak veri kullanmak, erişim çakışmalarını(race condition) engellemek.
//AŞAMA 1: Race Condition'lı Hatalı Kod (Senkronsuz)
//Thread'ler aynı global değişkeni artıracak, ama senkronizasyon olmadığından sonuç hatalı olacak.

/*

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define thread_count 3
#define Increment_per_thread 10000000


int global_counter = 0;

DWORD WINAPI threadFunction(LPVOID lpParam) {

	for (int i = 0; i < Increment_per_thread; i++) {
		global_counter++;//bu kısımda aynı aynı anda erişim olabiliyor

	}
	return 0;
}

int main() {
	HANDLE threads[thread_count];

	for (int i = 0; i < thread_count; i++) {
		threads[i] = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);

		if (threads[i] == NULL) {
			printf("Thread %d is not created!", i + 1);
			return 1;

		}

	}

	WaitForMultipleObjects(thread_count,threads,TRUE,INFINITE);

	for (int i = 0; i < thread_count; i++) {
		CloseHandle(threads[i]);
	}

	printf("Beklenen sonuc:%d\n", thread_count * Increment_per_thread);
	printf("Gercek sayac degeri:%d\n", global_counter);

	return 0;
}
*/

/*
🎯 Race Condition Neden Bazen Ortaya Çıkmaz?
CPU zamanlaması rastgele olduğundan
Thread’lerin başlama zamanları farklı olabildiğinden
Thread’ler sırayla çalışabildiğinden (tesadüfen)
İşlemci sayısı azsa ve çekirdek paylaşımı varsa
Bu durumda bazen race condition oluşmaz ama bu güvenli olduğu anlamına gelmez!*/

//-----------------------------------------------------------------------------------------------------------------------

//AŞAMA 2: Critical Section ile DÜZELTME
//Şimdi CRITICAL_SECTION kullanarak aynı anda erişimi engelleyeceğiz.

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define thread_count 3
#define Increment_per_thread 10000000

int global_counter = 0;
CRITICAL_SECTION cs;

DWORD WINAPI threadFunction(LPVOID lpParam) {

	for (int i = 0; i < Increment_per_thread; i++) {

		EnterCriticalSection(&cs); 
			global_counter++;
		LeaveCriticalSection(&cs);

		/*
		CRITICAL_SECTION cs;
     Windows’a özel bir senkronizasyon nesnesi.
     EnterCriticalSection() ile kilit alınır,
     LeaveCriticalSection() ile bırakılır.
     Aynı anda sadece bir thread kritik bölgeye girebilir.

        */

	}
	return 0;
}

int main() {

	HANDLE threads[thread_count];

	//critical section başlatma 
	//Thread'ler çalışmadan önce yapılmalı

	InitializeCriticalSection(&cs);



	for (int i = 0; i < thread_count; i++) {

		threads[i] = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);

		if (threads[i] == NULL) {

			printf("Thread %d is not created!\n", i + 1);

			return 1;
		}

	}
	WaitForMultipleObjects(thread_count, threads, TRUE, INFINITE);

	for (int i = 0; i < thread_count; i++) {

		CloseHandle(threads[i]);
	}

	//critical section temizleme
	DeleteCriticalSection(&cs);

	printf("Beklenen sonuc:%d\n", thread_count * Increment_per_thread);
	printf("Gercek sayi degeri:%d\n", global_counter);

	return 0;
   
}


