#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

int pmat[512];

void initPMat() {
  int i;
  for (i = 0; i < 512; i++) {
    pmat[i] = rand() % 256;
  }
}

double fade(double t) { return t * t * t * (t * (6 * t - 15) + 10); }
double fade2(double t) { return -2 + 4.0 / (1 + exp(-t)); }
double linterpolation(double x, double x1, double x2, double y1, double y2) {
  return y1 + (x - x1) * (y2 - y1) / (x2 - x1);
}

double PerlinNoise(double x, double y, double z) {
  //格子に治める
  x = x - ((int)x / 256) * 256;
  y = y - ((int)y / 256) * 256;
  z = z - ((int)z / 256) * 256;
  double inpx = x - (int)x;
  double inpy = y - (int)y;
  double inpz = z - (int)z;
  int ix = (int)x;
  int iy = (int)y;
  int iz = (int)z;

  // 1. 勾配ベクトル(方向)を求める
  // gv1x= (pmat[pmat[x]+y]&1 ? -1 : 1);
  // gv1y=((pmat[pmat[x]+y]>>1)&1 ? -1 : 1);
  // gv2x=(pmat[pmat[x+1]+y]&1 ? -1 : 1);
  // gv2y=((pmat[pmat[x+1]+y]>>1)&1 ? -1 : 1);
  // gv3x=(pmat[pmat[x]+y+1]&1 ? -1 : 1);
  // gv3y=((pmat[pmat[x]+y+1]>>1)&1 ? -1 : 1);
  // gv4x=(pmat[pmat[x+1]+y+1]&1 ? -1 : 1);
  // gv4y=((pmat[pmat[x+1]+y+1]>>1)&1 ? -1 : 1);
  double gv1x = (pmat[pmat[pmat[ix] + iy] + iz] & 15) / 7.5 - 1;
  double gv1y = ((pmat[pmat[pmat[ix] + iy] + iz] >> 4) & 15) / 7.5 - 1;
  double gv1z = ((pmat[pmat[pmat[ix] + iy] + iz] >> 8) & 15) / 7.5 - 1;
  double gv2x = (pmat[pmat[pmat[ix + 1] + iy] + iz] & 15) / 7.5 - 1;
  double gv2y = ((pmat[pmat[pmat[ix + 1] + iy] + iz] >> 4) & 15) / 7.5 - 1;
  double gv2z = ((pmat[pmat[pmat[ix + 1] + iy] + iz] >> 8) & 15) / 7.5 - 1;
  double gv3x = (pmat[pmat[pmat[ix] + iy + 1] + iz] & 15) / 7.5 - 1;
  double gv3y = ((pmat[pmat[pmat[ix] + iy + 1] + iz] >> 4) & 15) / 7.5 - 1;
  double gv3z = ((pmat[pmat[pmat[ix] + iy + 1] + iz] >> 8) & 15) / 7.5 - 1;
  double gv4x = (pmat[pmat[pmat[ix + 1] + iy + 1] + iz] & 15) / 7.5 - 1;
  double gv4y = ((pmat[pmat[pmat[ix + 1] + iy + 1] + iz] >> 4) & 15) / 7.5 - 1;
  double gv4z = ((pmat[pmat[pmat[ix + 1] + iy + 1] + iz] >> 8) & 15) / 7.5 - 1;
  double gv5x = (pmat[pmat[pmat[ix] + iy] + iz + 1] & 15) / 7.5 - 1;
  double gv5y = ((pmat[pmat[pmat[ix] + iy] + iz + 1] >> 4) & 15) / 7.5 - 1;
  double gv5z = ((pmat[pmat[pmat[ix] + iy] + iz + 1] >> 8) & 15) / 7.5 - 1;
  double gv6x = (pmat[pmat[pmat[ix + 1] + iy] + iz + 1] & 15) / 7.5 - 1;
  double gv6y = ((pmat[pmat[pmat[ix + 1] + iy] + iz + 1] >> 4) & 15) / 7.5 - 1;
  double gv6z = ((pmat[pmat[pmat[ix + 1] + iy] + iz + 1] >> 8) & 15) / 7.5 - 1;
  double gv7x = (pmat[pmat[pmat[ix] + iy + 1] + iz + 1] & 15) / 7.5 - 1;
  double gv7y = ((pmat[pmat[pmat[ix] + iy + 1] + iz + 1] >> 4) & 15) / 7.5 - 1;
  double gv7z = ((pmat[pmat[pmat[ix] + iy + 1] + iz + 1] >> 8) & 15) / 7.5 - 1;
  double gv8x = (pmat[pmat[pmat[ix + 1] + iy + 1] + iz + 1] & 15) / 7.5 - 1;
  double gv8y =
      ((pmat[pmat[pmat[ix + 1] + iy + 1] + iz + 1] >> 4) & 15) / 7.5 - 1;
  double gv8z =
      ((pmat[pmat[pmat[ix + 1] + iy + 1] + iz + 1] >> 8) & 15) / 7.5 - 1;

  // 2. 距離ベクトルを求める
  double dv1x = inpx;
  double dv1y = inpy;
  double dv1z = inpz;
  double dv2x = inpx - 1;
  double dv2y = inpy;
  double dv2z = inpz;
  double dv3x = inpx;
  double dv3y = inpy - 1;
  double dv3z = inpz;
  double dv4x = inpx - 1;
  double dv4y = inpy - 1;
  double dv4z = inpz;
  double dv5x = inpx;
  double dv5y = inpy;
  double dv5z = inpz - 1;
  double dv6x = inpx - 1;
  double dv6y = inpy;
  double dv6z = inpz - 1;
  double dv7x = inpx;
  double dv7y = inpy - 1;
  double dv7z = inpz - 1;
  double dv8x = inpx - 1;
  double dv8y = inpy - 1;
  double dv8z = inpz - 1;

  // 3. 勾配ベクトルと距離ベクトルの内積を求める
  double d1 = gv1x * dv1x + gv1y * dv1y + gv1z * dv1z;
  double d2 = gv2x * dv2x + gv2y * dv2y + gv2z * dv2z;
  double d3 = gv3x * dv3x + gv3y * dv3y + gv3z * dv3z;
  double d4 = gv4x * dv4x + gv4y * dv4y + gv4z * dv4z;
  double d5 = gv5x * dv5x + gv5y * dv5y + gv5z * dv5z;
  double d6 = gv6x * dv6x + gv6y * dv6y + gv6z * dv6z;
  double d7 = gv7x * dv7x + gv7y * dv7y + gv7z * dv7z;
  double d8 = gv8x * dv8x + gv8y * dv8y + gv8z * dv8z;

  // 4. サンプル値の位置をフェード関数を使って調整
  double inpxf = fade(inpx);
  double inpyf = fade(inpy);
  double inpzf = fade(inpz);

  // 5. 3の内積から4の位置の内積値を線形補間で求める
  // 5-1. xについて上下で求める
  double inpdx1 = linterpolation(inpxf, 0, 1, d1, d2);
  double inpdx2 = linterpolation(inpxf, 0, 1, d3, d4);
  double inpdx3 = linterpolation(inpxf, 0, 1, d5, d6);
  double inpdx4 = linterpolation(inpxf, 0, 1, d7, d8);
  double inpdy1 = linterpolation(inpyf, 0, 1, inpdx1, inpdx2);
  double inpdy2 = linterpolation(inpyf, 0, 1, inpdx3, inpdx4);
  double inpd = linterpolation(inpzf, 0, 1, inpdy1, inpdy2);
  // if (inpd>0.6||inpd<-0.6) console.log(inpd)
  return (inpd + 1) / 2;
}

double OctavePerlinNoise(double x, double y, double z, int oct, double per) {
  double total = 0;
  double freq = 1;
  double amp = 1;
  double maxv = 0;
  int i;
  for (i = 0; i < oct; i++) {
    total += PerlinNoise(x * freq, y * freq, z * freq) * amp;
    maxv += amp;
    amp *= per;
    freq *= 2;
  }
  return total / maxv;
}

int main(int argc, char **argv) {
  int i, x, y, z = 0;
  double xr=256.0,yr=256.0,zr=16;
  time_t t = time(NULL);
  char name[100];

  sprintf(name,"out%ld.bmp",t);
  FILE *fp = fopen(name, "w");
  // FILE *fp2 = fopen(argv[3], "w");
  if (fp == NULL) return 1;
  // if (fp2 == NULL) return 1;
  int w = 1024, h = 512;
  // int w = 7680, h = 4320;
  setBMPSize(w, h);
  writeBMPHeader(fp);
  // writeBMPHeader(fp2);

  printf("Time: %ld\n",t);
  srand(t);

  initPMat();
  double pr, bright;
  for (y = h - 1; y >= 0; y--) {
    for (x = 0; x < w; x++) {
      // pr =
      //     ((OctavePerlinNoise((x) / 128.0, (y) / 128.0, z / 16, 4, 0.5) -
      //     0.5) *
      //          5 +
      //      0.4) *
      //     256;
      pr = ((fade2(OctavePerlinNoise((x) / xr, (y) / yr, z / zr, 8, 0.5)) - 0.5) * 8 + 0.1) * 256;
      //       pr =
      // ((OctavePerlinNoise((x) / 128.0, (y) / 128.0, z / 16, 4, 0.5) - 0.5) *
      //      1 +
      //  1) *
      // 256;
      // printf("%f\n",pr);
      if (pr < 0) pr = 0;
      if (pr > 200) {
        bright = ((pr - 200) / 3);
        pr = 200;
      } else
        bright = 0;

      unsigned char g = 100 + ((int)pr) * (255 - 100) / 255 - bright;
      unsigned char b = 160 + ((int)pr) * (255 - 160) / 255 - bright;
      unsigned char r = 60 + ((int)pr) * (255 - 60) / 255 - bright;
      unsigned char a = 255;
      int dat = (a << 24) + (r << 16) + (g << 8) + b;
      fwrite(&dat, 4, 1, fp);
      // g = 160 + ((int)pr) * (255 - 160) / 255 - bright;
      // b = 160 + ((int)pr) * (255 - 160) / 255 - bright;
      // r = 160 + ((int)pr) * (255 - 160) / 255 - bright;
      // a = ((int)pr);
      // if (((int)pr) > 255) a = 255;
      // dat = (a << 24) + (r << 16) + (g << 8) + b;
      // fwrite(&dat, 4, 1, fp2);
    }
  }

  // int data[] = {0xff0000ff, 0xaa00ff00, 0x99ff0000, 0x33ffffff};
  // for (i = 0; i < 100 * 100; i += 4) {
  //   fwrite(data, 4, 4, fp);
  // }
  fclose(fp);
  // fclose(fp2);

  return 0;
}
