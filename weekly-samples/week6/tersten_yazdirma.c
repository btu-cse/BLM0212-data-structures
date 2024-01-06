// Verilen C programi, bir tek yonlu bagli listenin (linked list) tersini yazdirmak icin kullanilir.
// Başlangicta, bagli liste asagidaki gibi oluşturulur:
// 1 -> 2 -> 3 -> 4
// Ancak printReverse fonksiyonu, bu liste ogelerini ters sirada yazdirir. Yani cikti asagidaki gibi olur:
// 4 3 2 1
// Yani, programin amaci, bagli listeyi tersine cevirmek veya ters sirada olusturmak degil, mevcut bir bagli listeyi ters sirada yazdirmaktir.

#include<stdio.h>
#include<stdlib.h>

/* 
Node olusturma:
struct Node, bagli listedeki bir dugumu temsil etmek icin tanimlanir. 
Her dugum, bir tamsayi degeri data ve bir sonraki dugumu isaret eden bir isaretci next icerir.
*/
struct Node 
{
	int data;
	struct Node* next;
};

/* 
printReverse fonksiyonu, bagli listenin basini isaret eden bir isaretciyi arguman olarak alir ve bu bagli listeyi ters sirada yazdirir. 
Recursive icin taban durumu, head'in NULL olması durumunda gerceklesir, bu da listenin sonuna ulasildigini gosterir.
*/
void printReverse(struct Node* head)
{
	// Base case
	if (head == NULL){
		return;
	}
	
	else{

	// listeyi head node'dan sonra yazdir.
	// printReverse fonksiyonu icinde once kendisini bir sonraki dugumle (head->next) cagirarak listenin geri kalanini ters sirada yazdirmak icin bir rekursif cagri yapar 
	// Bu, listenin sonundaki ogelerin once yazilmasini saglar
	printReverse(head->next);

	// Diger her seyi yazdirdiktan sonra head'i yazdir
	// Rekursif cagrilar nedeniyle geri kalan ogeleri yazdirdiktan sonra, mevcut dugumun değerini (head->data) yazdirir. 
	// Bu, bagli listenin ogelerini ters sirada yazdirir.
	printf("%d ", head->data);
	}
}


/* 
Bir node'u linked liste'e ekleme, bu fonksiyon head'i degistirir.
push fonksiyonunda, yeni bir dugum dinamik bellek tahsisi kullanilarak oluşturulur (malloc). 
new_data, yeni dugumun data alanina atanir ve yeni dugumun next alani mevcut listenin basina baglanir. 
Ardindan, liste basi yeni dugumu gosterecek sekilde guncellenir, boylece yeni bir oge listenin basina eklenir. 
Bu islev, bagli listeyi olusturmak icin kullanilir.
*/
void push(struct Node** head_ref, char new_data)
{
	// Burada struct Node** kullandik cunku bagli listenin basini isaret eden bir isaretcinin degerini degistirmeye calistik
	// Yani isaretcinin isaret ettigi adresi degistirmeye calistik
	// Bu fonksiyon ile bagli listenin head'ini guncelledik, linked list uzerinde kalici degisiklikler yapabildik 
	
	// Node icin yer ayirma
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	// data'yi atama 
	new_node->data = new_data;

	// eski listeyi yeni dugume baglama 
	new_node->next = (*head_ref);

	// new node'u gosterecek sekilde head'i hareket ettir.
	(*head_ref) = new_node;
}

/* 
main fonksiyonunda ornek bir bagli liste olusturulur ve ogeler (1, 2, 3 ve 4) bu listeye eklenir. 
Bu ogeler sirasiyla (1, 2, 3 ve 4) eklenir ve ardindan bagli listenin basiyla printReverse fonksiyonu cagrilir ve ogeler ters sirada yazdirilir.
*/
int main()
{
	struct Node* head = NULL;
	push(&head, 4);
	push(&head, 3);
	push(&head, 2);
	push(&head, 1);

	printReverse(head);
	return 0;
}
