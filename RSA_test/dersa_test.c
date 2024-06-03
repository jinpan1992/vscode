#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

int main() {
    // 读取私钥
    FILE *privateKeyFile = fopen("private_key.pem", "r");
    if (privateKeyFile == NULL) {
        printf("无法打开私钥文件\n");
        return -1;
    }
    RSA *privateKey = PEM_read_RSAPrivateKey(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);
    if (privateKey == NULL) {
        printf("无法读取私钥\n");
        return -1;
    }

    // 读取加密后的数据
    FILE *encryptedDataFile = fopen("encrypted_data.bin", "rb");
    if (encryptedDataFile == NULL) {
        printf("无法打开加密数据文件\n");
        return -1;
    }
    fseek(encryptedDataFile, 0, SEEK_END);
    long fileSize = ftell(encryptedDataFile);
    fseek(encryptedDataFile, 0, SEEK_SET);
    unsigned char *encryptedData = malloc(fileSize);
    fread(encryptedData, 1, fileSize, encryptedDataFile);
    fclose(encryptedDataFile);

    // 计算解密后的数据长度
    int rsaSize = RSA_size(privateKey);
    printf("size;%d\n", rsaSize);
    unsigned char *decryptedData = malloc(rsaSize);

    // 进行RSA解密
    int result = RSA_private_decrypt(fileSize, encryptedData, decryptedData, privateKey, RSA_PKCS1_PADDING);
    if (result == -1) {
        printf("解密失败： %s\n", ERR_error_string(ERR_get_error(), NULL));
        return -1;
    }

    // 将解密后的数据写入输出文件
    FILE *outputFile = fopen("decrypted_data.txt", "wb");
    if (outputFile == NULL) {
        printf("无法打开输出文件\n");
        return -1;
    }
    fwrite(decryptedData, 1, rsaSize, outputFile);
    fclose(outputFile);

    // 释放内存和关闭密钥
    free(encryptedData);
    free(decryptedData);
    RSA_free(privateKey);

    printf("解密成功\n");
    return 0;
}

