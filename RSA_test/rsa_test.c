#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int main() {
    // 读取公钥
    FILE *publicKeyFile = fopen("public_key.pem", "r");
    if (publicKeyFile == NULL) {
        printf("无法打开公钥文件\n");
        return -1;
    }
    RSA *publicKey = PEM_read_RSA_PUBKEY(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);
    if (publicKey == NULL) {
        printf("无法读取公钥\n");
        return -1;
    }

    // 读取待加密的文件内容
    FILE *inputFile = fopen("test.txt", "rb");
    if (inputFile == NULL) {
        printf("无法打开输入文件\n");
        return -1;
    }
    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    printf("filesize:%d\n", fileSize);
    fseek(inputFile, 0, SEEK_SET);
    unsigned char *fileContent = malloc(fileSize);
    fread(fileContent, 1, fileSize, inputFile);
    fclose(inputFile);

    // 计算加密后的数据长度
    int rsaSize = RSA_size(publicKey);
    printf("rsasize:%d\n", rsaSize);
    unsigned char *encryptedData = malloc(rsaSize);

    // 进行RSA加密
    int result = RSA_public_encrypt(fileSize, fileContent, encryptedData, publicKey, RSA_PKCS1_PADDING);
    if (result == -1) {
        printf("加密失败： %s\n", ERR_error_string(ERR_get_error(), NULL));
        return -1;
    }

    // 将加密后的数据写入输出文件
    FILE *outputFile = fopen("encrypted_data.bin", "wb");
    if (outputFile == NULL) {
        printf("无法打开输出文件\n");
        return -1;
    }
    fwrite(encryptedData, 1, rsaSize, outputFile);
    fclose(outputFile);

    // 释放内存和关闭密钥
    free(fileContent);
    free(encryptedData);
    RSA_free(publicKey);

    printf("加密成功\n");
    return 0;
}

