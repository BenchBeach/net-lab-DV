#include <stdio.h>
#include "node.h"

struct distance_table dt0;
#define THIS_NODE_ID 0

void node0_comm(int[]);

/* students to write the following two routines, and maybe some others */

void rtinit0() 
{
    printf("init node0 . \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            dt0.costs[i][j]=999;
        }
    }
    dt0.costs[0][THIS_NODE_ID] = 0;
    dt0.costs[1][THIS_NODE_ID] = 1;
    dt0.costs[2][THIS_NODE_ID] = 3;
    dt0.costs[3][THIS_NODE_ID] = 7;
    printdt0(&dt0);
    int node0_init_mincost[4] = { 0 , 1 , 3 , 7};
    node0_comm(node0_init_mincost);
    printf("init node0 finish . \n \n");
}

void node0_comm(int new_cost[4]){
    struct rtpkt  pkt_2_node1;
    struct rtpkt  pkt_2_node2;
    struct rtpkt  pkt_2_node3;
    creatertpkt(&pkt_2_node1 , THIS_NODE_ID , 1, new_cost);
    creatertpkt(&pkt_2_node2 , THIS_NODE_ID , 2, new_cost);
    creatertpkt(&pkt_2_node3 , THIS_NODE_ID , 3, new_cost);
    printf("node0_comm: create pkt finish \n");
    tolayer2(pkt_2_node1);
    tolayer2(pkt_2_node2);
    tolayer2(pkt_2_node3);
}

void rtupdate0(struct rtpkt* rcvdpkt)
{
    printf("node%d recv rtpkt from node%d.\n",THIS_NODE_ID,rcvdpkt->sourceid);
    _Bool is_update=0;
    int base_dis=dt0.costs[rcvdpkt->sourceid][THIS_NODE_ID];
    for(int i=0;i<4;i++){
        dt0.costs[i][rcvdpkt->sourceid]=rcvdpkt->mincost[i]; //更新列
        if(dt0.costs[i][THIS_NODE_ID]>dt0.costs[i][rcvdpkt->sourceid]+base_dis){
            dt0.costs[i][THIS_NODE_ID]=dt0.costs[i][rcvdpkt->sourceid]+base_dis;
            is_update=1;
        }
    }
    if(is_update){
        int new_min_cost[4];
        for(int i=0;i<4;i++){
            new_min_cost[i]=dt0.costs[i][THIS_NODE_ID];
        }
        node0_comm(new_min_cost);
    }
    printdt0(&dt0);
    printf("\n");
}


void printdt0(struct distance_table* dtptr)
{
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%d ",dtptr->costs[i][j]);
        }
        printf("\n");
    }
//  printf("                via     \n");
//  printf("   D0 |    1     2    3 \n");
//  printf("  ----|-----------------\n");
//  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
//	 dtptr->costs[1][2],dtptr->costs[1][3]);
//  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
//	 dtptr->costs[2][2],dtptr->costs[2][3]);
//  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
//	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost) {
  /* called when cost from 0 to linkid changes from current value to newcost*/
  /* You can leave this routine empty if you're an undergrad. If you want */
  /* to use this routine, you'll need to change the value of the LINKCHANGE */
  /* constant definition in prog3.c from 0 to 1 */

}
