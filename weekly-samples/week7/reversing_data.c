#include <stdio.h>
#include <string.h>
#define maks 100

// Dizi ile yigin mantigiyla ters cevirme islemi yapma
// Yani bir dizi kullanarak bir yiginda karakterleri tersine ceviren program

int top;
stack[maks];




void push(char x){
      // Ekleme Islemi
      if(top == maks-1){
          printf("stack overflow");
      }  else {
          top+=1;
          stack[top]=x;
          // Burayi su sekilde de yazabiliriz:
          // stack[++top]=x;
      }
}




void pop(){
    // Silme Islemi
      printf("%c",stack[top]);
      top-=1;
      // Burayi su sekilde de yazabiliriz:
      //  printf("%c",stack[top--]);

// Yazdirma islemi pop() fonksiyonunda gerceklesiyor
// pop() fonksiyonu, yigindan bir karakter cikarip, cikarilan karakteri ekrana yazdiriyor.
}




main()
{
   char ad[]="ZEYNEP"; // Karater dizisi olusturuldu
   int uzunluk = strlen(ad); // strlen fonksiyonu ile karakter dizisinin uzunlugu hesaplanir
   int i;

   for(i=0;i<uzunluk;i++)
        push(ad[i]);

   for(i=0;i<uzunluk;i++)
      pop();
}

/*
"ADT", bir veri yapisinin davranislarini ve ozelliklerini tanimlayan bir kavramdir.
ADT, "Abstract Data Type"ýn kisaltmasidir ve Turkce karsiligi "Soyut Veri Tipi" olarak gecer.

ADT'ler, veri yapisi olarak dusunulen ancak ic isleyisinin ve detaylarinin gizlendigi bir yapidir.
Yani, bir ADT'nin kullanicilari, veri yapisinin nasil calistigina dair ic detaylari bilmeden sadece kullanim seklini ve sagladigi islevleri bilir.

Ornegin, stack bir ADT'dir.
Kullanicilar, stack'i eleman eklemek, cikarmak ve ustteki elemana erismek gibi temel islemleri gerceklestirmek icin kullanabilirler.
Ancak, stack'in ic yapisini (ornegin, dizilerle mi yoksa bagli listelerle mi olusturuldugunu) bilmezler veya bu ic detaylarla ilgilenmezler.

Bu soyutlama seviyesi, veri yapisinin kullanicilar ile veri yapisini olusturan kisiler veya kodlama tarafindan ayrilmasini saglar
Bu sayede, bir veri yapisinin ic yapisini degistirirken bile kullanicilarin bu degisikliklerden etkilenmemesi saglanabilir.
ADT'ler, veri yapilarini kullanirken bu tur bir soyutlama saglayarak programlamada buyuk esneklik ve modulerlik sunar.

Stack ADT'nin temel iislevler sunlardir:

Push (Ekleme): Yigina bir eleman ekler.
Pop (Cikarma): Yigidan en usteki elemani cikarir.
Top (Ustteki Eleman): Yiginin en ustteki elemanini gosterir.
*/



