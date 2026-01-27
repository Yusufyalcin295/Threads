# Windows Multithreading & Synchronization in C

Windows API kullanılarak geliştirilen bu proje seti, paralel programlama ve iş parçacığı (thread) senkronizasyonu üzerine kapsamlı teknik çalışmalar içermektedir. Projeler, temel thread yönetiminden başlayarak ileri seviye senkronizasyon mekanizmalarına kadar kademeli bir öğrenim yapısı sunar.

## Teknik İçindekiler

### I. Thread Yönetimi ve Veri İletişimi (01 - 04)
* **Yaşam Döngüsü:** `CreateThread` ve `WaitForSingleObject` ile thread oluşturma ve ana program senkronizasyonu.
* **Veri Aktarım Modelleri:** `LPVOID` üzerinden homojen dizilerin ve heterojen `struct` yapılarının aktarılması.
* **Dinamik Bellek Yönetimi:** Thread parametrelerinin Heap bölgesinde (`malloc`/`free`) yönetilerek veri güvenliğinin sağlanması.

### II. Paralel I/O Operasyonları (05)
* **Eşzamanlı Dosya İşleme:** `WaitForMultipleObjects` ile I/O yoğunluklu işlemlerin paralel yürütülmesi ve toplam işlem süresinin optimize edilmesi.

### III. Senkronizasyon ve Veri Bütünlüğü (06 - 08)
* **Race Condition Analizi:** Kontrolsüz erişimin sonuçlarının deneysel analizi.
* **Kritik Bölgeler (Critical Sections):** Kullanıcı modu kilitleri ile paylaşılan kaynakların korunması.
* **Kernel Nesneleri (Mutex & Semaphore):** Karşılıklı dışlama (Mutex) ve sayaca dayalı (Semaphore) erişim kontrolü ile sistem seviyesinde senkronizasyon.

## Kullanılan Fonksiyonlar ve Konseptler

| Kategori | Bileşenler |
| :--- | :--- |
| **Temel API** | `CreateThread`, `CloseHandle`, `Sleep` |
| **Senkronizasyon** | `WaitForSingleObject`, `WaitForMultipleObjects` |
| **Kilit Mekanizmaları** | `CRITICAL_SECTION`, `CreateMutex`, `CreateSemaphore` |
| **Bellek Yönetimi** | `malloc`, `free`, `LPVOID` casting |

---
*Not: Bu repo, profesyonel yazılım geliştirme standartlarına uygun olarak .gitignore yapılandırması ve modüler klasörleme ile düzenlenmiştir.*
