/*
Kullanicinin tanimladigi dugum sayisiyla bir linked list olusturan ve ardindan listedeki verileri goruntuleyen program
*/

#include <stdio.h>
#include <stdlib.h>

// Node olusturma
struct node {
    int data;          
    struct node *next; 
}*head;



// n node'dan olusan bir liste olusturma
void createList(int n)
{
    struct node *newNode, *temp;
    int data, i;

    head = (struct node *)malloc(sizeof(struct node)); // Bellek tahsis eder ve kulanicinin girdigi veriyi iceren ilk dugumu (head) oluþturur

    // bellek ayrilmamissa sonlandir
    if(head == NULL)
    {
        printf("Hafizada yer ayrilamiyor.");
        exit(0);
    }

    // Kullanicinin node verisini girmesi
    printf("Node 1'in verisini giriniz: ");
    scanf("%d", &data);

    head->data = data; // data alanýný data'ya bagla
    head->next = NULL; // adres alanini NULL yap


    // n-1 node olustur ve dugume ekle
    // Ardindan bir donguye girer ve n-1 daha fazla dugum olusturup listeye ekler
	// Her seferinde yeni bir dugum için bellek tahsis eder, kullanicinin girdigi veriyi saklar ve onceki dugume baglar
    temp = head;
    for(i=2; i<=n; i++)
    {
    	// Burada baslangic dugumu (head) zaten olusturuldugu icin for dongusunu 2'den baslatir
    	
        newNode = (struct node *)malloc(sizeof(struct node));

        // newNode icin yer ayrilmamissa
        if(newNode == NULL)
        {
            printf("Hafizada yer ayrilamiyor.");
            break;
        }

        printf("Node %d'nin verisini giriniz: ", i);
        scanf("%d", &data);

        newNode->data = data; // newNode'un data'sini bagla
        newNode->next = NULL; // newNode'un NULL'a isaret ettiginden emin ol

        temp->next = newNode; // yeni olusturulan dugumu onceki dugume (temp isaretcisi tarafindan temsil edilen) bagla
        temp = temp->next;    // temp isaretcisi su anki dugumu temsil etmekten ziyade bir sonraki dugumu temsil etmeye baslar
    }
}




// Listenin tamamini goruntuleme
// Linked listi head dugumunden baslayarak dolasir, her dugumdeki veriyi goruntuler ve listenin sonuna ulasana kadar devam eder
void traverseList()
{
    struct node *temp;

    // Liste bossa return 
    if(head == NULL)
    {
        printf("Liste bos.");
        return;
    }

    temp = head;
    while(temp != NULL)
    {
        printf("Data = %d\n", temp->data); // Mevcut node'un verisini yazdirma
        temp = temp->next;                 // next node'a ilerleme
    }
}



int main()
{
    int n;

    printf("Toplam node sayisini giriniz: ");
    scanf("%d", &n);

    createList(n);

    printf("\nListedeki veriler: \n");
    traverseList();

    return 0;
}
