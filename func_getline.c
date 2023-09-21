#include "shell.h"
/**
 * input_buf - chain of buffer commands
 * @info: struct
 * @buf: address
 * @len: address
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t l = 0;
	size_t length = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		l = getline(buf, &length, stdin);
#else
		l = _getline(info, buf, &length);
#endif
		if (l > 0)
		{
			if ((*buf)[l - 1] == '\n')
			{
				(*buf)[l - 1] = '\0';
				l--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = l;
				info->cmd_buf = buf;
			}
		}
	}

	return (l);
}
/**
 * get_input - gets a line minus the newline
 * @info: struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *chain_buffer;
	static size_t current_position, next_command_start, buffer_length;
	ssize_t bytes_read = 0;
	char **command_pointer = &(info->arg);
	char *command_start_pointer;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &chain_buffer, &buffer_length);

	if (bytes_read == -1)
		return (-1);
	if (buffer_length)
	{
		next_command_start = current_position;
		command_start_pointer = chain_buffer + current_position;
		check_chain(info, chain_buffer, &next_command_start, current_position, buffer_length);

		while (next_command_start < buffer_length)
		{
			if (is_chain(info, chain_buffer, &next_command_start))
				break;
			next_command_start++;
		}
		current_position = next_command_start + 1;
		if (current_position >= buffer_length)
		{
			current_position = buffer_length = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*command_pointer = command_start_pointer;
		return (_strlen(command_start_pointer));
	}

	*command_pointer = chain_buffer;
	return (bytes_read);
}
/**
 * read_buf - reads a buffer
 * @info: struct
 * @buf: buffer
 * @i: size i
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
/**
 * _getline - gets next line of input from STDIN
 * @info: struct
 * @ptr: address of pointer to buffer
 * @length: size pf pointer allocated
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
	{
		s = *length;
	}
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');

	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
	{
		if (p)
			free(p);
		return (-1);
	}
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - unable ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(int sig_num)
{
	(void)sig_num;
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

