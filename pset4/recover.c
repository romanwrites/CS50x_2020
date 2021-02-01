#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

_Bool is_jpeg(const uint8_t *block) {
	if (block[0] == 0xff && \
		block[1] == 0xd8 && \
		block[2] == 0xff && \
		block[3] >= 0xe0)
		return 1;
	return 0;
}

char *get_name(int num) {
	char *name = malloc(sizeof(char) * 7 + 1);
	name[3] = '.';
	name[4] = 'j';
	name[5] = 'p';
	name[6] = 'g';
	name[7] = '\0';
	if (num < 10) {
		name[0] = '0';
		name[1] = '0';
		name[2] = num + '0';
	} else if (num < 100) {
		name[0] = '0';
		name[1] = num / 10 + '0';
		name[2] = num % 10 + '0';
	} else {
		name[0] = num / 100 + '0';
		num %= 100;
		name[1] = num / 10 + '0';
		name[2] = num % 10 + '0';
	}
	return name;
}

void read_it(FILE *f, _Bool flag, int num_name, uint32_t bytes_read, char *name);

void routine(FILE *f, _Bool flag, int num_name, uint32_t bytes_read, char *name, FILE *new_jpeg) {
	uint8_t block[BLOCK];

	while ((bytes_read = fread(block, 1, BLOCK, f)) > 0) {
		if (is_jpeg(block)) {
			fclose(new_jpeg);
			name = get_name(num_name);
			new_jpeg = fopen(name, "w");
			fwrite(block, 1, BLOCK, new_jpeg);
			flag = 1;
			read_it(f, flag, num_name + 1, bytes_read, name);
		} else {
			fwrite(block, 1, BLOCK, new_jpeg);
		}
	}
}

void read_it(FILE *f, _Bool flag, int num_name, uint32_t bytes_read, char *name) {
	uint8_t block[BLOCK];

	while (bytes_read > 0) {
		if (!flag && (bytes_read = fread(block, 1, BLOCK, f)) > 0) {
			if (is_jpeg(block)) {
				name = get_name(num_name);
				FILE *new_jpeg = fopen(name, "w");
				free(name);
				fwrite(block, 1, BLOCK, new_jpeg);
				num_name++;
				routine(f, flag, num_name, bytes_read, NULL, new_jpeg);
			}
		} else if (flag) {
			FILE *new_jpeg = fopen(name, "a");
			free(name);
			fwrite(block, 1, BLOCK, new_jpeg);
			flag = 0;
			routine(f, flag, num_name, bytes_read, NULL, new_jpeg);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: ./recover image\n");
		return 1;
	}

	FILE *f = fopen(argv[1], "r");

	if (!f) {
		printf("Couldn't open the file\n");
		return 1;
	}

	read_it(f, 0, 0, 1, NULL);
	fclose(f);
}

