#include <time.h> 
//C Standart kütüphanesi 
int main() { 
    clock_t start, end; 
    // time.h isimli header dosyasında tanımlı, işlemci saatini saklamak için kullanılan veri türü 
    double cpu_time_used; 
    //ölçülen zamanı saniye cinsinden tutmak için tanımlanan değişken 
    start = clock(); 
    // ... koşma zamanı ölçülecek kod parçası buraya... 
    end = clock(); 
    //Tanımlanmış bir implementasyonun başlangıcından bu yana kullanılan işlemcinin saatini döndürür 
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
    // CLOCKS_PER_SEC saniyedeki işlemci clock sayısını verir (<time.h> headerında tanımlı) 
    printf ("%Geçen süre=%.9f saniyedir.", cpu_time_used); 
}