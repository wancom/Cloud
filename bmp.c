#include "bmp.h"

long biWidth = 0;             // Width
long biHeight = 0;            // Height
long biSize = 40 + 84;  // F:SizeOfHeader
long biSizeImage = 0;         // SizeOfImg

// Bitmap File Header
const char *bfType = "BM";           // F:MagicCode
long bfSize;// = 14 + biSize + 0;       // FileSize
const short bfReserved1 = 0;         // F:Res1
const short bfReserved2 = 0;         // F:Res2
long bfOffBits;// = 14 + biSize;  // F:Offset from head to img data

// Bitmap Information Header
// const long biSize;            // F:SizeOfHeader
// const long biWidth ;            // Width
// const long biHeight ;           // Height
const short biPlanes = 1;      // F:NumOfPlanes
const short biBitCount = 32;   // ColorBit
const long biCompression = 0;  // F:CompressionType
// const long biSizeImage;        // SizeOfImg
const long biXPixPerMeter = 1000;  // F:XDotPerMeter
const long biYPixPerMeter = 1000;  // F:YDotPerMeter
const long biClrUsed = 0;          // F:NumOfPalette
const long biCirImportant = 0;     // F:NumOfImportantColor

const long bV5RedMask = 0x00ff0000;
const long bV5GreenMask = 0x0000ff00;
const long bV5BlueMask = 0x000000ff;
const long bV5AlphaMask = 0xff000000;
const char *bV5CSType = "BGRs";
const long *bV5Endpoints[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
const long bV5GammaRed = 0;
const long bV5GammaGreen = 0;
const long bV5GammaBlue = 0;
const long bV5Intent = 4;
const long bV5ProfileData = 0;
const long bV5ProfileSize = 0;
const long bV5Reserved = 0;
// https://www.ruche-home.net/program/bmp/struct
void writeBMPHeader(FILE *fp) {
  fwrite(bfType, 1, 2, fp);
  fwrite(&bfSize, 4, 1, fp);
  fwrite(&bfReserved1, 2, 1, fp);
  fwrite(&bfReserved2, 2, 1, fp);
  fwrite(&bfOffBits, 4, 1, fp);

  fwrite(&biSize, 4, 1, fp);
  fwrite(&biWidth, 4, 1, fp);
  fwrite(&biHeight, 4, 1, fp);
  fwrite(&biPlanes, 2, 1, fp);
  fwrite(&biBitCount, 2, 1, fp);
  fwrite(&biCompression, 4, 1, fp);
  fwrite(&biSizeImage, 4, 1, fp);
  fwrite(&biXPixPerMeter, 4, 1, fp);
  fwrite(&biYPixPerMeter, 4, 1, fp);
  fwrite(&biClrUsed, 4, 1, fp);
  fwrite(&biCirImportant, 4, 1, fp);

  fwrite(&bV5RedMask, 4, 1, fp);
  fwrite(&bV5GreenMask, 4, 1, fp);
  fwrite(&bV5BlueMask, 4, 1, fp);
  fwrite(&bV5AlphaMask, 4, 1, fp);
  fwrite(bV5CSType, 1, 4, fp);
  fwrite(bV5Endpoints, 4, 9, fp);
  fwrite(&bV5GammaRed, 4, 1, fp);
  fwrite(&bV5GammaGreen, 4, 1, fp);
  fwrite(&bV5GammaBlue, 4, 1, fp);
  fwrite(&bV5Intent, 4, 1, fp);
  fwrite(&bV5ProfileData, 4, 1, fp);
  fwrite(&bV5ProfileSize, 4, 1, fp);
  fwrite(&bV5Reserved, 4, 1, fp);
}

void setBMPSize(int width, int height) {
  biWidth = width;                         // Width
  biHeight = height;                       // Height
  biSizeImage = 4 * (biWidth * biHeight);  // SizeOfImg
  bfSize = 14 + biSize + biSizeImage;      // FileSize
  bfOffBits = 14 + biSize;
}