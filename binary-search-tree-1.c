/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

    printf("[----- [배정민] [2023041088] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
    if(ptr) //만약 ptr이 NULL이 아니라면
    {
        inorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
        printf(" [%d] ", ptr->key); //현재 노드 출력
        inorderTraversal(ptr->right); //오른쪽 자식 노드로 이동
    }
}

void preorderTraversal(Node* ptr)
{
    if(ptr) //만약 ptr이 NULL이 아니라면
    {
        printf(" [%d] ", ptr->key); //현재 노드 출력
        preorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
        preorderTraversal(ptr->right);  //오른쪽 자식 노드로 이동
    }
}

void postorderTraversal(Node* ptr)
{
    if(ptr) //만약 ptr이 NULL이 아니라면
    {
        postorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
        postorderTraversal(ptr->right); //오른쪽 자식 노드로 이동
        printf(" [%d] ", ptr->key); //현재 노드 출력
    }
}


int insert(Node* head, int key)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드 동적할당
    newNode->key = key;  //새로운 노드의 key값 설정
    newNode->left = newNode->right = NULL; //새로운 노드의 자식 노드를 NULL로 초기화

    if(head->left == NULL) //만약 트리가 비어있다면
    {
        head->left = newNode; //새로운 노드를 루트 노드로 설정
        return 1; //1 반환
    }

    Node* ptr = head->left; //ptr을 루트 노드로 설정
    Node* parent = NULL; //부모 노드를 NULL로 초기화

    while(ptr != NULL) //ptr이 NULL이 아닐 때까지 반복
    {
        parent = ptr; //부모 노드를 ptr로 설정
        if(key < ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 작다면
        {
            ptr = ptr->left; //ptr을 왼쪽 자식 노드로 이동
        }
        else if(key > ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 크다면
        {
            ptr = ptr->right; //ptr을 오른쪽 자식 노드로 이동
        }

    }

    if(key < parent->key) //만약 매개변수로 넘겨받은 key값이 부모 노드의 key값보다 작다면
    {
        parent->left = newNode; //부모 노드의 왼쪽 자식 노드로 새로운 노드를 추가
    }
    else if(key > parent->key) //만약 매개변수로 넘겨받은 key값이 부모 노드의 key값보다 크다면
    {
        parent->right = newNode;  //부모 노드의 오른쪽 자식 노드로 새로운 노드를 추가
    }

    return 1; //1 반환
}

int deleteLeafNode(Node* head, int key)
{
    Node* parent = head; //부모 노드를 head로 설정
    Node* ptr = head->left; //ptr을 루트 노드로 설정

    while(ptr != NULL) //ptr이 NULL이 아닐 때까지 반복
    {
        if(key == ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값과 같다면
        {
            break; //반복문 탈출
        }
        
        parent = ptr; //부모 노드를 ptr로 설정
        
        if(key < ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 작다면
        {
            ptr = ptr->left; //ptr을 왼쪽 자식 노드로 이동
        }
        else if(key > ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 크다면
        {
            ptr = ptr->right; //ptr을 오른쪽 자식 노드로 이동
        }

    }

    if(ptr == NULL || ptr->left != NULL || ptr->right != NULL) //만약 ptr이 NULL이거나 ptr의 자식 노드가 존재한다면
    {
        printf("The node [%d] is not a leaf\n", key); //해당 노드가 리프 노드가 아님을 출력
        return -1; //-1 반환
    }

    if(parent->left == ptr) //만약 부모 노드의 왼쪽 자식 노드가 ptr이라면
    {
        parent->left = NULL; //부모 노드의 왼쪽 자식 노드를 NULL로 설정
    }
    else if(parent->right == ptr) //만약 부모 노드의 오른쪽 자식 노드가 ptr이라면
    {
        parent->right = NULL; //부모 노드의 오른쪽 자식 노드를 NULL로 설정
    }

    free(ptr); //ptr 동적할당 해제
    return 1; //1 반환
}

Node* searchRecursive(Node* ptr, int key)
{
    if(!ptr) //만약 ptr이 NULL이라면
    {
        return NULL; //NULL 반환
    }
    if(key == ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값과 같다면
    {
        return ptr; //ptr 반환
    }
    if(key < ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 작다면
    {
        return searchRecursive(ptr->left, key); //왼쪽 자식 노드로 이동
    }
    else //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 크다면
    {
        return searchRecursive(ptr->right, key); //오른쪽 자식 노드로 이동
    }
}

Node* searchIterative(Node* head, int key)
{
    Node *ptr = head->left; //ptr을 루트 노드로 설정

    while(ptr != NULL) //ptr이 NULL이 아닐 때까지 반복
    {
        if(key == ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값과 같다면
        {
            return ptr; //ptr 반환
        }
        if(key < ptr->key) //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 작다면
        {
            ptr = ptr->left; //ptr을 왼쪽 자식 노드로 이동
        }
        else //만약 매개변수로 넘겨받은 key값이 ptr의 key값보다 크다면
        {
            ptr = ptr->right; //ptr을 오른쪽 자식 노드로 이동
        }
    }
    return NULL; //NULL 반환
}


int freeBST(Node* head)
{
    if(head == NULL) //만약 트리가 비어있다면
	{
		return 1; //1 반환
	}

    if(head->left != NULL) //만약 트리가 비어있지 않다면
    {
        freeBST(head->left); //왼쪽 자식 노드로 이동
    }
    if(head->right != NULL) //만약 트리가 비어있지 않다면
    {
        freeBST(head->right); //오른쪽 자식 노드로 이동
    }
    free(head); //head 동적할당 해제.
}





