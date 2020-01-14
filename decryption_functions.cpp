#include "decryption_functions.h"

void decrypt_cipher(PlainText & deciphered, CipherText & cipher, KeySequence &key)
{
	cipher.calc_length();

	for (int i = 0; i < cipher.return_length(); i++)
	{
		if (cipher[i] >= 65 && cipher[i] <= 90)
		{
			deciphered.push_front((cipher[i] - key[i]) + 65);
			if (deciphered[i] < 65)
				deciphered.mod_at(i, deciphered[i] + 26);
		}
		else
			deciphered.push_front(cipher[i]);
	}
}
 