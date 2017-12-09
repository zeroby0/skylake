#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("max rt priority: %d\n",sched_get_priority_max());
	printf("min rt priority: %d\n",sched_get_priority_min());
}