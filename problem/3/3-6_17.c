// ある連結リストがNULLで停止するかサイクルになっているかチェックせよ
#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
  struct linked_list *next;
  int data;
} List;

typedef struct linked_list_p {
  struct linked_list_p *next;
  struct linked_list *data;
} List_p;

void add_node(List **list, int position, int value){
  List *inserted_node = (List *)malloc(sizeof(List));
  inserted_node -> data = value;

  if (0 == position) {
    inserted_node -> next = *list;
    *list = inserted_node;
    return;
  }

  int id = 0;
  List *head = *list;
  while (head -> next) {
    id++;
    if (id == position) {
      break;
    }
    head = head -> next;
  }

  inserted_node -> next = head -> next;
  head -> next = inserted_node;
  return;
}

void add_node_p(List_p **list, int position, List *ptr){
  List_p *inserted_node = (List_p *)calloc(1, sizeof(List_p));
  inserted_node -> data = ptr;

  if (0 == position) {
    inserted_node -> next = *list;
    *list = inserted_node;
    return;
  }

  int id = 0;
  List_p *head = *list;
  while (head -> next) {
    id++;
    if (id == position) {
      break;
    }
    head = head -> next;
  }

  inserted_node -> next = head -> next;
  head -> next = inserted_node;
  return;
}

List *last_node(List *list){
  List *head = list;
  while (head -> next) {
    head = head -> next;
  }
  return head;
}

void display_list(List *list){
  List *head = list;
  while (head) {
    printf("%d\n", head -> data);
    head = head -> next;
  }
  return;
}

List *null_case(){
  printf("--- null case ---\n" );
  List *list = (List *)calloc(1, sizeof(List));
  list -> data = 0;
  for (int i = 1; i < 10; i++) {
    add_node(&list, 1000, i);
  }

  // set NULL to the next variable of final node
  List *head = list;
  for (int i = 1; i < 10; i++) {
    head = head -> next;
  }
  head -> next = NULL;
  return list;
}

List *range(int start, int end, int step){
  printf("--- range [%d, %d] ---\n", start, end);
  List *list = (List *)calloc(1, sizeof(List));
  list -> data = start;
  for (int i = start+1; i < end; i+=step) {
    add_node(&list, end, i);
  }

  // set NULL to the next variable of final node
  List *head = list;
  for (int i = start+1; i < end; i+=step) {
    head = head -> next;
  }
  head -> next = NULL;
  return list;
}

List *cycle_case(){
  printf("--- cycle case ---\n" );
  List *cycle_node; // initialize in for loop
  List *list = (List *)calloc(1, sizeof(List));
  list -> data = 0;

  for (int i = 1; i < 10; i++) {
    add_node(&list, 100, i);
    if (4 == i) {
      cycle_node = last_node(list);
    }
  }
  last_node(list) -> next = cycle_node;
  return list;
}

void checkCycleList3_7(List *list){
  printf("--- check cycle list ---\n");
  List *head = list;
  List_p *temp = (List_p *)calloc(1, sizeof(List_p));
  temp -> data = list;

  List_p *temp_head = temp;
  while (head -> next) {
    printf("check head: %d\n", head -> next);
    add_node_p(&temp, 100, head);

    temp_head = temp;
    while(temp_head){
      printf("%d\n", temp_head -> data);
      if (temp_head -> data == head -> next) {
        printf("cycle list: %d, data: %d\n", temp_head -> data, temp_head -> data -> data);
        return;
      }
      temp_head = temp_head -> next;
    }
    head = head -> next;
  }
  printf("one directional list");
}

int isCycleList3_9(List *list){
  printf("--- check cycle list 3-9 ---\n");
  List *slowPtr = list;
  List *fastPtr = list;

  int cnt = 0;
  while (fastPtr) {
    cnt++;
    fastPtr = fastPtr -> next;
    if (cnt % 2 == 0) {
      slowPtr = slowPtr -> next;
    }

    printf("slow: %d, fast: %d\n", slowPtr, fastPtr);
    if (slowPtr == fastPtr) {
      printf("circular list\n");
      return 1;
    }
  }
  printf("one directional list\n");
  return 0;
}

// 3-11ある連結リストがNULLで停止するかどうかをチェックせよ。サイクルがあるなら、ループの開始ノードを見つけよ。
List* findFirstNodeOFCycleList(List *list) {
  if (!isCycleList3_9(list)) {
    printf("The list is not a cycle list.\n");
    return NULL;
  }
  printf("--- find the first node of cycle list ---\n");
  List *slowPtr = list;
  List *fastPtr = list;
  List *firstNodePtr = list;

  int firstCycle = 0;
  while (slowPtr && fastPtr) {
    firstCycle ++;
    for (size_t i = 0; i < 2; i++) {
      fastPtr = fastPtr -> next;
    }
    slowPtr = slowPtr -> next;

    printf("slow: %d, fast: %d\n", slowPtr -> data, fastPtr -> data);

    if (slowPtr == fastPtr) {
      // given i=(the root of cycle) and j=(meeting ptr from the root),
      // slow = i+j, fast = i+j+n, fast = 2*slow = 2(i+j), => n=i+j

      while (slowPtr && firstNodePtr) {
        slowPtr = slowPtr -> next;
        firstNodePtr = firstNodePtr -> next;

        printf("slow: %d, first: %d\n", slowPtr -> data, firstNodePtr -> data);

        if (slowPtr == firstNodePtr) {
          // when first = i, slow = i+j+i = n+i, these ptrs meet together
          printf("first node is %d and data is %d\n", firstNodePtr, firstNodePtr -> data);
          return firstNodePtr;
        }
      }
    }
  }
}

// 3-14 ある連結リストがNULLで停止するかどうかをチェックせよ。サイクルがあるなら、ループ長を求めよ。
int loopLengthOf(List *list) {
  List *slowPtr = list;
  List *fastPtr = list;

  int cnt = 0;
  while (slowPtr && fastPtr) {
    cnt ++;
    slowPtr = slowPtr -> next;
    for (size_t i = 0; i < 2; i++) {
      fastPtr = fastPtr -> next;
    }
    if (slowPtr == fastPtr) {
      printf("We found the cycle in the list! The length is %d\n", cnt);
      return cnt; // fastPtr はループ1周分多く移動しているため、合流時のcntはループ長
    }
  }
  printf("There is not any cycles in the list.");
  return 0; // NULLで停止 → ループ無し
}

// 3-15 ソートされた連結リストにノードを挿入せよ
int insertNodeInLinkedList(List **ptrSortedList, List **ptrInsertedNode){
  // 最初のノードとの大小比較
  if ((*ptrSortedList) -> data >= (*ptrInsertedNode) -> data) {
    (*ptrInsertedNode) -> next = (*ptrSortedList);
    *ptrSortedList = (*ptrInsertedNode);
    return 0; // inserted in first
  }

  List *ptrList = *ptrSortedList;
  while (ptrList -> next) {
    // 次のノードの値より、挿入するノードの値が小さければ、前のノードに挿入
    if (ptrList -> next -> data > (*ptrInsertedNode) -> data) {
      (*ptrInsertedNode) -> next = ptrList -> next;
      ptrList -> next = (*ptrInsertedNode);
      return 1;
    }
    ptrList = ptrList -> next;
  }

  ptrList -> next = (*ptrInsertedNode);
  return 2; // ノードの最後に挿入
}

void testInsertNodeInLinkedList() {
  List *list;
  List *node;
  int status;

  printf("--- Should be -10, 0, 1, ... ---\n");
  list = null_case();
  node = (List *) calloc(1, sizeof(List));
  node -> data = -10;
  status = insertNodeInLinkedList(&list, &node);
  printf("status: %d\n", status);
  display_list(list);

  printf("--- Should be 0, 0, 1, ... ---\n");
  list = null_case();
  node = (List *) calloc(1, sizeof(List));
  node -> data = 0;
  status = insertNodeInLinkedList(&list, &node);
  printf("status: %d\n", status);
  display_list(list);

  printf("--- Should be 0, 1, 2, 3, 4, 4, 5 ... ---\n");
  list = null_case();
  node = (List *) calloc(1, sizeof(List));
  node -> data = 4;
  status = insertNodeInLinkedList(&list, &node);
  printf("status: %d\n", status);
  display_list(list);

  printf("--- Should be ..., 8, 9, 9 ---\n");
  list = null_case();
  node = (List *) calloc(1, sizeof(List));
  node -> data = 9;
  status = insertNodeInLinkedList(&list, &node);
  printf("status: %d\n", status);
  display_list(list);


  printf("--- Should be ..., 8, 9, 100 ---\n");
  list = null_case();
  node = (List *) calloc(1, sizeof(List));
  node -> data = 100;

  printf("--- insertNodeInLinkedList ---\n");
  status = insertNodeInLinkedList(&list, &node);
  printf("status: %d\n", status);
  display_list(list);
}

// 3-16 単一連結リストを逆転させよ。
int reverseSingleLinkedList(List **list) {
  List *nextNode;
  List *prevNode = NULL;

  // 後ノードを保持して、各ノードのnext要素を前ノードにする
  while ((*list) -> next) {
    nextNode = (*list) -> next;
    // printf("%d, %d, %d\n", prevNode, *list, nextNode);
    (*list) -> next = prevNode;
    prevNode = (*list);
    *list = nextNode;
  }
  (*list) -> next = prevNode;
  return 1;
}

// 3-16 単一連結リストを逆転させよ。<再帰関数版>
List *recursiveReverseSingleLinkedList(List *head) {
  // printf("ptrHead: %d, ptrNext: %d\n", head, head->next);
  if (NULL == head) { // これは、元々のListがnullだった場合にTrue
    return NULL;
  }
  if (head -> next == NULL) { //再帰が最後のノードまでたどり着いた場合にTrue
    return head;
  }

  List *nextNode = head -> next;
  List *recursiveNode = recursiveReverseSingleLinkedList(nextNode); // 最後のノードを見つけて保持する
  nextNode -> next = head; // 後ノードnextポインタが現ノードを指すようにする → 逆順
  head -> next = NULL; // 最初のノードのnextポインタは1番目のポインタを指したままだから、NULLを代入。再帰呼び出し元での上行の操作で新しいnextが指定される
  // printf("ptrHead: %d, ptrNext: %d, ptrRecursive: %d\n", head, nextNode, recursiveNode);
  return recursiveNode;
}

void testReverseSingleLinkedList() {
  List *list = null_case();
  display_list(list);
  printf("--- reverse single linked list ---\n");
  reverseSingleLinkedList(&list);
  display_list(list);
  reverseSingleLinkedList(&list);
  display_list(list);
}

void testRecursiveReverseSingleLinkedList() {
  List *list = null_case();
  List *reversedList = (List *) calloc(1, sizeof(List));

  display_list(list);
  printf("--- recursive single linked list ---\n");
  reversedList = recursiveReverseSingleLinkedList(list);
  display_list(reversedList);
  reversedList = recursiveReverseSingleLinkedList(reversedList);
  display_list(reversedList);
}

// 3-17 2つの単一連結リストがあり、ある場所で合流して１つの単一連結リストとなるとする。
// 両者のheadすなわち開始ポインタはわかっているが、合流ノードはわかっていない。
// さらに、合流までのそれぞれのリストの長さも未知で、異なる可能性がある。
// List1 は合流点までnノード、List2は合流点までmノードで、
// mとnは m=n, m<n, n<m のいずれでもありうる。合流点を探すアルゴリズムを示せ。

// <効率的方式>
List* findMeetingPoint(List *list1, List *list2) {
  List *temp1 = list1;
  List *temp2 = list2;

  int len1 = 0, len2 = 0; // 各リストの長さを調べる
  while (temp1) {
    len1 ++;
    temp1 = temp1 -> next;
  }
  while (temp2) {
    len2 ++;
    temp2 = temp2 -> next;
  }

  while (list1 && list2) { // 先頭から順に調べる。長さを揃えてから比較する。
    if (len1 > len2) {
      list1 = list1 -> next;
      len1 --;
    } else if (len2 > len1) {
      list2 = list2 -> next;
      len2 --;
    } else if(len1 == len2) {
      if (list1 == list2) {
        return list1;
      }
      list1 = list1 -> next;
      list2 = list2 -> next;
    }
  }
  return NULL; // not found
}

void testFindMeetingPoint() {
  List *list1 = range(1,5,1);
  List *list2 = range(3,5,1);
  List *list3 = range(7,10,1);
  last_node(list1) -> next = list3;
  last_node(list2) -> next = list3;
  display_list(list1);
  display_list(list2);

  printf("\n--- should be 7 ---\n"); // n > m
  List *meetingNode = findMeetingPoint(list1, list2);
  printf("meetingNode: %d\n", meetingNode);
  if (meetingNode != NULL) {
    printf("meetingNode data: %d\n", meetingNode -> data);
    if (7 == meetingNode -> data) {
      printf(" TEST1 OK\n" );
    }
  }

  printf("\n--- should be 7 ---\n"); // m = n
  list1 = range(1,5,1);
  list2 = range(8,12,1);
  list3 = range(7,10,1);
  last_node(list1) -> next = list3;
  last_node(list2) -> next = list3;
  meetingNode = findMeetingPoint(list1, list2);
  printf("meetingNode: %d\n", meetingNode);
  if (meetingNode != NULL) {
    printf("meetingNode data: %d\n", meetingNode -> data);
    if (7 == meetingNode -> data) {
      printf(" TEST2 OK\n" );
    }
  }

  printf("\n--- should be 7 ---\n"); // m < n
  list1 = range(3,5,1);
  list2 = range(8,12,1);
  list3 = range(7,10,1);
  last_node(list1) -> next = list3;
  last_node(list2) -> next = list3;
  meetingNode = findMeetingPoint(list1, list2);
  printf("meetingNode: %d\n", meetingNode);
  if (meetingNode != NULL) {
    printf("meetingNode data: %d\n", meetingNode -> data);
    if (7 == meetingNode -> data) {
      printf(" TEST3 OK\n" );
    }
  }

  printf("\n--- should be 1 ---\n");
  meetingNode = findMeetingPoint(list1, list1);
  printf("meetingNode: %d\n", meetingNode);
  if (meetingNode != NULL) {
    printf("meetingNode data: %d\n", meetingNode -> data);
    if (1 == meetingNode -> data) {
      printf(" TEST4 OK\n" );
    }
  }

  printf("\n--- pointer should be NULL ---\n"); // 合流しない
  List *list4 = range(1,5,1);
  List *list5 = range(3,5,1);
  meetingNode = findMeetingPoint(list4, list5);
  printf("meetingNode: %d\n", meetingNode);
  if (NULL == meetingNode) {
    printf(" TEST5 OK\n" );
  }

  printf("\n--- should be 7 ---\n");
  List *list6 = range(1,5,1);
  List *list7 = range(3,5,1);
  List *list8 = range(7,8,1);
  last_node(list6) -> next = list8;
  last_node(list7) -> next = list8;
  meetingNode = findMeetingPoint(list6, list7);
  printf("meetingNode: %d\n", meetingNode);
  if (meetingNode != NULL) {
    printf("meetingNode data: %d\n", meetingNode -> data);
    if (7 == meetingNode -> data) {
      printf(" TEST6 OK\n" );
    }
  }
}

// 3-24: 連結リストの中央を見つけよ
List* findMedianOf(List *head) {
  int len = 1;
  List *node = head;
  while (node -> next) {
    len ++;
    node = node -> next;
  }

  int middle = (int) len / 2;
  if (len % 2 == 1) {
    middle ++;
  }
  node = head;
  for (int i = 0; i < middle-1; i++) {
    node = node -> next;
  }
  return node;
}

// (効率的実装)
List* findMedianOf2(List *head) {
  List *fastNode = head;
  List *slowNode = head;
  int cnt = 0;
  while (fastNode -> next) {
    fastNode = fastNode -> next;
    if (cnt % 2 == 1) {
      slowNode = slowNode -> next;
    }
    cnt ++;
  }
  return slowNode;
}

void testFindMedianOf(){
  List *list = range(1,10,1);  // [1,2,3,4,5,6,7,8,9]
  List *middle = findMedianOf(list);
  printf("%d\n", middle -> data);
  if (5 == middle -> data) {
    printf("Test is ok\n");
  }

  List *list2 = range(1,1,1);  // [1]
  List *middle2 = findMedianOf(list2);
  printf("%d\n", middle2 -> data);
  if (1 == middle2 -> data) {
    printf("Test is ok\n");
  }

  List *list3 = range(1,11,1);  // [1,2,3,4,5,6,7,8,9,10]
  List *middle3 = findMedianOf(list3);
  printf("%d\n", middle3 -> data);
  if (5 == middle3 -> data) {
    printf("Test is ok\n");
  } else {
    printf("Test failed\n");
  }
  return;
}

void testFindMedianOf2(){
  List *list = range(1,10,1);  // [1,2,3,4,5,6,7,8,9]
  List *middle = findMedianOf2(list);
  printf("%d\n", middle -> data);
  if (5 == middle -> data) {
    printf("Test is ok\n");
  } else {
    printf("Test failed\n");
  }

  List *list2 = range(1,1,1);  // [1]
  List *middle2 = findMedianOf2(list2);
  printf("%d\n", middle2 -> data);
  if (1 == middle2 -> data) {
    printf("Test is ok\n");
  } else {
    printf("Test failed\n");
  }

  List *list3 = range(1,11,1);  // [1,2,3,4,5,6,7,8,9,10]
  List *middle3 = findMedianOf2(list3);
  printf("%d\n", middle3 -> data);
  if (5 == middle3 -> data) {
    printf("Test is ok\n");
  } else {
    printf("Test failed\n");
  }
  return;
}

void main(){
  // List *list = null_case();
  // List *node = (List *) calloc(1, sizeof(List));
  // findFirstNodeOFCycleList(list);
  // int len = loopLengthOf(list);
  // testReverseSingleLinkedList();
  // testRecursiveReverseSingleLinkedList();
  // testFindMeetingPoint();
  // testFindMedianOf();
  // testFindMedianOf2();
}
