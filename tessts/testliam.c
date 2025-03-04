#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int wildcard_match(const char *pattern, const char *str) {
    if (*pattern == '\0')
        return (*str == '\0');
    if (*pattern == '*')
        return (wildcard_match(pattern + 1, str) || (*str && wildcard_match(pattern, str + 1)));
	if (*pattern == *str)
        return (wildcard_match(pattern + 1, str + 1));
    return (0);
}

// Fonction de test
void test_wildcard_match(const char *pattern, const char *str) {
    if (wildcard_match(pattern, str)) {
        printf("Le motif \"%s\" correspond à la chaîne \"%s\"\n", pattern, str);
    } else {
        printf("Le motif \"%s\" ne correspond pas à la chaîne \"%s\"\n", pattern, str);
    }
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char* concat_subdirs(void)
{
    DIR* dir;
	size_t total_length = 1;
	char* result;
    struct dirent* entry;
	
	dir  = opendir(path);
    if (!dir) {
        perror("opendir");
        return NULL;
    }
    result = malloc(total_length);
    if (!result) {
        perror("malloc");
        closedir(dir);
        return NULL;
    }
    result[0] = '\0';
    while ((entry = readdir(dir)) != NULL) 
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		size_t needed = strlen(sep) + strlen(entry->d_name) + 1;
		char* new_result = realloc(result, total_length + needed);
		if (!new_result) {
			perror("realloc");
			free(result);
			closedir(dir);
			return NULL;
		}
		result = new_result;
		strcat(result, " ");
		strcat(result, entry->d_name);
		total_length += needed;
    }

    closedir(dir);
    return result;
}

int main(void)
{
    char* all_subdirs = concat_wildcard(".");
    if (all_subdirs) {
        printf("Sous-dossiers concaténés : %s\n", all_subdirs);
        free(all_subdirs);
    }
    return 0;
}

