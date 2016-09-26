#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "binary.h"

#define print(x) printf("%20s=" PRIbin32 "\n", #x, binary32((x)))

int leastSignificantBit(uint32_t v){
  static const int MultiplyDeBruijnBitPosition[32] = 
  {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
  };
  return MultiplyDeBruijnBitPosition[((uint32_t)((v & -v) * 0x077CB531U)) >> 27];
}

uint32_t
bitReverse(register uint32_t x)
{
  x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
  x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
  x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
  x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
  return((x >> 16) | (x << 16));
}

struct Label {
 uint8_t startBit = 0;
 uint8_t numBits = 1;
 uint32_t tupleBits = -1;
 uint32_t idxTuple = 0;

 void reset(){
  startBit = 0;
  numBits = 1;
  tupleBits = -1;
  idxTuple = 0;
 }

 void startNext(){
  startBit += numBits;
  numBits = 1;
 }

 bool operator<(const Label& l) const {
  //figure out the least significant bit
  //that differs in the tuple descriptors
  uint32_t myRev = bitReverse(tupleBits);
  uint32_t otherRev = bitReverse(l.tupleBits);
  uint32_t XOR = tupleBits ^ l.tupleBits;
  int secondLeastBit = leastSignificantBit(XOR);
  //create a mask to clear everything after this bit in the reverse
  uint32_t clearMask = uint32_t(-1) << (32-secondLeastBit);
  int ignorePivot = leastSignificantBit(myRev & clearMask);
  if (ignorePivot < 31){
    //now create a mask to clear everything before this bit
    clearMask = uint32_t(-1) << (ignorePivot+1);
    //I only want to compare the bits prior to this bit
    //move everything to the end
    uint32_t myComparator = bitReverse(idxTuple) & clearMask;
    uint32_t otherComparator = bitReverse(l.idxTuple) & clearMask;
    if (myComparator != otherComparator)
      return myComparator < otherComparator;
  }
  //slightly counter-intuitive
  //the larger the number, the more the zeros in the tuple bits
  return myRev > otherRev;
 }

 void operator++() {
  uint32_t maxBits(-1);
  //figure out the largest number that can fit
  maxBits = maxBits ^ (maxBits << numBits); 
  uint32_t clearMask = ~(maxBits << startBit);
  uint32_t tmp = idxTuple >> startBit;
  tmp++;
  if (tmp > maxBits){
    uint32_t tupleBitSetter = ~(maxBits << (startBit + 1));
    tupleBits = tupleBits & tupleBitSetter;
    ++numBits;
  }
  //clear out the old bits

  idxTuple = idxTuple & clearMask;
  idxTuple = idxTuple | (tmp << startBit);
 }

};

void makeTuple(Label& l, int depth, int counts[])
{
  l.reset();
  for (int d=0; d < depth; ++d){
    for (int i=0; i < counts[d]; ++i){
      ++l;
    }
    l.startNext();
  }
}

void makeTuple(Label& l, int x, int y, int z)
{
  int labels[3];
  labels[0] = x;
  labels[1] = y;
  labels[2] = z;
  makeTuple(l, 3, labels);
}

int main(int argc, char** argv)
{
  Label l, r;
  makeTuple(l, 0, 2, 1);
  makeTuple(r, 0, 2, 3);
  std::cout << (l<r) << std::endl;

  makeTuple(l, 1, 3, 5);
  makeTuple(r, 1, 4, 1);
  std::cout << (l<r) << std::endl;

  makeTuple(l, 0, 9, 2);
  makeTuple(r, 1, 10, 1);
  std::cout << (l<r) << std::endl;

  makeTuple(l, 14, 3, 2);
  makeTuple(r, 16, 11, 1);
  std::cout << (l<r) << std::endl;

  makeTuple(l, 17, 3, 15);
  makeTuple(r, 17, 11, 3);
  std::cout << (l<r) << std::endl;

  makeTuple(l, 46, 113, 15);
  makeTuple(r, 142, 78, 39);
  std::cout << (l<r) << std::endl;

  return 0;
}

