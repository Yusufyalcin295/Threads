//Mutex kullanımıyla senkronizasyon sağlama

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define thread_count 3
#define increment_per_thread 100000

int global_counter = 0;
HANDLE hMutex;  //hMutex: Bir HANDLE, yani sistemde mutex’i temsil eden özel tanımlayıcı. CreateMutex ile oluşturulacak.



DWORD WINAPI threadFunction(LPVOID lpParam) {

	for (int i = 0; i < increment_per_thread; i++) {

		//Mutex kilidini alma 
		WaitForSingleObject(hMutex, INFINITE);
		global_counter++;
        
		ReleaseMutex(hMutex);//Thread işini bitirince kilidi bırakır.



	}

	return 0;
}


int main() {

	HANDLE threads[thread_count];

	//mutex oluşturuluyor(vrasyalın olarak unlocked) başta kilitsiz

	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL) {
		printf("Mutex is not created.Code of Error is:%ld\n", GetLastError());

		return 1;

	}

	//threadlerin olusturulması

	for (int i = 0; i < thread_count; i++) {

		threads[i] = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);

		if (threads[i] == NULL) {
			printf("Thread %d is not cretated!\n", i + 1);
			return 1;

		}
	}


	//threadlerin bitmesinin beklenmesi
	WaitForMultipleObjects(thread_count, threads, TRUE, INFINITE);

	for (int i = 0; i < thread_count; i++) {
		CloseHandle(threads[i]);
	}
	//Mutex kapatılıyor
	CloseHandle(hMutex);

	printf("Beklenen sonuc:%d\n", thread_count * increment_per_thread);
	printf("Gercek sayac degeri:%d\n", global_counter);


	return 0;

}
/*
 🔐 Nedir Bu Mutex?
Mutex (Mutual Exclusion = karşılıklı dışlama), bir kaynağa (örneğin bir değişkene, dosyaya, belleğe vs.) 
aynı anda sadece bir thread’in erişmesini sağlayan bir kilittir.
Örneğin:
Birden fazla kişi aynı anda bir kasayı açmaya çalışırsa karışıklık olur.
Mutex, bu kasaya tek kişinin sırayla erişmesini sağlar.

🎯 Ne İçin Kullanılır?
Race condition (yarış durumu) dediğimiz tehlikeli durumlardan kaçınmak için:
Aynı anda iki thread global_counter++ yaparsa:
Okuma → artırma → yazma işlemleri birbirine karışır.Sonuç yanlış olur.

🔧 Temel Terimler
1. Kilit Almak (Lock)

WaitForSingleObject(hMutex, INFINITE);
Bir thread, mutex'i kullanmak için kilit alır.
Eğer o anda mutex boşsa:
Hemen kilit alır ve kritik bölgeye girer.
Eğer başka bir thread mutex’i zaten kullanıyorsa:
Bu thread bekler (INFINITE: sonsuza kadar bekle anlamına gelir).

2. Kritik Bölge (Critical Section)

global_counter++; // Bu satır kritik bölge
Ortak kullanılan kod bloğu.
Bu bölgeye aynı anda sadece bir thread girebilir.
Mutex işte bu bölgeyi korumak için vardır.

3. Kilit Bırakmak (Unlock / Release)

ReleaseMutex(hMutex);
Thread işini bitirince kilidi bırakır.
Böylece sırada bekleyen diğer thread mutex'i alabilir.

🔄 Arka Planda Ne Oluyor?
Bir thread WaitForSingleObject(hMutex, INFINITE) yaptığında:
Windows işletim sistemi, mutex'in durumuna bakar.
Eğer mutex serbestse:
Thread hemen devam eder ve mutex kilitlenmiş hale gelir.
Eğer mutex başka bir thread’teyse:
Thread beklemeye alınır. (CPU zamanı harcamaz!)
O thread ReleaseMutex yapınca işletim sistemi diğer thread’i uyandırır.

Windows kernel seviyesinde bu işlemler şu şekilde işler:

Mutex nesnesi bir "wait queue" tutar.
Mutex kilitliyse, diğer thread’ler bu kuyruğa girer.
Mutex serbest bırakıldığında kuyruktaki ilk thread aktif edilir.

🧠 Mutex Ne Değildir?
Mutex, bir thread’i tamamen durdurmaz, sadece paylaşılan veriye erişimi sınırlar.
Mutex, birden çok thread’in çalışmasını engellemez, sadece sıra ile çalışmasını sağlar.

🧪 Gerçek Hayattan Benzetme
Bir tuvalet düşün:
Kapıda bir anahtar var.
İçeri giren kişi kapıyı kilitler (lock).
Diğer kişiler bekler.
Kişi işi bitirince kilidi açar (unlock).
Sıradaki girer.
İşte mutex tam da bu şekilde çalışır. Kilit alınır, iş yapılır, sonra kilit bırakılır.

✅ Mutex'in Özeti
Terim	                                            Anlamı
WaitForSingleObject	Mutex’i kilitle (lock) —    kritik bölgeye gir
ReleaseMutex	                                Mutex’i serbest bırak (unlock)
CreateMutex                           	        Mutex’i oluşturur
CloseHandle	                                    Mutex’i siler (program sonunda yapılır)
Kritik Bölge	                                Paylaşılan veri işlemlerinin yapıldığı yer
*/



