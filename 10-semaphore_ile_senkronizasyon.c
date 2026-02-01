#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define thread_count 5
#define max_simulatenous 2

typedef struct {
	int id;
	HANDLE hSemaphore;
}thread_info;


DWORD WINAPI threadFunction(LPVOID lpParam) {

	thread_info* info = (thread_info*)lpParam;

	//semaphoreden izin alma
	WaitForSingleObject(info->hSemaphore, INFINITE); //count-- yapar

	printf("Thread %d is enter the critical section!\n", info->id);
	Sleep(1000 + rand() % 2000); //simulasyon kısmı

	printf("Thread %d is exit the critical section!\n", info->id);
	ReleaseSemaphore(info->hSemaphore, 1, NULL); //count++ yapar 

	return 0;
}


int main() {
	HANDLE threads[thread_count];
	thread_info* infos[thread_count];
	HANDLE hSemaphore;

	//semaphore oluşturma (başlangıç count = 2, maksimum count = 2

	hSemaphore = CreateSemaphore(NULL, max_simulatenous, max_simulatenous, NULL);
    
	if (hSemaphore == NULL) {
		printf("Semaphore is not created!\n");
		return 1;
	}

	srand((unsigned)time(NULL));

	 // verileri olusturma

	for (int i = 0; i < thread_count; i++) {

		infos[i] = (thread_info*)malloc(sizeof(thread_info));
		infos[i]->id = i + 1;
		infos[i]->hSemaphore = hSemaphore;

		//threadleri oluşturma 
		threads[i] = CreateThread(NULL, 0, threadFunction, infos[i], 0, NULL);

		if (threads[i] == NULL) {
			printf("Thread %d is not created!\n", i);
		}

	}
	
	WaitForMultipleObjects(thread_count, threads, TRUE, INFINITE);

	for (int i = 0; i < thread_count; i++) {

		CloseHandle(threads[i]);
		free(infos[i]);

	}
	CloseHandle(hSemaphore);

	printf("\nTum threadler tamamlandi!\n");

	return 0;

}
/*
SEMAPHORE NEDİR?

Semaphore, çoklu thread'lerin aynı kaynağa erişimini kontrol eden bir senkronizasyon nesnesidir.
Mutex gibi erişimi kısıtlar ama:
Mutex tek thread’e izin verirken,
Semaphore birden fazla thread’e aynı anda izin verebilir (sayaca bağlıdır).

🔹 SEMAPHORE'UN TEMEL MANTIĞI
Semaphore’un arkasında bir sayaç (count) vardır:

İşlem	Etki
WaitForSingleObject (izin istemek)	Sayaç -- (azaltılır)
ReleaseSemaphore (izin bırakmak)	Sayaç ++ (artırılır)

Örnek:
count = 2 başlangıç değeri → Aynı anda sadece 2 thread geçebilir.
bir thread gelirse, bekler.
Bir thread işini bitirip ReleaseSemaphore yapınca, başka biri geçer.

🔹 SEMAPHORE VS MUTEX
Özellik	                    Semaphore	                Mutex
Kaç thread geçebilir?	  Birden fazla (count kadar)	Yalnızca 1
Sahiplik?	              Sahiplik yok	               Mutex’i kilitleyen thread bırakmalı
Kullanımı	              Sayaca bağlı, daha esnek	     Daha katı, sadece bir kişi içeri girer

🔹 ARKA PLANDA NASIL ÇALIŞIR?

İşletim sistemi (Windows/Linux) her semaphore’un bir sayaç değerini tutar.
WaitForSingleObject() çağrıldığında:
Sayaç > 0 ise → geçer, sayaç 1 azalır.
Sayaç == 0 ise → thread bekletilir (uykuya alınır).
ReleaseSemaphore() çağrılınca:
Sayaç artırılır.
Eğer bekleyen bir thread varsa → OS onu uyandırır, devam ettirir.
Yani semaphore, arka planda işletim sistemi desteğiyle erişim kontrolü
ve thread'lerin sıralı bekletilmesi işlerini yapar.

🔹 GÜNLÜK HAYATTAN SEMAPHORE BENZETMESİ
🎳 Bowling Salonu Örneği (Gerçek Hayat Analojisi)
Düşün ki bir bowling salonu var.
İçeride sadece 2 oyun pisti var (yani aynı anda sadece 2 kişi oynayabilir).
5 kişi sıraya girmiş durumda (5 thread).
Semaphore nasıl çalışır?
Başlangıç semaphore count: 2
İlk 2 kişi doğrudan içeri girer → count = 0
kişi beklemek zorunda kalır.
İçerideki biri işi bitirip çıkınca → ReleaseSemaphore() çağrılır → count = 1
Bekleyen kişi geçebilir.

Bu örnekte:

Thread = Oyuncu
Semaphore = Giriş kontrol memuru
Count = Boş pist sayısı

🔹 SEMAPHORE KULLANIMI NE ZAMAN GEREKLİ?
Aynı anda belirli sayıda thread’in bir işlemi yapmasını istiyorsan:
Dosya erişimi (aynı anda 3 thread okuma yapsın ama fazlası beklesin)
Ağ bağlantısı (aynı anda 4 kişi bağlanabilsin)
Kaynak sınırlıysa (örneğin yazıcı, veri tabanı bağlantısı, cihaz kontrolü)

🔹 ÖZETLE:
✅ Semaphore, birden fazla thread’in aynı anda erişebileceği ama sayıyla sınırlanmış kaynaklar için kullanılır.
✅ Sayacına göre thread'lere sırayla izin verir veya bekletir.
✅ Günlük hayatta sınırlı kaynaklara sırayla erişim gerektiren her senaryo için uygundur.*/
