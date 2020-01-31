
int x,y,k;
int maxValue = 0;
int hit[256];

//hist 배열 초기화
for(k=0;k<256;k++)
   hist[k]=0;
for(y=0;y<256;y++){
   for(x=0;x<256;x++){
      k=inputImg[y][x];
      hist[k]++;
      resultImg[y][x]=255;
   }
}

//히스토그램 최대값 계산
for(k=0;k<256;k++){
  if(maxValue < hist[k])
     maxValue = hist[k];
}

//resultImg에 히스토그램 그리기
for(y=0;y<256;y++){
   int value=hist[y]*255/maxValue;
   for(x=0;x<value;x++){
   resultImg[255-x][y]=0;
   }
}
