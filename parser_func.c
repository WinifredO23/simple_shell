#include "shell.h"
/**
 * is_cmd - determines an executable file
 * @info: info struct
 * @path: path to the file
 * Return: 1 if true, else 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - duplicates char
 * @pathstr: PATH
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			buf[j++] = pathstr[i];
		}
	}
	buf[j] = 0;
	return (buf);
}
/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return:path or Null
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int curr_pos = 0;
	char *path;
	int i;

	if (!pathstr)
		return (NULL);

	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	for (i = 0; ; i++)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(&pathstr[curr_pos], 0, i - curr_pos);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
			{
				return (path);
			}
			if (!pathstr[i])
			{
				break;
			}
			curr_pos = i + 1;
		}
	}
	return (NULL);

}
