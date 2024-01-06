// Bagli Listede tum ekleme yontemlerini gosteren program

#include <stdio.h>
#include <stdlib.h>

struct Node
{
int data;
struct Node *next;
};

// Bir listenin basina bir referans (pointer to pointer) ve bir int verildiginde, listenin onune yeni bir dugum ekler
void basina_ekle(struct Node** head_ref, int new_data)
{
	 // Dugume yer ayir 
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	// Dugumun verilerini gir 
	new_node->data = new_data;
	printf("Verileri gir \n");

	// Yeni dugumun yanindakini head olarak yap 
	// Yeni dugumun "next" isaretcisi mevcut baslangic dugumunu isaret eder
	// Bu, yeni dugumun bagli listenin basinda oldugu ve diðer dugumlerin bu dugume baglanacagi anlamina gelir
	// Yani, yeni dugum eski baslangic dugumunu isaret eder ve bu sayede bagli liste yapisi korunmus olur
	new_node->next = (*head_ref);
	printf("Yeni dugumun yanindakini head gir \n");

	// Yeni dugume isaret etmek icin headi hareket ettir 
	(*head_ref) = new_node;
    printf("Yeni dugume isaret etmek icin headi hareket ettir\n");
}

// Bir prev_node dugumu verildiginde, verilen prev_node'dan sonra yeni bir dugum ekleyin 
void araya_ekle(struct Node* prev_node, int new_data)
{
	// Verilen prev_node'un NULL olup olmadigini kontrol edin 
	if (prev_node == NULL)
	{
	printf("Verilen onceki dugum NULL olamaz \n");

	return;
	}

	// Yeni dugume hafizadan yer ayir 
	struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));

	// Dugumun verilerini gir 
	new_node->data = new_data;

	// Yeni dugumun sonrakini prev_node'un sonraki yap, bu sayede yeni dugum, onceki dugumun ardina dogru bir sekilde eklenir
	// Eger new_node = prev_node->next; boyle yazsaydik 
	// Bu durumda new_node yeni dugumun baska bir dugumun yerini almasina neden olur ve bagli listedeki bu dugum kaybolur
	// Bu, dugumlerin duzgun bir sekilde bagli listeye eklenmesi yerine, bir dugumun baska bir dugumu sadece degistirmesi anlamina gelir
	new_node->next = prev_node->next;

	 // Onceki_dugum'un sonrakini yeni_dugum olarak tasi 
	prev_node->next = new_node;
}


// Bir listenin basina bir referans (pointer to pointer) ve bir int verildiginde, sonuna yeni bir dugum ekler 
void sonuna_ekle(struct Node** head_ref, int new_data)
{
	// Yeni dugume hafizadan yer ayir 
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	struct Node *last = *head_ref;

	// Dugumun verilerini gir 
	new_node->data = new_data;
	 printf("Verileri gir \n");

	// Bu yeni dugum son dugum olacak, bu yuzden bir sonrakini NULL yap
	new_node->next = NULL;
	printf("Bir sonrakini Null yap \n");

    // Baglantili Liste bossa, yeni dugumu head olarak yapin 
	if (*head_ref == NULL)
	{
	*head_ref = new_node;
	printf("Liste bossa yeni dugumu head yap \n");

	return;
	}

    // Aksi takdirde son dugume kadar gecis 
	while (last->next != NULL){
		last = last->next;
        printf("Son dugume kadar gecis \n");
    }

	// Son dugumun bir sonrakini degistir 
	last->next = new_node;
	printf("Son dugumun bir sonrakini degistir \n");
	return;
}

// Bu islem, baglantili listenin icerigini suradan baslayarak yazdirir:
void listeyi_yazdir(struct Node *node)
{

while (node != NULL)
{
	printf(" %d ", node->data);
	node = node->next;
}
}


int main()
{

// Bos listeyle basla 
struct Node* head = NULL;

// Ekle 6. Boylece baglantili liste 6->NULL olur
sonuna_ekle(&head, 6);

// Basina 7 ekleyin. Boylece baglantili liste 7->6->NULL olur
basina_ekle(&head, 7);

// Basa 1 ekleyin. Boylece baglantili liste 1->7->6->NULL olur
basina_ekle(&head, 1);

// Sonuna 4 ekleyin. Boylece baglantili liste 1->7->6->4->NULL olur
sonuna_ekle(&head, 4);

// 7'den sonra 8'i ekleyin. Boylece baglantili liste 1->7->8->6->4->NULL olur.
araya_ekle(head->next, 8);

printf("\nLinked list olusturuldu: \n");
listeyi_yazdir(head);

return 0;
}

