# Yet another secure password generator

The security is based on the safety of random device(which is good for most system) and arc4random(ChaCha20 for Linux and AES for macOS).

# The required security bits

The Bitcoin hash rate is about 200E, which is 67 bits every second.

The most powerful organization should have $1 Billion of ASIC computer power, about 42000 bitcoins, which is 47 days of mining.
The 47 days is 4 million seconds or 21bits.

So the maximum possible human archivable password crack can crack about 90 bits of security. The normal PBKDF for SHA can get 19 bits in 50ms and 21 bits in 200 ms.
The entropy of the required password for the most extreme condition is 70 bits. For normal political conditions, only $1 million of real ASIC-based hash power can be used at most, which means 60 bits, or 56 bits for good KDF.

So for the unbreakable password, 56 bits is enough for most cases, unless you are a top 10 target for US, CN or JP, in such cases, password is really not the most serious problem, but 72 bits will provide enough protection even in those cases with a good KDF function.

So for the long-term master password, we suggest 56 bits. For mid-term, secure enclave protected or compound password, we suggest 40 bits. Even an ancient Apple secure enclave can provide 16 bits of protection upon the KDF. The 40 bits are also suitable for most web passwords since I will never use an un-secure web system without a password manager. My password manager will, of course, provide 16 bits more protection over plain KDF.

Still, **NEVER USE ANYTHING WITHOUT A PASSWORD MANAGER IF IT IS NOT WELL KDFED**. S2K, PBKDF2 or scrypt all can be regard as good kdf solution. For things like a simple MD5, **YOU SHOULD NEED 90 BIT OF ENTROPY**.

In summary:

 * 90 bits for no KDF password
 * 72 bits for Top 10 WANTED personal with a good KDF
 * 56 bits for most people with a good KDF, or for Top 10 WANTED personal using hardware based secure enclave protection
 * 40 bits for most people with a hardware based secure enclave or for a website you are sure that has good protection
