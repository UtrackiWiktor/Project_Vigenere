#pragma once
#include "PlainText.h"
#include "CipherText.h"
#include "KeySequence.h" 

void decrypt_cipher(PlainText &deciphered, CipherText &cipher, KeySequence &key);
