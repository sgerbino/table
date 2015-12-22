#include <table.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("table major version: %d\n", table_get_major_version());
	printf("table minor version: %d\n", table_get_minor_version());
	printf("table patch version: %d\n", table_get_patch_version());
	printf("table version: %s\n", table_get_version());
	return 0;
}
