/*
Ikili arama agaci (Binary Search Tree):
Sol alt agactaki tum elemanlar kokten daha kucuktur. 
Sað alt agactaki tum elemanlar kokten buyuk veya koke esittir.
Her alt agacin kendisi ikili bir arama agacidir
Bu program, bir Binary Search Tree (BST) veri yapisini olusturmak icin C dilinde yazilmistir. 
BST, verileri belirli bir duzende saklayan ve bu verilere hizli erisim saglayan bir veri yapisidir.
*/

#include <stdbool.h>

typedef struct node
{ // Bu struct, bir Binary Search Tree yapisinin dugumlerini temsil etmek icin kullanilir.
	void* dataPtr; // Bu, dugumun tasidigi veriye isaret eden bir void pointerdir.
	struct node* left; // Bu, dugumun sol alt dugumune isaret eden bir pointerdir.
	struct node* right; // Bu ise dugumun sag alt dugumune isaret eden bir pointerdir. 
} NODE;



typedef struct
{ // Bu struct, bir Binary Search Tree veri yapisinin genel ozelliklerini ve bilgilerini saklamak icin kullanilir.
	int count; // BST'deki toplam dugum sayisini tutan bir tamsayidir.
	int (*compare) (void* argu1, void* argu2); 
	// BST'nin dugumlerini siralamak icin kullanýlan bu fonksiyon, iki void pointer alir ve bu verileri karsilastirarak siralama kriterini belirler. 
	// Bu fonksiyon, BST'nin hangi dugumu nereye yerlestirecegini belirlemede kullanilir.
	NODE* root; //  BST'nin kok dugumune isaret eden bir pointerdir. 
} BST_TREE;


    // Fonksiyon prototipleri
	BST_TREE* BST_Create(int (*compare) (void* argu1, void* argu2));
	BST_TREE* BST_Destroy (BST_TREE* tree);
	bool BST_Insert (BST_TREE* tree, void* dataPtr);
	bool BST_Delete (BST_TREE* tree, void* dltKey);
	void* BST_Retrieve (BST_TREE* tree, void* keyPtr);
	void BST_Traverse (BST_TREE* tree, void (*process)(void* dataPtr));
	bool BST_Empty (BST_TREE* tree);
	bool BST_Full (BST_TREE* tree);
	int BST_Count (BST_TREE* tree);
	static NODE* _insert (BST_TREE* tree, NODE* root,NODE* newPtr); 
	static NODE* _delete (BST_TREE* tree, NODE* root,void* dataPtr, bool* success);
	static void* _retrieve(BST_TREE* tree, void* dataPtr, NODE* root);
	static void _traverse (NODE* root, void (*process) (void* dataPtr));
	static void _destroy (NODE* root);




#include <stdlib.h>

/* 
Binary Search Tree olusturmak icin kullanilan fonksiyon
*/
BST_TREE* BST_Create(int (*compare) (void* argu1, void* argu2)){

	BST_TREE* tree; // Bellekten bir BST_TREE yapisi icin hafizada yer ayirilmasini saglar ve bu yapýiya isaret eden tree pointerini olusturur
	 
	tree = (BST_TREE*) malloc (sizeof (BST_TREE)); // malloc, BST_TREE yapisinin boyutu kadar bellekte yer ayirir ve bu iþaretçiyi tree pointerina atar.
	if (tree){ // Eger bellek basariyla ayrildiysa (yani malloc basarili olduysa), tree pointerinn alanlari baslatilir
	 tree->root = NULL; // root (kok dugum pointeri) NULL olarak atanir cunku henuz bir agac olusturulmamistir.
	 tree->count = 0; // count, baslangicta 0 olarak ayarlanir cunku henuz agac bostur.
	 tree->compare = compare; // compare alani, parametre olarak gelen compare fonksiyonu isaretcisine atanir.
	} 
	return tree;
} 








/* 
Bu fonksiyon, bir degeri Binary Search Tree yapisina eklemek icin kullanilir.
*/
bool BST_Insert (BST_TREE* tree, void* dataPtr){
	
	NODE* newPtr;
	newPtr = (NODE*)malloc(sizeof(NODE)); // Bellekten yeni bir NODE yapisi icin hafizada yer ayirilmasini saglar ve bu yapinin bir isaretcisi olan newPtr'ye atar. 
	
	if (!newPtr)
		return false; // Eger bellek ayrilmasi basarisiz olursa (malloc islemi basarisiz olursa), yetersiz bellek nedeniyle false dondurur ve islemi sonlandirir.
		
	newPtr->right = NULL; // Yeni dugumun right ve left pointerlari baslangicta NULL olarak atanir cunku yeni dugum henuz agaca eklenmedi ve hicbir alt dugume sahip degil.
	newPtr->left = NULL;
	newPtr->dataPtr = dataPtr;
	 
	if (tree->count == 0) // Eger agac bossa, yeni dugum agacin koku olarak atanir
	// Aksi takdirde, _insert fonksiyonu kullanilarak agaca yeni dugum eklenir.
		tree->root = newPtr;
	else
		_insert(tree, tree->root, newPtr);
	 
	(tree->count)++; // Dugum eklendikten sonra, agactaki dugum sayisi arttirilir 
	return true; // islem basariyla tamamlandigi icin true dondurulur.
} 







/*
BST_Insert fonksiyonu, yeni dugumu olusturduktan sonra _insert fonksiyonunu cagirarak BST'ye eklemek icin kullanilir. 
_insert fonksiyonu, ozyinelemeli bir yaklasim kullanarak BST'ye yeni bir dugum eklemek icin kullanilir.
*/
NODE* _insert (BST_TREE* tree, NODE* root, NODE* newPtr){
	if (!root) // Eger root dugumu bossa (NULL ise), yani agacta hiç dugum yoksa, yeni dugumu (newPtr) dondurur. 
	// Bu, agacin bu kismina yeni bir dugum eklemenin baslangicidir.
		return newPtr;
		
	if (tree->compare(newPtr->dataPtr,root->dataPtr) < 0){
		root->left = _insert(tree, root->left, newPtr);
		return root; 
// Eger root dugumu bos degilse, karsilastirma yapilir.
// Yeni dugumun verisi, mevcut dugumun verisinden kucukse, 
// sol alt agaca ozyinelemeli olarak _insert fonksiyonu cagrilir ve bu islem sonucu donen dugum, mevcut dugumun sol alt dugumune atanir. 
// Daha sonra, mevcut dugumun kendisi root olarak dondurulur.
 	}
 	
	else {
 		root->right = _insert(tree, root->right, newPtr);
 		return root;
// yeni dugumun verisi mevcut dugumun verisinden buyukse veya esitse,
// sag alt agaca ozyinelemeli olarak _insert fonksiyonu çaðrýlýr ve bu islem sonucu dönen dugum, mevcut dugumun sag alt dugumune atanir. 
// Daha sonra, mevcut dugumun kendisi root olarak dondurulur.
 } 
	return root;
// Fonksiyonun en sonunda return root; ifadesi kullanilarak mevcut dugum dondurulur. Bu, ozyinelemeli islemin bittigi yerdir.
} 









/* 
Bu fonksiyon, verilen key degerine sahip bir dugumu Binary Search Tree yapisidan silmeyi amaclar.
*/
bool BST_Delete (BST_TREE* tree, void* dltKey){
	bool success;
	NODE* newRoot;
	newRoot = _delete (tree, tree->root, dltKey, &success); // _delete fonksiyonundan gelen sonuc, newRoot isaretcisine atanir.
		
	if (success){ // success degiskeni, dugumun basariyla silinip silinmedigini belirtir.
	// Eger success true ise:
		tree->root = newRoot; // newRoot, silme isleminden sonra degisebilecek olan agacin kok dugumunu temsil eder. 
		// Bu nedenle tree->root isaretcisi newRoot ile guncellenir. 
		// Yani, eger silme islemi sonucunda agacin kok dugumu degistiyse, tree->root isaretcisi bu yeni kok dugumu isaret edecek sekilde guncellenir.
		(tree->count)--; // tree->count azaltilir cunku bir dugum silindi.
		
		if (tree->count == 0) // Eger agac tamamen bosaldiysa, tree->root NULL olarak atanir.
			tree->root = NULL;
 } 
	return success; // Son olarak, islem basarili olduysa success degeri dondurulur.
} 











/* 
Bu fonksiyon, BST'den belirli bir anahtar degerine sahip dugumu silmeyi amaclar. 
Fonksiyon, ozyinelemei bir yaklasim kullanarak bu islemi gerceklestirir.
*/
NODE* _delete (BST_TREE* tree, NODE* root, void* dataPtr, bool* success){
	NODE* dltPtr;
	NODE* exchPtr;
	NODE* newRoot;
	void* holdPtr;

	if (!root){ // agacta dugum yoksa, silme islemi basarisiz oldugu icin success degiskeni false olarak ayarlanir ve NULL dondurulur.
		*success = false;
		return NULL;
	} 
	if (tree->compare(dataPtr, root->dataPtr) < 0) // silinecek dugumun verisi, mevcut root dugumun verisinden kucukse, sol alt agaca ozyinelemeli olarak _delete fonksiyonu cagrilir.
		root->left = _delete (tree, root->left,dataPtr, success);
	else if (tree->compare(dataPtr, root->dataPtr) > 0) // silinecek dugumun verisi, mevcut root dugumun verisinden buyukse, sag alt agaca ozyinelemeli olarak _delete fonksiyonu cagrilir.
		root->right = _delete (tree, root->right, dataPtr, success);
		
	else{ // silinecek dugum mevcut dugumse (dataPtr mevcut root->dataPtr'ye esitse)
		dltPtr = root; // dltPtr isaretcisi, silinecek dugumu isaret eder.
		if (!root->left){ // Eðer mevcut dugumun sol alt dugumu yoksa, silinecek dugumun yerine sag alt dugumu geçer ve bellekten silinir. 
		// success degiskeni true olarak ayarlanir ve yeni kok dugum dondurulur.
			free (root->dataPtr); 
			newRoot = root->right;
			free (dltPtr); 
			*success = true;
			return newRoot; 
 			} 
		else if (!root->right){ // mevcut dugumun sag alt dugumu yoksa, silinecek dugumun yerine sol alt dugumu geçer ve bellekten silinir. 
			// success degiskeni true olarak ayarlanir ve yeni kok dugum dondurulur.
 				newRoot = root->left;
 				free (dltPtr);
 				*success = true;
 				return newRoot;} 
 			else{ // mevcut dugumun hem sol hem de sag alt duumleri varsa, silinecek dugumun yerine gececek dugum bulunur. 
			 // Bu, sol alt agactaki en sag alt dugume (exchPtr) ulasarak yapilir. 
				exchPtr = root->left;
				while (exchPtr->right)
					exchPtr = exchPtr->right;

 				holdPtr = root->dataPtr; // Veri degis tokusu yapilir. Mevcut dugumun verisi (root->dataPtr) ile exchPtr'nin verisi degistirilir. 
				 // Bu, silinecek dugumun yerine gececek uygun dugumu belirlemek icindir.
				root->dataPtr = exchPtr->dataPtr;
				exchPtr->dataPtr = holdPtr;
				root->left = _delete (tree, root->left,exchPtr->dataPtr, success);
				// Ozyinelemeli olarak sol alt agacta bu kez exchPtr->dataPtr'ye sahip dugum silinir. 
				// Yani, silinecek dugum yerine, sol alt agactaki en sagdaki dugum gecirilir ve sonrasinda bu dugum silinir.
 				} 
 		} 
	return root; 
}	






/* 
Bu fonksiyon, Binary Search Tree yapisinda belirli bir anahtar degere sahip olan dugumun verisini aramak icin kullanilir.
*/
void* BST_Retrieve (BST_TREE* tree, void* keyPtr){
	if (tree->root) // Eger agacin koku NULL degilse, _retrieve yardimci fonksiyonunu cagirarak arama islemini gerceklestirir.
		return _retrieve (tree, keyPtr, tree->root);
	else // Eger agacin koku NULL ise (yani, agac bossa), aranan dugumun olmadigi anlamýna gelir ve bu durumda NULL dondurulur.
		return NULL;
}





/* 
Bu fonksiyon Binary Search Tree yapisinda belirli bir anahtar degere sahip olan dugumun verisini aramak icin kullanilir. 
Bu fonksiyon ozyinelemeli bir yapi kullanir.
*/
void* _retrieve (BST_TREE* tree, void* dataPtr, NODE* root){
	if (root){ // Eger root dugumu NULL degilse (yani, agacta dugum varsa)
		
 		if (tree->compare(dataPtr, root->dataPtr) < 0) // Eger aranan dataPtr degeri, root->dataPtr'den kucukse, sol alt agaca ozyinelemeli olarak _retrieve fonksiyonu cagrilir.
 			return _retrieve(tree, dataPtr, root->left);
 			
 		else if (tree->compare(dataPtr, root->dataPtr) > 0) // Eger aranan dataPtr degeri, root->dataPtr'den buyukse, sag alt agaca ozyinelemeli olarak _retrieve fonksiyonu cagrilir.
 			return _retrieve(tree, dataPtr, root->right);
 			
 		else // Eger aranan dataPtr degeri, root->dataPtr'ye esitse, bulunan dugumun veri isaretcisi dondurulur.
 			return root->dataPtr;
 } 
	else // Eger agacta dugum yoksa, aranan dugumun bulunmadigi anlamina gelir ve NULL degeri dondurulur.
 		return NULL;
} 








/* 
Bu fonksiyon, Binary Search Tree yapisindaki dugumleri belirli bir isleme tabi tutmak icin kullanilir. 
*/
void BST_Traverse (BST_TREE* tree,void (*process) (void* dataPtr)){	
	_traverse (tree->root, process);
	// _traverse yardimci fonksiyonunu cagirir ve agacin kok dugumunu belirtilen process ile birlikte gonderir.
	// _traverse fonksiyonu, ozyinelemeli bir yapi kullanarak agacin dugumlerini isler. 
	// Bu islem sirasinda, once sol alt agactaki dugumler islenir, sonra kok dugumde belirtilen islem yapilir ve en son olarak da sag alt agactaki dugumler islenir.
    // Islem sirasinda her bir dugum, belirtilen process islevine tabi tutulur. 
   // Bu, dugumun verisini islemek icin belirtilen bir fonksiyon olabilir. 
   // Ornegin, dugumlerin verilerini yazdirmak, toplamak veya farklý bir islem yapmak icin kullanýlabilir.
	return;
} 







/* 
Bu _traverse fonksiyonu, ozyinelemeli bir yapi kullanarak Binary Search Tree yapisindaki dugumleri belirtilen isleme tabi tutmak icin kullanilir.
*/
void _traverse (NODE* root, void (*process) (void* dataPtr)){
	
if (root){ // Eger root dugumu NULL degilse (yani agacta dugum varsa)
	_traverse (root->left, process); // Fonksiyon ozyinelemeli olarak sol alt agaca dogru ilerler ve _traverse fonksiyonunu bu dugum uzerinde calistirir.
	process (root->dataPtr); // Ardindan, dugumde belirtilen process uygulanir. Bu, dugumun verisini islemek icin belirtilen bir fonksiyon olabilir.
	_traverse (root->right, process); // Son olarak, sag alt agaca ozyinelemeli olarak _traverse fonksiyonu cagrilir.
} 
return; 
} 






/* 
Bu fonksiyon, bir Binary Search Tree yapisinin bos olup olmadigini kontrol etmek icin kullanilir.
*/
bool BST_Empty (BST_TREE* tree){
	return (tree->count == 0);	
// BST_Empty fonksiyonu, verilen BST agacinin dugum sayisini kontrol eder.
// Dugum sayisi 0 ise, bu durum BST yapisinin bos oldugunu ifade eder.
// Eger dugum sayisi 0 ise, fonksiyon true degerini dondurur, aksi takdirde false degerini dondurur.
} 








/* 
Bu fonksiyon, Binary Search Tree yapisinin dolu olup olmadigini kontrol etmek icin kullanilir.
*/
bool BST_Full (BST_TREE* tree){
	
	NODE* newPtr;
	newPtr = (NODE*)malloc(sizeof (*(tree->root))); // Yeni bir dugum olusturmak icin bellekten bir alan ayrilir. 
	// Malloc ile yer ayirma islemi, agacin bellekte yeni bir dugum icin yer ayirmaya hazir olup olmadigini belirlemek icin yapilir. 
	// Eger bu islem basarili olursa (bellekte yeterli yer varsa), newPtr isaretcisi NULL olmayacaktýr ve false dondurulur. 
	// Bu durumda, agacin dolu olmadigi anlamina gelir.
	
	if (newPtr){ 
	// Eger bellek tahsis islemi basariliysa, agac dolu degildir. 
	// Bu nedenle false degeri dondurulur.
 		free (newPtr);
 		return false;
	} 
	else
		 return true;
   // Eger bellek tahsis islemi basarili degilse, agac doludur.
   // Bu nedenle true degeri dondurulur.
}








/*
Bu fonksiyon, bir Binary Search Tree yapisindaki toplam dugum sayisini dondurmek icin kullanilir.
*/
int BST_Count (BST_TREE* tree){
	return (tree->count);
} 








/* 
Bu fonksiyon, Binary Search Tree yapisini yok etmek ve bu agaca ayrilan bellegi serbest birakmak icin kullanilir.
*/
BST_TREE* BST_Destroy (BST_TREE* tree) {
	
	if (tree) // Eger verilen BST_TREE tipindeki agac gecerli bir agaci temsil ediyorsa (yani, NULL degilse):
		_destroy (tree->root); // _destroy adli yardimci fonksiyon cagrilir ve agacin kok dugumu (tree->root) uzerinde islem yaparak agactaki tum dugumleri siler. 
		// Bu surec, ozyinelemeli bir yapi kullanarak tum dugumleri dolasarak bellegi serbest birakir.
	
	free (tree); // Daha sonra, agaca ayrilan bellek serbest birakilir. free(tree) komutu ile agac yapisinin kendisi bellekten silinir.
	return NULL; // Fonksiyon NULL degerini dondurur, böylece fonksiyon cagrildiginda artýk gecersiz bir agac isaret edilmez.
} 







/*
Bu _destroy fonksiyonu, Binary Search Tree yapisindaki dugumleri silmek ve agaca ayrilan bellegi serbest birakmak icin kullanilir. 
Bu islem, ozyinelemeli bir yapi kullanarak agactaki tum dugumleri dolasir ve her dugumu siler.
*/
void _destroy (NODE* root){
	if (root){ // Eger kok dugumu NULL degilse (yani, agacta dugum varsa):
		_destroy (root->left); // Fonksiyon ozyinelemeli olarak sol alt agaca dogru ilerler ve _destroy fonksiyonunu bu dugum uzerinde cagirir.
		free (root->dataPtr); // Daha sonra, dugumun verisini temsil eden bellek serbest birakilir 
		_destroy (root->right); // Sag alt agaca ozyinelemeli olarak _destroy fonksiyonu cagrilir.
		free (root); // Son olarak, bu dugumun kendisi bellekten serbest birakilir 
	} 
return; // Eger kok dugumu NULL ise (yani, agacta dugum yoksa veya islem tamamlandiysa), fonksiyon sonlanir.
} 







// Bu program bir BST olusturur ve yazdirir.
#include <stdio.h>
#include <stdlib.h>

// Prototip tanimlamalari
int compareInt (void* num1, void* num2);
void printBST (void* num1);

int main (void){
	
	BST_TREE* BSTRoot;
	int* dataPtr;
	int dataIn = +1;
	
	
	printf("BST olusturmak icin baslayin\n");
	BSTRoot = BST_Create (compareInt);
// BST_Create fonksiyonu cagrilarak bos bir BST agaci (BSTRoot) olusturulur. 
// Bu agacin siralama islemleri icin compareInt fonksiyonunu kullanacagini belirtmek amaciyla bu fonksiyon bu agacin 
// karsilastirma fonksiyonu olarak atanir.
	
	
	
	// Agac olusturma
	printf("Pozitif tam sayilarin listesini girin;\n");
	printf("Durdurmak icin negatif bir sayi girin.\n");
	do 
	 {
 		printf("Bir numara girin: ");
 		scanf ("%d", &dataIn);
 		if (dataIn > -1){
 			dataPtr = (int*) malloc (sizeof (int)); // Girilen her bir tam sayi icin bellekte yeni bir tamsayi hafizasi ayrilir 
 			if (!dataPtr){
 				printf("Memory Overflow\n"), // Bellekte yer ayrilamazsa, "Memory Overflow" hatasi yazdirilir ve program hata kodu 100 ile birlikte sonlandirilir (exit(100)).
 				exit(100);
 				} 
 			*dataPtr = dataIn; // Yeterli bellek ayrildiysa, kullanicinin girdisi (dataIn) bu hafizaya (dataPtr) atanir
 			BST_Insert (BSTRoot, dataPtr); // Ardindan, bu deger BST agacina eklenir 
 		} 
 	} 
 		while (dataIn > -1); // Kullanýcý negatif bir sayý girdiðinde döngü sonlanýr
 		
printf("\nBST sunlari icerir:\n");
BST_Traverse (BSTRoot, printBST);
// BST agaci olusturulduktan sonra, BST_Traverse fonksiyonu cagrilarak agacta sirali olarak dolasilarak 
// her bir dugum printBST fonksiyonu araciligiyla ekrana yazdirilir.

printf("\nBST'yi sonlandirin\n");
return 0;
} 


/* 
Bu fonksiyon, iki tamsayi degerini karsilastirmak icin kullanilir. 
low (-1), equal (0), veya high (+1) doner
*/
int compareInt (void* num1, void* num2){ // Fonksiyon iki tamsayi degerini temsil eden isaretciler (num1 ve num2) alir.
	
	int key1;
	int key2;
	
	key1 = *(int*)num1;
	key2 = *(int*)num2; // Bu isaretcilerin icerdikleri tamsayi degeerleri (key1 ve key2) okunur.
	
	if (key1 < key2)
	 	return -1;
	if (key1 == key2)
	 	return 0;
	return +1;
} 



/*
Bu fonksiyon, bir tamsayi degerini ekrana yazdirmak icin kullanilir. 
Fonksiyon, void* turunde bir isaretci alir, bu isaretci bir tamsayi degerini gosterir.
*/
void printBST (void* num1)
{
	printf("%4d\n", *(int*)num1); 
	// *(int*)num1 ifadesi ile isaretcinin gosterdigi bellek bolgesindeki tamsayi degeri okunur.
	return;
} 

