#include <stdio.h>

// Bu program, linked list (bagli listeyi) kullanarak veri eklemeyi ve eklenen verileri ileri yonde yazdirmayi gostermektedir. 
// Bagli liste, her dugumun verisini ve bir sonraki dugumun adresini iceren bir veri yapisidir. 

struct Node { // struct Node ad�nda bir struct tanimlanir. Bu struct, bir dugumun icerigini ve bir sonraki dugumun adresini saklar.
  int data;
  struct Node *next; 
};


struct Node *head = NULL; // struct Node *head adinda bir baslangic dugumu (baslangic noktasi) tanimlanir ve baslangicta NULL olarak ayarlanir. Bu, bagli listenin baslangicta bos oldugunu gosterir.


void insert(int data) { // insert fonksiyonu, bagli liste i�ine yeni bir dugum eklemek i�in kullanilir. Fonksiyon, yeni bir dugum olu�turur, veriyi bu dugume ekler ve bu dugumu mevcut bagli listenin sonuna ekler.
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;

// Burada bagli listenin sonuna yeni bir dugum eklemeyi sa�lar. Eger bagli liste bossa, newNode head olur ve bu, bagli listenin ilk dugumu olur. Aksi takdirde, current isaretcisi son dugumu isaret edene kadar dongu ile ilerler ve yeni dugumu bagli listenin sonuna ekler. Bu sekilde bagli liste, veri eklemek i�in kullan�labilir ve mevcut verileri korur.
  if (head == NULL) { // Ilk durum icin
    head = newNode;
  } else {
    struct Node *current = head; //  �lk olarak, current ad�nda bir isaretci olu�turulur ve bu isaretci head isaretcisi ile baslatilir. head, bagli listenin basini gosterir.
    while (current->next != NULL) { // Bir while dongusu baslatilir. Bu dongu, current isaretcisi bagli listenin son dugumunu gosterene kadar calismaya devam eder. Dongu, current isaretcisinin son dugumu (yani, next isaretcisi NULL olan dugum) bulmasina yardimci olur.
      current = current->next; // Dongu her d�nd���nde, current isaretcisi bir sonraki d���me ilerler. Bu, bagli listeyi ileri do�ru tarayarak son dugumu bulma s�recini temsil eder.
    }
    current->next = newNode; // Dongu tamamlandiginda, current isaretcisi son dugumun �zerinde bulunur. Yeni bir dugum eklemek icin, bu son dugumun next i�aret�isi, yeni dugumun adresini (newNode) g�sterir. Bu islem, yeni dugumu bagli listenin sonuna ekler.
  }
}



void print_forward(struct Node *node) { // print_forward fonksiyonu, bagli listeyi ileri yonde dolasarak dugumlerin icerigini ekrana yazd�r�r. Fonksiyon, ozyinelemeli bir sekilde her dugumun icerigini yazdirir ve ardisik dugumlere gecer.
  if (node == NULL) {
    return;
  }

  printf("%d ", node->data);
  print_forward(node->next);
}



int main() {
  insert(1); // main fonksiyonu, bagli listeye uc farkl� veriyi ekler (1, 2 ve 3), sonra bagli listeyi ileri yonde yazdirmak i�in print_forward fonksiyonunu cagirir.
  insert(2);
  insert(3);

  print_forward(head);

  return 0;
}

