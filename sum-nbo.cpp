#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

void dump(void* p, size_t n){
	uint8_t* u8 = static_cast<uint8_t*>(p);
	size_t i = 0 ;
	while (i < n){
		printf("%02X", u8[i]);
		if (++i % 8 == 0) 
			printf("\n");
	}	
	printf("\n");
}

uint32_t read_and_print(char* filename){
	FILE* fp = fopen(filename, "rb");
	if (!fp) {
		printf("fail: %s\n", filename);
		exit(1);
	}

	uint32_t n;
	size_t read = fread(&n, sizeof(uint32_t), 1, fp);
	fclose(fp);

	if (read != 1){
		printf("fail %s\n", filename);
		exit(1);
	}
	
	uint32_t host_n = ntohl(n);
	printf("%u(0x%08x)", host_n, host_n);
	return host_n;
}

int main(int argc, char* argv[]){
	uint64_t total = 0;

	for (int i =1; i < argc; i++){
		uint32_t val = read_and_print(argv[i]);
		total += val;
		if (i < argc - 1){
			printf(" + ");
		}	
	}

	printf(" = %u(0x%08x)\n", total, total);
	return 0;
}
