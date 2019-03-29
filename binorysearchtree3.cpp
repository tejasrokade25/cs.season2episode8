/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
//BST
#include<iostream>
using namespace std;

//The node class
class Node{
	public:
	int data;
	Node* l = NULL;
	Node* r = NULL;
	Node* p = NULL;
	
	//Constructor
	Node(int val){
		data = val;
	}
};

//The tree class
class BST{
	public:
	Node* root;
	int count = 0;
	//Constructor
	BST(){
		root = NULL;
	}

	
	//Insert
	void insert(int value){
		//If tree is null direct enter
		if(root==NULL){
			root = new Node(value);
			count++;
			return;
		}
		insertHelper(root, value);
		count++;
	}

	void insertHelper(Node* curr, int value){
		//move accordingly 
		if(curr->data > value){
			//If the next position is NULL direct enter
			if(curr->l==NULL){
				curr->l = new Node(value);
				curr->l->p = curr;
				return;
			}
			//else go for recursion
			else{insertHelper(curr->l, value);}
		}
		else{
			//If the next position is NULL direct enter
			if(curr->r==NULL){
				curr->r = new Node(value);
				curr->r->p = curr;
				return;
			}
			//else go for recursion
		 	else {insertHelper(curr->r, value);}
		}
		
	}

	void display(){
		display2(root);
		cout<<"\b "<<endl;
	}
	
	//This is display
	void display2(Node* curr){
		//Base condition
		if(curr == NULL){return;}
		//display left
		display2(curr->l);
		//display current
		cout << curr->data << ",";
		//display right
		display2(curr->r);
	}




	//Search
	Node* search(int val){
		return search2(val, root);
	}

	Node* search2(int val,Node* curr){
		//If tree is empty 
		if(curr == NULL || curr->data == val){return curr;}
		else if(curr->data > val){return search2(val, curr->l);}
		else{return search2(val, curr->r);}
	}

	//Find min.
	Node* fmin(int val){
		Node* curr = search(val);
		if(root==NULL||curr==NULL){return NULL;}
		return fmin2(val,curr);
	}

	Node* fmin2(int val, Node* curr){
		if(curr->l==NULL){return curr;}
		else{fmin2(val, curr->l);}
	}
	
	//Count
	int Count(){
		return count;
	}

	//Delete 
	void Delete(int val){
		Node* curr = search(val);
		//If node doesn't exist
		if(curr==NULL){
			cout << "This value doesn't exist in the tree.\nTry again!"<<endl;
		}
		else{
			count--;
			//If it has one kid
			if(curr->l&&curr->r==NULL||curr->l==NULL&&curr->r){
				//If left child exist
				if(curr->l&&curr->r==NULL){
				Node* temp = curr->l;
					//if current is root
					if(curr==root){root=temp;}
					else{
						//Wether curr is left child or right one
						if((curr->data)<(curr->p->data)){
							curr->p->l=temp;}

						else{curr->p->r=temp;}
					}
				temp->p=curr->p;
				}
				//If right child exist
				else{
					Node* temp = curr->r;
					//if current is root
					if(curr==root){root=temp;}
					else{
						//Wether curr is left child or right one
						if((curr->data)<(curr->p->data)){
							curr->p->l=temp;}
						else{curr->p->r=temp;}
					}
				temp->p=curr->p;
				}		
				delete curr;
				return;
			}
			//If it has 2 children
			if(curr->l&&curr->r){
				//Go for inorder succesor
				Node* temp = fmin(curr->r->data);
				curr->data = temp->data;
				
			
				if(temp->r){
					temp->p->l=temp->r;
					temp->r->p=temp->p;
				}
				else{
					temp->p->l=NULL;
				}
				delete temp;
				return;
			}
			//If it is impotent
			if(curr->l==NULL&&curr->r==NULL){
				//if current is root
				if(curr==root){root=NULL;}
				//removing previous links
				if((curr->data)<(curr->p->data)){
					curr->p->l=NULL;
				}
				else{curr->p->r=NULL;}
				delete curr;
			}
		}
	}

	//The function to print all values in between the range 
	void printrange(int low,int high){	
		printrange2(root,low,high);
	}
	void printrange2(Node* curr,int low,int high){
		//Base condition
		if(curr == NULL){return;}
		//display left
		printrange2(curr->l,low,high);
		//display current if within range
		if((curr->data)>=low && (curr->data)<=high){cout << curr->data << ",";}
		//display right
		printrange2(curr->r,low,high);
	}

	//The function to count nodes with values within the range
	int rangecount(int low,int high){	
		return rangecount2(root,low,high);
	}

	int rangecount2(Node* curr,int low,int high){
		//Base case
		if(!curr){return 0;}
		//Special Optional case for improving efficiency
		if(curr->data == high && curr->data == low){return 1;}

		//If current node is in range, then include it in count and recur for left and right 		
		if((curr->data)<=high && (curr->data)>=low)
			{return 1 + rangecount2(curr->l,low,high) + rangecount2(curr->r,low,high);}

		//If current node is smaller than low, then recur for right child
		else if((curr->data)<low){return rangecount2(curr->r,low,high);}

		// Else recur for left child
		else{return rangecount2(curr->l,low,high);}
	}

	//The function for height of the tree
	int height(){
		return height2(root);
	}

	int height2(Node* curr){
		//Base case
		if(!curr){return 0;}

		//Create two parameters for l and r
		int lh = height2(curr->l);
		int rh = height2(curr->r);

		//compare the levels from left and right subtree and use larger one
		if(lh>rh){return (lh+1);}
		else {return (rh+1);}
	}
};


int main(){
	//Creating a tree
	BST b1;

	//Inserting in tree and checking with display
	b1.insert(3);
	b1.insert(6);
	b1.insert(2);
	b1.insert(5);
	b1.insert(4);
	b1.insert(1);
	b1.insert(9);
	b1.insert(7);
	b1.insert(8);
	b1.display();

	//Now the search function
	Node* find = b1.search(2);
	if (find!=NULL){cout << find->data << endl;}
	else{cout << "The number is not there in the tree" << endl;} 
	
	//How do you find the min? well look no more :-p
	Node* p = b1.fmin(6);
	cout << p-> data << endl;

	//Let's count
	int r = b1.Count();
	cout << "No of nodes = " << r << endl;
	b1.display();

	//Showing off my delete function
	b1.Delete(3);
	b1.display();

	//Ahhh the range search (my version is split into 2 parts)
	cout << "Now comes range search."<<endl;
	cout << "Give the ranges."<<endl;
	int x,y;
	cin >> x >> y;
	cout << "Items in between the range:-"<<endl;
	b1.printrange(x,y);
	cout << endl <<"Number of items in the range = " << b1.rangecount(x,y) <<endl;
	cout << "range search over" << endl;

	//Finally Mr.Tree your height.
	cout << "The height of tree = " << b1.height() << endl;
	
return 0;
}
