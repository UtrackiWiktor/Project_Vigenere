#pragma once
#include <string>
#include "Vigenere_table.h"
#include "PlainText.h"
#include "CipherText.h"
#include "KeySequence.h"

std::string encrypt_txt(std::string &plain_text, std::string key, Vigenere_table &vig_tab);

void encrypt_plain_text(PlainText &plain_txt, CipherText &cipher, KeySequence &key, Vigenere_table &vig_tab);

 