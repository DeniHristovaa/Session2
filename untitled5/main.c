#include <stdio.h>

    int main(void){
        int N;
        printf("Enter width/hight: ");
        scanf("%d",&N);
        int W;
        printf("Enter tile's width: ");
        scanf("%d",&W);
        int L;
        printf("Enter tile's height: ");
        scanf("%d",&L);
        int M;
        printf("Enter bench's width: ");
        scanf("%d",&M);
        int O;
        printf("Enter bench's height: ");
        scanf("%d",&O);
        int area = N * N;
        int area_bench = M * O;
        int area_tile = W * L;
        int tile = (area - area_bench) / area_tile;
        printf("tiles: %d\n",tile);
        float time = tile * 0.2;
        printf("time: %f\n",time);
        // float tile_width = (N-M) / W;
        // float tile_height = (N-O) / L;
        // float tile = (tile_width * tile_height);
        // printf("tiles: %f\n",tile);
        // float time = tile * 0.2;
        // printf("time: %f\n",time);
        return 0;
    }