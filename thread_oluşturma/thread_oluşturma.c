
#include <windows.h>
#include <stdio.h>
/*
Bir thread oluşturacağız 
thread bir mesaj yazacak 
ana program thread'in bitmesini bekleyecek


| Konsept | Anlamı |
|--------|--------|
| `CreateThread` | Yeni bir iş parçacığı başlatır |
| `LPVOID` | Thread'e veri göndermek için kullanılan tür |
| `HANDLE` | Thread’i temsil eden Windows sistem nesnesi |
| `WaitForSingleObject` | Thread bitene kadar bekler |
| `CloseHandle` | Thread kaynağını serbest bırakır |
    DWORD → Fonksiyonun dönüş tip
	WINAPI → Windows’un çağrı kuralları
*/




//thread fonksiyonu 

DWORD WINAPI myThreadFunction(LPCVOID lpParam) {
	char* mesaj = (char*)lpParam;
	printf("Thread calisiyor:%s\n", mesaj);

	// Bu thread'in ID'sini al
	DWORD currentThreadId = GetCurrentThreadId();
	printf("Thread ID: %lu\n", currentThreadId);


	return 0;

}

int main() {

	HANDLE threadHandle;
	DWORD threadId;

/*
	HANDLE threadHandle;
   📌 HANDLE nedir?
HANDLE, Windows işletim sisteminde kullanılan soyut bir nesne tanımlayıcısıdır.
Birçok sistem kaynağını (thread, dosya, mutex, process vs.) temsil etmek için kullanılır.
Basitçe düşünürsen: HANDLE, Windows’un bir kaynağı izlemesi için tuttuğu bir işaretçidir.
*/

	char* veri = "Merhaba ,thread!";

	//thread oluşturuluyor
	threadHandle = CreateThread(
		NULL,               //varsayılan güvenlik
		0,                //varsayılan yığın boyutu  
		myThreadFunction, //çalışacak fonksiyon
		veri,            //parametre olarak mesaj
		0,               //varsayılan başlangıç bayrakları
		&threadId        //thread ıd  çıktısı
	);

	//oluşturulmadıysa hata ver 
	if (threadHandle == NULL) {
		printf("Thread olusturulmadı!\n");
		return 1;
	}

    //Ana thread thread ID’yi yazdırıyor
		printf("Olusturulan thread'in ID'si: %lu\n", threadId);

	//threadin bitmesini bekle 
	WaitForSingleObject(threadHandle, INFINITE);
	/*Amaç: Ana program, thread bitene kadar bekler.
     threadHandle → Beklenecek thread’in tanımlayıcısı.
     INFINITE → Sonsuza kadar bekle (thread bitene kadar).
     Thread işi bitince program devam eder.  Eğer bu satır olmazsa, ana program thread bitmeden kapanabilir.
	*/

	//thread temizle 
	CloseHandle(threadHandle);

	printf("Ana program sona erdi \n");
	return 0;
}

  