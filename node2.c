#include <stdio.h>
#include "node.h"

struct distance_table dt2;
#define THIS_NODE_ID 2
void node2_comm(int[]);
/* students to write the following two routines, and maybe some others */

void rtinit2() 
{
    printf("init node2 . \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            dt2.costs[i][j]=999;
        }
    }
    dt2.costs[0][THIS_NODE_ID] = 3;
    dt2.costs[1][THIS_NODE_ID] = 1;
    dt2.costs[2][THIS_NODE_ID] = 0;
    dt2.costs[3][THIS_NODE_ID] = 2;
    printdt2(&dt2);
    int node2_init_mincost[4] = { 3 , 1 , 0 , 2};
    node2_comm(node2_init_mincost);
    printf("init node2 finish . \n \n");
}

void node2_comm(int new_cost[4]){
    struct rtpkt  pkt_2_node0;
    struct rtpkt  pkt_2_node1;
    struct rtpkt  pkt_2_node3;
    creatertpkt(&pkt_2_node0 , THIS_NODE_ID , 0, new_cost);
    creatertpkt(&pkt_2_node1 , THIS_NODE_ID , 1, new_cost);
    creatertpkt(&pkt_2_node3 , THIS_NODE_ID , 3, new_cost);
    printf("node2_comm: create pkt finish \n");
    tolayer2(pkt_2_node0);
    tolayer2(pkt_2_node1);
    tolayer2(pkt_2_node3);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
    printf("node%d recv rtpkt from node%d.\n",THIS_NODE_ID,rcvdpkt->sourceid);
    _Bool is_update=0;
    int base_dis=dt2.costs[rcvdpkt->sourceid][THIS_NODE_ID];
    for(int i=0;i<4;i++){
        dt2.costs[i][rcvdpkt->sourceid]=rcvdpkt->mincost[i]; //更新列
        if(dt2.costs[i][THIS_NODE_ID]>dt2.costs[i][rcvdpkt->sourceid]+base_dis){
            dt2.costs[i][THIS_NODE_ID]=dt2.costs[i][rcvdpkt->sourceid]+base_dis;
            is_update=1;
        }
    }
    if(is_update){
        int new_min_cost[4];
        for(int i=0;i<4;i++){
            new_min_cost[i]=dt2.costs[i][THIS_NODE_ID];
        }
        node2_comm(new_min_cost);
    }
    printdt2(&dt2);
    printf("\n");
}


void printdt2(struct distance_table* dtptr) {
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",dtptr->costs[i][j]);
        }
        printf("\n");
    }
//  printf("                via     \n");
//  printf("   D2 |    0     1    3 \n");
//  printf("  ----|-----------------\n");
//  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
//	 dtptr->costs[0][1],dtptr->costs[0][3]);
//  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
//	 dtptr->costs[1][1],dtptr->costs[1][3]);
//  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
//	 dtptr->costs[3][1],dtptr->costs[3][3]);
}