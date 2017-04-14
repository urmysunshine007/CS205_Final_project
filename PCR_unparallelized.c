/////Cs205 final project PCR code
//// parallelization version

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>


int main(void){


    
    FILE * fp;
    char * line = (char*)malloc(1000);
    size_t len = 0;
    ssize_t read;

    fp = fopen("out1.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    

    ////Get the length of file (N)
    int N = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        N++;
    }
    fclose(fp);


    char * malware = "/sbin/modprobe/This_is_a_malware";
    int num_chars_malware = strlen(malware);


    int Table_signature[N][20];

    int pos;
    
    for (pos  = 0; pos < N; pos ++){ //insert malware at pos

        FILE * fp;
        char * line = (char*)malloc(1000); /* CHANGE 1 */
        size_t len = 0;
        ssize_t read;

        fp = fopen("out1.txt", "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);

        SHA_CTX ctx;
        SHA1_Init(&ctx);

        int line_index = 0;
        while ((read = getline(&line, &len, fp)) != -1) {

            if(line_index == pos){//insert malware here
                SHA1_Update(&ctx, malware, num_chars_malware);
            }
            
            // line_head points to the beginning of application "measurement"
            char* line_head = strchr(line, '/');
            int num_chars = strlen(line_head) - 1;

            // Hash each piece of data as it comes in:
            SHA1_Update(&ctx, line_head, num_chars);

            line_index++;
        }

        fclose(fp);
        if (line)
            free(line);
        //exit(EXIT_SUCCESS);

        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1_Final(hash, &ctx);

        /* CHANGE 2 */
        
        int i;
        for (i = 0; i < SHA_DIGEST_LENGTH; i++)
            Table_signature[pos][i]= hash[i];
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < 20; j++){
            printf("%d ", Table_signature[i][j]);
        }
        printf("\n");
    }
}

