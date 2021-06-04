/******************************************************************************************************************************
*Student: Mehmet Aysevinç-150110705
*Source name: BinarySearchTree.cpp
*This program creates a binary search tree that stores student information. Program reads the input files and keeps the student
 id, name and surname information in a binary tree.
*Data structures: The program has one data structure which is Student node that forms the binary search tree.
*Global variables: The program has two global variables which are named as root that is the root of the tree and counter that
 counts the number of iteration in search functions to measure the performance.
*******************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <queue>


using namespace std;

struct student {
	char stid[15];
	char name[30];
	char surname[30];
	student *left;
	student *right;
};

typedef student Student;

Student *root = NULL; //The root of the binary search tree
int counter; // Counts the iteration
/******************************************************************************************************************************
*Function name: setTree
*Purpose: It creates a binary search tree with specified input files
*Input parameter: file
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as iterative
*******************************************************************************************************************************/
void setTree(char *file) {
	char id[15], name[30], surname[30];
	int a[100], i, j=0, spaces=0;
	string strname1, strname2, line1, line2;
    ifstream data;
	data.open(file);
    if(!data) {
		cerr << "File could not be opened! " << endl;
		exit(1); 
	}
	/*Counts the spaces for each line*/
	while(!data.eof ()) {
		getline(data, line1);
		if(line1.empty()) //If there exists a blank line, ignore it
			continue;
		
		for(i=0; (i+1)<line1.size(); i++) {
			if(line1.at(i)== ' ')
				spaces++;
        }
		a[j]=spaces; //For each line, array a holds the number of spaces
		spaces=0;
		j++;
	}
	data.close();
	ifstream data1;
	data1.open(file);
	i=0;//Setting i to 0 for using it with another loops
  
	while(!data1.eof()) {
	    if(a[i]==1) { //If the number of spaces between name and surname is 1, the student has one name
			data1 >> id >> name >> surname;
		}
		else if (a[i]==2) {//The student has two names
	
			data1 >> id >> strname1 >> strname2 >> surname;
			strname1 = strname1 + " " + strname2; //concatenate two names, for students having two names
			/*String to char array conversion*/
			/*string strname1's characters are copied to the array name*/
			char *a =new char[strname1.size()+1];
			a[strname1.size()]=0;
			memcpy(a, strname1.c_str(), strname1.size());
			strcpy(name, a);
		}
		else 
			break;
		i++;
		if(id==NULL || name==NULL || surname == NULL) //For passing blank lines
			continue;
		/*Setting the binary search tree */
		Student *traverse, *newNode;
		traverse = root;
		int comparison;
		bool added = false; 
		newNode = new Student;
		strcpy(newNode->stid, id);
		strcpy(newNode->name, name);
		strcpy(newNode->surname, surname);
		newNode->left = newNode->right= NULL;
		if(root == NULL) { //First node is added
			root = newNode;
			continue;
		}
		while(traverse && !added) {
			comparison = strcmp(newNode->stid, traverse->stid);
			if(comparison < 0) {
				if(traverse->left != NULL) 
					traverse = traverse -> left;
				else {
					traverse->left=newNode;
					added = true;
				}
			}
			else if(comparison > 0) {
				if(traverse->right != NULL) 
					traverse = traverse->right;
				else {
					traverse->right = newNode;
					added = true;
				}
			}
			else 
				cout << "Data cannot repeat!" << endl;
		}
	}
	data1.close();

}
/******************************************************************************************************************************
*Function name: deleteStudent
*Purpose: It deletes a student from the tree with specified student id.
*Input parameter: id, traverse
*Output parameter: traverse
*Data structures: Student node
*Algorithm: It is implemented as iterative
*******************************************************************************************************************************/

Student * deleteStudent(char id[15], Student *traverse) {
    Student *temp;
    if( traverse == NULL ) {
        cout << "Element not found";
	}
    else if(strcmp(id, traverse->stid ) < 0) { /* Go left */
		traverse->left = deleteStudent(id, traverse->left);
	}
	else if(strcmp(id, traverse->stid ) > 0) { /* Go right */
		traverse->right = deleteStudent(id, traverse->right);
	}
	/* Found element to be deleted */
	else if(traverse->left && traverse->right) { /* Two children */
		/* Replace with smallest in right subtree */
		temp = traverse->right;
		while(temp->left!=NULL) {
			if( temp == NULL )
				cout << "!!" <<endl; 
			else {
				if( temp->left == NULL )
					break;
				else
					temp = temp->left;
			}
		}
		strcpy(traverse->stid, temp->stid);
		strcpy(traverse->name, temp->name);
		strcpy(traverse->surname, temp->surname);
		traverse->right = deleteStudent(traverse->stid, traverse->right);
	}
    else {/* One or zero children */
		temp = traverse;
		if( traverse->left == NULL ) {/* Also handles 0 children */
			traverse = traverse->right;
		}
		else if( traverse->right == NULL ) {
			traverse = traverse->left;
		}
			delete temp;
	}
    return traverse;
}
/******************************************************************************************************************************
*Function name: preorder
*Purpose: It prints the preorder traversal of the tree
*Input parameter: ptr
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as recursive
*******************************************************************************************************************************/				
void preorder(Student *ptr) {
	if(ptr!=NULL) {
		cout << ptr->stid << " " << ptr->name << " " << ptr->surname << endl;
		preorder(ptr->left);
		preorder(ptr->right);
	}
}
/******************************************************************************************************************************
*Function name: inorder
*Purpose: It prints the inorder traversal of the tree
*Input parameter: ptr
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as recursive
*******************************************************************************************************************************/
void inorder(Student *ptr) {
	if(ptr!=NULL) {
		inorder(ptr->left);
		cout << ptr->stid << " " << ptr->name << " " << ptr->surname << endl;
		inorder(ptr->right);
	}
}
/******************************************************************************************************************************
*Function name: postorder
*Purpose: It prints the postorder traversal of the tree
*Input parameter: ptr
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as recursive
*******************************************************************************************************************************/
void postorder(Student *ptr) {
	if(ptr != NULL) {
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->stid << " " << ptr->name << " " << ptr->surname << endl;
	}
}
/******************************************************************************************************************************
*Function name: printToFile
*Purpose: It writes the binary tree in preorder to the output file
*Input parameter: ptr, myFile
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as recursive
*******************************************************************************************************************************/
void printToFile(Student *ptr, ofstream &myFile) {
	if(!ptr)
		return;
	myFile << ptr->stid << " " << ptr->name << " " << ptr->surname << endl;
	printToFile(ptr->left, myFile);
	printToFile(ptr->right, myFile);
}
/******************************************************************************************************************************
*Function name: depth_first_search
*Purpose: Takes the student id from the user and search the tree in depth first manner
*Input parameter: ptr, id
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as recursive
*******************************************************************************************************************************/
void depth_first_search(Student *ptr, char id[15]) {
	counter = 0;
    if (!ptr) 
       return;
    deque <Student *> queue;
	Student* traverse;
    queue.push_front(ptr);
    while (queue.size() > 0) {
        traverse = queue.front();
        queue.pop_front();
        if(strcmp(traverse->stid, id) == 0) {
           cout << traverse->stid << " " << traverse->name << " " << traverse->surname << endl;
           return;
        }
        if (traverse->right != NULL) {
            queue.push_front(traverse->right);
        }
        if (traverse->left != NULL) {
            queue.push_front(traverse->left);
        }
		counter++;
    }
    cout<< "Not found!" << endl;
}
/******************************************************************************************************************************
*Function name: breadth_first_search
*Purpose: Takes the student id from the user and search the tree in breadth first manner
*Input parameter: ptr, id
*Output parameter: ---
*Data structures: Student node
*Algorithm: It is implemented as recursive
*******************************************************************************************************************************/
void breadth_first_search(Student *ptr, char id[15]) {
	counter = 0;
	if (!ptr) 
       return;
	deque <Student *> queue;
	Student *traverse;
	queue.push_back(ptr); //Add element at the end
	while(queue.size() != 0) {
		traverse =  queue.front(); //Access first element
		if(strcmp(traverse->stid, id) == 0) {
			cout << traverse->stid << " " << traverse->name << " " << traverse->surname << endl;
			return;
		}
		queue.pop_front(); //Delete first element
        if (traverse->left) {
            queue.push_back(traverse->left);
		}
        if (traverse->right) {
            queue.push_back(traverse->right);
		}
		counter++;
	}
	cout << "not found!" << endl;
}
/*MAIN FUNCTION*/
void main() {
	int option;
	char id[15];
	ofstream myFile;
	myFile.open("OUTPUT.txt");
	cout << "WELCOME TO BINARY SEARCH TREE PROGRAM! \n*programmed by Mehmet Aysevinc-150110705*" << endl << endl;
	cout << "You have to create the tree to get started!" << endl << "Please enter 1 to set the tree and 0 to exit: ";
	cin >> option;
	if(option==1) {
		cout << "Now, select a text file to create and perform operation on tree: " << endl;
		cout << "1: data1.txt" << endl << "2: data2.txt" << endl << "3: data3.txt" << endl;
		cin >> option;
		if(option == 1)
			setTree("data1.txt");
		else if(option == 2)
			setTree("data2.txt");
		else if(option == 3)
			setTree("data3.txt");
		else
			cout << "Invalid option" << endl;
	}
	else
		exit(1);
	cout << "The tree has been created succesfully!" << endl;
	cout << "Now you can perform operations on tree!" << endl << endl;
	
	while(true) {
		cout << "Please select an operation: " << endl;
		cout << "1: Recreate the tree " << endl << "2: Preorder list representation" << endl << "3: Inorder list representation" << endl;
		cout << "4: Postorder list representation" << endl << "5: Depth First Search" << endl << "6: Breadth First Search" << endl << "7: Delete student" << endl;
		cout << "8: Print to file" << endl << "0: Exit" << endl;
		cin >> option;
		if(option == 1) {
			root = NULL;
			cout << "Now, select a text file to create and perform operation on tree: " << endl;
			cout << "1: data1.txt" << endl << "2: data2.txt" << endl << "3: data3.txt" << endl;
			cin >> option;
			if(option == 1)
				setTree("data1.txt");
			else if(option == 2)
				setTree("data2.txt");
			else if(option == 3)
				setTree("data3.txt");
			else
				cout << "Invalid option" << endl;
			cout << "The tree has been created succesfully!" << endl;
			cout << "Now you can perform operations on tree!" << endl << endl;
			continue;
		}
		else if(option == 2) 
			preorder(root);
		else if(option == 3)
			inorder(root);
		else if(option == 4)
			postorder(root);
		else if(option == 5) {
			cout << "***DEPTH FIRST SEARCH***" << endl << "Please enter the student id: ";
			cin >> id;
			depth_first_search(root, id);
			cout <<"The number of iteration: " << counter << endl;
		}
		else if(option == 6) {
			cout << "***BREADTH FIRST SEARCH***" << endl << "Please enter the student id: ";
			cin >> id;
			breadth_first_search(root, id);
			cout <<"The number of iteration: " << counter << endl;
		}
		else if(option == 7) {
			cout << "Please enter the student id to be deleted from the tree: ";
			cin >> id;
			deleteStudent(id, root);
	        cout << "The student has been deleted from the tree succesfully! " << endl;
		}
		else if(option == 8) {
			printToFile(root, myFile);
			cout << "The file is printed to the output text!" << endl;
		}
		else if(option == 0)
			exit(1);
		else
			cout << "You have entered an invalid number, please enter again! "<< endl;	
		cout << "Press any key to continue!";
		getchar();
		getchar();
		system("cls");
	}
}
	
	
	
	
	
	
	
	
	
