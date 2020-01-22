#pragma once
#include <string>

bool input_switches(int argc, char **argv, std::string &plaintxt, std::string &key, std::string &cipher, std::string &encrypt_out, std::string &decrypt_out);

void print_usage_message();