#include<stdio.h>
#include<string.h>

/*
Infix ve postfix, matematiksel ifadelerin farkli gosterim bicimleridir.

Infix: Bu, en yaygin olarak kullanilan ifade bicimidir. 
Operatorler, operandlarin arasinda bulunur. 
Ornegin: 2 + 3 * 5

Postfix: Bu, operatorlerin operandlarin sonunda bulundugu bir ifade bicimidir. 
Bu notasyon, operatorlerin onceliklerine ve ifadenin daha acik bir sekilde degerlendirilmesine izin verir. 
Ornegin, 2 3 5 * + (Bu, 2 + (3 * 5) ifadesine karsilik gelir.)

Postfix notasyonu, islemleri bir yigin uzerinde sirali olarak gerceklestirme yetenegi 
sayesinde bilgisayar programlamada ve hesaplama cihazlarýnda kullanilmaktadir. 
Bu, ozellikle parantezlerin gerekliligini ortadan kaldirir ve operatorlerin onceligini acik bir sekilde ifade eder.

Bu ornekte, verilen bir infix ifadeyi postfix ifadeye donusturmek ve daha sonra bu postfix ifadeyi degerlendirmek icin bir program iceriyor.
Ornegin, "2 * (2 + 3)" ifadesi infix notasyonundadir ve bu ifadeyi postfix notasyonuna donusturdugumuzde "2 2 3 + *" seklinde olur. 
Bu sekilde, postfix ifade operatorlerin operandlari takip ettigi ve operator oncelikleri daha belirgin oldugu icin islemler daha rahat bir sekilde gerceklestirilir.

Prefix: Operatorler, operandlarin onunde bulunur. Bu notasyon, operatorlerin onceligini ve ifadeyi daha acik bir sekilde gosterir. 
Ornegin, + 2 * 3 5 (Bu, 2 + (3 * 5) ifadesine karsilik gelir.)


Bu uc gosterim bicimi, ayni ifadeyi farkli sekillerde yazmayi saglar.
Infix, insanlar tarafindan daha cok kullanilan ve yaygin olarak anlasilan bicimdir. 
Prefix ve postfix ise, bilgisayarlar tarafindan daha kolay islenebilir ve hesaplanabilir bicimlerdir. 
Postfix notasyonu ozellikle yiginlarin kullanilmasiyla hesaplama islemlerinde tercih edilir 
cunku operatorlerin ve operandlarin sirasi belirgindir ve operasyonlarin islenme sirasini otomatik olarak belirler.
*/





// char stack
char stack[25]; 
// Bu dizi, yigini depolamak için kullanilir.
int top = -1; 
// Yiginin en ustunde (en son eklenen oge) bulunan indeksi temsil eder. 
// -1, yiginin baslangicta bos oldugunu gosterir.


void push(char item) { 
   // Yiginin ustundeki indeksi bir arttirarak yeni ogeyi ekler.
   stack[++top] = item;
}

char pop() { 
   // yýgýnýn ustundeki ogeyi cikarir ve cikardigi ogeyi dondurur. 
   // Ardidan, yiginin ustundeki indeksi bir azaltir.
   return stack[top--];
}




// Operatorlerin onceliklerini dondurur
// Fonksiyon, symbol isimli bir karakter alir ve bu karakterin hangi operatore denk geldigini kontrol eder. 
// Her operator icin belirli bir oncelik degeri atanmistir:
// + ve - operatorleri onceligi 2'dir.
// * ve / operatorleri onceligi 3'dur.
// ^ operatorunun onceligi 4'tür.
// (, ) ve # sembolleri onceligi 1'dir.
int ustunluk(char symbol) {

   switch(symbol) {
      case '+':
      case '-':
         return 2;
         break;
      case '*':
      case '/':
         return 3;
         break;
      case '^':
         return 4;
         break;
      case '(':
      case ')':
      case '#':
         return 1;
         break;
   }
}






// Bu fonksiyon, belirtilen sembolun bir operator olup olmadigini kontrol eder. 
// Verilen bir sembolün operator olup olmadigini belirlemek icin karakter dizisi icinde arama yapar.
int isOperator(char symbol) {

   switch(symbol) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '(':
      case ')':
         return 1;
      break;
         default:
         return 0;
   }
}




// Infix ifadesini postfix'e donusturur
void convert(char infix[],char postfix[]) {
   int i,symbol,j = 0;
   stack[++top] = '#'; // Yigina baslangic olarak '#' sembolunu ekler.

   for(i = 0;i<strlen(infix);i++) {
      symbol = infix[i]; // infix[] ifadesini sembol sembol okuyarak, karakter dizisi icinde ilerler. Her sembol icin su adimlar gerceklestrilir:

      if(isOperator(symbol) == 0) {
         postfix[j] = symbol; // Eger sembol bir operator degilse, postfix ifadenin bir parcasidir ve dogrudan postfix[] karakter dizisine eklenir.
         j++;
      } else {
         if(symbol == '(') { // Eger sembol ( ise, yigina bu sembol eklenir.
            push(symbol);
         } else {
            if(symbol == ')') { // Eger sembol ) ise, yigindan ( sembolune kadar olan tum operatorler postfix ifadesine eklenir.

               while(stack[top] != '(') {
                  postfix[j] = pop();
                  j++;
               }

               pop();   // '(' sembolu cikarilir.
            } else { // Diger durumlarda, sembolun onceligi ile yigindaki ustteki sembolun onceligini karsilastirir.
               if(ustunluk(symbol)>ustunluk(stack[top])) {
               	// Eger sembolun onceligi yigindaki ustteki sembolun onceliginden buyukse, sembol yigina eklenir.
                  push(symbol);
               } else {
				// Eger sembolun onceligi yigindaki ustteki sembolun onceliginden kucuk veya esitse, 
				// yigindaki ustteki sembol postfix ifadesine eklenir ve islem bu sekilde devam eder.
				// Infixdeki sembol de yigina eklenir.
                  while(ustunluk(symbol)<=ustunluk(stack[top])) {
                     postfix[j] = pop();
                     j++;
                  }

                  push(symbol);
               }
            }
         }
      }
   }
 // Yigindaki kalan semboller postfix ifadeye eklenir ve null terminator ile sonlandirilir.
   while(stack[top] != '#') {
      postfix[j] = pop();
      j++;
   }

   postfix[j]='\0';  // null terminate string.
}






// int stack
// Bu stack_int ve onunla iliskili islevler, sayisal degerlerin saklanmasi ve islenmesi icin bir stack olusturur. 
// Normalde karakterler icin kullanilan stack dizisine benzer bir yapidir, ancak bu kez tam sayi degerlerini saklamak icin olusturulmustur.
// Bu tur bir yigin, postfix ifadenin degerlendirilmesi sirasinda gecici olarak operandlari depolamak icin kullanýlabilir. 
// push_int fonksiyonu, yigina bir tam sayi degeri eklerken pop_int fonksiyonu yiginin en ustundeki tam sayi degerini cikarir ve geri dondurur.
// Postfix ifadenin degerlendirilmesi sirasinda, operandlar yigina konulur ve operatorler bu operandlari alarak islemleri gerceklestirir. 
// Yigin, geçici degerleri saklamak icin kullanilarak islemlerin dogru sirayla gerceklestirilmesine olanak tanir.
int stack_int[25];
int top_int = -1;

void push_int(int item) {
   stack_int[++top_int] = item;
}

char pop_int() {
   return stack_int[top_int--];
}






// Bu fonksiyon, verilen bir postfix ifadeyi degerlendirmek icin kullanilir. 
int evaluate(char *postfix){

   char ch;
   int i = 0,operand1,operand2;

   while( (ch = postfix[i++]) != '\0') { 
   // while dongusu, postfix ifadeyi eleman eleman okur.
   // Her bir karakteri (sembolu) okurken, karakterin operand mi yoksa operator mu oldugunu kontrol eder.
   // isdigit() bir standart C kutuphanesi fonksiyonudur ve hazir olarak sunulmustur. 
   // Bu fonksiyon, bir karakterin sayisal bir karakter olup olmadigini kontrol eder.
   // isdigit() fonksiyonu, bir karakterin '0' ile '9' arasýnda olup olmadigini kontrol eder. 
   // Eger kontrol edilen karakter '0' ile '9' arasinda bir rakam ise, isdigit() fonksiyonu 0 disi bir deger dondurur; aksi halde 0 dondurur.
   // ch - '0' islemi, bir karakterin gercek sayisal degerini elde etmek icin kullanilir.
   // Ornegin, '5' karakteri icin, '5' - '0' ifadesi 5'e esit olur, 
   // cunku '5' karakterinin ASCII degeri 53 ve '0' karakterinin ASCII deðeri 48'dir, bu fark da gercek sayisal deger olan 5'e denk gelir. 
     
	  if(isdigit(ch)) { // Eger karakter bir operand ise 
	     push_int(ch-'0');  // Karakterin sayisal degeri, ASCII tablosunda bir sayi karakteri olarak saklanir. 
		 // Bu nedenle, ch - '0' islemi ile gercek sayisal degeri elde eder ve bu degeri push_int fonksiyonuyla yigina ekler.
		 
      } else { // Eger karakter bir operator ise 
         // Yigindan iki operand cikarilir
         operand2 = pop_int();
         operand1 = pop_int();

         switch(ch) { // Cikarilan iki operand ile islem yapmak icin switch-case yapisi icinde operatore gore islem yapilir (toplama, cikarma, carpma, bolme).
            case '+':
               push_int(operand1+operand2); // Islem sonucu elde edilen deger, tekrar yigina (push_int) eklenir.
               break;
            case '-':
               push_int(operand1-operand2);
               break;
            case '*':
               push_int(operand1*operand2);
               break;
            case '/':
               push_int(operand1/operand2);
               break;
         }
      }
   }

   return stack_int[top_int];
   // Tum postfix ifade elemanlari islendikten sonra, yigindaki son deger (stack_int[top_int]) hesaplamanin sonucunu temsil eder. 
   // Bu deger return ile geri dondurulur.
}






void main() {
   char infix[25] = "2*(2+3)",postfix[25];
   convert(infix,postfix);

   printf("Infix expression is: %s\n" , infix);
   printf("Postfix expression is: %s\n" , postfix);
   printf("Evaluated expression is: %d\n" , evaluate(postfix));
}
