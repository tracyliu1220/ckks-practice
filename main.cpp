#include <bits/stdc++.h>
#include "CKKSEncoder.h"
#include "CKKSEncryptor.h"
#include "vector_ops.h"
#include "ciphertext.h"

using namespace std;

int main() {
    int M = 16;
    int N = M / 2;

    CKKSEncoder encoder(M, 1LL << 14);
    CKKSEncryptor encryptor(N);

    vector<complex<double>> message = {1, 2, 3, 4};
    vector<complex<double>> message2 = {2, 2, 1, 1};

    vector<long long> encoded = encoder.encode(message);
    vector<long long> encoded2 = encoder.encode(message2);

    for (int i = 0; i < (int)encoded.size(); i++) {
        cout << encoded[i] << ' ';
    }
    cout << endl;

    Ciphertext encrypted = encryptor.encrypt(encoded);
    Ciphertext encrypted2 = encryptor.encrypt(encoded2);

    for (int i = 0; i < (int)encrypted.c1.size(); i++) {
        cout << encrypted.c1[i] << ' ' << encrypted2.c1[i] << endl;
    }

    encrypted = encrypted + encrypted2;

    for (int i = 0; i < (int)encrypted.c1.size(); i++) {
        cout << encrypted.c1[i] << endl;
    }

    vector<long long> decrypted = encryptor.decrypt(encrypted);

    vector<complex<double>> decoded = encoder.decode(decrypted);
    for (int i = 0; i < (int)decoded.size(); i++) {
        cout << decoded[i] << ' ';
    }
    cout << endl;

    /*
    CKKSEncryptor encryptor(N);

    cout << "secret_key:" << endl;
    for (int i = 0; i < encryptor.secret_key.size(); i++) {
        cout << encryptor.secret_key[i] << ' ';
    }
    cout << endl;

    cout << "public_key:" << endl;
    for (int i = 0; i < encryptor.public_key.first.size(); i++) {
        cout << encryptor.public_key.first[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < encryptor.public_key.second.size(); i++) {
        cout << encryptor.public_key.second[i] << ' ';
    }
    cout << endl;
    */
}
