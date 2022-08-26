# Yet another secure password generator

The security is based on the safety of random device(which is good for most system) and arc4random(ChaCha20 for Linux and AES for macOS).

# The required security bits

The Bitcoin hash rate is about 200E, which is 67 bits every second.
We believe it's practicable to use 128 seconds of total world hash power, which is 74 bits.
Add with 1 bit as margin, it should be my preferred password security for a plain md5.

The normal s2k is 26 bits. We aim a password of 49 bits for good security for encrypt, though it must be combined with either u, h, or both as a defence.

As the defence should provide another 15 bit of security, 35 bit is enough. So the password length should be at least 6.

We use 37 bits for password. for convinence, reduce it into 6 charactor password yearly. It should be **TRUE RANDOM** password.

Still, **NEVER USE ANYTHING WITHOUT A PASSWORD MANAGER IF IT IS NOT WELL KDFED**. S2K, PBKDF2 or scrypt all can be regard as good kdf solution. For things like a simple MD5, **YOU SHOULD NEED 100 BIT OF ENTROPY, 17 charactors**.

In summary:

 * 6 charactors true random password for compound header
 * 17 charactors true random password for non-protected security
