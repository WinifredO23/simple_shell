#include "shell.h"
/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int linecount = 0, last, i;
	ssize_t fd, rdlen, fsize = -1;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (fstat(fd, &st) != -1)
		fsize = st.st_size;
	if (fsize < 2)
	{
		close(fd);
		return (0);
	}
	buf = (char *)malloc((size_t)(fsize + 1));
	if (!buf)
	{
		close(fd);
		return (0);
	}
	rdlen = read(fd, buf, (size_t)fsize);
	close(fd);
	if (rdlen <= 0)
	{
		free(buf);
		return (0);
	}
	buf[fsize] = '\0';
	last = 0;
	for (i = 0; i <= fsize; i++)
	{
		if (buf[i] == '\n' || buf[i] == '\0')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}
	info->histcount = linecount;
	while (info->histcount >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
		info->histcount--;
	}
	renumber_history(info);
	free(buf);
	return (info->histcount);
}
