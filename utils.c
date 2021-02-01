/****************************************************************

Name: utils.c

Description:
    Utilites and other stuff used to make life easier.

****************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Include openssl for hashing and base64 decoding
#include <openssl/md5.h>

#include <openssl/bio.h>
#include <openssl/evp.h>

// Check to see if a file exists
int file_exists (char *filename) {
	if( access( filename, F_OK ) == 0 ) {
		return(1);
	} else {
		return(0);
	}
}

// Conversion for epoch time used in the timeline
char *epoch_to_datetime(char * input_time){
    time_t epoch_time = atoi(input_time);
    struct tm ts;
    static char modified_time[80];
    ts = *localtime(&epoch_time);
    strftime(modified_time, sizeof(modified_time), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    return modified_time;
}

// Return substring found between two strings
char *find_substring(const char *main_string, const char *start_pattern, const char *end_pattern){

    char *target = NULL;
    char *start, *end;

    if ((start = strstr(main_string, start_pattern))) {
        start += strlen(start_pattern);
        if ((end = strstr(start, end_pattern))) {
            target = (char *)malloc(end - start + 1);
            memcpy(target, start, end - start);
            target[end - start] = '\0';
        }
    }

    return(target);
}

// Hash for forenisc verification that the database file is unchanged
char *md5_hash_file(char *filename) {
    unsigned char c[MD5_DIGEST_LENGTH];
    int i;
    FILE *inFile = fopen (filename, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];
    char output_hash[33];
    static char total[33];

    // Clear the array for when it's called the 2nd time, if not we'll get "hashhash" on the second call instead of "hash"
    memset(total, 0, 33);

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);
    for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
       sprintf(output_hash, "%02x", c[i]);
       strcat(total, output_hash);
    }
    fclose(inFile);
    return(total);
}

// For base64 decode
size_t calcDecodeLength(const char* b64input) { //Calculates the length of a decoded string
	size_t len = strlen(b64input),
		padding = 0;

	if (b64input[len-1] == '=' && b64input[len-2] == '=') //last two chars are =
		padding = 2;
	else if (b64input[len-1] == '=') //last char is =
		padding = 1;

	return (len*3)/4 - padding;
}

// Base64 decode clipboard data - OpenSSL implimentation from https://gist.github.com/barrysteyn/7308212
int base_64_decode(const char* b64message, char** buffer, size_t* length) { //Decodes a base64 encoded string
	BIO *bio, *b64;

	int decodeLen = calcDecodeLength(b64message);
	*buffer = (char*)malloc(decodeLen + 1);
	(*buffer)[decodeLen] = '\0';

	bio = BIO_new_mem_buf(b64message, -1);
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Do not use newlines to flush buffer
	*length = BIO_read(bio, *buffer, strlen(b64message));
	assert(*length == decodeLen); //length should equal decodeLen, else something went horribly wrong
	BIO_free_all(bio);

	return (0); //success
}

// Remove characters from a string
void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}