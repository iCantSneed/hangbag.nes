#if !defined(MMC3_H_)
#define MMC3_H_

#define mmc3_bank_select(reg, bank) {\
  *((char*)0x8000) = reg; \
  *((char*)0x8001) = bank; \
}

#define mcc3_nametable_arrangement(arr) *((char*)0xa000) = arr

#endif // MMC3_H_
