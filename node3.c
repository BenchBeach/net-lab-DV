#include <stdio.h>
#include "node.h"

struct distance_table dt3;
#define THIS_NODE_ID 3

void node3_comm(int[]);

/* students to write the following two routines, and maybe some others */

void rtinit3() {
    printf("init node3 . \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            dt3.costs[i][j]=999;
        }
    }
    dt3.costs[0][THIS_NODE_ID] = 7;
    dt3.costs[1][THIS_NODE_ID] = 999;
    dt3.costs[2][THIS_NODE_ID] = 2;
    dt3.costs[3][THIS_NODE_ID] = 0;
    printdt3(&dt3);
    int node3_init_mincost[4] = { 7 , 999, 2 , 0};
    node3_comm(node3_init_mincost);
    printf("init node3 finish . \n \n");
}

void node3_comm(int new_cost[4]){
    struct rtpkt  pkt_2_node0;
    struct rtpkt  pkt_2_node2;
    creatertpkt(&pkt_2_node0 , THIS_NODE_ID , 0, new_cost);
    creatertpkt(&pkt_2_node2 , THIS_NODE_ID , 2, new_cost);
    printf("node3_comm: create pkt finish \n");
    tolayer2(pkt_2_node0);
    tolayer2(pkt_2_node2);
}

void rtupdate3(struct rtpkt* rcvdpkt) {
    printf("node%d recv rtpkt from node%d.\n",THIS_NODE_ID,rcvdpkt->sourceid);
    _Bool is_update=0;
    int base_dis=dt3.costs[rcvdpkt->sourceid][THIS_NODE_ID];
    for(int i=0;i<4;i++){
        dt3.costs[i][rcvdpkt->sourceid]=rcvdpkt->mincost[i]; //更新列
        if(dt3.costs[i][THIS_NODE_ID]>dt3.costs[i][rcvdpkt->sourceid]+base_dis){
            dt3.costs[i][THIS_NODE_ID]=dt3.costs[i][rcvdpkt->sourceid]+base_dis;
            is_update=1;
        }
    }
    if(is_update){
        int new_min_cost[4];
        for(int i=0;i<4;i++){
            new_min_cost[i]=dt3.costs[i][THIS_NODE_ID];
        }
        node3_comm(new_min_cost);
    }
    printdt3(&dt3);
    printf("\n");
}


void printdt3(struct distance_table* dtptr) {
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",dtptr->costs[i][j]);
        }
        printf("\n");
    }
//  printf("             via     \n");
//  printf("   D3 |    0     2 \n");
//  printf("  ----|-----------\n");
//  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
//  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
//  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}






