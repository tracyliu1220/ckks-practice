#include <bits/stdc++.h>
#include "CKKSEncoder.h"
#include "CKKSEncryptor.h"
#include "vector_ops.h"
#include "ciphertext.h"

using namespace std;

const int print_width = 8;
int length;

void print_message(string name, const vector<complex<double>> & message) {
    cout << name << ":\t";
    for (int i = 0; i < length; i++) {
        cout << setw(print_width) << message[i].real() << ' ';
    }
    cout << endl;
}

void test_ciphertext_plaintext_addition(
        vector<complex<double>> a,
        vector<complex<double>> b,
        CKKSEncoder encoder,
        CKKSEncryptor encryptor) {
    cout << "\033[38;5;123m=== ciphertext plaintext addition ===\033[0m" << endl;
    print_message("a", a);
    print_message("b", b);

    vector<long long> encoded_a = encoder.encode(a);
    vector<long long> encoded_b = encoder.encode(b);

    Ciphertext encrypted_a = encryptor.encrypt(encoded_a);

    Ciphertext encrypted_result = encrypted_a + encoded_b;

    vector<long long> encoded_result = encryptor.decrypt(encrypted_result);
    vector<complex<double>> result = encoder.decode(encoded_result);

    print_message("result", result);
    cout << "answer:\t";
    for (int i = 0; i < length; i++) {
        cout << setw(print_width) << a[i].real() + b[i].real() << ' ';
    }
    cout << endl;
}

void test_ciphertext_plaintext_multiplication(
        vector<complex<double>> a,
        vector<complex<double>> b,
        CKKSEncoder encoder,
        CKKSEncryptor encryptor) {
    cout << "\033[38;5;123m=== ciphertext plaintext multiplication ===\033[0m" << endl;
    print_message("a", a);
    print_message("b", b);

    vector<long long> encoded_a = encoder.encode(a);
    vector<long long> encoded_b = encoder.encode(b);

    Ciphertext encrypted_a = encryptor.encrypt(encoded_a);

    Ciphertext encrypted_result = encrypted_a * encoded_b;
    encrypted_result.rescale();

    vector<long long> encoded_result = encryptor.decrypt(encrypted_result);
    vector<complex<double>> result = encoder.decode(encoded_result);

    print_message("result", result);
    cout << "answer: ";
    for (int i = 0; i < length; i++) {
        cout << setw(print_width) << a[i].real() * b[i].real() << ' ';
    }
    cout << endl;
}

void test_ciphertext_ciphertext_addition(
        vector<complex<double>> a,
        vector<complex<double>> b,
        CKKSEncoder encoder,
        CKKSEncryptor encryptor) {
    cout << "\033[38;5;123m=== ciphertext ciphertext addition ===\033[0m" << endl;
    print_message("a", a);
    print_message("b", b);

    vector<long long> encoded_a = encoder.encode(a);
    vector<long long> encoded_b = encoder.encode(b);

    Ciphertext encrypted_a = encryptor.encrypt(encoded_a);
    Ciphertext encrypted_b = encryptor.encrypt(encoded_b);

    Ciphertext encrypted_result = encrypted_a + encrypted_b;

    vector<long long> encoded_result = encryptor.decrypt(encrypted_result);
    vector<complex<double>> result = encoder.decode(encoded_result);

    print_message("result", result);
    cout << "answer: ";
    for (int i = 0; i < length; i++) {
        cout << setw(print_width) << a[i].real() + b[i].real() << ' ';
    }
    cout << endl;
}

void test_ciphertext_ciphertext_multiplication(
        vector<complex<double>> a,
        vector<complex<double>> b,
        CKKSEncoder encoder,
        CKKSEncryptor encryptor) {
    cout << "\033[38;5;123m=== ciphertext ciphertext multiplication ===\033[0m" << endl;
    print_message("a", a);
    print_message("b", b);

    vector<long long> encoded_a = encoder.encode(a);
    vector<long long> encoded_b = encoder.encode(b);

    Ciphertext encrypted_a = encryptor.encrypt(encoded_a);
    Ciphertext encrypted_b = encryptor.encrypt(encoded_b);

    Ciphertext encrypted_result = encrypted_a * encrypted_b;
    encrypted_result.rescale();

    vector<long long> encoded_result = encryptor.decrypt(encrypted_result);
    vector<complex<double>> result = encoder.decode(encoded_result);

    print_message("result", result);
    cout << "answer: ";
    for (int i = 0; i < length; i++) {
        cout << setw(print_width) << a[i].real() * b[i].real() << ' ';
    }
    cout << endl;
}

/*
int M = 16;
int N = M / 2;
int scale = 10000000;

CKKSEncoder encoder(M, scale);

mpz_class q0("100000000");
vector<mpz_class> p = {scale, scale};
mpz_class P = 10000000000;

CKKSEncryptor encryptor(N, q0, p, P);
*/

int main() {
    length = 4;

    int M = 16;
    int N = M / 2;
    int scale = 10000000;

    CKKSEncoder encoder(M, scale);

    mpz_class q0("100000000");
    vector<mpz_class> p = {scale, scale};
    mpz_class P = 10000000000;

    CKKSEncryptor encryptor(N, q0, p, P);

    vector<complex<double>> message1 = {1, 2.5, 3, 4};
    vector<complex<double>> message2 = {4, 3, 2, 1};

    message1.resize(N / 2);
    message2.resize(N / 2);

    fill(message1.begin() + length, message1.end(), 0);
    fill(message2.begin() + length, message2.end(), 0);

    test_ciphertext_plaintext_addition(message1, message2, encoder, encryptor);
    test_ciphertext_plaintext_multiplication(message1, message2, encoder, encryptor);
    test_ciphertext_ciphertext_addition(message1, message2, encoder, encryptor);
    test_ciphertext_ciphertext_multiplication(message1, message2, encoder, encryptor);
}
