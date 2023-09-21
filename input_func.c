#include "shell.h"

/**
 * open_input_file - Attempt to open an input file
 * @filename: The name of the file to open
 * @info: Information structure for your shell
 *
 * Return: The file descriptor or -1 on failure
 */
int open_input_file(const char *filename, info_t *info)
{
	int fd = open(filename, O_RDONLY);
	char *error_msg;

	if (fd == -1)
	{
		if (errno == EACCES)
		{
			error_msg = "Permission denied: ";
			write(STDERR_FILENO, info->argv[0], _strlen(info->argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			write(STDERR_FILENO, filename, _strlen(filename));
			write(STDERR_FILENO, "\n", 1);
			exit(EXIT_FILE_ACCESS_ERROR);
		}
		if (errno == ENOENT)
		{
			error_msg = "No such file or directory: ";
			write(STDERR_FILENO, info->argv[0], _strlen(info->argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			write(STDERR_FILENO, filename, _strlen(filename));
			write(STDERR_FILENO, "\n", 1);
			exit(EXIT_FILE_NOT_FOUND);
		}
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

