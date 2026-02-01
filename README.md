# Windows Multithreading & Synchronization in C

This repository serves as a comprehensive technical guide for **Parallel Programming** and **Thread Synchronization** using the Windows API (`windows.h`). It covers everything from basic lifecycle management to advanced concurrency primitives.

## 📁 Project Roadmap & Hierarchy

### I. Fundamental Thread Management (01 - 04)
* **01-thread_creation:** Understanding the `CreateThread` lifecycle and entry points.
* **02 & 03-thread_struct_mapping:** Securely passing heterogeneous data sets to threads using custom `struct` definitions.
* **04-passing_arrays:** Practical implementation of passing dynamic memory buffers to worker threads.

### II. Advanced Parallel Processing (05 - 07)
* **05-multi_thread_management:** Orchestrating multiple concurrent tasks using `WaitForMultipleObjects`.
* **06-parallel_array_averaging:** Divide-and-conquer approach for statistical calculations across multiple data streams.
* **07-threaded_io_operations:** Enhancing performance in I/O bound tasks via parallel execution.

### III. Concurrency & Data Integrity (08 - 10)
* **08-shared_resource_analysis:** Experimental analysis of **Race Conditions** in unprotected shared memory.
* **09-mutex_synchronization:** Implementing **Mutual Exclusion** to protect Critical Sections.
* **10-semaphore_control:** Managing resource-constrained access using counting semaphores.



---

## 🧠 Key Technical Concepts (Glossary)

* **Thread:** The smallest execution unit within a process. Allows background tasks without freezing the main application.
* **Race Condition:** A flaw where the output is dependent on the sequence or timing of uncontrollable events (multiple threads accessing shared data).
* **Synchronization:** Mechanisms to ensure that threads coordinate their execution (e.g., `WaitForSingleObject`).
* **Mutex (Mutual Exclusion):** A locking mechanism that ensures only one thread can access a resource at a time.
* **Semaphore:** A counter-based synchronization tool that allows a specific number of threads to access a resource pool.
* **Context Switching:** The process of storing and restoring the state of a CPU so that multiple threads can share a single CPU core.



---

## 🛠 Tech Stack & API Reference

| Category | Components & Functions |
| :--- | :--- |
| **Management** | `CreateThread`, `CloseHandle`, `LPVOID`, `DWORD` |
| **Synchronization** | `WaitForSingleObject`, `WaitForMultipleObjects`, `INFINITE` |
| **Primitives** | `CreateMutex`, `CreateSemaphore`, `ReleaseMutex`, `ReleaseSemaphore` |
| **Memory** | `malloc`, `free`, `Heap Allocation`, `Struct Padding` |

---

<details>
<summary><b>🇹🇷 Proje Detaylarını Türkçe Okumak İçin Tıklayın (Click for Turkish)</b></summary>

### Türkçe Özet

Bu depo, Windows API kullanılarak paralel programlama ve iş parçacığı senkronizasyonu üzerine geliştirilen teknik çalışmaları içerir.

#### Önemli Kavramlar:
* **Thread (İş Parçacığı):** Aynı süreç içinde paralel çalışan birimler.
* **Yarış Durumu (Race Condition):** Veri tutarsızlığına yol açan kontrolsüz erişim.
* **Mutex:** Kritik bölgeleri koruyan kilit mekanizması.
* **Semaphore:** Belirli sayıda kaynağa erişimi yöneten sayaç.

*Bu çalışma, Yusuf Yalçın tarafından Bilgisayar Mühendisliği akademik çalışmaları kapsamında geliştirilmiştir.*
</details>

---
*Developed by Yusuf Yalçın.*