
#define PRIbin4 "%c%c%c%c"
#define PRIbin8 PRIbin4 PRIbin4
#define PRIbin16 PRIbin8 PRIbin8
#define PRIbin32 PRIbin16 PRIbin16
#define binary4(byte)  \
  (byte & 0x0001 ? '1' : '0'), \
  (byte & 0x0002 ? '1' : '0'), \
  (byte & 0x0004 ? '1' : '0'), \
  (byte & 0x0008 ? '1' : '0') 

#define binary8(byte) \
  binary4(byte), \
  (byte & 0x0010 ? '1' : '0'), \
  (byte & 0x0020 ? '1' : '0'), \
  (byte & 0x0040 ? '1' : '0'), \
  (byte & 0x0080 ? '1' : '0') 

#define binary12(byte) \
  binary8(byte), \
  (byte & 0x0100 ? '1' : '0'), \
  (byte & 0x0200 ? '1' : '0'), \
  (byte & 0x0400 ? '1' : '0'), \
  (byte & 0x0800 ? '1' : '0') 

#define binary16(byte) \
  binary12(byte), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x8000 ? '1' : '0') 

#define binary20(byte) \
  binary16(byte), \
  (byte & 0x10000 ? '1' : '0'), \
  (byte & 0x20000 ? '1' : '0'), \
  (byte & 0x40000 ? '1' : '0'), \
  (byte & 0x80000 ? '1' : '0') 

#define binary24(byte) \
  binary20(byte), \
  (byte & 0x100000 ? '1' : '0'), \
  (byte & 0x200000 ? '1' : '0'), \
  (byte & 0x400000 ? '1' : '0'), \
  (byte & 0x800000 ? '1' : '0') 

#define binary28(byte) \
  binary24(byte), \
  (byte & 0x1000000 ? '1' : '0'), \
  (byte & 0x2000000 ? '1' : '0'), \
  (byte & 0x4000000 ? '1' : '0'), \
  (byte & 0x8000000 ? '1' : '0') 

#define binary32(byte) \
  binary28(byte), \
  (byte & 0x10000000 ? '1' : '0'), \
  (byte & 0x20000000 ? '1' : '0'), \
  (byte & 0x40000000 ? '1' : '0'), \
  (byte & 0x80000000 ? '1' : '0') 

