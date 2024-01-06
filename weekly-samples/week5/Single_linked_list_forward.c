#include <stdio.h>

// Bu program, linked list (bagli listeyi) kullanarak veri eklemeyi ve eklenen verileri ileri yonde yazdirmayi gostermektedir. 
// Bagli liste, her dugumun verisini ve bir sonraki dugumun adresini iceren bir veri yapisidir. 

struct Node { // struct Node adýnda bir struct tanimlanir. Bu struct, bir dugumun icerigini ve bir sonraki dugumun adresini saklar.
  int data;
  struct Node *next; 
};


struct Node *head = NULL; // struct Node *head adinda bir baslangic dugumu (baslangic noktasi) tanimlanir ve baslangicta NULL olarak ayarlanir. Bu, bagli listenin baslangicta bos oldugunu gosterir.


void insert(int data) { // insert fonksiyonu, bagli liste içine yeni bir dugum eklemek için kullanilir. Fonksiyon, yeni bir dugum oluþturur, veriyi bu dugume ekler ve bu dugumu mevcut bagli listenin sonuna ekler.
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;

// Burada bagli listenin sonuna yeni bir dugum eklemeyi saðlar. Eger bagli liste bossa, newNode head olur ve bu, bagli listenin ilk dugumu olur. Aksi takdirde, current isaretcisi son dugumu isaret edene kadar dongu ile ilerler ve yeni dugumu bagli listenin sonuna ekler. Bu sekilde bagli liste, veri eklemek için kullanýlabilir ve mevcut verileri korur.
  if (head == NULL) { // Ilk durum icin
    head = newNode;
  } else {
    struct Node *current = head; //  Ýlk olarak, current adýnda bir isaretci oluþturulur ve bu isaretci head isaretcisi ile baslatilir. head, bagli listenin basini gosterir.
    while (current->next != NULL) { // Bir while dongusu baslatilir. Bu dongu, current isaretcisi bagli listenin son dugumunu gosterene kadar calismaya devam eder. Dongu, current isaretcisinin son dugumu (yani, next isaretcisi NULL olan dugum) bulmasina yardimci olur.
      current = current->next; // Dongu her döndüðünde, current isaretcisi bir sonraki düðüme ilerler. Bu, bagli listeyi ileri doðru tarayarak son dugumu bulma sürecini temsil eder.
    }
    current->next = newNode; // Dongu tamamlandiginda, current isaretcisi son dugumun üzerinde bulunur. Yeni bir dugum eklemek icin, bu son dugumun next iþaretçisi, yeni dugumun adresini (newNode) gösterir. Bu islem, yeni dugumu bagli listenin sonuna ekler.
  }
}



void print_forward(struct Node *node) { // print_forward fonksiyonu, bagli listeyi ileri yonde dolasarak dugumlerin icerigini ekrana yazdýrýr. Fonksiyon, ozyinelemeli bir sekilde her dugumun icerigini yazdirir ve ardisik dugumlere gecer.
  if (node == NULL) {
    return;
  }

  printf("%d ", node->data);
  print_forward(node->next);
}



int main() {
  insert(1); // main fonksiyonu, bagli listeye uc farklý veriyi ekler (1, 2 ve 3), sonra bagli listeyi ileri yonde yazdirmak için print_forward fonksiyonunu cagirir.
  insert(2);
  insert(3);

  print_forward(head);

  return 0;
}

