#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>


int main(int ac, char **av)
{
	int				errno;
	DIR				*dir;
	struct dirent	*entry;
	struct stat		buf;

	if (ac != 2)
	{
		errno = EINVAL;
		perror("");
		exit(1);
	}
	if (!(dir = opendir(av[1])))
	{
		perror("");
		exit(1);
	}
	while ((entry = readdir(dir)))
	{
		printf("%s", entry->d_name);
		lstat(entry->d_name, &buf);
		printf(" %lld\n", buf.st_size);
	}
	perror("");
	return (0);
}
