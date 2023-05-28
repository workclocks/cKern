int atoi(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle negative numbers
    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    // Iterate through each character of the string
    while (str[i] != '\0') {
        // Convert character to digit
        int digit = str[i] - '0';

        // Accumulate the number
        result = result * 10 + digit;

        // Move to the next character
        i++;
    }

    // Apply the sign
    return sign * result;
}
