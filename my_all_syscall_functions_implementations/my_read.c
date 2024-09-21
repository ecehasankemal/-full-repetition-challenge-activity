#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

unsigned int my_read(int fd, void *buf, unsigned int count);

int
    main()
{
    int fd;
    char buffer[128]; // Okunan veriyi tutacak bir buffer
    unsigned int bytes_read;

    // Bir dosyayı aç
    fd = open("my_read.c", O_RDONLY);
    if (fd < 0) {
        perror("Dosya açılamadı");
        return 1;
    }

    // Dosyadan veri oku
    bytes_read = my_read(fd, buffer, sizeof(buffer) - 1); // 1 byte ayırarak null sonlandırma için

    // Hata kontrolü
    if (bytes_read == 0) {
        perror("Okunacak veri yok veya hata oluştu");
        close(fd);
        return 1;
    }

    // Okunan veriyi null ile sonlandır
    buffer[bytes_read] = '\0';

    // Okunan veriyi yazdır
    printf("Okunan veri:\n%s\n", buffer);

    // Dosyayı kapat
    close(fd);
    return 0;
}

// my_read fonksiyonu burada tanımlanacak
unsigned int
    my_read(int fd, void *buf, unsigned int count)
{
    unsigned long long ret;

    __asm__ volatile
    (
        "mov $0, %%rax;"        // sys_read için 0'ı rax'a taşı
        "mov %1, %%rdi;"        // fd'yi rdi'ye taşı
        "mov %2, %%rsi;"        // buf'u rsi'ye taşı
        "mov %3, %%rdx;"        // count'u rdx'e taşı
        "syscall;"              // Sistem çağrısını gerçekleştir
        "mov %%rax, %0;"        // Sonucu kaydet
        : "=r" (ret)            // Çıkış operandı
        : "r" ((unsigned long long)fd), "r" ((unsigned long long)buf), "r" ((unsigned long long)count) // Giriş operandları
        : "%rax", "%rdi", "%rsi", "%rdx"   // Kullanılan registerler
    );

    return (unsigned int)ret;
}
