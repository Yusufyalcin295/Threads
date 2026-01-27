//küçük dosya okuma 

#include <stdio.h>
#include <stdlib.h>



int main() {
    FILE* file;
    char buffer[256]; //satırları tutmak için

    file = fopen("C:\\Users\\Yusuf\\OneDrive - Çukurova Üniversitesi\\Masaüstü\\ornek.txt", "r");
    
    if (file == NULL) {

        printf("File is not open");
        return 1;
    }

    //dosyayı satır satır yazdırma 

    printf("Dosya icerigi:\n\n");

    while (fgets(buffer, sizeof(buffer), file)) {

        printf("%s", buffer);
    }

    fclose(file);

    return 0;
}






/*
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define THREAD_COUNT 3

typedef struct {
    int id;
    char fileName[100];
} ThreadData;

DWORD WINAPI threadFunc(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    FILE* file;
    char buffer[256];

    fopen_s(&file, data->fileName, "r");
    if (file == NULL) {
        printf("Thread %d: Dosya açılamadı: %s\n", data->id, data->fileName);
        return 1;
    }

    printf("Thread %d, Dosya: %s içeriği:\n", data->id, data->fileName);
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("Thread %d >> %s", data->id, buffer);
    }
    printf("\n");

    fclose(file);
    return 0;
}

int main() {
    HANDLE threads[THREAD_COUNT];
    ThreadData* threadData[THREAD_COUNT];

    const char* fileNames[THREAD_COUNT] = { "file1.txt", "file2.txt", "file3.txt" };

    for (int i = 0; i < THREAD_COUNT; i++) {
        threadData[i] = (ThreadData*)malloc(sizeof(ThreadData));
        threadData[i]->id = i + 1;
        strcpy_s(threadData[i]->fileName, sizeof(threadData[i]->fileName), fileNames[i]);

        threads[i] = CreateThread(NULL, 0, threadFunc, threadData[i], 0, NULL);
        if (threads[i] == NULL) {
            printf("Thread %d oluşturulamadı!\n", i + 1);
            return 1;
        }
    }

    WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, INFINITE);

    for (int i = 0; i < THREAD_COUNT; i++) {
        CloseHandle(threads[i]);
        free(threadData[i]);
    }

    printf("Tüm thread'ler işlemi tamamladı.\n");

    return 0;
}
*/