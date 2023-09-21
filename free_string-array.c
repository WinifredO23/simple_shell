#include "shell.h"
/**
 * free_string_array - Frees an array of strings and the array itself.
 * @array: The array of strings to free.
 * It checks if the array is not NULL to avoid segmentation faults.
 */
void free_string_array(char **array)
{
	int i;

	if (array)
	{
		for (i = 0; array[i] != NULL; i++)
		{
			free(array[i]);
		}
		free(array);
	}
}

