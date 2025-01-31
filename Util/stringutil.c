#include <stdio.h>
#include <string.h>
#include <Util/stringutil.h>

bool string_starts_with(const char *str, const char *prefix) {
    size_t lenStr = strlen(str);
    size_t lenPrefix = strlen(prefix);
    if (lenPrefix > lenStr) {
        return false;
    }

    return strncmp(str, prefix, lenPrefix) == 0;
}
