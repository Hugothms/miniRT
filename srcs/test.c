#include "../includes/minirt.h"
#include "../lib/libft/includes/libft.h"

void hexDump(char *desc, void *addr, int len)
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf("  %s\n", buff);

            // Output the offset.
            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = pc[i];
        }

        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf("  %s\n", buff);
}

int main()
{
	// printf("%s\n", screenshot_datetime());
	int fd = open("Screenshot 2020-02-21 20/09/01.bmp", O_RDONLY);
	char *memory = malloc((3*4 * 4 + 54) * sizeof(char));
	read(fd, memory, 3*4 * 4 + 54);
	printf("%s\n",memory);
	hexDump("memory", memory, 3*4 * 4 + 54);
	free(memory);

	fd = open("Screenshot 2020-02-21 20/18/12.bmp", O_RDONLY);
	memory = malloc((3*4 * 4 + 54) * sizeof(char));
	read(fd, memory, 3*4 * 4 + 54);
	printf("%s\n",memory);
	hexDump("\nmemory", memory, 3*4 * 4 + 54);
	free(memory);
}

