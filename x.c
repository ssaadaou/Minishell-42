#include <stdio.h>
#include <string.h>

void substring_before_equal(const char *str, char *result, size_t result_size) {
    // Find the position of the first '=' character in the string
    const char *equal_sign = strchr(str, '=');

    if (equal_sign != NULL) {
        // Calculate the length of the substring before '='
        size_t length = equal_sign - str;

        // Check if the result buffer is large enough
        if (length < result_size) {
            // Copy the substring before '=' into the result buffer
            strncpy(result, str, length);
            result[length] = '\0'; // Null-terminate the result
        }
    } else {
        // '=' was not found in the string, so copy the entire string
        strncpy(result, str, result_size);
        result[result_size - 1] = '\0'; // Ensure null-termination
    }
}

int main() {
    const char *input1 = "example=text";
    const char *input2 = "noequalsignhere";
    char result1[256]; // Assuming a maximum result size of 256 characters
    char result2[256];

    substring_before_equal(input1, result1, sizeof(result1));
    substring_before_equal(input2, result2, sizeof(result2));

    printf("Result 1: %s\n", result1); // Should print "example"
    printf("Result 2: %s\n", result2); // Should print "noequalsignhere"

    return 0;
}
