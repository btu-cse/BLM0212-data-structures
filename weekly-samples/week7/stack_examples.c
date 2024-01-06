#include <stdio.h>
#include <stdlib.h>
#define boyut 10

/*
Stack ve queue kisitlanmis dogrusal listelerdir, kisitlanmis bir dogrusal listede (restricted
linear list), verilerin eklenmesi ve silinmesi listenin uclarindan olacak sekilde sinirlandirilmistir.

Yigin (Stack), verilerin eklenmesi ve silinmesinin tepe (top) adi verilen listenin
bir ucu ile kisitlandigi dogrusal bir listedir.
Yalnizca en uste bir nesneyi ekleyebileceginiz veya cikarabileceginiz herhangi bir durum bir yigindir.
Ustteki nesneden baska herhangi bir nesneyi cikarmak
istiyorsaniz, once onun uzerindeki tum nesneleri kaldirmaniz gerekir.


Bir dizi veriyi bir yigina yerlestirip cikarirsak, veri sirasi tersine cevrilir.
Bu ozellik Last In – First Out (LIFO) olarak bilinir.

LIFO - Last In – First Out - Son Giren Ilk Cikar (stack)
FIFO - First In – First Out - Ilk Giren Ilk Cikar (queue)
*/

// Stack uzerinde ekleme, silme, listeleme islemlerini gerceklestiren program:


struct stack{
//  Bu struct, yigini temsil etmek icin kullanilir.
// Icinde top adinda bir ust sinir ve deger adinda bir dizi bulunur.

int top; // yiginin üzerinde calistigi indis degeri
int deger[boyut];

};



struct stack s;
// stack yapisindan s adinda bir degisken olusturur
// Bu durumda s degiskeni struct stack yapisinin ozelliklerini iceren bir yigini temsil eder
// Bu yiginin icinde top adinda bir tamsayı degiskeni ve boyut buyuklugunde bir dizi olan deger bulunur
// s üzerinden yigin islemleri gerceklestirilebilir.






void push(struct stack *ps, int x) // Eleman eklemek icin kullanilan fonksiyon
{ // Yiginin dolu olup olmadigini kontrol eder ve dolu degilse x degerini yigina ekler.

    if(ps->top==9)
        printf("stack dolu");
        // Boyut 10 olarak tanimlandigi icin,
        // yiginin indisleri 0'dan baslar ve 0'dan 9'a kadar olan indisleri kullanarak 10 elemani saklayabilir

    else
		ps->deger[(ps->top)]=x;
		ps->top = ps->top +1; // yiginin deger dizisine x degerini ekler.

        // Burayi su sekilde de yazabiliriz:
        // ps->deger[(ps->top)++]=x; //deger[i+1]=x;
}






void pop(struct stack *ps) // Eleman silmek icin kullanilan fonksiyon
{ // Yiginin bos olup olmadigini kontrol eder ve bos degilse ustteki elemani cikarir.
 if(ps->top==0)
        printf("stack bos");
 else
    ps->top--;

// ps isimli isaretci, struct stack turunden bir veri yapisina isaret etmek icin olusturulmustur
// Yigin uzerinde islemler yapabilmek icin bu isaretci kullanilir
}




int main()
{

    int sayi=0;
    while(sayi!=4){
    printf("\nLutfen bir secim yapin: \n1 Ekleme Islemi \n2 Silme Islemi\n3 Listeleme Islemi\n4 Cikis\n");
    scanf("%d",&sayi);


        switch(sayi){
        case 1:
            printf("Eklemek istediginiz sayiyi girin:\n");
            int ekle;
            scanf("%d",&ekle);
            push(&s,ekle);
            break;
        case 2:
            pop(&s);
            break;
        case 3:
            if(s.top==0)
                printf("Liste bos ");
            else
            printf("Listeniz:  ");
            for(int a=0;a<s.top;a++)
                printf("%d ",s.deger[a]);
            break;
            // for döngüsü, yigitin top degiskeni tarafindan belirtilen eleman sayisi kadar donuyor.
            // Bu, yigitin icindeki mevcut eleman sayisini temsil eder.
            // Her bir eleman, yigitin deger dizisinde saklanir.
            // Dongu, a degiskenini 0'dan baslatir ve s.top (yigitin mevcut eleman sayisi) degerine kadar devam eder.
            // Her adimda, yigitin deger dizisindeki a indisli elemanini ekrana yazdirir.
            // Bu sekilde, yigitin icerigi ekrana sirali bir sekilde yazdirilir.
        default:

            printf("\n");
            break;

    }
    }

}
