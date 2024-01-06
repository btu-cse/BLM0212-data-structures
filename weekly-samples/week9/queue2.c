#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Bir dizi kullanarak bir kuyruk (queue) veri yapisinin uygulanmasi

// Bir kuyruk veri yapisini temsil etmek icin bir struct Queue tanimlanir
// Bu yapi, kuyrugun mantiksal ozelliklerini saklamak icin kullanilir
// front: Kuyrugun basini gosteren bir indeks.
// rear: Kuyrugun sonunu gosteren bir indeks.
// size: Kuyruktaki mevcut oge sayisini tutar.
// capacity: Kuyrugun maksimum kapasitesini belirtir.
// array: Kuyrugun elemanlarini depolamak icin dinamik olarak ayrilmis bir diziye isaret eden bir isaretci.
struct Queue {
    int front, rear, size;
    unsigned capacity; 
	// Bircok veri turu, hem negatif hem de pozitif degerleri icerebilirken, unsigned belirleyici, 
	// yalnizca pozitif tamsayilari ve sifiri iceren degerleri ifade etmek icin kullanilir. 
	// Bu, bir degiskenin sadece pozitif sayilari alacagini ve hicbir zaman negatif bir degere sahip olmayacagini gosterir.
    int* array;
};




// Bu fonksiyon, belirtilen kapasiteye sahip yeni bir kuyruk olusturmak icin kullaniliyor. 
// Kuyrugun boyutunu 0 olarak baslatir
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    // Bellek tahsis ediliyor: malloc fonksiyonuyla struct Queue turunde bellek ayriliyor. 
	// Bu bellek, kuyrugun kendisi icin kullanilacak.
    queue->capacity = capacity;
    // queue isaretcisi olusturuluyor ve kapasite degeri ataniyor.
	// queue isaretcisi olusturulur ve capacity (kapasite) degeri capacity parametresinden alinarak atanir.
    queue->front = queue->size = 0;
    // Diger degiskenlere baslangic degerleri ataniyor:
    // front ve size sifirlaniyor, cunku kuyruk henuz bos.


    queue->rear = capacity - 1;
    // rear degeri ataniyor: Kuyrugun sonunu temsil eden rear degiskeni kapasitenin bir eksigi olarak atanir. 
	// Bu, kuyrugun bosken rear degerinin mantiksal olarak -1 olmasini saglar.
	// Dongusel bir kuyruk olustururken, eleman eklemek veya cikarmak icin front ve rear degerleri belirli bir islemle guncellenir. 
	// rear kapasitenin bir eksigi olarak baslatilarak, tam dolu olan kuyrukta dairesel bir þekilde rear degeri 0 olacak sekilde devam edebilir. 
	// Bu da bellek kullanimini optimize eder ve kuyrugun dongusel yapisini saglar.
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    // Kuyrugun elemanlarini depolamak icin bellek ayriliyor
	// Kuyrugun maksimum kapasitesi kadar bir int turunde dizi icin bellek ayrilir. 
	// (int*) ile yapýlan donusum, malloc'in dondurdugu void* isaretciyi int* turunde bir isaretciye donusturur.
	// Bu dizi, kuyrugun elemanlarini depolamak icin kullanilacak.
    return queue;
}




// Boyut kapasiteye esit oldgunda kuyruk doludur
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}




// Boyut 0 oldugunda kuyruk bostur
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}




// Kuyruga bir oge ekleme fonksiyonu.
// rear ve boyutu degistirir
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
        // isFull fonksiyonuyla mevcut kuyrugun dolu olup olmadigi kontrol ediliyor. 
        
    queue->rear = (queue->rear + 1) % queue->capacity;
    // rear degiskeni, kuyrugun sonunu gosteren indeks, bir sonraki bos pozisyona geciriliyor. 
	// queue->rear ifadesi, rear'in bir sonraki pozisyonunu queue->capacity'ye gore modlu alarak hesaplanir. 
	// Boylece dongusel bir kuyrukta son elemandan sonra ilk elemana gecis saglanir.
    queue->array[queue->rear] = item;
    // item degeri, kuyrugun guncellenmis rear konumuna ekleniyor.
    queue->size = queue->size + 1;
    // Kuyruktaki oge sayisi arttiriliyor, cunku bir oge eklenmis oldu
    printf("%d enqueued to queue\n", item);
}




// Bir ogeyi kuyruktan kaldirma fonksiyonu.
// Front ve boyutu degistirir
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
        // Kuyrugun bos olup olmadigi isEmpty fonksiyonu ile kontrol edilir. 
		// Eger kuyruk bos ise islem yapilmadan INT_MIN (minimum deger) dondurulur.
		// INT_MIN C standard kutuphanesinde bulunan bir sabit degerdir. 
		// Bu, limits.h baslik dosyasinda tanimlanmistir. 
		// INT_MIN, int veri tipinin saklayabilecegi en kucuk degeri temsil eder. 
		
    int item = queue->array[queue->front];
    // Ilk oge cikarilir: Kuyrugun basindaki oge queue->array[queue->front] ile alinir ve item adli bir degiskene atanir.
    queue->front = (queue->front + 1) % queue->capacity;
    // Kuyruktan cikarilan oge nedeniyle front indeksi bir sonraki ogeyi gosterecek sekilde guncellenir. 
	// Bu, kuyruktan cikarilan ogenin artýk kuyrukta olmadigini belirtir.
    queue->size = queue->size - 1;
    // Kuyruktan bir oge cikarildigi icin, kuyruktaki oge sayisi bir azaltilir.
    return item;
    // Cikarilan oge geri dondurulur.
}





// Kuyrugun front fonksiyonu
int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
        // Eger kuyruk bos ise islem yapilmadan INT_MIN (minimum deger) dondurulur. 
    return queue->array[queue->front];
    // Kuyrugun basindaki oge, queue->array[queue->front] ifadesi ile elde edilir ve bu deger return ile geri dondurulur.
}




// Kuyrugun rear fonksiyonu
int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
        // Eger kuyruk bos ise islem yapilmadan INT_MIN (minimum deger) dondurulur. 
    return queue->array[queue->rear];
    // Sonundaki oge degeri dondurulur: 
	// Kuyrugun sonundaki oge, queue->array[queue->rear] ifadesi ile elde edilir ve bu deger return ile geri dondurulur.
}




int main()
{
    struct Queue* queue = createQueue(1000);
    // createQueue fonksiyonunu cagirip, 1000 eleman kapasiteli bir kuyruk olusturduktan sonra 
	// bu kuyrugun adresini queue adli bir isaretciye atiyor.

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);

    printf("%d dequeued from queue\n\n", dequeue(queue));
    printf("Front item is %d\n", front(queue));
    printf("Rear item is %d\n", rear(queue));

    return 0;
}
