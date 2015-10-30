int topologicalSort()
{
    int i,j;
    int index = 0;
    int head = 0;	//head of queue          		
    int rear = 0;       //rear of queue
    int *queue;           
    int *ins;           //table of incident degree
    char *tops;         
    ENode *node;

    ins   = new int[VexNum];
    queue = new int[VexNum];
    tops  = new char[VexNum];
    memset(ins, 0, VexNum*sizeof(int));
    memset(queue, 0, VexNum*sizeof(int));
    memset(tops, 0, VexNum*sizeof(char));
	
    //calculate incident degrees
    for(i = 0; i < VexNum; i++)
    {
        node = Vexs[i].firstEdge;
        while (node != NULL)
        {
            ins[node->ivex]++;
            node = node->nextEdge;
        }
    }

    // push all points with zero incident degree
    for(i = 0; i < mVexNum; i ++)
        if(ins[i] == 0)
            queue[rear++] = i;          

    while (head != rear)                
    {
        j = queue[head++];              
        tops[index++] = Vexs[j].data;  //add this point to tops
        node = mVexs[j].firstEdge;     //get edges linked with this point 

        //decrease the incident degree of points linked to j
        //add the point if its incident degree become 0 after the decrease
        while(node != NULL)
        {
            ins[node->ivex]--;
            if( ins[node->ivex] == 0)
                queue[rear++] = node->ivex;

            node = node->nextEdge;
        }
    }

    if(index != mVexNum)
    {
        cout << "Graph has a cycle" << endl;
        delete queue;
        delete ins;
        delete tops;
        return 1;
    }

    //print the result
    cout << "== TopSort: ";
    for(i = 0; i < mVexNum; i ++)
        cout << tops[i] << " ";
    cout << endl;

    delete queue;
    delete ins;
    delete tops;

    return 0;
}
