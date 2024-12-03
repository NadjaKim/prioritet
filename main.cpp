#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
	int id;
	int time_for_job;
	int prior;
	struct Process* next;
}process;

process* read_all_process(int n) {
	int a = 0, b = 0, c = 0;
	scanf("%d %d %d", &a, &b, &c);
	process* first = (process*)malloc(sizeof(process));
	process* prev = NULL, * curr = NULL;
	first->id = a;
	first->time_for_job = b;
	first->prior = c;
	first->next = NULL;
	prev = first;
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		curr = (process*)malloc(sizeof(process));
		curr->id = a;
		curr->time_for_job = b;
		curr->prior = c;
		curr->next = NULL;
		prev->next = curr;
		prev = curr;
	}
	return first;
}

void execute(int n, process** first) {
	process* curr = NULL, * prev = NULL;
	prev = *first, curr = (*first)->next;
	for (int i = 0; i < n - 1; i++) {
		prev = *first;
		curr = (*first)->next;
		for (int j = 0; j < n - 1; j++) {
			if (curr->prior > prev->prior) {
				int temp1 = prev->id;
				int temp2 = prev->time_for_job;
				int temp3 = prev->prior;
				prev->id = curr->id;
				prev->time_for_job = curr->time_for_job;
				prev->prior = curr->prior;
				curr->id = temp1;
				curr->time_for_job = temp2;
				curr->prior = temp3;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	curr = *first;
	while (curr != NULL) {
		printf("process %d zakonchil ispolneni\n", curr->id);
		process* for_delete = curr;
		curr = curr->next;
		for_delete->next = NULL;
		free(for_delete);
	}
}

int main() {
	int n = 0;
	scanf("%d ", &n);
	process* first, * prev = NULL, * curr = NULL;
	first = read_all_process(n);
	curr = first;
	execute(n, &first);
	return 0;
}