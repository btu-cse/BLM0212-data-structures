#include <stdio.h>

// Bu program, linked list (bagli listeyi) kullanarak veri eklemeyi ve eklenen verileri ters sirada yazdirmayi gostermektedir. 

struct Node {
  int data;
  struct Node *prev;
};



struct Node *tail = NULL; // struct Node tipinden bir isaretci olan tail, baslangicta NULL olarak ayarlanir. Bu isaretci, bagli listemizin son dugumune isaret eder.

void insert(int data) { // insert fonksiyonu, parametre olarak alinan bir tamsayi veriyi iceren yeni bir dugum olusturur ve bu dugumu bagli listenin sonuna ekler. Eğer bagli liste bossa (yani tail NULL ise), yeni dugum tail isaretcisine atanır. Aksi takdirde, bagli listenin sonuna gitmek icin bir dongu kullanilir ve son dugume ulasildiginda yeni dugum bu son dugumun "prev" (önceki) isaretcisine eklenir.
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->prev = NULL;

  if (tail == NULL) { // İlk olarak, tail isaretcisi NULL ile karsilastirilir. tail, bagli listenin son dugumune isaret etmeliyse ve eger tail NULL ise, bu, bagli listenin su anda bos oldugu anlamina gelir.
    tail = newNode; // Eğer tail NULL ise, yeni dugum newNode, tail isaretcisine atanır. Bu, bagli listenin ilk dugumudur ve tail artik bu dugume isaret eder.
  } else { // Eger tail NULL degilse, yani bagli liste boş degilse, else blogu calistirilir.
    struct Node *current = tail; // Bir gecici isaretci olan current, tail ile baslatilir. Bu, current isaretcisinin baslangicta bagli listenin son dugumune isaret ettigi anlamina gelir.
    while (current->prev != NULL) { // Bir while dongusu kullanilir ve bu dongu, bagli listenin sonuna gitmek icin current isaretcisini onceki dugumler uzerinde hareket ettirir. Dongu, current->prev ifadesi ile kontrol edilir, yani current isaretcisi bir önceki dugume işaret ediyorsa dongu devam eder. Bu dongu, bagli listenin son dugumune ulasmak icin calisir.
      current = current->prev; // Donguden cikildiginda, current isaretcisi son dugume isaret eder. Yani current->prev artık NULL'dir. Bu, bagli listenin son dugumune ulasildigini gosterir.
    }
    current->prev = newNode; // Son adimda, yeni dugum newNode, current->prev ile baglanir. Yani, yeni dugum, bagli listenin son dugumunun "prev" isaretcisine eklenir ve bu sayede bagli liste sona eklenir.
  }
}



void print_backward(struct Node *node) { // print_backward fonksiyonu, bir dugum isaretcisi alir ve bu dugumden baslayarak bagli listeyi ters sirada yazdirmak icin ozyinelemeli bir yaklasim kullanir. İlk olarak, isaretci NULL ise (yani bagli listenin sonuna ulasilmissa), islev cagrilmadan geri döner. Aksi takdirde, ozyinelemeli olarak onceki dugume (onceki dugumun isaret ettigi dugume) gitmek için print_backward fonksiyonunu tekrar cagirir ve ardindan mevcut dugumun verisini yazdirir. Bu sayede, bagli liste ters sirada yazdirilir.
  if (node == NULL) {
    return;
  }

  print_backward(node->prev);
  printf("%d ", node->data);
}



int main() {
  insert(1); // main işlevi, örnek verileri (1, 2 ve 3) bağlı listeye ekler ve ardından bağlı listeyi ters sırada yazdırmak için print_backward fonksiyonunu çağırır.
  insert(2);
  insert(3);

  print_backward(tail);

  return 0;
}



