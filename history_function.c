#include "shell.h"
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 * Return: allocated string containing history file
 */
char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int linecount = 0;
	int last;
	int i;
	ssize_t fd, rdlen;
	ssize_t fsize = -1;
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
/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *n = NULL;

	if (info->history)
	{
		n = info->history;
	}

	add_node_end(&n, buf, linecount);
	if (!info->history)
	{
		info->history = n;
	}
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	if (!info->history)
		return (0);

	for (; node; node = node->next)
	{
		node->num = i++;
	}
	return (info->histcount = i);
}
