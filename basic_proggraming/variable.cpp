#include <iostream>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#else
    #include <sys/resource.h>
#endif

using namespace std;
using namespace chrono;

// Fungsi untuk mendapatkan penggunaan memori
void printMemoryUsage() {
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS memInfo;
        GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
        cout << "Memory usage: " << memInfo.WorkingSetSize / 1024 << " KB" << endl;
    #else
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        cout << "Memory usage: " << usage.ru_maxrss << " KB" << endl;
    #endif
}

int main() {
    printMemoryUsage();  // Sebelum menjalankan operasi

    auto start = high_resolution_clock::now();  // Mulai hitung waktu

    // Operasi yang diuji
    int a = 3;
    int b = 3;
    int c = a * b;
    cout << c << endl;

    auto stop = high_resolution_clock::now();  // Selesai hitung waktu
    auto duration = duration_cast<microseconds>(stop - start);  // Konversi ke mikrodetik

    cout << "Waktu eksekusi: " << duration.count() << " microseconds" << endl;

    printMemoryUsage();  // Setelah menjalankan operasi

    return 0;
}
