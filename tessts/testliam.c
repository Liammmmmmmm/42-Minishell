
int wildcard_match(const char *pattern, const char *str) {
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (wildcard_match(pattern + 1, str) || (*str && wildcard_match(pattern, str + 1)));
	if (*pattern == *str)
		return (wildcard_match(pattern + 1, str + 1));
	return (0);
}

char *ft_realloc(char *str, size_t new_len)
{
	int	len_str;
	char *new_str;

	len_str = ft_sstrlen(str);
	new_str = malloc(sizeof(char) * (ft_sstrlen + new_len));
	if (new_str == NULL)
	{
		free(str);
		return(NULL);
	}
	ft_memcpy(new_str, str, len_str);
	free(str);
	return (new_str);
}

char *wildcard_loop(char *result, DIR *dir, const char *pattern)
{
	struct dirent* entry;
	size_t total_length;

	total_length = 1;
	entry = readdir(dir);
	while (entry != NULL) 
	{
		if (!(ft_strcmp(entry->d_name, ".") == 0
				|| ft_strcmp(entry->d_name, "..") == 0)
			&& wildcard_match(pattern, entry->d_name))
		{
			total_length += ft_sstrlen(entry->d_name) + 2;
			result = realloc(result, total_length);
			if (!result) {
				perror("realloc");
				closedir(dir);
				return (NULL);
			}
			ft_strcat(result, " ");
			ft_strcat(result, entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (result);
}

char *concat_wildcard(const char *pattern)
{
    DIR *dir;
	char* result;

	dir  = opendir(".");
    if (!dir) {
        perror("opendir");
        return NULL;
    }
    result = malloc(1);
    if (!result) {
        perror("malloc");
        closedir(dir);
        return NULL;
    }
    result[0] = '\0';
	result = wildcard_loop(result, dir, pattern);
	if (result == NULL)
		return (NULL);
	if (result[0] == '\0')
		return (ft_strdup(pattern));
    return (result);
}


