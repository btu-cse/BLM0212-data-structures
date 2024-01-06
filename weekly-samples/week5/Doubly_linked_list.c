#include <stdio.h>

// Bu program, cift yonlu bir bagli liste olusturur ve eklenen verileri ileri ve ters yonde yazdirmayi gostermektedir. 

struct Node { // Cift yonlu bagli listeyi temsil etmek icin Node adýnda bir struct tanimlanir. Her bir dugum iki yonde baglantilari saklar: bir sonraki dugumu (next) ve bir onceki dugumu (prev) isaret eder.
  int data;
  struct Node *next;
  struct Node *prev;
};

struct Node *head = NULL; // struct Node türünde iki isaretci (head ve tail) tanimlanir. head, baðlý listenin basini (ilk dugumu) isaret ederken, tail bagli listenin sonunu (son dugumu) isaret eder. Baslangicta her ikisi de NULL olarak ayarlanir, cunku baslangicta herhangi bir dugum yoktur.
struct Node *tail = NULL;

void insert(int data) { // insert fonksiyonu, bagli liste icine yeni bir dugum eklemek icin kullanilir. 
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node)); // Yeni bir dugum oluþturulur ve bu dugum icin hafiza tahsis edilir (malloc ile).
  newNode->data = data; // Yeni dugumun veri kismina, data parametresi ile gelen veri atanýr.
  newNode->prev = NULL; // Yeni dugumun önceki ve sonraki isaretcileri (prev ve next) NULL olarak ayarlanir.
  newNode->next = NULL; 

  if (head == NULL) { // Eger bagli liste bossa (head == NULL), head ve tail yeni dugumu isaret eder. Ilk dugum eklenir.
    head = newNode;
    tail = newNode;
  } else {
    struct Node *current = tail; // Eger bagli liste bos deðilse, yeni dugum sona eklenir. Onceki son dugumun sonraki isaretcisi yeni dugumu isaret eder ve tail yeni dugumu isaret eder.
    current->next = newNode;
    newNode->prev = current; // Dugumleri karsilikli olarak bagladik.
    tail = newNode; // Burada while dongusu kullanilmadi, tek yonlu listelerde referans noktasindan listenin sonuna kadar hareket edilir, son elemana yeni dugum baglanir. Ama cift yonlu listelerde son ve ilk elemanýn adresleri bilindigi icin tek islemle eklenecek adres bulunabilir.
  }
}

// print_forward ve print_backward fonksiyonlari, baðlý listeyi hem ileri hem de geri doðru yazdýrmak için kullanýlýr. 
void print_forward(struct Node *node) { // print_forward, baþlangýç dugumunu (genellikle head) alir ve ileri dogru bagli listeyi dolasarak dugumlerin verilerini yazdirir. Bu fonksiyon, baþlangýç dugumunu alir ve her dugumun next isaretisini takip ederek dugumlerin verilerini yazdirir.
  if (node == NULL) {
    return;
  }

  printf("%d ", node->data);
  print_forward(node->next);
}

void print_backward(struct Node *node) { // print_backward, baslangic dugumunu (genellikle tail) alir ve geriye dogru bagli listeyi dolasarak dugumlerin verilerini yazdirir. Bu fonksiyon, baslangic dugumunu alir ve her dugumun prev isaretcisini takip ederek dugumlerin verilerini yazdirir.
  if (node == NULL) {
    return;
  }
  printf("%d ", node->data);
  print_backward(node->prev);
}

int main() {
  insert(1); // Main icerisinde (1, 2, ve 3) iceren dugumler bagli liste icine eklenir. Ardindan, print_forward ve print_backward fonksiyonlarý cagrilarak bagli liste hem ileri hem de geri dogru yazdirilir. Bu sekilde, bagli listeyi kontrol etmek icin kullanilir.
  insert(2);
  insert(3);

  print_forward(head);
  printf("\n");
  print_backward(tail);

  return 0;
}

