#include <stdio.h>
#include <stdlib.h>

struct node {
	int data; // ����� ��
	struct node* next; // ����� ����
	struct node* prev; // ����� ����
};

struct list {
	struct node* head; // �պκ�
	struct node* tail; // �޺κ�
	int size; // ũ��
};

struct node* node_create(int value);
struct node* node_destructor(struct node* nd);

struct list* list_create();

void list_destructor(struct list* lst);
void list_insert(struct list* lst, int pos, int value);
void list_erase(struct list* lst, int pos);
void list_clear(struct list* lst);
void list_reverse(struct list* lst);

void push_front(struct list* lst, int value);
void push_back(struct list* lst, int value);
void pop_front(struct list* lst);
void pop_back(struct list* lst);
int list_front(struct list* lst);
int list_back(struct list* lst);
int list_empty(struct list* lst);
void list_print(struct list* lst);

int list_size(struct list* lst);

int main() {
	
}

struct node* node_create(int value) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node)); // ��� �����
	new_node->data = value; // ��忡 �� �ֱ�
	new_node->next = NULL; // �ڿ��ִ� �� - ������ NULL �ֱ�
	new_node->prev = NULL; // �տ��ִ� �� - ������ NULL �ֱ�

	return new_node; // ��� �ּ� ��ȯ
} // ��� �����

struct node* node_destructor(struct node* nd) {
	struct node* mynext = nd->next; // ���� ��尪�� ����
	free(nd); // ����

	return mynext; // ���� ��尪 ��ȯ
} // ��� ������

struct list* list_create() {
	struct list* new_list = (struct list*)malloc(sizeof(struct list)); // ����Ʈ �����
	new_list->head = NULL; // �պκ� ����
	new_list->tail = NULL; // �޺κ� ���� 
	new_list->size = 0; // ũ�� 0

	return new_list; //����Ʈ ��ȯ
}

void list_destructor(struct list* lst) {
	list_clear(lst); // ����Ʈ ��� ��
	free(lst); // ����Ʈ ����
}

void list_insert(struct list* lst, int pos, int value) {
	if (pos <= list_size(lst)) { // �Է¹��� ��ġ�� ������� �������
		struct node* ins_node = node_create(value); // ���ο� ��� �����
		if (list_size(lst) == 0) { // ����ٸ�
			lst->head = ins_node; // �պκа� 
			lst->tail = ins_node; // �޺κ��� ���ο� ���� ����
		}
		else {
			if (pos == 0) { // �Է¹��� ��ġ�� 0�̶��
				ins_node->next = lst->head; //���ο� ����� ������ ���� ���� ���� ����
				lst->head = ins_node; // ���ο� ��带 �պκ����� ����
			}
			else if (pos == list_size(lst)) { // �Է¹��� ��ġ�� ũ����
				lst->tail->next = ins_node; // ������ ����� ������ ���ο� ���� ����
				lst->tail = ins_node; // ���ο� ��带 �޺κ����� ����
			}
			else { // �յ� �ڵ� �ƴ϶��
				int lst_size = list_size(lst); // ũ�� ����
				struct node* cur;
				if (lst_size / 2 >= pos) {
					struct node* cur = lst->head; // �պκ��� ����
					int loop_cnt = pos - 1; // ���ϴ� ��ġ - 1 �� �Ͽ� 

					while (loop_cnt--) // �ݺ����� ���ư� �� ���ϴ� ��ġ�� ������ ��
						cur = cur->next; // �������� �̵�
				}
				else {
					struct node* cur = lst->tail; // ������ �κ� ����
					int loop_cnt = lst_size - pos; // ũ�� - ���ϴ� ��ġ�� �Ͽ�

					while (loop_cnt--) // �ݺ����� �� �� ���ϴ� ��ġ�� �̵�
						cur = cur->prev; // �������� �̵�
				}
				ins_node->next = cur->next; // ���ο� ����� ������ ���ϴ� ��ġ�� ���� ����
				ins_node->next = ins_node; // ���ϴ� ��ġ�� ���� ��带 ���ο� ���� ����
				ins_node->next->prev = ins_node; // ���ο� ��� ���� ����� ������ ���ο� ���� ����
				ins_node->prev = cur; //���ο� ����� ������ ���ϴ� ��ġ�� ����
			}
			lst->size++;//����Ʈ�� ũ�� 1 ����
		}
	}
}

void list_erase(struct list* lst, int pos) {
	if (pos < list_size(lst)) { // ������ ����Ʈ�� ũ�⸦ �Ѿ�� �ʴ´ٸ�
		if (pos == 0) { // �պκ��̶��
			lst->head = lst->head->next; // ����Ʈ������ �� ���� �ι�° ������ �����Ͽ� ���� �� �� �̻��� ������ �ʵ��� ��
			node_destructor(lst->head->prev); // �ٲ� �ص��� ���� ����� ����
			lst->head->prev = NULL; // ���� ��带 ����
		}
		else if (pos == list_size(lst) - 1) { // �������̶��
			lst->tail = lst->tail->prev; // �������� ���������� �ι�°�� ����
			node_destructor(lst->tail->next); //�ٲ� ������ ���� ��带 ����
			lst->tail->next=NULL; // �������� ������ �ʱ�ȭ
		}
		else { // ������
			int lst_size = list_size(lst);
			struct node* del_node;
			if (lst_size / 2 >= pos) { // ������ �������� 2�� ������ �տ������� Ž������ �ڿ������� Ž������ ����
				struct node* del_node = lst->head; // �պκ��� ����
				int loop_cnt = pos - 1; // ���ϴ� ��ġ - 1 �� �Ͽ�

				while (loop_cnt--) // �ݺ����� ���ư� �� ���ϴ� ��ġ�� ������ ��
					del_node = del_node->next; // �������� �̵�
			}
			else {
				struct node* del_node = lst->tail; // ������ �κ� ����
				int loop_cnt = lst_size - pos; // ũ�� - ���ϴ� ��ġ�� �Ͽ�

				while (loop_cnt--) // �ݺ����� �� �� ���ϴ� ��ġ�� ������ ��
					del_node = del_node->prev; // �������� �̵�
			}
			del_node->prev->next = del_node->next; // ������ ����� �� ��尡 ������ ����� �� ��带 �ڷ� ����Ű���� ��
			del_node->next->prev = del_node->prev; // ������ ����� �� ��尡 ������ ����� �� ��带 ����Ű���� ��
			node_destructor(del_node);
		}
		lst->size--; // �ϳ��� ���� �����Ƿ� ũ�⸦ 1 ����
	}
}

void list_clear(struct list* lst) {
	struct node* del_node = lst->head; //�պκ��� ����

	while (del_node <= NULL) // �ƹ��͵� ����Ű�� �ʴ� ���, �� �������� �ִ� ������ �ݺ�
		del_node = node_destructor(del_node); //����Ű�� ��尪�� ������ ��ȯ���� �ٽ� ����
	// �ʱ�ȭ
	lst->head = NULL; // �պκ�
	lst->tail = NULL; // �޺κ�
	lst->size = 0; // ũ��
}

void list_reverse(struct list* lst) {
	struct node* p = lst->head; // �պκк��� ����
	lst->tail = p; // ���� �ڷ� �ٲ�
	while (p != NULL) { // ������ ������ �ݺ�
		struct node* temp = p->prev;// �հ� �ڸ� ����Ű�� ����
		p->prev = p->next;
		p->next = temp;// ���� �ٲ�
		p = p->prev; // ���� �� ���
	}
	lst->head = p;// �ڸ� ������ �ٲ�
}

void push_front(struct list* lst, int value) {
	list_insert(lst, 0, value);
}

void push_back(struct list* lst, int value) {
	list_insert(lst, list_size(lst), value);
}

void pop_front(struct list* lst) {
	list_erase(lst, 0);
}

void pop_back(struct list* lst) {
	list_erase(lst, list_size(lst)-1);
}

int list_front(struct list* lst) {
	return lst->head->data; // �պκп� ����ִ� ���� ��ȯ
}

int list_back(struct list* lst) {
	return lst->tail->data; // ���κп� ����ִ� ���� ��ȯ
}

int list_empty(struct list* lst) {
	return list_size(lst) == 0; // ��尡 ����־� ũ�Ⱑ 0�̶�� true��ȯ �ƴ϶�� false��ȯ
}

void list_print(struct list* lst) {
	struct node* nd = lst->head; //���� �κ��� ����
	int lst_size = list_size(lst); // ũ�⸦ ����
	while(lst_size--) { // ũ�⸸ŭ �ݺ�
		printf("%d ", nd->data); // nd�� �����Ͱ��� ���
		nd = nd->next; // nd�� ���ϴ� ���� �̵�
	}
}

int list_size(struct list* lst) { // ������ ���ϱ�
	return lst->size; // ����� ��ȯ
}