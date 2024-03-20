// Header Program
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

// Struct data motor
struct Motor {
	int no_seri;
	string merk;
	string tipe;
};

// Struct node 
struct Node {
	Motor mtr;
  	Node *left;
  	Node *right;
  	int height ;
};

// fungsi memberikan maksimal 2 integer
int max( int a , int b)
{
	return (a>b)?a:b ;
}

// fungsi untuk mendapatkan ketinggian pohon
int height(struct Node *N)
{
	if(N==NULL)
		return 0 ;
	return N->height ;
}

// Fungsi membuat node baru
Node *createNode(Motor data) {
  	Node *node = new Node();
  	node->mtr = data;
  	node->height = 1 ;
  	node->left = NULL;
  	node->right = NULL;
  	return node;
}

// AVL

// Fungsi Memutar sub-tree ke kanan yang berakar dengan x
struct Node *rightrotate(struct Node *y)
{
	struct Node *x = y->left ;
	struct Node *z = x->right ;
	
	x->right = y ;
	y->left = z ;
	
	x->height = max(height(x->right) , height(x->left)) + 1 ;
	y->height = max(height(y->right) , height(y->left)) + 1 ;
	
	return x ;
}

// Fungsi Memutar sub-tree ke kiri yang berakar dengan x
struct Node *leftrotate(struct Node *y)
{
	struct Node *x = y->right ;
	struct Node *z = x->left ;
	
	x->left = y ;
	y->right = z ;
	
	x->height = max(height(x->right) , height(x->left)) + 1 ;
	y->height = max(height(y->right) , height(y->left)) + 1 ;
	
	return x ;
}

// Mengambil Balance dari struct N
int getBal(struct Node* N)
{
	if(N==NULL)
		return 0 ;
	return (height(N->left) - height(N->right)) ;
}

// Fungsi menambahkan node baru ke AVL
struct Node *insertavl(struct Node *Node , Motor data)
{
	if(Node==NULL)
		return(createNode(data)) ;
		
	if(data.no_seri < Node->mtr.no_seri)
		Node->left = insertavl(Node->left,data) ;
	else if(data.no_seri > Node->mtr.no_seri)
		Node->right = insertavl(Node->right,data) ;
	else return Node ;
	
	// Memperbarui ketinggian simpul
	Node->height = 1 + max(height(Node->left) , height(Node->right)) ;
	
	// hitung balance factor untuk menentukan apakah root balance atau unbalance
	int balance =  getBal(Node) ;
	
	//Jika tidak balance, return hasil rotation
	// kasus 1: left left
	if(balance>1 && data.no_seri < Node->left->mtr.no_seri)
		return rightrotate(Node) ;
	
	// kasus 2: right right
	if(balance<-1 && data.no_seri> Node->right->mtr.no_seri)
		return leftrotate(Node) ;
		
	// kasus 3: left right
	if(balance>1 && data.no_seri > Node->left->mtr.no_seri)
	{
		Node->left = leftrotate(Node->left) ;
		return rightrotate(Node) ;
	}
	
	// kasus 4: right left 
	if(balance<-1 && data.no_seri<Node->right->mtr.no_seri)
	{
		Node->right = rightrotate(Node->right) ;
		return leftrotate(Node) ;
	}
	
	return Node ;
}

// Delete AVL
Node *delete_node(struct Node *root, int deletedData)
{
	if(root==NULL){
		cout << "Data Tidak Ditemukan \n";
		return root;
	}
	struct Node *cursor;
	if(deletedData > root->mtr.no_seri){
		root->right = delete_node(root->right, deletedData);
		cout << "Data berhasil dihapus \n";
	}
	else if(deletedData < root->mtr.no_seri){
		root->left = delete_node(root->left, deletedData);
		cout << "Data berhasil dihapus \n";
	}
	else
	{
		//1 child
		if(root->left == NULL)
		{
			cursor = root->right;
			free(root);
			root = cursor;
		}
		else if(root->right == NULL)
		{
			cursor = root->left;
			free(root);
			root = cursor;
		}
		
		//2 child
		else
		{
			cursor = root->right;
			while(cursor->left != NULL)
			{
				cursor = cursor->left;
			}
			root->mtr.no_seri = cursor->mtr.no_seri;
			root->right = delete_node(root->right, cursor->mtr.no_seri);
		}
	}
	
	//Jika setelah dilakukan delete, tree kosong maka return root
	if (root == NULL)
		return root;
		
	//2. update height dari node
	root->height = 1 + max(height(root->left), height(root->right));
	
	//3. hitung balance factor untuk menentukan apakah root balance atau unbalance
	int balance = getBal(root);
	
	//Jika tidak balance, return hasil rotation
	// kasus 1: left left
	if(balance > 1 && getBal(root->left) >= 0)
		return rightrotate(root);
		
	// kasus 2: right right
	if(balance < -1 && getBal(root->right) <= 0)
		return leftrotate(root);
	
	// kasus 3: right left
	if(balance < -1 && getBal(root->left) > 0)
	{
		root->right = rightrotate(root->left);
		return leftrotate(root);
	}
	// kasus 4: left right
	if(balance > 1 && getBal(root->left) < 0)
	{
		root->left = rightrotate(root->right);
		return rightrotate(root);
	}
	
	return root;
}

//BST
// Fungsi menambahkan node baru ke BST
void insert(Node *&root, Motor data) {
  	if (root == NULL) {
    root = createNode(data);
    return;
  }

  	if (data.no_seri < root->mtr.no_seri) {
    insert(root->left, data);
  } else {
    insert(root->right, data);
  }
}

// Fungsi mencetak data node  (inorder)
void inorder(Node *root) 
{
  	if (root == NULL) {
    return;
    }

  	inorder(root->left);

    // Mencetak data dari root
  	cout << "No Seri: " << root->mtr.no_seri << endl;
  	cout << "Merk Motor: " << root->mtr.merk << endl;
  	cout << "Tipe Motor: " << root->mtr.tipe << endl;

  	inorder(root->right);
}

// Fungsi menghapus data BST
Node *deleteNode(Node *root, int no_seri) {
  	// Jika root masih kosong, tidak ada data yang bisa dihapus
  	if (root == NULL) {
  	cout << "Data Tidak Ditemukan \n";
    return NULL;
 	}

// Jika no seri yang dicari lebih kecil root, cari di subtree kiri
  	if (no_seri < root->mtr.no_seri) {
    root->left = deleteNode(root->left, no_seri);
    cout << "Data berhasil dihapus \n";
  	} else if (no_seri > root->mtr.no_seri) {
    root->right = deleteNode(root->right, no_seri);
    cout << "Data berhasil dihapus \n";
  	} else {

    // Jika root satu subtree atau tidak memiliki subtree sama sekali
    if (root->left == NULL) {
    Node *temp = root->right;
    delete root;
    return temp;
    } else if (root->right == NULL) {
    Node *temp = root->left;
    delete root;
    return temp;
    } else {
    // Jika root terdapat subtree, cari node terkecil di subtree kanan
    Node *temp = root->right;
    while (temp->left != NULL) {
	temp = temp->left;}
	// Salin data dari node terkecil ke root
  	root->mtr = temp->mtr;

  	// Hapus node terkecil di subtree kanan
  	root->right = deleteNode(root->right, temp->mtr.no_seri);
}}
return root;
}

// Fungsi mencari data Motor
Node *search(Node *root, int no_seri) {
// Jika root masih kosong atau no seri yang dicari sama dengan no seri dari root, kembalikan pointer ke root
if (root == NULL || no_seri == root->mtr.no_seri) {
return root;
}

// cari di subtree kiri
if (no_seri < root->mtr.no_seri) {
return search(root->left, no_seri);
} else {
//cari di subtree kanan
return search(root->right, no_seri);
	}
}

int main() {
  // Membuat root
  	Node *root = NULL;

  // Variabel menyimpan data Motor
  	Motor Motor;
  	int ans, order, input;

while(1)
{
	menu :
		
	system("cls");
    printf("_____________________________________________________________________\n\n");
    printf("\t\t  -- SELAMAT DATANG DI DEALER XYZ --\n\n");
    printf("\t\t\t Spesialis Motor Dunia\n");
    printf("_____________________________________________________________________\n\n");

	cout << "Pilihan Menu : \n";
  	cout << "==================================\n";
  	cout << "1. Insert Data \n";
  	cout << "2. Delete Data \n";
  	cout << "3. Display Data \n";
  	cout << "4. Find Data\n";
  	cout << "5. Exit\n";
  	cout << "==================================\n";
  	cout << "Masukkan Pilihan : ";
	cin>>ans;
	
	if(ans==1)
	{
		system ("cls");
  		cout<<"//Menu Insert"<<endl;
		cout<<"1. Insert (BST)"<<endl;
		cout<<"2. Insert (AVL)"<<endl;
		cout<<"3. Kembali"<<endl;
		cout << "Masukkan Pilihan : ";
		cin >> order;
		
		if(order==1){
			cout << "Masukkan No Seri Motor: ";
  			cin >> Motor.no_seri;
  			cin.ignore();
  			cout << "Masukkan Merk Motor: ";
  			getline(cin, Motor.merk);
  			cout << "Masukkan Tipe Motor: ";
  			getline(cin, Motor.tipe);
  			// Menambahkan data Motor ke BST
    		insert(root, Motor);
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	  		goto menu;
		}
		if(order==2)
		{
			cout << "Masukkan No Seri Motor: ";
  			cin >> Motor.no_seri;
  			cin.ignore();
  			cout << "Masukkan Merk Motor: ";
  			getline(cin, Motor.merk);
  			cout << "Masukkan Tipe Motor: ";
  			getline(cin, Motor.tipe);
  			// Menambahkan data Motor ke AVL
    		root = insertavl(root, Motor) ;
    		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	  		goto menu;
		}
		if(order==3)
		{
			goto menu;
		}
		
	}
	if(ans==2)
	{
		system ("cls");
  		cout<<"//Menu Delete"<<endl;
		cout<<"1. Delete (BST)"<<endl;
		cout<<"2. Delete (AVL)"<<endl;
		cout<<"3. Kembali"<<endl;
		cout << "Masukkan Pilihan : ";
		cin >> input;
		
		if(input==1){
			system ("cls");
	  		int no_seriHapus;
			cout << "Masukkan No Seri Motor yang ingin dihapus: ";
			cin >> no_seriHapus;
			// Menghapus data Motor dari BST
			root = deleteNode(root, no_seriHapus);
			getch();
			goto menu;
		}
		if(input==2)
		{
			system ("cls");
	  		int no_seriHapus;
			cout << "Masukkan No Seri Motor yang ingin dihapus: ";
			cin >> no_seriHapus;
			// Menghapus data Motor dari AVL
			root = delete_node(root, no_seriHapus);
			getch();
			goto menu;
		}
		if(input==3)
		{
			goto menu;
		}	
	}
	if(ans==3)
	{
		// Mencetak data Motor secara inorder
	  	system ("cls");
		inorder(root);
		getch();
		goto menu;
	}
	if(ans==4)
	{
		// Variabel untuk menyimpan no seri Motor yang ingin dicari
	  	system ("cls");
		int no_seriCari;
		cout << "Masukkan No Seri Motor yang ingin dicari: ";
		cin >> no_seriCari;

		// Mencari data Motor
		Node *node = search(root, no_seriCari);

		// Menampilkan data Motor
		if (node != NULL) {
		cout << "No Seri Motor: " << node->mtr.no_seri << endl;
		cout << "Merk Motor: " << node->mtr.merk << endl;
		cout << "Tipe Motor: " << node->mtr.tipe << endl;		
		
		} else {
		cout << "Data Motor tidak ditemukan!" << endl;
		}
		getch();
		goto menu;
	}
	
	// fungsi exit 
	if(ans==5){
		exit(0);
        break;
	}
}

return 0;
}
