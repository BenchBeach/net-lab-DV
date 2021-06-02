#include <stdio.h>
#include "node.h"


int connectcosts1[4] = { 1,  0,  1, 999 };

struct distance_table dt1;
void node1_comm(int[]);
#define THIS_NODE_ID 1


/* students to write the following two routines, and maybe some others */


void rtinit1() {
    printf("init node1 . \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            dt1.costs[i][j]=999;
        }
    }
    dt1.costs[0][THIS_NODE_ID] = 1;
    dt1.costs[1][THIS_NODE_ID] = 0;
    dt1.costs[2][THIS_NODE_ID] = 1;
    dt1.costs[3][THIS_NODE_ID] = 999;
    printdt1(&dt1);
    int node1_init_mincost[4] = { 1 , 0 , 1 , 999};
    node1_comm(node1_init_mincost);
    printf("init node1 finish . \n \n");
}

void node1_comm(int new_cost[4]){
    struct rtpkt  pkt_2_node0;
    struct rtpkt  pkt_2_node2;
    creatertpkt(&pkt_2_node0 , THIS_NODE_ID , 0, new_cost);
    creatertpkt(&pkt_2_node2 , THIS_NODE_ID , 2, new_cost);
    printf("node1_comm: create pkt finish \n");
    tolayer2(pkt_2_node0);
    tolayer2(pkt_2_node2);
}

void rtupdate1(struct rtpkt *rcvdpkt) {
    printf("node%d recv rtpkt from node%d.\n",THIS_NODE_ID,rcvdpkt->sourceid);
//    for(int i=0;i<4;i++){
//        printf("%d ",rcvdpkt->mincost[i]);
//    }
//    printf("%d \n",rcvdpkt->sourceid);
    _Bool is_update=0;
    int base_dis=dt1.costs[rcvdpkt->sourceid][THIS_NODE_ID];
    for(int i=0;i<4;i++){
        dt1.costs[i][rcvdpkt->sourceid]=rcvdpkt->mincost[i]; //update col
        if(dt1.costs[i][THIS_NODE_ID]>dt1.costs[i][rcvdpkt->sourceid]+base_dis){
            dt1.costs[i][THIS_NODE_ID]=dt1.costs[i][rcvdpkt->sourceid]+base_dis;
            is_update=1;
        }
    }
    if(is_update){
        int new_min_cost[4];
        for(int i=0;i<4;i++){
            new_min_cost[i]=dt1.costs[i][THIS_NODE_ID];
        }
        node1_comm(new_min_cost);
    }
    printdt0(&dt1);
}


void printdt1(struct distance_table* dtptr) {
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",dtptr->costs[i][j]);
        }
        printf("\n");
    }
//  printf("             via   \n");
//  printf("   D1 |    0     2 \n");
//  printf("  ----|-----------\n");
//  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
//  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
//  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



void linkhandler1(int linkid, int newcost) {
  /* called when cost from 1 to linkid changes from current value to newcost*/
  /* You can leave this routine empty if you're an undergrad. If you want */
  /* to use this routine, you'll need to change the value of the LINKCHANGE */
  /* constant definition in prog3.c from 0 to 1 */
}

