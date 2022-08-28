# Yet another secure password generator

The security is based on the safety openssl(cryptographic quality rng).

# The required security level in bits

The required security level in bits is computed using public data, and it is
more realistic than most other estimations.

## Security level needed in bits

All data is based on 2022-08-28T00:00:00Z.

The Bitcoin hash rate is about 2.47e20 per second.

The most powerful organization should have \$1.00e7 of ASIC computer power or
\$1.50e8 of generic supercomputing power budget for every password. As far as I
know, it's impossible to spend more computing power than \$1.50e8 budget,
governments will use other methods if they believe the price of cracking a
password is more than \$1.50e8.

The current bitcoin price is \$2.00e5. So the budget can purchase 500 bitcoins,
or the computing power behind it. There is 900 bitcoins mined every day, so
it requires about 0.556 days, or 4.80e4 seconds of mining.

As bitcoin hash rate is 2.47e20, the total hash number that can be tried will be
1.19e25. It represents a security level of 83 bits.

That's the required security level for 2022-08-28T00:00:00Z. The target date of
protection, for me, is 2035-01-01T00:00:00Z. Based on the the computing power
growth[1], the required security level will be 92 bits for everything.

So, we can conclude, the target security level shall be **92 bits**.

## Security level needed for passwords

Passwords are protected by key derivation function, or KDF. Thus the security
level needed for passwords is lower than the raw security level it provides. We
shall consider the KDF for a normal modern computer, e.g., a computer build
after 2012-01-01T00:00:00Z with a budget of \$1.00e3. All calculation below is
assuming the KDF is happened on this computer, within 0.5 seconds.

The weakest KDF function that are commonly used is S2K, the expected hash
iteration is 6.50e7, which is 25.9 bits of additional security level.

PBKDF2, scrypt all provide more bits of security level than S2K. This is the
three most used KDF method in the real world.

Based on the security level calculated above, the required entropy for a
unbreakable password shall be **66 bits**. If you just want to have an
unbreakable password for 2022, the required entropy of a password shall be **57
bits**.

If you are certain that the password is well protected and hardware try count
enforced, like password stored in Secure Enclave of YubiKey or Apple device with
counter lockbox (Apple A14+, S6+ and M1+), I believe it will provide another 12
bits of protection. However, it depends whether your trust a 3rd party. With
secure enclave hardware protation, the required entropy of a password shall be
**45 bits**.

# Password types and required 

## Complete random password with Jyn's charset

I defined the charset used by my password as all upper case and lower case
letters, number from 0 to 9, and underscore. There is 63 possible choices in
each password. We define lg function to represent log function with a base of 2,
or log2.

Let's assume the needed length of password is n.  To generate a password with
underscore, first a random number is generated, to set the position of force
inserted underscore. That process provides a security level of lg(n).

Other n-1 slots is filled with truely random choice of Jyn's charset, which
provides lg(63) each.

To reach a security level of 45 bits, the equation will be
`lg(n) + (n-1)lg(63) = 45`
The n shall be 8 for this security level.

To reach a security level of 57 bits, the equation will be 
`lg(n) + (n-1)lg(63) = 57`
The n shall be 10 for this security level.

To reach a security level of 66 bits, the equation will be 
`lg(n) + (n-1)lg(63) = 66`
The n shall be 12 for this security level.

So a random password with length between 10 and 12 is considered as good for any
usecase currently. If long-term protection is needed, a password of length 12 is
suggested.

To generate this kind of password, you can use passgen like:

```bash 
# Generate 10 random password with a length of 12
passgen

# Generate 10 random password with a length of 11
passgen 11

# Generate 30 random password with a length of 9
passgen 30 9 
```

## Complete random password with words

Random password can be hard to remember. English words will be much easier to
remember. Using word list defined in BIP39, in BIP39, each word provides entropy
of 11 bits. to get a security level of 66 bits, 6 words will be needed. The
password will be underscore linked, an example of such password is:


`assume_myth_near_hope_person_hat`

To generate this kind of password, you can use passgen like:

```bash
# Generate 10 random word password with 6 words
passgen -w

# Generate 10 random password with 7 words
passgen -w 7

# Generate 30 random password with 2 words
passgen -w 30 2
```

# References

1\. A. K. Lenstra, "Key Lengths", The Handbook of Information Security, 2004
