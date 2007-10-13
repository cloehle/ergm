#include "edgeTree.h"


/*******************
 Network NetworkInitialize

 Initialize, construct binary tree version of network.  Note
 that the 0th TreeNode in the array is unused and should 
 have all its values set to zero
*******************/
Network NetworkInitialize(Vertex *heads, Vertex *tails, Edge nedges, 
			  Vertex nnodes, int directed_flag, Vertex bipartite,
			  int lasttoggle_flag) {
  Edge i, j;
  Vertex h, t;
  Network nw;

  nw.next_inedge = nw.next_outedge = (Edge)nnodes+1;
  nw.outdegree = (Vertex *) malloc(sizeof(Vertex) * (nnodes+1));
  nw.indegree  = (Vertex *) malloc(sizeof(Vertex) * (nnodes+1));
  nw.inedges = (TreeNode *) malloc(sizeof(TreeNode) * MAXEDGES);
  nw.outedges = (TreeNode *) malloc(sizeof(TreeNode) * MAXEDGES);

  if(lasttoggle_flag){
    nw.duration_info.MCMCtimer=0;
    i = directed_flag? nnodes*(nnodes-1) : (nnodes*(nnodes-1))/2;
    nw.duration_info.lasttoggle = (int *) calloc(i,sizeof(int));
  }
  else nw.duration_info.lasttoggle = NULL;

  for (i=0; i<=nnodes; i++) {
    nw.inedges[i].value = nw.outedges[i].value = 0;
    nw.inedges[i].parent = nw.outedges[i].parent = 0;
    nw.inedges[i].left = nw.outedges[i].left = 0;
    nw.inedges[i].right = nw.outedges[i].right = 0;
    nw.indegree[i] = nw.outdegree[i] = 0;
  }
  
  for (; i<MAXEDGES; i++)
    nw.inedges[i].value = nw.outedges[i].value = 0;

  /*Configure a Network*/
  nw.nnodes = nnodes;
  nw.nedges = 0; /* Edges will be added one by one */
  nw.directed_flag=directed_flag;
  nw.bipartite=bipartite;

  for(i = nedges; i > 0; i--) {
    j = i * unif_rand();  /* shuffle to avoid worst-case performance */
    h = (Vertex)heads[j];
    t = (Vertex)tails[j];
    heads[j] = heads[i-1];
    tails[j] = tails[i-1];
    heads[i-1] = h;
    tails[i-1] = t;
    if (!directed_flag && h > t) 
      AddEdgeToTrees(t,h,&nw); /* Undir edges always have head < tail */ 
    else 
      AddEdgeToTrees(h,t,&nw);
  }  
  return nw;
}
/*Takes vectors of doubles for edges; used only when constructing from inputparams. */
Network NetworkInitializeD(double *heads, double *tails, Edge nedges, 
			  Vertex nnodes, int directed_flag, Vertex bipartite,
			  int lasttoggle_flag) {
  Edge i, j;
  Vertex h, t;
  Network nw;

  nw.next_inedge = nw.next_outedge = (Edge)nnodes+1;
  nw.outdegree = (Vertex *) malloc(sizeof(Vertex) * (nnodes+1));
  nw.indegree  = (Vertex *) malloc(sizeof(Vertex) * (nnodes+1));
  nw.inedges = (TreeNode *) malloc(sizeof(TreeNode) * MAXEDGES);
  nw.outedges = (TreeNode *) malloc(sizeof(TreeNode) * MAXEDGES);

  if(lasttoggle_flag){
    nw.duration_info.MCMCtimer=0;
    i = directed_flag? nnodes*(nnodes-1) : (nnodes*(nnodes-1))/2;
    nw.duration_info.lasttoggle = (int *) calloc(i,sizeof(int));
  }
  else nw.duration_info.lasttoggle = NULL;

  for (i=0; i<=nnodes; i++) {
    nw.inedges[i].value = nw.outedges[i].value = 0;
    nw.inedges[i].parent = nw.outedges[i].parent = 0;
    nw.inedges[i].left = nw.outedges[i].left = 0;
    nw.inedges[i].right = nw.outedges[i].right = 0;
    nw.indegree[i] = nw.outdegree[i] = 0;
  }
  
  for (; i<MAXEDGES; i++)
    nw.inedges[i].value = nw.outedges[i].value = 0;

  /*Configure a Network*/
  nw.nnodes = nnodes;
  nw.nedges = 0; /* Edges will be added one by one */
  nw.directed_flag=directed_flag;
  nw.bipartite=bipartite;

  for(i = nedges; i > 0; i--) {
    j = i * unif_rand();  /* shuffle to avoid worst-case performance */
    h = (Vertex)heads[j];
    t = (Vertex)tails[j];
    heads[j] = heads[i-1];
    tails[j] = tails[i-1];
    heads[i-1] = h;
    tails[i-1] = t;
    if (!directed_flag && h > t) 
      AddEdgeToTrees(t,h,&nw); /* Undir edges always have head < tail */ 
    else 
      AddEdgeToTrees(h,t,&nw);
  }  
  return nw;
}
WtNetwork WtNetworkInitialize(int *heads, int *tails, double *weights,
			      int nedges, int nnodes, int directed_flag, int bipartite) {
  Edge i, j;
  Vertex h, t;
  double w;
  WtNetwork nw;

  nw.next_inedge = nw.next_outedge = (Edge)nnodes+1;
  nw.outdegree = (Vertex *) malloc(sizeof(Vertex) * (nnodes+1));
  nw.indegree  = (Vertex *) malloc(sizeof(Vertex) * (nnodes+1));
  nw.inedges = (WtTreeNode *) malloc(sizeof(WtTreeNode) * MAXEDGES);
  nw.outedges = (WtTreeNode *) malloc(sizeof(WtTreeNode) * MAXEDGES);
  
  nw.duration_info.MCMCtimer=0;
  i = directed_flag? nnodes*(nnodes-1) : (nnodes*(nnodes-1))/2;
  nw.duration_info.lasttoggle = (int *) malloc(sizeof(int) * i);

  for (i=0; i<=nnodes; i++) {
    nw.inedges[i].value = nw.outedges[i].value = 0;
    nw.inedges[i].parent = nw.outedges[i].parent = 0;
    nw.inedges[i].left = nw.outedges[i].left = 0;
    nw.inedges[i].right = nw.outedges[i].right = 0;
    nw.inedges[i].weight = nw.outedges[i].weight = 0.0;
    nw.indegree[i] = nw.outdegree[i] = 0;
  }
  
  for (; i<MAXEDGES; i++)
    nw.inedges[i].value = nw.outedges[i].value = 0;

  /*Configure a Network*/
  nw.nnodes = nnodes;
  nw.nedges = 0; /* Edges will be added one by one */
  nw.directed_flag=directed_flag;
  nw.bipartite=bipartite;

  for(i = nedges; i > 0; i--) {
    j = i * unif_rand();  /* shuffle to avoid worst-case performance */
    h = (Vertex)heads[j];
    t = (Vertex)tails[j];
    w = weights[j];
    heads[j] = heads[i-1];
    tails[j] = tails[i-1];
    weights[j] = weights[i-1];
    heads[i-1] = h;
    tails[i-1] = t;
    weights[i-1] = w;
    if (!directed_flag && h > t) 
      WtAddEdgeToTrees(t,h,w,&nw); /* Undir edges always have head < tail */ 
    else 
      WtAddEdgeToTrees(h,t,w,&nw);
  }
  return nw;
}

/*******************
 void NetworkDestroy
*******************/
void NetworkDestroy(Network *nwp) {
  free (nwp->indegree);
  free (nwp->outdegree);
  free (nwp->inedges);
  free (nwp->outedges);
  if(nwp->duration_info.lasttoggle){
    free (nwp->duration_info.lasttoggle);
    nwp->duration_info.lasttoggle=NULL;
  }
}

void WtNetworkDestroy(WtNetwork *nwp) {
  free (nwp->indegree);
  free (nwp->outdegree);
  free (nwp->inedges);
  free (nwp->outedges);
  free (nwp->duration_info.lasttoggle);
}

/*****************
 Edge EdgetreeSearch

 Check to see if there's a TreeNode with value b 
 in the tree rooted at edges[a].  Return i such that 
 edges[i] is that TreeNode, or 0 if none.
*****************/
Edge EdgetreeSearch (Vertex a, Vertex b, TreeNode *edges) {
  TreeNode *es;
  Edge e = a;
  Vertex v;

  es = edges + e;
  v = es->value;
  while(e != 0 && b != v)
    {
      e = (b<v)?  es->left : es->right;
      es = edges + e;
      v = es->value;
    }
  return e;
}

Edge WtEdgetreeSearch (Vertex a, Vertex b, WtTreeNode *edges) {
  WtTreeNode *es;
  Edge e = a;
  Vertex v;

  es = edges + e;
  v = es->value;
  while(e != 0 && b != v)
    {
      e = (b<v)?  es->left : es->right;
      es = edges + e;
      v = es->value;
    }
  return e;
}

/*****************
 Edge EdgetreeSuccessor

 Return the index of the TreeNode with the smallest value
 greater than edges[x].value in the same edge tree, or 0
 if none.  This is used by (for instance)
 the DeleteHalfedgeFromTree function.
*****************/
Edge EdgetreeSuccessor (TreeNode *edges, Edge x) {
  TreeNode *ptr;
  Edge y;

  if ((y=(ptr=edges+x)->right) != 0) 
    return EdgetreeMinimum (edges, y);
  while ((y=ptr->parent)!=0 && x==(ptr=edges+y)->right) 
    x=y;
  return y; 
}   

Edge WtEdgetreeSuccessor (WtTreeNode *edges, Edge x) {
  WtTreeNode *ptr;
  Edge y;

  if ((y=(ptr=edges+x)->right) != 0) 
    return WtEdgetreeMinimum (edges, y);
  while ((y=ptr->parent)!=0 && x==(ptr=edges+y)->right) 
    x=y;
  return y; 
}   

/*****************
 Edge EdgetreeMinimum

 Return the index of the TreeNode with the
 smallest value in the subtree rooted at x
*****************/
Edge EdgetreeMinimum (TreeNode *edges, Edge x) {
  Edge y;

  while ((y=(edges+x)->left) != 0)
    x=y;
  return x;
}

Edge WtEdgetreeMinimum (WtTreeNode *edges, Edge x) {
  Edge y;

  while ((y=(edges+x)->left) != 0)
    x=y;
  return x;
}

/*****************
 Edge ToggleEdge

 Toggle an edge:  Set it to the opposite of its current
 value.  Return 1 if edge added, 0 if deleted.
*****************/
int ToggleEdge (Vertex head, Vertex tail, Network *nwp) 
{
  if (!(nwp->directed_flag) && head > tail) {
    Vertex temp;
    temp = head; /*  Make sure head<tail always for undirected edges */
    head = tail;
    tail = temp;
  }
  if (AddEdgeToTrees(head,tail,nwp))
    return 1;
  else 
    return 1 - DeleteEdgeFromTrees(head,tail,nwp);
}

int WtToggleEdge (Vertex head, Vertex tail, double weight, WtNetwork *nwp) 
{
  if (!(nwp->directed_flag) && head > tail) {
    Vertex temp;
    temp = head; /*  Make sure head<tail always for undirected edges */
    head = tail;
    tail = temp;
  }
  if (WtAddEdgeToTrees(head,tail,weight,nwp))
    return 1;
  else 
    return 1 - WtDeleteEdgeFromTrees(head,tail,nwp);
}


/*****************
 Edge ToggleEdgeWithTimestamp
 By MSH 11/26/06

 Same as ToggleEdge, but this time with the additional
 step of updating the matrix of 'lasttoggle' times
 *****************/
int ToggleEdgeWithTimestamp (Vertex head, Vertex tail, Network *nwp) 
{
  Edge k;

  if (!(nwp->directed_flag) && head > tail) {
    Vertex temp;
    temp = head; /*  Make sure head<tail always for undirected edges */
    head = tail;
    tail = temp;
  }
  
  if(nwp->duration_info.lasttoggle){ // Skip timestamps if no duration info.
    if (nwp->directed_flag) 
      k = (tail-1)*(nwp->nnodes-1) + head - ((head>tail) ? 1:0) - 1; 
    else
      k = (tail-1)*(tail-2)/2 + head - 1;    
    nwp->duration_info.lasttoggle[k] = nwp->duration_info.MCMCtimer;
  }
  
  if (AddEdgeToTrees(head,tail,nwp))
    return 1;
  else 
    return 1 - DeleteEdgeFromTrees(head,tail,nwp);
}

int WtToggleEdgeWithTimestamp (Vertex head, Vertex tail, double weight, WtNetwork *nwp) 
{
  Edge k;
  if (!(nwp->directed_flag) && head > tail) {
    Vertex temp;
    temp = head; /*  Make sure head<tail always for undirected edges */
    head = tail;
    tail = temp;
  }
  if(nwp->duration_info.lasttoggle){ // Skip timestamps if no duration info.
    if (nwp->directed_flag) 
      k = (tail-1)*(nwp->nnodes-1) + head - ((head>tail) ? 1:0) - 1; 
    else
      k = (tail-1)*(tail-2)/2 + head - 1;    
    nwp->duration_info.lasttoggle[k] = nwp->duration_info.MCMCtimer;
  }

  if (WtAddEdgeToTrees(head,tail,weight,nwp))
    return 1;
  else 
    return 1 - WtDeleteEdgeFromTrees(head,tail,nwp);
}

/*****************
 long int ElapsedTime

 Return time since given (head,tail) was last toggled using
 ToggleEdgeWithTimestamp function
 *****************/
int ElapsedTime (Vertex head, Vertex tail, Network *nwp) 
{
  Edge k;
  if (!(nwp->directed_flag) && head > tail) {
    Vertex temp;
    temp = head; /*  Make sure head<tail always for undirected edges */
    head = tail;
    tail = temp;
  }

  if(nwp->duration_info.lasttoggle){ // Return 0 if no duration info.
    if (nwp->directed_flag) 
      k = (tail-1)*(nwp->nnodes-1) + head - ((head>tail) ? 1:0) - 1; 
    else
      k = (tail-1)*(tail-2)/2 + head - 1;    
    return nwp->duration_info.MCMCtimer - nwp->duration_info.lasttoggle[k];
  }
  else return 0; 
  /* Should maybe return an error code of some sort, since 0 elapsed time
     is valid output. Need to think about it. */
}

/*****************
 void TouchEdge

 Named after the UNIX "touch" command.
 Set an edge's time-stamp to the current MCMC time.
 *****************/

R_INLINE void TouchEdge(Vertex head, Vertex tail, Network *nwp){
  unsigned int k;
  if(nwp->duration_info.lasttoggle){ // Skip timestamps if no duration info.
    if (nwp->directed_flag) 
      k = (tail-1)*(nwp->nnodes-1) + head - ((head>tail) ? 1:0) - 1; 
    else
      k = (tail-1)*(tail-2)/2 + head - 1;    
    nwp->duration_info.lasttoggle[k] = nwp->duration_info.MCMCtimer;
  }
}

/*****************
 Edge AddEdgeToTrees

 Add an edge from head to tail after checking to see
 if it's legal. Return 1 if edge added, 0 otherwise.  Since each
 "edge" should be added to both the list of outedges and the list of 
 inedges, this actually involves two calls to AddHalfEdgeToTree (hence
 "Trees" instead of "Tree" in the name of this function).
*****************/
int AddEdgeToTrees(Vertex head, Vertex tail, Network *nwp){
  if (EdgetreeSearch(head, tail, nwp->outedges) == 0) {
    AddHalfedgeToTree(head, tail, nwp->outedges, &(nwp->next_outedge));
    AddHalfedgeToTree(tail, head, nwp->inedges, &(nwp->next_inedge));
    ++nwp->outdegree[head];
    ++nwp->indegree[tail];
    ++nwp->nedges;
    return 1;
  }
  return 0;
}

int WtAddEdgeToTrees(Vertex head, Vertex tail, double weight, WtNetwork *nwp){
  if (WtEdgetreeSearch(head, tail, nwp->outedges) == 0) {
    WtAddHalfedgeToTree(head, tail, weight, nwp->outedges, 
			&(nwp->next_outedge));
    WtAddHalfedgeToTree(tail, head, weight, nwp->inedges, &(nwp->next_inedge));
    ++nwp->outdegree[head];
    ++nwp->indegree[tail];
    ++nwp->nedges;
    return 1;
  }
  return 0;
}

/*****************
 Edge AddHalfedgeToTree
*****************/
void AddHalfedgeToTree (Vertex a, Vertex b, TreeNode *edges, 
			Edge *next_edge) 
{
  TreeNode *eptr = edges+a, *new;
  Edge e;
  
  if (eptr->value==0) { /* This is the first edge for this vertex. */
    eptr->value=b;
    return;
  }
  (new=edges+*next_edge)->value=b;  
  new->left=new->right=0;
  /* Now find the parent of this new edge */
  for (e=a; e!=0; e=(b < (eptr=edges+e)->value) ? eptr->left : eptr->right);
  new->parent=eptr-edges;  /* Point from the new edge to the parent... */
  if (b < eptr->value)  /* ...and have the parent point back. */
    eptr->left=*next_edge; 
  else
    eptr->right=*next_edge;
  /* Finally, update the value of *next_edge for next time.  Note that this
     is done simplistically, but simply counting up until a free TreeNode is 
     found.  However, the delete-edge routine does a better job.  */
  while (++*next_edge<MAXEDGES && edges[*next_edge].value!=0);
}

void WtAddHalfedgeToTree (Vertex a, Vertex b, double weight, 
			  WtTreeNode *edges, Edge *next_edge) 
{  /*  See comments in AddHalfedgeToTree.  */
  WtTreeNode *eptr = edges+a, *new;
  Edge e;
  
  if (eptr->value==0) { 
    eptr->value=b;
    eptr->weight = weight;  /*  Add weight too */
    return;
  }
  (new=edges+*next_edge)->value=b;  
  new->left=new->right=0;
  new->weight=weight;  /*  Add weight too */
  for (e=a; e!=0; e=(b < (eptr=edges+e)->value) ? eptr->left : eptr->right);
  new->parent=eptr-edges;
  if (b < eptr->value)
    eptr->left=*next_edge;
  else
    eptr->right=*next_edge;
  while (++*next_edge<MAXEDGES && edges[*next_edge].value!=0);
}

/*****************
 int DeleteEdgeFromTrees

 Find and delete the edge from head to tail.  
 Return 1 if successful, 0 otherwise.  As with AddEdgeToTrees, this must
 be done once for outedges and once for inedges.
*****************/
int DeleteEdgeFromTrees(Vertex head, Vertex tail, Network *nwp){
  if (DeleteHalfedgeFromTree(head, tail, nwp->outedges,&(nwp->next_outedge))&&
      DeleteHalfedgeFromTree(tail, head, nwp->inedges, &(nwp->next_inedge))) {
    --nwp->outdegree[head];
    --nwp->indegree[tail];
    --nwp->nedges;
    return 1;
  }
  return 0;
}

int WtDeleteEdgeFromTrees(Vertex head, Vertex tail, WtNetwork *nwp){
  if (WtDeleteHalfedgeFromTree(head, tail, nwp->outedges,
			       &(nwp->next_outedge))&&
      WtDeleteHalfedgeFromTree(tail, head, nwp->inedges, 
			       &(nwp->next_inedge))) {
    --nwp->outdegree[head];
    --nwp->indegree[tail];
    --nwp->nedges;
    return 1;
  }
  return 0;
}

/*****************
 int DeleteHalfedgeFromTree

 Delete the TreeNode with value b from the tree rooted at edges[a].
 Return 0 if no such TreeNode exists, 1 otherwise.  Also update the
 value of *next_edge appropriately.
*****************/
int DeleteHalfedgeFromTree(Vertex a, Vertex b, TreeNode *edges,
		     Edge *next_edge){
  Edge x, z, root=(Edge)a;
  TreeNode *xptr, *zptr, *ptr;

  if ((z=EdgetreeSearch(a, b, edges))==0)  /* z is the current TreeNode. */
    return 0;  /* This edge doesn't exist, so return 0 */
  /* First, determine which node to splice out; this is z.  If the current
     z has two children, then we'll actually splice out its successor. */
  if ((zptr=edges+z)->left != 0 && zptr->right != 0) {
    z=EdgetreeSuccessor(edges, z);  
    zptr->value = (ptr=edges+z)->value;
    zptr=ptr;
  }
  /* Set x to the child of z (there is at most one). */
  if ((x=zptr->left) == 0)
    x = zptr->right;
  /* Splice out node z */
  if (z == root) {
    zptr->value = (xptr=edges+x)->value;
    if (x != 0) {
      if ((zptr->left=xptr->left) != 0)
	(edges+zptr->left)->parent = z;
      if ((zptr->right=xptr->right) != 0)
	(edges+zptr->right)->parent = z;
      zptr=edges+(z=x);
    }  else 
      return 1;
  } else {
    if (x != 0)
      (xptr=edges+x)->parent = zptr->parent;
    if (z==(ptr=(edges+zptr->parent))->left)
      ptr->left = x;
    else 
      ptr->right = x;
  }  
  /* Clear z node, update *next_edge if necessary. */
  zptr->value=0;
  if (z < *next_edge)
    *next_edge=z;
  return 1;
}

int WtDeleteHalfedgeFromTree(Vertex a, Vertex b, WtTreeNode *edges,
		     Edge *next_edge){ 
  /* see comments in DeleteHalfedgeFromTree */
  Edge x, z, root=(Edge)a;
  WtTreeNode *xptr, *zptr, *ptr;

  if ((z=WtEdgetreeSearch(a, b, edges))==0)  /* z is the current TreeNode. */
    return 0;
  if ((zptr=edges+z)->left != 0 && zptr->right != 0) {
    z=WtEdgetreeSuccessor(edges, z);
    zptr->value = (ptr=edges+z)->value;
    zptr=ptr;
  }
  if ((x=zptr->left) == 0)
    x = zptr->right;
  if (z == root) {
    zptr->value = (xptr=edges+x)->value;
    if (x != 0) {
      if ((zptr->left=xptr->left) != 0)
	(edges+zptr->left)->parent = z;
      if ((zptr->right=xptr->right) != 0)
	(edges+zptr->right)->parent = z;
      zptr=edges+(z=x);
    }  else 
      return 1;
  } else {
    if (x != 0)
      (xptr=edges+x)->parent = zptr->parent;
    if (z==(ptr=(edges+zptr->parent))->left)
      ptr->left = x;
    else 
      ptr->right = x;
  }  
  zptr->value=0;
  if (z < *next_edge)
    *next_edge=z;
  return 1;
}

/*****************
 void printedge

 Diagnostic routine that prints out the contents
 of the specified TreeNode (used for debugging).  
*****************/
void printedge(Edge e, TreeNode *edges){
  Rprintf("Edge structure [%d]:\n",e);
  Rprintf("\t.value=%d\n",edges[e].value);
  Rprintf("\t.parent=%d\n",edges[e].parent);
  Rprintf("\t.left=%d\n",edges[e].left);
  Rprintf("\t.right=%d\n",edges[e].right);
}

void Wtprintedge(Edge e, WtTreeNode *edges){
  Rprintf("Edge structure [%d]:\n",e);
  Rprintf("\t.value=%d\n",edges[e].value);
  Rprintf("\t.parent=%d\n",edges[e].parent);
  Rprintf("\t.left=%d\n",edges[e].left);
  Rprintf("\t.right=%d\n",edges[e].right);
  Rprintf("\t.weight=%d\n",edges[e].weight);
}

/*****************
 void NetworkEdgeList

 Print an edgelist for a network
*****************/
void NetworkEdgeList(Network *nwp) {
  Vertex i;
  for(i=1; i<=nwp->nnodes; i++) {
    Rprintf("Node %d:\n  ", i);
    InOrderTreeWalk(nwp->outedges, i);
    Rprintf("\n");
  }
}

void WtNetworkEdgeList(WtNetwork *nwp) {
  Vertex i;
  for(i=1; i<=nwp->nnodes; i++) {
    Rprintf("Node %d:\n  ", i);
    WtInOrderTreeWalk(nwp->outedges, i);
    Rprintf("\n");
  }
}

/*****************
 void InOrderTreeWalk

 Diagnostic routine that prints the nodes in the tree rooted
 at edges[x], in increasing order of their values.
*****************/
void InOrderTreeWalk(TreeNode *edges, Edge x) {
  if (x != 0) {
    InOrderTreeWalk(edges, (edges+x)->left);
    /*    printedge(x, edges); */
    Rprintf(" %d ",(edges+x)->value); 
    InOrderTreeWalk(edges, (edges+x)->right);
  }
}

void WtInOrderTreeWalk(WtTreeNode *edges, Edge x) {
  if (x != 0) {
    WtInOrderTreeWalk(edges, (edges+x)->left);
    /*    printedge(x, edges); */
    Rprintf(" %d ",(edges+x)->value); 
    WtInOrderTreeWalk(edges, (edges+x)->right);
  }
}

/*****************
 Edge DesignMissing (see EdgetreeSearch)
*****************/
Edge DesignMissing (Vertex a, Vertex b, Network *mnwp) {
  int miss;
  miss = EdgetreeSearch(a,b,mnwp->outedges);
  if(mnwp->directed_flag){
    miss += EdgetreeSearch(a,b,mnwp->inedges);
  }
  return(miss);
}

Edge WtDesignMissing (Vertex a, Vertex b, WtNetwork *mnwp) {
  int miss;
  miss = WtEdgetreeSearch(a,b,mnwp->outedges);
  if(mnwp->directed_flag){
    miss += WtEdgetreeSearch(a,b,mnwp->inedges);
  }
  return(miss);
}

/*****************
  int FindithEdge

  Find the ith edge in the Network *nwp and
  update the values of head and tail appropriately.  Return
  1 if successful, 0 otherwise.  
  Note that i is numbered from 1, not 0.  Thus, the maximum possible
  value of i is nwp->nedges.
******************/
int FindithEdge (Vertex *head, Vertex *tail, Edge i, Network *nwp) {
  Vertex h=1;
  Edge e;

  if (i > nwp->nedges || i<=0)
    return 0;
  while (i > nwp->outdegree[h]) {
    i -= nwp->outdegree[h];
    h++;
  }
  e=EdgetreeMinimum(nwp->outedges,h);
  while (i-- > 1) {
    e=EdgetreeSuccessor(nwp->outedges, e);
  }
  *head = h;
  *tail = nwp->outedges[e].value;
  return 1;
}

int WtFindithEdge (Vertex *head, Vertex *tail, Edge i, WtNetwork *nwp) {
  Vertex h=1;
  Edge e;

  if (i > nwp->nedges || i<=0)
    return 0;
  while (i > nwp->outdegree[h]) {
    i -= nwp->outdegree[h];
    h++;
  }
  e=WtEdgetreeMinimum(nwp->outedges,h);
  while (i-- > 1) {
    e=WtEdgetreeSuccessor(nwp->outedges, e);
  }
  *head = h;                             
  *tail = nwp->outedges[e].value;
  return 1;
}


/*****************
  int FindithnonEdge

  Find the ith nonedge in the Network *nwp and
  update the values of head and tail appropriately.  Return
  1 if successful, 0 otherwise.  
  Note that i is numbered from 1, not 0.  Thus, the maximum possible
  value of i is (ndyads - nwp->nedges).
******************/

/* These functions are not yet written.  It's not clear whether they'll
   be needed. */      

/* int FindithnonEdge (Vertex *head, Vertex *tail, Edge i, Network *nwp) {
} */


/* int WtFindithnonEdge (Vertex *head, Vertex *tail, Edge i, WtNetwork *nwp) {
} */


/*****************
 long int EdgeWeight

 Return weight of (head,tail) in a WtNetwork
 *****************/
double EdgeWeight (Vertex head, Vertex tail, WtNetwork *nwp) 
{
  Edge k;
  if (!(nwp->directed_flag) && head > tail) {
    Vertex temp;
    temp = head; /*  Make sure head<tail always for undirected edges */
    head = tail;
    tail = temp;
  }

  if (nwp->directed_flag) 
    k = (tail-1)*(nwp->nnodes-1) + head - ((head>tail) ? 1:0) - 1; 
  else
    k = (tail-1)*(tail-2)/2 + head - 1;    
  return nwp->outedges[k].weight;
}

/****************
 unsigned int EdgeTree2EdgeList

 Write the edgelist of a network into head and tail arrays.
 Returns the number of edges in the network.
****************/
Edge EdgeTree2EdgeList(Vertex *heads, Vertex *tails, Network *nwp, Edge nmax){
  Edge nextedge=0;
  if (nwp->directed_flag) {
    for (Vertex v=1; v<=nwp->nnodes; v++){
      for(Vertex e = EdgetreeMinimum(nwp->outedges, v);
      nwp->outedges[e].value != 0 && nextedge < nmax;
      e = EdgetreeSuccessor(nwp->outedges, e)){
        heads[nextedge] = v;
        tails[nextedge] = nwp->outedges[e].value;
        nextedge++;
      }
    }
  }else{
    for (Vertex v=1; v<=nwp->nnodes; v++){
      for(Vertex e = EdgetreeMinimum(nwp->outedges, v);
      nwp->outedges[e].value != 0 && nextedge < nmax;
      e = EdgetreeSuccessor(nwp->outedges, e)){
        Vertex k = nwp->outedges[e].value;
        if(v < k){
          heads[nextedge] = k;
          tails[nextedge] = v;
          nextedge++;
        }else{
          heads[nextedge] = v;
          tails[nextedge] = k;
          nextedge++;
        }
      }
    }
  }
  return nextedge;
}
