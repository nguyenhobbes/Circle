#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

struct Hinhtron
{
	int ma;		
	char ten;	
	int R;		
	int mau;	

	//Khoi tao mac dinh
	Hinhtron() { 
		ma = 1;
		ten = 'A';
		R = 1;
		mau = 1;
	}

	//Khoi tao theo tham so
	Hinhtron(int code, char name, int radius, int color) {
		ma = color; // gan cac tham so vao
		ten = name;
		R = radius;
		mau = color;
	}
	string toString() {
		//tao stringstream
		stringstream builder; 

		// setw() + left de tao va can le trai
		builder << setw(5) << left << ma << setw(3) << left << ten 
			<< setw(5) << left << R << setw(5) << left << mau; 

		//dua stringstream vao chuoi
		string result = builder.str();  

		//tra ve chuoi
		return result;
	}
};

struct Node
{
	Hinhtron Data;
	Node* next;
	Node() {}
	Node(Hinhtron a, Node* N = NULL) {
		Data = a;
		next = N;
	}
	Node* &getNext() {
		return next;
	}
	Hinhtron &getData() {
		return Data;
	}
	void setNext(Node* N = NULL) {
		next = N;
	}
	void setData(Hinhtron a) {
		Data = a;
	}
};

struct Iterator
{
	Node* curr;//con tro tro vao Node hien tai

	Iterator() { curr = NULL; }
	Iterator(Node* p) { curr = p; }
	Node* getcurr() {
		return curr;
	}	
};

struct LinkedList
{
	Node* head, * tail;
	unsigned int num;  //so phan tu hien tai trong list -> size

	//khoi tao mac dinh
	LinkedList() { head = tail = nullptr; num = 0; } 

	//Khoi tao theo so phan tu
	LinkedList(int k, Hinhtron x) {
		head = tail = NULL; num = 0;
		for (int i = 1; i <= k; i++) push_back(x);
	} 

	//con tro tra ve head
	Iterator begin() {
		return head; 
	}

	//con tro tra ve tail
	Iterator end() {
		return NULL;
	}


	unsigned size() { return num; }

	//check List co phan tu hay khong (check list rong)
	bool empty() { return num == 0; } 

	//tra ve Dau danh sach
	Hinhtron& front() { return head->getData(); } 

	//tra ve Cuoi danh sach
	Hinhtron& back() { return tail->getData(); }  

	Iterator insert(Iterator it, Hinhtron& obj) {
		//tao node chi vao dau danh sach
		Node* cur = head;

		//truong hop con tro nam o dau danh sach
		if (it.getcurr() == head) { 
			//ham push_front them vao dau danh sach
			push_front(obj); 

			//tao con tro chi vao head
			Iterator result(head); 

			//tang so phan tu
			num++; 

			//tra ve con tro
			return result; 
		}

		//truong hop con tro nam o cuoi danh sach
		else if (it.getcurr() == tail) { 
			//ham push_back them vao cuoi danh sach
			push_back(obj); 

			//tao con tro chi vao tail
			Iterator result(tail); 

			//tang so phan tu
			num++; 

			//tra ve con tro
			return result;  

		}			
		else {		//truong hop con tro nam giua danh sach	

			//vong lap while dua cur den truoc vi tri can them
			while (cur->getNext() != it.getcurr())  
				cur = cur->getNext();		
			
			//Tao node moi, gan gia tri va gan vao vi tri cur->next
			cur->setNext(new Node(obj, it.getcurr()));	
			
			//tao con tro chi vao vi tri vua them vao
			Iterator result(cur->getNext()); 

			//tang so phan tu
			num++; 

			//tra ve con tro
			return result; 
		}			
	}

	Iterator remove(Iterator it) {
		//tao node chi vao dau danh sach
		Node* cur = head;

		//truong hop con tro nam o dau danh sach
		if (it.getcurr() == head) {
			//tao con tro chi vao head
			Iterator result(head);

			//giam so phan tu
			num--;

			//ham pop_front xoa dau danh sach
			pop_front();

			//tra ve con tro
			return result;
		}	
		//tuong tu nam o dau (nhu tren)
		else if (it.getcurr() == tail) { 			
			Iterator result(tail);
			num--;
			pop_back();
			return result;
		}

		//truong hop con tro chi vao giua danh sach
		else {
			//vong lap while dua cur den truoc vi tri can xoa
			while (cur->getNext() != it.getcurr())
				cur = cur->getNext();

			//tao con tro vao vi tri can xoa
			Iterator result(cur->getNext());

			//lien ket next cua cur hien tai voi next tiep theo
			cur->setNext(it.getcurr()->getNext());	

			//giam so phan tu
			num--;

			//tra ve con tro
			return result;
		}
	
	}
	void push_front(Hinhtron x) {
		//tao head moi lien ket voi head hien tai va co Data la x
		head = new Node(x, head);

		//truong hop danh sach rong
		if (num == 0) tail = head;

		//tang so phan tu
		num++;
	}
	void push_back(Hinhtron x) {
		//truong hop danh sach rong
		//them o dau cung la them o cuoi
		if (num == 0) push_front(x);
		else {
			//tao node moi dung sau Tail
			tail->setNext(new Node(x, NULL));

			//dich chuyen Tail sang node moi tao
			tail = tail->getNext();

			//tang so phan tu
			num++;
		}
	}
	void pop_front() {
		//danh sach rong, khong can xoa
		if (num == 0) return;
		
		//danh sanh 1 phan tu duy nhat
		if (num == 1) {
			//unlink head va tail
			head = tail = NULL;
		}
		else {
			//dich chuyen head sang node tiep theo
			head = head->getNext();
		}

		//giam so phan tu
		num--;
	}
	void pop_back() {
		// tuong tu nhu tren
		if (num == 0) return;
		if (num == 1) { head = tail = NULL; num--; return; }
		
		//tao node p tai head
		Node* p = head;

		//dich chuyen p den truoc tail
		while (p->getNext() != tail) p = p->getNext();
		
		//unlink p voi tail
		p->setNext(NULL);

		//dua p len tail moi
		tail = p;

		//giam so phan tu
		num--;
	}

	void Show() {
		cout << "Danh sach hien tai\n";

		//tao node cur tai head
		Node* cur = head;

		//truong hop danh sach rong
		if (!cur)
		{
			cout << "Danh sach rong!";
		}
		while (cur)
		{	
			//xuat gia tri cur
			cout << cur->Data.toString() << endl;

			//dua cur den cuoi
			cur = cur->getNext();
		}
		cout << endl;
	}
	void Sort() { //ham rut gon cua MergeSort
		MergeSort(&head);
	}
	// Gop 2 list
	Node* MergeSortedList(Node* lst1, Node* lst2)
	{

		Node* result = NULL;

		// Neu 2 list rong
		if (lst1 == NULL)
			return (lst2);
		else if (lst2 == NULL)
			return (lst1);

		// Ham de quy gop 2 list nho
		if (lst1->getData().ma <= lst2->getData().ma) {
			result = lst1;
			result->getNext() = MergeSortedList(lst1->getNext(), lst2);
		}
		else {
			result = lst2;
			result->getNext() = MergeSortedList(lst1, lst2->getNext());
		}
		return result;
	}

	// Chia nho 2 list
	// Neu so phan tu le, phan tu thua vao list 1
	void SplitList(Node* source, Node** front, Node** back)
	{
		Node* ptr1;
		Node* ptr2;
		ptr2 = source;
		ptr1 = source->next;

		while (ptr1 != NULL) {
			ptr1 = ptr1->next;
			if (ptr1 != NULL) {
				ptr2 = ptr2->next;
				ptr1 = ptr1->next;
			}
		}

		*front = source;
		*back = ptr2->next;
		ptr2->next = NULL;
	}


	// Merge Sort
	void MergeSort(Node** thead)
	{
		Node* head = *thead;
		Node* ptr1;
		Node* ptr2;

		//truong hop danh sach rong
		if ((head == NULL) || (head->next == NULL)) {
			return;
		}

		// Chia list
		SplitList(head, &ptr1, &ptr2);

		// Sap xep bang de quy
		MergeSort(&ptr1);
		MergeSort(&ptr2);

		// tra ve list da sap xep
		*thead = MergeSortedList(ptr1, ptr2);
	}
	bool search(int ma) {
		Node* cur = head;
		if (!head)
			return 0;
		bool check = 0;
		while (cur)
		{
			if (cur->getData().ma == ma)
			{
				check = 1;
				break;
			}
			cur = cur->getNext();
		}
		return check;
	}
};

void menu() {
	cout << "Menu\n";
	cout << "1.\tChen vao List (Iterator)\n";
	cout << "2.\tXoa khoi List(Iterator)\n";
	cout << "3.\tBo sung vao cuoi List (Push back)\n";
	cout << "4.\tLoai bo o cuoi List (Pop back)\n";
	cout << "5.\tSap xep List (Merge Sort)\n";
	cout << "6.\tTim kiem phan tu (Search)\n";
	cout << "7.\tIn cac phan tu cua List\n";
	cout << "8.\tXuat file ra Output\n";
	cout << "0.\tKet thuc chuong trinh\n";

}
void outputFile(LinkedList Ht) {
	fstream f;
	f.open("Output.txt", ios::out);
	Node* cur = Ht.head;
	if (!cur)
	{
		f << "Danh sach rong!";
	}
	else
	{
		while (cur)
		{
			f << cur->Data.toString() << endl;
			cur = cur->getNext();
		}
	}
	cout << "Da xuat List vao file 'Output.txt'\n";
 }

int main() {
	Hinhtron temp;
	LinkedList Ht;
	fstream f;
	unsigned int pos;
	f.open("inputHinhtron.txt", ios::in);
	while (!f.eof())
	{
		f >> temp.ma;
		f >> temp.ten;
		f >> temp.R;
		f >> temp.mau;
		Ht.push_back(temp);
	}
	f.close();
	
	cout << "Du lieu da duoc doc vao tu file 'inputHinhtron.txt'\n\n";
	Ht.Show();
	int choose;
	menu();
	cout << "Nhap lua chon: ";
	cin >> choose;
	system("CLS");
	while (choose != 0) {
		switch (choose)
		{
		default:
			break;
		case 1:
			cout << "Nhap vi tri muon chen: ";
			cin >> pos;
			if (pos > Ht.size()) {
				cout << "Vi tri khong hop le!\n";
				break;
			}
			else
			{
				Node* cur = Ht.head;
				for (auto i = 0; i < pos; i++)
				{
					cur = cur->getNext();
				}
				Iterator it(cur);

				cout << "Nhap cac thong so cua hinh tron can them (ma, ten, R, mau)\n";
				cin >> temp.ma;
				cin >> temp.ten;
				cin >> temp.R;
				cin >> temp.mau;
				Iterator result = Ht.insert(it, temp);
				cout << "Con tro hien tai dang chi den: " << result.getcurr()->getData().toString() << endl;
				Ht.Show();
			}
			break;
		case 2:
			cout << "Nhap vi tri muon xoa: ";
			cin >> pos;
			if (pos > Ht.size()) {
				cout << "Vi tri khong hop le!\n";
				break;
			}
			else
			{
				Node* cur2 = Ht.head;
				for (auto i = 0; i < pos; i++)
				{
					cur2 = cur2->getNext();
				}
				Iterator it2(cur2);
				Iterator result2 = Ht.insert(it2, temp);
				cout << "Con tro hien tai dang chi den: " << result2.getcurr()->getData().toString() << endl;
				Ht.Show();
			}
			break;
		case 3:
			cout << "Nhap cac thong so cua hinh tron can them (ma, ten, R, mau)\n";
			cin >> temp.ma;
			cin >> temp.ten;
			cin >> temp.R;
			cin >> temp.mau;
			Ht.push_back(temp);
			Ht.Show();
			break;
		case 4:
			Ht.pop_back();
			Ht.Show();
			break;
		case 5:
			Ht.Sort();
			Ht.Show();
			break;
		case 6: {
			int code;
			cout << "Nhap ma can tim: ";
			cin >> code;
			bool check = Ht.search(code);
			if (check)
			{
				cout << "Ton tai phan tu voi ma: " << code << endl;
			}
			else
			{
				cout << "Khong ton tai phan tu voi ma: " << code << endl;
			}
			break;
		}
		case 7:
			Ht.Show();
			break;
		case 8:
			outputFile(Ht);
			break;

		}
		menu();
		cout << "Nhap lua chon: ";
	
		cin >> choose;
		system("CLS");
	}
	
	return 0;
}

