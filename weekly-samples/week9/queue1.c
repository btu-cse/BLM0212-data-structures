#include <stdio.h>
#include <stdlib.h>

/*
Queue(Kuyruk): Kuyruk kisitlanmis bir dogrusal listedir. 
Yani verilerin eklenmesi ve silinmesi listenin uclarindan olacak sekilde sinirlandirilmistir.
Veriler bir uctan eklenir(rear) ve diger uctan silinir(front)
Veriler kuyruga alindiklari sirayla islenir
First In First Out - FIFO
4 temel kuyruk islemi vardir
Veriler kuyruga sondan eklenir ve bas taraftan alinip islenir.
1. Enqueue: Kuyrugun sonuna bir eleman ekler.
2. Dequeue: Kuyrugun basindan bir eleman siler.
3. Queue Front: Kuyrugun basindaki elemani okur.
4. Queue Rear: Kuyrugun sonundaki elemani okur.
*/


// Linked liste dayalý kuyrugun uygulanmasini gosteren bir C programi



// Kuyrugun her bir elemanini temsil eden dugumleri tanimlamak icin bir struct olusturur. 
// Yapi, her bir kuyruk elemaninin hangi veriyi (burada int key ile temsil ediliyor) saklayacagini 
// ve bir sonraki elemana olan baglantisini (struct QNode* next) icerir.
struct QNode {
    int key;
    struct QNode* next;
};




// Bu struct Queue yapisi, kuyrugun genel yapisini temsil etmek icin kullanilir. 
// Bu yapi, kuyrugun basini (front) ve sonunu (rear) gosteren isaretciler icerir.
struct Queue {
    struct QNode *front, *rear;
};





// Bu fonksiyon, kuyruk icin yeni bir dugum olusturur ve bu dugume veri ekler.
struct QNode* newNode(int k)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    // Bellekte struct QNode tipinde bir alan tahsis eder. sizeof(struct QNode) ifadesi, struct QNode yapisinin boyutunu verir. 
	// Bu alan, yeni bir dugum olusturmak icin gereken bellek miktarini temsil eder.
	// malloc fonksiyonu, dondurdugu bellek blogunun adresini verir. 
	// Bu adres, struct QNode* turunde bir isaretcidir. 
	// Burada donus tipi struct QNode*'a donusturuluyor cunku malloc, void* turunde bir isaretci dondurur.
    temp->key = k;
    // Olusturulan yeni dugumun key alanina (veri saklama alani) parametre olarak alinan k degeri atanir. 
    temp->next = NULL;
    // Yeni olusturulan dugumun next alani NULL olarak ayarlanir. 
	// Bu, yeni olusturulan dugumun, su anda herhangi bir sonraki dugume isaret etmedigini belirtir.
    return temp;
    // Olusturulan yeni dugumun isaretcisi return ifadesiyle geri dondurulur
}






// Bos (empty) bir kuyruk olusturmak icin bir fonksiyon
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    // Bellekte struct Queue turunden bir alan ayirir. 
    // malloc fonksiyonu, bu bellek blogunun adresini dondurur. 
    // Fonksiyondan void* dondugu icin cast ederiz.
	// Bu adres, struct Queue turunden bir isaretci olan q degiskenine atanir. 
	// Bu isaretci, dinamik olarak olusturulan kuyrugun baslangic adresini gosterir.
    q->front = q->rear = NULL;
    // Olusturulan kuyrugun hem front hem de rear isaretcilerini NULL olarak ayarlar. 
    return q;
    // Olusturulan kuyrugun baslangic adresi geri dondurulur. 
}






// q'ya k degerini ekleme fonksiyonu
void enQueue(struct Queue* q, int k)
{
    // newNode fonksiyonu cagrilarak yeni bir linked list dugumu olusturur
    struct QNode* temp = newNode(k);

    // Kuyruk bossa, yeni dugum hem onde hem de arkada olur
    if (q->front == NULL && q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Yeni dugum kuyrugun sonuna eklenir ve rear isaretcisi guncellenerek yeni son elemani isaret eder hale getirilir.
    q->rear->next = temp;
    q->rear = temp;
}




// Verilen q kuyrugundan bir keyi kaldirma fonksiyonu 
void deQueue(struct Queue* q)
{
    // Kuyruk bossa return ile cikar
    if (q->front == NULL && q->rear == NULL)
        return;


    // Onceki front kismi saklayin ve onu bir dugum ileriye tasiyin
    struct QNode* temp = q->front;
    // Kuyrugun basindaki elemanin adresi gecici olarak saklanir. 
	// Bu islem, cikarilacak olan elemanin bilgilerini (degerini) korumak icin yapilir.
    q->front = q->front->next;
    // kuyrugun basi bir sonraki elemana ilerletilir.

    // Eger kuyrugun yeni basi (front) NULL ise, bu durumda kuyrugun sonu (rear) da NULL olarak ayarlanir. 
	// Bu durum, kuyrugun icinde son elemanin cikarildigi ve kuyrugun bos oldugu durumu ifade eder.
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    // Onceki bastaki elemanin (temp) hafizadan serbest birakilmasini saglar. 
	// Bu adim, artik kuyrukta olmayan elemanin bellekte ayrilan alanini geri verir.
}






int main()
{
    struct Queue* q = createQueue();
    // q adinda bir isaretci olusturur ve bu isaretci, 
	// createQueue() fonksiyonunun dondurdugu bos bir kuyrugun baslangic adresini tutar. 
	
    enQueue(q, 10);
    enQueue(q, 20);
    deQueue(q);
    deQueue(q);
    enQueue(q, 30);
    enQueue(q, 40);
    enQueue(q, 50);
    deQueue(q);
    
    printf("Queue Front : %d \n", q->front->key);
    printf("Queue Rear : %d", q->rear->key);
    // Bu iki printf ifadesi, kuyrugun onndeki elemani (front) ve arkasindaki elemani (rear) ekrana yazdirmak icin kullanilmis.
    return 0;
}
