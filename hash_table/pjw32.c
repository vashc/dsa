#include "pjw32.h"

// hash_pjw32 implements PJW-32 non-cryptographic hash algorithm.
// This implementation is adapted for string hashing
unsigned int hash_pjw32(const char *value) {
    unsigned int hash = 0;
    unsigned int test = 0;

    for (; *value != '\0'; value++) {
        // Shift to the left and add current character bit representation
        hash = (hash << 4) + (*value);

        // Check whether any of four MSB is equal to 1 or not.
        // In case it is, perform right shift by 24 bits
        if ((test = hash & 0xf0000000) != 0) {
            hash = ((hash ^ (test >> 24)) & 0xfffffff);
        }
    }

    return hash;
}
