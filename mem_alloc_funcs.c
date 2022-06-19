#include "main.h"

/**
 * _memcpy - copies information between memory addresses.
 * @newptr: pointer to the destination address.
 * @ptr: pointer to the source address.
 * @size: size of the new pointer.
 * Return: nothing.
 */

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *ptr_cpy = (char *)ptr;
	char *newptr_cpy = (char *)newptr;
	unsigned int i;

	i = 0;

	while (i < size)
	{
		newptr_cpy[i] = ptr_cpy[i];
		i++;
	}
}


/**
 * _realloc - reallocates a memory block.
 * @ptr: a pointer to the previously allocated memory address.
 * @old_size: the old size of the allocated memory.
 * @new_size: the new size of the allocated memory.
 * Return:a pointer to the allocated memory address.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}


/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */

char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);

	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);
	return (newptr);
}
