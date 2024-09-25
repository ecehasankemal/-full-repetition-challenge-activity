/*#include <stddef.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>*/

void*
    my_sbrk(long increment)
{
    void* current_brk;

    // Mevcut brk'yi almak için
    __asm__ volatile
    (
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
    __asm__ volatile
    (
        "mov %0, %%rdi\n"            // Yeni brk değerini rdi'ye taşı
        "mov $12, %%rax\n"           // brk sistem çağrısı numarası (12)
        "syscall\n"                  // Sistem çağrısını gerçekleştir
        :
        : "r" (new_brk)              // Giriş operandı
        : "%rax", "%rdi"             // Kullanılan registerler
    );

    return (current_brk); // Eski brk değerini döner
}

void*
    my_mmap(void* addr, unsigned long length, int prot, int flags, int fd, long offset)
{
    void* result;

    // mmap sistem çağrısı
    __asm__ volatile
    (
        "mov %1, %%rdi\n"            // 1. parametre: addr
        "mov %2, %%rsi\n"            // 2. parametre: length
        "mov %3, %%rdx\n"            // 3. parametre: prot
        "mov %4, %%r10\n"            // 4. parametre: flags
        "mov %5, %%r8\n"             // 5. parametre: fd
        "mov %6, %%r9\n"             // 6. parametre: offset
        "mov $9, %%rax\n"            // mmap sistem çağrısı numarası (9)
        "syscall\n"                  // Sistem çağrısını gerçekleştir
        "mov %%rax, %0\n"            // Sonuç (mmap'in dönüş değeri) result'a aktar
        : "=r" (result)              // Çıkış operandı
        : "r" ((unsigned long)addr), "r" ((unsigned long)length), "r" ((unsigned long)prot), "r" ((unsigned long)flags), "r" ((unsigned long)fd), "r" ((unsigned long)offset)  // Giriş operandları
        : "%rax", "%rdi", "%rsi", "%rdx", "%r10", "%r8", "%r9"  // Kullanılan registerler
    );

    return (result);
}

void
    my_munmap(void* addr, unsigned long length)
{
    // munmap sistem çağrısı
    __asm__ volatile
    (
        "mov %0, %%rdi\n"            // 1. parametre: addr
        "mov %1, %%rsi\n"            // 2. parametre: length
        "mov $11, %%rax\n"           // munmap sistem çağrısı numarası (11)
        "syscall\n"                  // Sistem çağrısını gerçekleştir
        :
        : "r" ((unsigned long)addr), "r" ((unsigned long)length)  // Giriş operandları
        : "%rax", "%rdi", "%rsi"     // Kullanılan registerler
    );
}

void*
    my_malloc(unsigned long size)
{
    if (size == 0)
        return ((void *)0); // 0 boyut için NULL döner

    // Bellek bloklarının hizalanması için ek boyut
    unsigned long total_size = size + sizeof(unsigned long); // Boyutu depolamak için ek alan

    // Kullanıcı tanımlı bir eşik belirleyelim
    const unsigned long mmap_threshold = 4096; // Örneğin, 4KB

    void* block;
    if (total_size < mmap_threshold)
    {
        // Küçük tahsisler için sbrk kullan
        block = my_sbrk(total_size);
    }
    else
    {
        // Büyük tahsisler için mmap kullan
        block = my_mmap(((void *)0), total_size,
                         0x7 /* PROT_READ | PROT_WRITE */,
                         0x22 /* MAP_PRIVATE | MAP_ANONYMOUS */,
                         -1, 0);
    }

    if (block == (void*)-1)
        return ((void *)0); // Hata durumunda NULL döner

    // Tahsis edilen alanın başına boyutu yaz
    *((unsigned long*)block) = size;

    // Kullanıcıya gösterilecek adres: boyut bilgisinden sonraki kısım
    return (char*)block + sizeof(unsigned long);
}

void
    my_free(void **ptr)
{
    if (ptr && *ptr)
    {  // ptr ve *ptr'yi kontrol et
        void *p = (char*)*ptr - sizeof(unsigned long);
        my_sbrk(-(*(unsigned long *)p + sizeof(unsigned long)));
        *ptr = ((void *)0);  // İşaretçiyi NULL yap
    }
}

int
    my_strlen(char const *s)
{
    char const *p = s;
    while (*p)
        p++;
    return p - s;
}

char
    *my_strdup(const char *s)
{
    unsigned long   size;
    char            *result;

    result = (char *)my_malloc(sizeof(char) * (size = my_strlen(s) + 1));
    while (size--)
        result[size] = s[size];
    return (result);
}


#include <stdio.h>

int main() {
    void* ptr = my_malloc(1024);  // 1KB'lık alan tahsis et
    if (ptr == NULL) {
        // Hata durumu
        return 1;
    }

    // Tahsis edilen belleği kullan
    ((char*)ptr)[0] = 'A';  // İlk byte'a 'A' yaz
    printf("Allocated memory: %s\n", (char*)ptr); // Tahsis edilen belleği yazdır

    // Belleği serbest bırak
    my_free(&ptr);  // İşaretçiyi referans olarak geç
    if (ptr == ((void *)0))
        printf("Pointer successfully freed and set to NULL\n");

    ptr = my_strdup("hello, world");  // Yeni bir string oluştur
    if (ptr)
    {
        printf("Allocated memory: ");
        puts(ptr);  // String'i yazdır
        my_free(&ptr);  // Belleği serbest bırak
    }

    my_free(&ptr);  // İşaretçiyi tekrar serbest bırak
    if (ptr == ((void *)0))
        printf("Pointer successfully freed and set to NULL\n");

    return 0;
}


/*#include <stdio.h>
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
}*/