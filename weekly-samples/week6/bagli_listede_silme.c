// Tekli linked list uzerinde eleman ekleme ve silme

#include <stdio.h>
#include <stdlib.h>


struct Node {
	int data;
	struct Node* next;
};


// Bir listenin head'ine bir referans (pointer to pointer) ve bir int verildiginde, listenin onune yeni bir node ekler 
void push(struct Node** head_ref, int new_data)
{
	// push fonksiyonu, verilen bir head_ref (bagli listenin basini tutan bir isaretcinin isaret ettigi isaretci) ve yeni bir veri new_data ile cagrilir 
	// Bu fonksiyon, yeni bir dugum olusuturur ve bu dugumu bagli listenin basina ekler 
	// Yani yeni dugum, liste basi haline gelir ve yeni dugumun sonraki dugumu eski liste basini gosterir
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}


// deleteNode fonksiyonu, bir head_ref ve bir key degeri ile cagrilir
// Bu fonksiyon, verilen key değerini iceren dugumu bagli listeden siler
void deleteNode(struct Node** head_ref, int key)
{
	
	// temp, bagli listenin baslangicini gosterir ve prev, onceki dugumun isaretcisini saklamak icin kullanilir
	struct Node *temp = *head_ref, *prev;

	// İlk olarak, temp isaretcisi listenin basindaki dugumu temsil ediyor mu kontrol edilir
	// Eger oyleyse ve bu dugumun verisi key ile eslesiyorsa, bu dugum silinir ve head_ref baska bir dugumu isaret eder hale getirilir
	// Bu islem, listenin basindaki dugumun silinmesini saglar
	if (temp != NULL && temp->data == key) {
		*head_ref = temp->next; // head degisti
		free(temp); // eski head'i birak
		// free fonksiyonu, linked listten bir dugumun bellekten serbest birakilmasini ifade eder
		// Dugum, malloc veya benzer bir bellek tahsisi islemi kullanilarak dinamik olarak olusurulmussa
		// programin bellek yonetimi ve kaynak temizligi acisindan onemlidir
		return;
	}


	// Eger yukaridaki sartlar saglanmazsa, dongu ile bagli listeyi tarariz
	// Dongu, temp isaretcisi NULL olana veya key degeri ile eslesene kadar devam eder
	// Her adimda prev isaretcisi, temp isaretcisini takip eder ve temp isaretcisi bir sonraki düğüme gecer
	while (temp != NULL && temp->data != key) {
		prev = temp;
		temp = temp->next;
	}

	// Eger temp isaretcisi NULL ise, bu durumda key degeri bagli listede bulunamadi demektir ve fonksiyon herhangi bir islem yapmadan sonlanir
	if (temp == NULL)
		return;

	// Node'un linked listten baglantisini kaldir
	// Eger temp isaretcisi key değeri ile eslesen bir dugumu temsil ediyorsa, prev isaretcisi kullanilarak bu dugumun baglantisi kesilir (yani onceki dugumun next isaretcisi, temp->next ile guncellenir) ve ardindan temp isaretcisi serbest birakilir
	prev->next = temp->next;
	free(temp); // Free memory
}



// Bu fonksiyon, verilen bir dugum isaretcisi ile cagrildiginda, bagli listeyi bastan sona dolasarak dugumlerin verilerini ekrana yazdirir
void printList(struct Node* node)
{
	while (node != NULL) {
		printf(" %d ", node->data);
		node = node->next;
	}
}


int main() 
// main fonksiyonunda, ornek bir bagli liste oluşturulur
// Bu liste, sirasiyla 7, 1, 3 ve 2 degerlerini iceren dugumleri icerir
{

	struct Node* head = NULL;


	push(&head, 7);
	push(&head, 1);
	push(&head, 3);
	push(&head, 2);

	puts("Olusturulan Linked List: ");
	printList(head);
	
	deleteNode(&head, 1);
	
	puts("\n1'in silinmesinden sonra Linked List: ");
	printList(head);
	return 0;
}
