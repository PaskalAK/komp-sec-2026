#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

void md5_str(char *str, char output[33]){
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)str, strlen(str), digest);

    for(int i=0; i < MD5_DIGEST_LENGTH; i++)
    sprintf(&output[i*2], "%02x", digest[i]);

    output[32] = '\0';
}

int main(){
char target[]= "81dc9bdb52d04dc20036dbd8313ed055";
char input[10];
char hash[33];

for(int i=0; i<=9999; i++){
sprintf(input, "%04dEND", i);
md5_str(input, hash);
if(strcmp(hash, target)== 0){
    printf("Success: %04d\n", i);
    break;
}
}
return 0;


}