#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("read_error.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	close(fd);
	free(str);
	// printf("%d", strcmp("aaaaaaaaaa\n", str));
	// close(fd);
}
