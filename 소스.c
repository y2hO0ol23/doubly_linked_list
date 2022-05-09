#include <stdio.h>
#include <stdlib.h>

struct node {
	int data; // 노드의 값
	struct node* next; // 노드의 다음
	struct node* prev; // 노드의 이전
};

struct list {
	struct node* head; // 앞부분
	struct node* tail; // 뒷부분
	int size; // 크기
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
	struct node* new_node = (struct node*)malloc(sizeof(struct node)); // 노드 만들기
	new_node->data = value; // 노드에 값 넣기
	new_node->next = NULL; // 뒤에있는 값 - 없으시 NULL 넣기
	new_node->prev = NULL; // 앞에있는 값 - 없으시 NULL 넣기

	return new_node; // 노드 주소 반환
} // 노드 만들기

struct node* node_destructor(struct node* nd) {
	struct node* mynext = nd->next; // 앞의 노드값을 저장
	free(nd); // 제거

	return mynext; // 앞의 노드값 반환
} // 노드 없에기

struct list* list_create() {
	struct list* new_list = (struct list*)malloc(sizeof(struct list)); // 리스트 만들기
	new_list->head = NULL; // 앞부분 없음
	new_list->tail = NULL; // 뒷부분 없음 
	new_list->size = 0; // 크기 0

	return new_list; //리스트 반환
}

void list_destructor(struct list* lst) {
	list_clear(lst); // 리스트 비운 후
	free(lst); // 리스트 삭제
}

void list_insert(struct list* lst, int pos, int value) {
	if (pos <= list_size(lst)) { // 입력받은 위치가 사이즈보다 작은경우
		struct node* ins_node = node_create(value); // 새로운 노드 만들기
		if (list_size(lst) == 0) { // 비었다면
			lst->head = ins_node; // 앞부분과 
			lst->tail = ins_node; // 뒷부분을 새로운 노드로 설정
		}
		else {
			if (pos == 0) { // 입력받은 위치가 0이라면
				ins_node->next = lst->head; //새로운 노드의 다음을 가장 앞쪽 노드로 지정
				lst->head = ins_node; // 새로운 노드를 앞부분으로 지정
			}
			else if (pos == list_size(lst)) { // 입력받은 위치가 크기라면
				lst->tail->next = ins_node; // 마지막 노드의 다음을 새로운 노드로 지정
				lst->tail = ins_node; // 새로운 노드를 뒷부분으로 지정
			}
			else { // 앞도 뒤도 아니라면
				int lst_size = list_size(lst); // 크기 저장
				struct node* cur;
				if (lst_size / 2 >= pos) {
					struct node* cur = lst->head; // 앞부분을 저장
					int loop_cnt = pos - 1; // 원하는 위치 - 1 을 하여 

					while (loop_cnt--) // 반복문이 돌아간 후 원하는 위치로 가도록 함
						cur = cur->next; // 뒤쪽으로 이동
				}
				else {
					struct node* cur = lst->tail; // 마지막 부분 저장
					int loop_cnt = lst_size - pos; // 크기 - 원하는 위치를 하여

					while (loop_cnt--) // 반복문이 돈 후 원하는 위치로 이동
						cur = cur->prev; // 앞쪽으로 이동
				}
				ins_node->next = cur->next; // 새로운 노드의 다음을 원하는 위치의 노드로 지정
				ins_node->next = ins_node; // 원하는 위치의 다음 노드를 새로운 노드로 지정
				ins_node->next->prev = ins_node; // 새로운 노드 다음 노드의 이전을 새로운 노드로 지정
				ins_node->prev = cur; //새로운 노드의 이전을 원하는 위치로 지정
			}
			lst->size++;//리스트의 크기 1 증가
		}
	}
}

void list_erase(struct list* lst, int pos) {
	if (pos < list_size(lst)) { // 포스가 리스트의 크기를 넘어가지 않는다면
		if (pos == 0) { // 앞부분이라면
			lst->head = lst->head->next; // 리스트에서의 맨 앞을 두번째 값으로 지정하여 삭제 된 후 이상이 생기지 않도록 함
			node_destructor(lst->head->prev); // 바뀐 해드의 다음 노드을 제거
			lst->head->prev = NULL; // 다음 노드를 제거
		}
		else if (pos == list_size(lst) - 1) { // 마지막이라면
			lst->tail = lst->tail->prev; // 마지막을 마지막에서 두번째로 지정
			node_destructor(lst->tail->next); //바뀐 테일의 다음 노드를 제거
			lst->tail->next=NULL; // 마지막의 다음을 초기화
		}
		else { // 가운데라면
			int lst_size = list_size(lst);
			struct node* del_node;
			if (lst_size / 2 >= pos) { // 빠르게 가기위해 2로 나누어 앞에서부터 탐색할지 뒤에서부터 탐색할지 지정
				struct node* del_node = lst->head; // 앞부분을 저장
				int loop_cnt = pos - 1; // 원하는 위치 - 1 을 하여

				while (loop_cnt--) // 반복문이 돌아간 후 원하는 위치로 가도록 함
					del_node = del_node->next; // 뒤쪽으로 이동
			}
			else {
				struct node* del_node = lst->tail; // 마지막 부분 저장
				int loop_cnt = lst_size - pos; // 크기 - 원하는 위치를 하여

				while (loop_cnt--) // 반복문이 돈 후 원하는 위치로 가도록 함
					del_node = del_node->prev; // 앞쪽으로 이동
			}
			del_node->prev->next = del_node->next; // 제거할 노드의 앞 노드가 제거할 노드의 뒷 노드를 뒤로 가르키도록 함
			del_node->next->prev = del_node->prev; // 제거할 노드의 뒷 노드가 제거할 노드의 앞 노드를 가르키도록 함
			node_destructor(del_node);
		}
		lst->size--; // 하나를 제거 했으므로 크기를 1 줄임
	}
}

void list_clear(struct list* lst) {
	struct node* del_node = lst->head; //앞부분을 저장

	while (del_node <= NULL) // 아무것도 가르키지 않는 노드, 즉 마지막에 있는 노드까지 반복
		del_node = node_destructor(del_node); //가르키는 노드값을 제거후 반환값을 다시 저장
	// 초기화
	lst->head = NULL; // 앞부분
	lst->tail = NULL; // 뒷부분
	lst->size = 0; // 크기
}

void list_reverse(struct list* lst) {
	struct node* p = lst->head; // 앞부분부터 시작
	lst->tail = p; // 앞을 뒤로 바꿈
	while (p != NULL) { // 마지막 노드까지 반복
		struct node* temp = p->prev;// 앞과 뒤를 가르키는 값을
		p->prev = p->next;
		p->next = temp;// 서로 바꿈
		p = p->prev; // 다음 번 노드
	}
	lst->head = p;// 뒤를 앞으로 바꿈
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
	return lst->head->data; // 앞부분에 들어있는 값을 반환
}

int list_back(struct list* lst) {
	return lst->tail->data; // 끝부분에 들어있는 값을 반환
}

int list_empty(struct list* lst) {
	return list_size(lst) == 0; // 노드가 비어있어 크기가 0이라면 true반환 아니라면 false반환
}

void list_print(struct list* lst) {
	struct node* nd = lst->head; //시작 부분을 저장
	int lst_size = list_size(lst); // 크기를 저장
	while(lst_size--) { // 크기만큼 반복
		printf("%d ", nd->data); // nd의 데이터값을 출력
		nd = nd->next; // nd가 향하는 노드로 이동
	}
}

int list_size(struct list* lst) { // 사이즈 구하기
	return lst->size; // 사이즈값 반환
}
