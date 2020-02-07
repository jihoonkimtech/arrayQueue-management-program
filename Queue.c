/*
	큐 Queue (대기열)
	선입 선출 (First In First Out) 구조이다.
	삽입과 삭제가 다른 곳에서 일어난다.
	삽입이 일어난 곳은 후단(rear)이고, 삭제가 일어나는 곳은 전단(front)이다.

	<- out [0][1][2][3][4] <- in
	(front)					(rear)


	큐 추상 데이터 타입(ADT)
		∙객체: n개의 element형으로 구성된 요소들의 순서있는 모임
		∙연산:
		 ▪ create() ::=        큐를 생성한다.
		 ▪ init(q) ::=         큐를 초기화한다.
		 ▪ is_empty(q) ::=     큐가 비어있는지를 검사한다.
		 ▪ is_full(q) ::=      큐가 가득 찼는가를 검사한다.
		 ▪ enqueue(q, e) ::=   큐의 뒤에 요소를 추가한다.
		 ▪ dequeue(q) ::=      큐의 앞에 있는 요소를 반환한 다음 삭제한다.
		 ▪ peek(q) ::=         큐에서 삭제하지 않고 앞에 있는 요소를 반환한다.


	1) 직접적인 응용
		시뮬레이션의 대기열(공항에서의 비행기들, 은행에서의 대기열)
		통신에서의 데이터 패킷들의 모델링에 이용
		프린터와 컴퓨터 사이의 버퍼링
		운영체제에서도 사용
		컴퓨터의 CPU와 주변기긱 사이에 속도 차이 때문에 CPU를 효율적으로 사용하기 위해 큐를 사용

	2) 간접적인 응용
		스택과 마찬가지로 프로그래머의 도구
		많은 알고리즘에서 사용됨


	배열로 구현된 큐
		선형 큐
			배열을 선형으로 사용하여 큐를 구현
			삽입을 계속하기 위해서는 요소들을 이동시켜야 함
			문제점이 많아 사용되지 않음
				<- out [0][1][2][3][4] <- in
				(front)					(rear)

		원형 큐
			배열을 원형으로 사용하여 큐를 구현
			[4] <- [0][1][2][3][4] <- [0] (후단과 전단이 맞물려 원형처럼 보임.)


	연결리스트 큐 (Linked-list Queue)
		배열로 구현된 원형 큐
		- 원형큐는 배열이 원형으로 처음과 끝이 연결된 상태이다. 실제 배열이 원형으로 연결된 것이 아니라 배열의 인덱스를 변경시켜 준 것 뿐이다.
		- 초기값이 0이다.
		- front는 항상 큐의 첫번째 요소의 앞을 가르킨다.
		- rear는 마지막 요소를 가리킨다.
		- 삽입일 때 처음에는 front, rear는 모두 0 이고, 삽입 시에는 rear가 먼저 증가하고, 증가된 위치에 새로운 데이터가 삽입된다.
		- 삭제시일 때 front가 먼저 증가된 다음, 증가된 위치에서 데이터를 삭제한다.
		- front와 rear가 값이 같으면 원형 큐가 비어 있다.
		- 원형 큐에서는 하나의 자리는 항상 비워둔다. (front와 rear가 역으로 한칸 차이일때 까지 가능 ([rear][][front]))
		- 공백상태 : front == rear
		- 포화상태 : front 가 rear보다 하나 앞에 있으면 front > rear

		삽입
			[(front)(rear)][][][][] -> A 삽입. -> [(front)][(rear)A][][][] -> B 삽입 -> [(front)][A][(rear)B][][]
			고로 초기에는 front, rear 모두 0인 상태에서 원소 1개가 들어갈 때 마다 rear가 ++된다.
			front는 항상 맨 처음 요소의 앞을 가르키므로 front는 0 인덱스이며 값이 들어가선 안된다. (1부터 원소 삽입)

		삭제
			[(front)][A][(rear)B][][] -> A 삭제 -> [][(front)][(rear)B][][]
			고로 삭제시에는 front가 ++되고 front 자리의 원소를 제거한다.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

typedef int element;

typedef struct {
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

void error(char* msg) {
	fprintf(stderr, "ERR! %s\n", msg);
	exit(1);
}

void init(QueueType* queue) {
	queue->front = queue->rear = 0;
}

void frontRear(QueueType* queue) {
	printf("front : %d	/	rear : %d  ", queue->front, queue->rear);
	printf("\n");
}

int is_empty(QueueType* queue) {
	return queue->front == queue->rear; //empty -> true
}

int is_full(QueueType* queue) {
	return(queue->front == (queue->rear + 1) % MAX_QUEUE_SIZE); //front가 rear보다 1개 더 많다면 [rear][front]
																//같거나 더 적을 순 있지만 더 많을 수는 없다.
}

element enqueue(QueueType* queue, element item) {
	if (is_full(queue))
		error("포화 상태입니다.");
	//printf("before : %d\n\n", queue->rear);
	queue->rear = (++queue->rear) % MAX_QUEUE_SIZE;
	queue->queue[queue->rear] = item;
	//printf("after : %d\n\n", queue->rear);

	return item;
}

//반환만
element peek(QueueType* queue) {

	if (is_empty(queue))
		error("빈 상태입니다.");

	return queue->queue[(queue->front+1)];
}

//반환 후 삭제
element dequeue(QueueType* queue) {

	element rtn = peek(queue);

	queue->queue[queue->front++] = 0;

	return rtn;
	
}



void display(QueueType* queue) {
	printf("\n<- [front]  ");
	for (int i = (queue->front + 1); i <= queue->rear; i++) {
		printf("  [%d]  ", queue->queue[i]);
	}
	printf("  <- rear\n");
}



main() {
	QueueType queue;

	init(&queue); //초기화

	printf("요소 %d 추가! \n", enqueue(&queue, 10));
	printf("요소 %d 추가! \n", enqueue(&queue, 15));
	printf("요소 %d 추가! \n\n", enqueue(&queue, 12));
	
	
	

	display(&queue);

	printf("\n맨 앞에 있는 요소는.. : %d\n\n", peek(&queue));

	printf("\n요소 %d 삭제! \n\n", dequeue(&queue));

	display(&queue);


}