#include <stdio.h>
#include <stdlib.h>

typedef  struct data_type{
	int age;
	char name[20];
} data;
static data *bob;
int main(int argc,char* argv){
		bob = (data *) malloc( sizeof(data) );
	if( bob != NULL ) {
		bob->age = 22;
		strcpy( bob->name, "Robert" );
		printf( "%s is %d years old\n", bob->name, bob->age );
	}else{
		printf("malloc error!\n");
		exit(1);
	}
	free( bob );
	bob = NULL;
}
