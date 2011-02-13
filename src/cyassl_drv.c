#include <config.h>
#include <types.h>
#include <ctc_hmac.h>
#include <ctc_aes.h>
#include <random.h>
#include <coding.h>

#include "cyassl_drv.h"

int cyassl_init (void)
{
    return 0;
}

int cyassl_gen_iv (scs_t *scs)
{
    RNG rng;
    scs_keyset_t *ks = &scs->cur_keyset;

    if (InitRng(&rng))
        return -1;

    RNG_GenerateBlock(&rng, scs->iv, ks->block_sz);

    return 0;
}

int cyassl_enc (scs_t *scs, uint8_t *in, size_t in_sz, uint8_t *out)
{
    Aes aes;
    scs_keyset_t *ks = &scs->cur_keyset;

    AesSetKey(&aes, ks->key, ks->key_sz, scs->iv, AES_ENCRYPTION);
    AesCbcEncrypt(&aes, out, in, in_sz);

    return 0;
}

int cyassl_tag (scs_t *scs)
{
    /* TODO */
    memset(scs->tag, sizeof scs->tag, 120);
    return 0;
}

void cyassl_term (void) {}