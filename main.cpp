#include <bits/stdc++.h>
#include "CKKSEncoder.h"
#include "CKKSEncryptor.h"
#include "vector_ops.h"
#include "ciphertext.h"

using namespace std;

int main() {
    int M = 16;
    int N = M / 2;
    int scale = 100000;

    CKKSEncoder encoder(M, scale);
    // CKKSEncryptor encryptor(N, 1073741824, {1021, 1019});
    CKKSEncryptor encryptor(N, 1000000000, {100000, 100000});

    vector<complex<double>> message = {1, 2.5, 3, 4};
    vector<complex<double>> message2 = {1, 1, 1, 1};
    vector<complex<double>> message3 = {2, 3, 4, 5};

    vector<long long> encoded = encoder.encode(message);
    vector<long long> encoded2 = encoder.encode(message2);
    vector<long long> encoded3 = encoder.encode(message3);

    for (int i = 0; i < (int)encoded.size(); i++) {
        cout << encoded[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < (int)encoded.size(); i++) {
        cout << encoded2[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < (int)encoded.size(); i++) {
        cout << encoded3[i] << ' ';
    }
    cout << endl;

    // for (int i = 0; i < (int)encoded.size(); i++) {
    //     encoded[i] += 100;
    //     encoded2[i] += 100;
    //     encoded3[i] += 100;
    // }

    Ciphertext encrypted = encryptor.encrypt(encoded);
    Ciphertext encrypted2 = encryptor.encrypt(encoded2);
    Ciphertext encrypted3 = encryptor.encrypt(encoded3);

    /*
    for (int i = 0; i < (int)encrypted.c1.size(); i++) {
        cout << encrypted.c1[i] << ' ' << encrypted2.c1[i] << endl;
    }
    */

    // for (int i = 0; i < (int)encrypted.c1.size(); i++) {
    //     cout << encrypted.c1[i] << ' ' << encrypted2.c1[i] << endl;
    // }

    encrypted = encrypted * encoded;
    cout << "orig Q: " << encrypted.Q << endl;
    encrypted.rescale();
    cout << "new Q: " << encrypted.Q << endl;
    // encrypted = encrypted + encrypted;

    // for (int i = 0; i < (int)encrypted.c0.size(); i++) {
    //     encrypted.c0[i] *= 2;
    //     encrypted.c1[i] *= 2;
    // }

    vector<long long> decrypted = encryptor.decrypt(encrypted);

    // for (int i = 0; i < (int)decrypted.size(); i++) {
    //     decrypted[i] -= 200; // TODO
    // }
    cout << "decrypted:" << endl;
    for (int i = 0; i < (int)decrypted.size(); i++) {
        cout << decrypted[i] << ' ';
    }
    cout << endl;

    vector<complex<double>> decoded = encoder.decode(decrypted);
    cout << "decoded:" << endl;
    for (int i = 0; i < (int)decoded.size(); i++) {
        cout << decoded[i] << ' '; // / (double)scale << ' ';
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

    /*
    vector<mpz_class> a1 = {1, 0, 2, 3};
    vector<mpz_class> a2 = {2, 1, 4, 0};
    a1 = polynomial_times(a1, a2, 5);
    for (int i = 0; i < (int)a1.size(); i++) {
        cout << a1[i] << ' ';
    }
    cout << endl;
    */
}
