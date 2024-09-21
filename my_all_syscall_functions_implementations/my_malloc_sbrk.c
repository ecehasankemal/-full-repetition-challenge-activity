//#include <stddef.h> // size_t için
//#include <unistd.h> // brk ve sbrk için
#include <stdio.h>  // printf için
//#include <stdlib.h> // malloc için

void* my_sbrk(long increment) {
    void* current_brk;

    // Mevcut brk'yi almak için
    __asm__ volatile (
        "mov $0, %%rdi\n"            // rdi'ye 0 atarak mevcut brk'yi al
        "mov $12, %%rax\n"           // brk sistem çağrısı numarası (12)
        "syscall\n"                  // Sistem çağrısını gerçekleştir
        "mov %%rax, %0\n"            // Mevcut brk'yi ptr'ye taşı
        : "=r" (current_brk)         // Çıkış operandı
        :                             // Giriş operandı yok
        : "%rax", "%rdi"             // Kullanılan registerler
    );

    // Yeni brk değerini hesapla
    void* new_brk = (char*)current_brk + increment;

    // Yeni brk'yi ayarlamak için syscall
    __asm__ volatile (
        "mov %0, %%rdi\n"            // Yeni brk değerini rdi'ye taşı
        "mov $12, %%rax\n"           // brk sistem çağrısı numarası (12)
        "syscall\n"                  // Sistem çağrısını gerçekleştir
        :                             // Çıkış operandı yok
        : "r" (new_brk)              // Giriş operandı
        : "%rax", "%rdi"             // Kullanılan registerler
    );

    return current_brk; // Eski brk değerini döner
}

void* my_malloc(unsigned long size) {
    if (size == 0) {
        return ((void *)0); // 0 boyut için NULL döner
    }

    // Boyutu artırarak hizalamak
    unsigned long total_size = size + sizeof(unsigned long); // Boyutu depolamak için ek alan
    void* ptr = my_sbrk(total_size);

    if (ptr == (void*) -1) {
        return ((void *)0); // Hata durumunda NULL döner
    }

    // Tahsis edilen alanın başına boyutu yaz
    *((unsigned long *)ptr) = size;

    return (char*)ptr + sizeof(unsigned long); // Kullanıcıya gösterilecek adres
}

void add_alphabet(void* ptr, unsigned long size) {
    unsigned long i;
    char* p = (char*)ptr; // Typecast

    for (i = 0; i < size; i++) {
        p[i] = 'A' + (i % 26); // 'A' ile 'Z' arasında döner
    }
    p[size - 1] = '\0'; // Diziyi sonlandır
}

char
    *my_strdup(const char *s)
{
    size_t size = 0;
    const char *p = s;
    while (*p++) size++;
    char *d = my_malloc(size + 1);
    if (d) {
        char *q = d;
        while ((*q++ = *s++));
    }
    return d;
}

void
    my_free(void *ptr)
{
    if (ptr) {
        void *p = (char*)ptr - sizeof(unsigned long);
        my_sbrk(-(*(unsigned long *)p + sizeof(unsigned long)));
    }
}
#include <stdio.h>
int
    main(void)
{
    char *s = my_strdup("hello, world");
    if (s) {
        puts(s);
        my_free(s);
    }
    printf("%ld\n", sizeof(s));
    return 0;
}

/*int main() {
    unsigned long size = 128; // Örnek boyut
    void* ptr = my_malloc(size);

    if (ptr == ((void *)0)) {
        return 1; // Hata durumu
    }

    // Belleği kullan
    add_alphabet(ptr, size);
    printf("%s\n", (char*)ptr); // Dizi yazdırılır

    return 0;
}*/


