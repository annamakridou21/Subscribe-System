/***************************************************************
 *
 * file: p.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "p.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include "pss.h"

typedef struct Info* p;
typedef struct Subscription* pS;
typedef struct SubInfo* pa;
struct Group G[MG];
struct SubInfo *T[MG];
int size,num,a,b;
pS head;      
p h; 

/**
 * @brief Optional function to initialize sId structures that
 *        need initialization
 *
 * @param m Size of the hash table.
 * @param p Prime number for the universal hash functions.
 *
 * @return 0 on success
 *         1 on failure
 */

int initialize(int m, int p){
    int i,upperA,upperB,lowerA,lowerB;
    for(i=0;i<m;i++){
        T[i]=NULL;
    }
    size=m;
    num=p;
    upperA=num-1;
    lowerA=1;
    upperB=num-1;
    lowerB=0;
    a=(rand()%(upperA-lowerA+1))+lowerA;
    b=(rand()%(upperB-lowerB+1))+lowerB;
    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    return EXIT_SUCCESS;
}


int L_Insert(pS qent,int x,int index) {
    pS newInfo;
    pS last;
    newInfo=(struct Subscription*)malloc(sizeof(struct Subscription));
    if (!newInfo) return 0;
    last=G[index].gsub;
    newInfo->sId=x;
    newInfo->snext=NULL;                                        
    if(qent==NULL) {                                     /*an h lista einai adeia tote to newInfo einai to head ths listas*/
        newInfo->snext=G[index].gsub;                          
        G[index].gsub=newInfo;
    }
    else{ 
        while(last->snext!=NULL) {                          /*alliws vazw to stoixeio sto telos ths listas. vriskw to telos ths listas me to last pointer*/
            last=last->snext;
        }       
        last->snext=newInfo;                                    /*teleutaio stoixeio to newInfo*/
    }
    return 0;
}

int L_Delete(int key,int i) {
    pS qent;
    pS prev;
    qent=G[i].gsub;
    prev=qent;
    while(qent->sId!=key && qent!=NULL) {                     /*psaxnw to stoixeio pou thelw na diagrapsw*/
        prev=qent;                                               /*krataw kai enan prev pointer epeidh thelw o prev pointer na deixnei sto next tou stoixeiou pou tha diagrapsw*/
        qent=qent->snext;
    }
    if(qent==G[i].gsub) {                                       /*an thelw na diagrapsw to prwto stoixeio ths listas tote apla proxwraw to head kai xanetai to prwto stoixeio*/
        G[i].gsub=G[i].gsub->snext;
    }else{
        if(qent->snext!=NULL) {
            prev->snext=qent->snext;                             /*an den thelw na svhsw to teleutaio stoixeio tote o prev pointer deixnei sto next tou qent.etsi to qent xanetai*/
        }
        else prev->snext=NULL;                                      /*an thelw na svhsw to teleutaio stoixeio ths listas tote o next pointer tou prev deixnei sto null. ara to teleutaio stoixeio xanetai*/
    }
    return 0;
}

int L_LookUp(int x,int i) {
    pS qent=G[i].gsub;
    while(qent!=NULL) {
        if(qent->sId==x) return 1;                   /*epistrefw 1 an vrw to stoixeio pou psaxnw*/
        qent=qent->snext;
    }
    return 0;
}

int L_Print(int i) {
    pS qent,prev;
    printf("GROUPID= <%d>, ",G[i].gId);
    printf("SUBLIST:");
        qent=G[i].gsub; 
        prev=G[i].gsub;
            while(qent!=NULL){   
                /*PRINTS*/
                 if(qent->snext==NULL && qent==G[i].gsub) {
                        printf("<%d>",qent->sId);                    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    }
                    else if(qent->snext==NULL && prev!=NULL){          /* ama uparxoun parapanw apo ena stoixeia tote to teleutaio stoixeio teleiwnei me >*/
                        printf("%d>",qent->sId);
                    }
                    else if(qent==G[i].gsub) {                      /*kai to prwto arxizei me <*/
                          printf("<%d,",qent->sId);
                    }
                    else{
                        printf("%d,",qent->sId);             /* alliws diaxwrizetai me komma */
                    }                
                prev=qent;
                qent=qent->snext;                      /*kanw traverse th lista kai tupwnw ena ena to sId*/  
            }                            
    printf("\n");
    return 0;
}

p BST_Insert(p qent, int x,int y,int i){
    p q=G[i].gr,prev=NULL;
    struct Info* newInfo=(struct Info*)malloc(sizeof(struct Info));
    newInfo->iId = x;
    newInfo->itm=y;
    newInfo->ilc = NULL;            /*ftiaxnw ton kainourgio komvo*/
    newInfo->irc = NULL;
    newInfo->ip=NULL;
    while (q!=NULL) {
        prev=q;
        q->ip=prev;                 /*enwnw me ton prohgoumeno*/
        if (x<q->iId)
            q=q->ilc;               /*an einai mikroteros o arithmos pou thelw na eisagw apo th riza tote ton eisagw sto aristero upodendro alliws antistoixa sto deksi*/
        else
            q=q->irc;
    }
    if (prev == NULL) return newInfo; /*an to dentro einai adeio tote vazoume ws root to newInfo*/
    else if (x < prev->iId) {
        prev->ilc=newInfo;              /*sundew ton neo komvo me ton prohgoumeno tou*/
        newInfo->ip=prev;
    }
    else {
        prev->irc=newInfo;
        newInfo->ip=prev;
    }
    return G[i].gr;     
}

p BST_LookUp(p q,int x){
    while (q!=NULL){  
                  /*diatrexw olo to bst*/
        if(x==q->iId) return q;             /*an to vrw,epistrefw ton komvo pou periexei to iId*/
        if(x<q->iId)q=q->ilc;              
        else q=q->irc;
    }
    return NULL;       /*an de vrw tipota, epistrefw 0*/
}

p BST_Delete(p q,int x,int i){
    p n=NULL,nextOrd;
    q=BST_LookUp(q,x);       /*an auto pou psaxnw den uparxei kanw return*/
    if (q==NULL) return G[i].gr;     
    /*1H PERIPTWSH: O pros diagrafh komvos einai fullo.*/
    if(q->ilc==NULL && q->irc==NULL){ 
        if(q->ip==NULL) {
            G[i].gr=NULL;           /*an einai fullo kai den exei gonea tote einai h riza pou theloume na diagrapsoume opote thetw th riza null*/
        }
        else {
            if(q->ip->ilc==q)q->ip->ilc=NULL;             /*An o pros diagrafh komvos einai aristero paidi tou patera tou, tote o aristeros pointer tou patera tha deixnei sto null*/
            else if(q->ip->irc==q) q->ip->irc=NULL;         /*antistoixa gia an einai deksi paidi*/
        }
    }
    /*2H PERIPTWSH: O pros diagrafh komvos exei mono ena paidi*/
    else if (q->ilc==NULL || q->irc==NULL) {
        if(q->ip!=NULL){                                    
            if (q->ilc==NULL) {                             /*an exei mono deksi paidi tote elegxoume an */
                if(q->ip->ilc==q)q->ip->ilc=q->irc;
                else if(q->ip->irc==q)q->ip->irc=q->irc;
            }
            else if(q->irc==NULL){
                if(q->ip->ilc==q)q->ip->ilc=q->ilc;
                else if(q->ip->irc==q)q->ip->irc=q->ilc;
            }
        }   
        else{                                       /*an o komvos exei mono ena paidi kai den exei patera, tote vriskomaste sth riza*/
            if(q->ilc==NULL) {              
                G[i].gr=G[i].gr->irc;               /*an to paidi auto einai to deksi paidi tote h riza deixnei pia sto deksi paidi,antistoixa gia to aristero */
            }
            else if(q->irc==NULL) {
                G[i].gr=G[i].gr->ilc;
            }
        }
    }
    /*3H PERIPTWSH:O pros diagrafh komvos exei duo paidia ara psaxnw ton epomeno sthn endodiatetagmenh diasxish*/
    else {
        nextOrd=q->irc;            /*apothikeuw to deksi paidi mou gia na vrw terma aristera sto upodendro ton epomeno sthn endodiatetagmenh*/
        while (nextOrd->ilc!= NULL) {  /*paw terma aristera gia na vrw ton epomeno*/
            n=nextOrd;                /*apothikeuw ton epomeno*/
            nextOrd=nextOrd->ilc;
        }
        if (n!=NULL) {                  
            n->ilc=nextOrd->irc;      /*an ton vrhka tote vazw to deksi paidi tou nextord,an uparxei, ws paidi mou*/
            q->iId=nextOrd->iId;          /*antikathistw ton pros diagrafh komvo me to deksi paidi tou*/
            q->irc=n;                       /*ara o komvos pou vrhkame na einai o epomenos sthn endodiatetagmenh deixnei ston epomeno sthn endo tou diegramenou komvoy*/

        }
        else {
            q->irc=nextOrd->irc;             /*alliws diwxnw to deksi paidi kai to antikathistw me ton pros diagrafh komvo*/
            q->iId=nextOrd->iId;          /*antikathistw ton pros diagrafh komvo me to deksi paidi tou*/

        }
    }
    return G[i].gr;
}

 

void BST_Print(p qent){
    if(qent!=NULL) {
        BST_Print(qent->ilc);
        printf("%d ",qent->iId);         
        BST_Print(qent->irc);
    }
}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    int i,j;
    struct Info ptr;
    for(i=0;i<MG;i++){
        G[i].gId=i;                     /*arxikopoihsh*/
        ptr.igp[i]=0;    
    }
    for(i=0;i<MG;i++) {                     /*gia kathe omada i*/
        for(j=0;j<size_of_gids_arr;j++){                        /*elegxw ama kapoio stoixeio tou gids_arr isoutai me kapoio apo ta gid twn omadwn*/
            if(G[i].gId==gids_arr[j] && gids_arr[j]!=-1) {              
                    if(BST_LookUp(G[i].gr,iId)==0) {
                        if(G[i].gr==NULL)G[i].gr=BST_Insert(G[i].gr,iId,iTM,i);          /*eisagw sth riza to prwto stoixeio*/
                        else BST_Insert(G[i].gr,iId,iTM,i);     
                        ptr.igp[i]=1;                                   /*h plhroforia susxetizetai me thn omada i*/
                        printf("GROUPID=<%d>, ",G[i].gId);              
                        printf("INFOLIST:");                        /*tupwnw to InfoTree*/
                        BST_Print(G[i].gr); 
                        printf("\n");
                    }
            }  
        }
    }
    return EXIT_SUCCESS;
}
int Universal_Hash_Function(int x){
    return (a*x+b)%size;                    /*h hash function pou kaname sto mathima*/
}

void HT_Insert(int key){
    int pos;
    struct SubInfo* q;
    struct SubInfo* newInfo;
    struct SubInfo* prev;
    newInfo=(struct SubInfo*)malloc(sizeof(struct SubInfo));
    newInfo->sId=key;                                               /*ftiaxnw ton neo komvo*/
    newInfo->snext=NULL;
    pos= Universal_Hash_Function(key);          /*h hash function mou leei pou na to valw*/
    q=T[pos];
    if(T[pos]==NULL){                   /*ama h alusida einai adeia to vazw sth prwth thesh*/
        T[pos]=newInfo;
    }
    else if(q->sId>=newInfo->sId){                  /*auksousa taksinomhmenh lista me vash to sId*/
        newInfo->snext=T[pos];                    /*an o arithmos pou paw na eisagw einai mikroteros/isos apo to head ths listas tote prepei na mpei ws prwto stoixeio sth lista*/
        T[pos]=newInfo;
    }
    else{
        while(q!=NULL&&q->sId<=newInfo->sId){                    /*oso to neo stoixeio einai mikrotero proxwrame sth lista mexri na vroume pou prepei na mpei kai kratame ton prohgoumeno tou*/
            prev=q;                                                 
            q=q->snext;
        }
        newInfo->snext=prev->snext;         /*eisagwgh meta ton prohgoumeno*/
        prev->snext=newInfo;
    }
}
void HT_Delete(int key){
    int pos;
    struct SubInfo* q;
    struct SubInfo* prev;
    pos= Universal_Hash_Function(key);
    q=T[pos];
    while(q->sId!=key && q!=NULL) {                     /*psaxnw to stoixeio pou thelw na diagrapsw*/
        prev=q;                                               /*krataw kai enan prev pointer epeidh thelw o prev pointer na deixnei sto next tou stoixeiou pou tha diagrapsw*/
        q=q->snext;
    }
    if(q==T[pos]) {                                       /*an thelw na diagrapsw to prwto stoixeio ths listas tote apla proxwraw to head kai xanetai to prwto stoixeio*/
        T[pos]=T[pos]->snext;
    }else{
        if(q->snext!=NULL) {
            prev->snext=q->snext;                             /*an de thelw na svhsw to teleutaio stoixeio tote o prev pointer deixnei sto next tou qent.etsi to qent xanetai*/
        }
    }
}
struct SubInfo* HT_LookUp(int key){
    int pos;
    struct SubInfo* q;
    pos= Universal_Hash_Function(key);
    q=T[pos];                                       /*psaxnw sth thesh tou pinaka katakermatismou sthn alusida pou mou leei h hash function*/
        while(q!=NULL){
            if (q->sId==key)return q;
            q=q->snext;
        }
    return NULL;
}

void HT_Print(){
    int i;
    struct SubInfo *q;
    printf("SUBSCRIBERLIST=");
    for(i = 0; i < size; i++){
        q=T[i];
        while(q!=NULL){
            printf("%d ",q->sId);
            q = q->snext;
        }
    }
    printf("\n");
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    int i,j,c;
    struct SubInfo ptr;                
    for(i=0;i<MG;i++){
        G[i].gId=i;                                 
    }
    if (HT_LookUp(sId)==0) {                      
        HT_Insert(sId);                     /*an den uparxei autos o sundromhths tote ton eggrafw */
    }
    for(i=0;i<MG;i++) {
        for(j=0;j<size_of_gids_arr;j++){
            if(G[i].gId==gids_arr[j]) { 
                if(gids_arr[j]!=-1){
                    c=L_LookUp(sId,i);                  /*an den uparxei autos o sundromhths sth lista sundromwn ths k omadas tote ton eisagw*/
                    if(c==0) {
                        L_Insert(G[i].gsub,sId,i);                       
                    }
                }
            }
        }    
    }
    HT_Print();
    for(i=0;i<MG;i++) {                                               /*tupwnw*/
        for(j=0;j<size_of_gids_arr;j++){
            if(G[i].gId==gids_arr[j] && gids_arr[j]!=-1) L_Print(i);                
        }
    }
    return EXIT_SUCCESS;
}

struct TreeInfo* LO_BST_Insert(struct TreeInfo * root,int x,int y,int pos,int i){
    struct TreeInfo* ptr;
    struct TreeInfo* newnode1,*newnode2;
    newnode1=(struct TreeInfo*)malloc(sizeof(struct TreeInfo));
    newnode2=(struct TreeInfo*)malloc(sizeof(struct TreeInfo));
    newnode1->ttm=x;
    newnode1->tId=y;                /*ftiaxnw ton neo komvo*/
    if (root==NULL){                    /*ama to list einai adeio tote to vazw san riza*/
        T[pos]->tgp[i]=newnode1;
        return T[pos]->tgp[i];
    }
    else{
        ptr=root;
        while(ptr->tlc!=NULL)ptr=ptr->tlc;                              /*eisagoume mono sta fulla opote paw terma aristera sto dentro kai kanw traverse th lista twn fulwn*/
        while(ptr->ttm<x && ptr->next!=NULL)ptr=ptr->next;          /*psaxnw na vrw se poia thesh tha valw to neo stoixeio*/
        
        if(x<ptr->ttm){             /*ama h eisagwgh de theloume na ginei sto telos*/
            newnode1->ttm=x;                    
            newnode2->ttm=ptr->ttm;
            ptr->tlc=newnode1;
            ptr->trc=newnode2;
            ptr->ttm=x;
            newnode1->tp=ptr;
            newnode2->tp=ptr;
            newnode1->next=newnode2;
            newnode2->prev=newnode1;
            ptr->tlc->prev=ptr->prev;
            ptr->trc->next=ptr->next;
            if(ptr->prev!=NULL)  {
                if(ptr->prev->next!=NULL)ptr->prev->next=newnode1;
            }
            if(ptr->next!=NULL) {
                if(ptr->next->prev!=NULL )  ptr->next->prev=newnode2;
            }
        }
        else {                                  /*ama h eisagwgh ginei sto telos*/
            newnode1->ttm=ptr->ttm;
            newnode2->ttm=x;
            ptr->tlc=newnode1;
            ptr->trc=newnode2;
            ptr->ttm=x;
            newnode1->tp=ptr;
            newnode2->tp=ptr;
            newnode1->next=newnode2;
            newnode2->prev=newnode1;
            if(ptr->prev!=NULL)if(ptr->tlc->prev!=NULL)ptr->tlc->prev=ptr->prev;
            if(ptr->next!=NULL)if(ptr->trc->next!=NULL)ptr->trc->next=ptr->next;
            if(ptr->prev!=NULL)  {
                if(ptr->prev->next!=NULL)ptr->prev->next=newnode1;
            }
        }
    }
    return root;
}
int LO_BST_LookUp(struct TreeInfo* q,int x){
    while(q->tlc!=NULL)q=q->tlc;            /*h anazhthsh ginetai sta fulla tou dentrou epeidh ekei ginontai oi eisagwges*/
    while(q!=NULL){
        if(q->tId==x) return 1;
        q=q->next;
    }
    return 0;
}
void LO_Print(struct TreeInfo *q){
    if (q==NULL) return ;
    if (q->tlc==NULL && q->trc==NULL){              /*ama vrhka fullo tupwnw*/
        printf("%d ",q->tId);
    }
    LO_Print(q->tlc);
    LO_Print(q->trc);
}

/*VOHTHITIKH LISTA GIA TO PRUNE EVENT*/
int helpLookUp(int x) {
    p qent=h;
    while(qent!=NULL) {
        if(qent->iId==x) return 1;                   /*epistrefw 1 an vrw to stoixeio pou psaxnw*/
        qent=qent->ilc;
    }
    return 0;
}
int helpInsert(p qent,int x,int y) {
    p newnode;
    p prev;
    newnode=(struct Info*)malloc(sizeof(struct Info));
    if (!newnode) return 0;

    prev=qent;                                                       
    newnode->iId=x;       
    newnode->itm=y;                                      

    if(h==NULL) {                               /*an h lista einai adeia tote vazw ws head to newnode*/
        h=newnode;
    }
    else if(qent->iId <= newnode->iId) {
        newnode->ilc=h;                                 /*h lista einai taksinomhmenh me auksousa seira. an o arithmos pou paw na eisagw einai mikroteros/isos apo to head ths listas tote prepei na mpei ws prwto stoixeio sth lista*/
        h=newnode;
    }
    else{
        while(qent!=NULL && qent->iId >= newnode->iId) {              /*oso to neo stoixeio einai mikrotero proxwrame sth lista*/
            prev=qent;
            qent=qent->ilc;
        }                                                      
        newnode->ilc=prev->ilc;                       
        prev->ilc=newnode;                              
    }    
    return 0;
}
/*VOHTHITIKES SUNARTHSEIS GIA TO PRUNE EVENT*/
void r(struct Info* q,int tm){
    int j;
    if(q==NULL)return;
    r(q->ilc,tm);
    if(q->itm<=tm) {
        if(helpLookUp(q->iId)==0)helpInsert(h,q->iId,q->itm);
    }
    r(q->irc,tm);
}
struct TreeInfo* ins(struct Info* q,struct TreeInfo* root,int tm,int pos,int i){
    int j;
    struct SubInfo o;
    if(q==NULL)return NULL;
    ins(q->ilc,root,tm,pos,i);
    if(q->itm<=tm) {                    /*an to tm einai mikrotero tote kanw eisagwgh sto lo bst*/         
        LO_BST_Insert(root,q->itm,q->iId,pos,i);
    }
    ins(q->irc,root,tm,pos,i);
    return root;
}
/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */

int Prune(int tm){
    struct TreeInfo* ptr;
    struct SubInfo* q2;
    struct SubInfo* pp;
    pS pt,prev,qent;
    int i,j,pos,count=0;
    p q,pr;
    for(i=0;i<MG;i++){
      r(G[i].gr,tm);            
    }
    for(i=0;i<MG;i++){
        pt=G[i].gsub;
            while(pt!=NULL){    
                pp=HT_LookUp(pt->sId);                                  
                if(pt->sId==pp->sId) {              /*gia kathe sundromhth ftiaxnw to lo bst tou gia kathe omada pou endiaferetai*/          
                    pos=Universal_Hash_Function(pp->sId);
                    pp->tgp[i]=ins(G[i].gr,pp->tgp[i],tm,pos,i);
                }
                else pp->tgp[i]=(struct TreeInfo*)1;
                pt=pt->snext;
            }
    }
    q=h;
        while(q!=NULL){
            for(i=0;i<MG;i++) BST_Delete(G[i].gr,q->iId,i);       /*delete ta info pou apothikeusame sto lo bst*/
            q=q->ilc;
        }
    for(i=0;i<MG;i++) {
            if(G[i].gId>=0 && G[i].gId<=MG-1) {             /*an to gid einai egkuro tote metraw count++ tis omades*/    
                printf("GROUPID=<%d>, ",G[i].gId);
                printf("INFOLIST:");
                BST_Print(G[i].gr); 
                printf(", SUBLIST:");
                qent=G[i].gsub; 
                prev=G[i].gsub;
                while(qent!=NULL){   
                    printf("%d ",qent->sId);             /* alliws diaxwrizetai me komma */          
                    prev=qent;
                    qent=qent->snext;
                }        
                printf(", TREELIST:");
                for(j=0;j<size;j++){
                    q2=T[j];
                    while(q2!=NULL) { 
                        LO_Print(q2->tgp[i]);
                        q2=q2->snext;
                    }
                }
                printf("\n");
        }
    }
        for(i=0;i<size;i++){
        q2=T[i];
        while(q2!=NULL) {
            printf("SUBSCRIBERID=<%d>, GROUPLIST=",q2->sId);                 /*tupwnw enan enan tous sundromhtes tou susthmatos*/
            for(j=0;j<MG;j++){
                pt=G[j].gsub;
                while(pt!=NULL){
                    if (pt->sId==q2->sId) printf("%d ",G[j].gId);
                    pt=pt->snext;
                }
            }
            printf("\n");
            q2=q2->snext;
        }
    }    
    return EXIT_SUCCESS;
}


/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
 
int Consume(int sId){
   return EXIT_SUCCESS;
}


/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
    int c,i;
    if(HT_LookUp(sId)!=NULL) {                          /*an uparxei to sid sth lista sundromhtwn tote mporw na to diagrapsw*/
        HT_Delete(sId);
        HT_Print();
    }
    else return EXIT_FAILURE;
    for(i=0;i<MG;i++) {
        if(G[i].gId>=0 && G[i].gId<=MG-1) {             /*an uparxei to sid sth lista sundromwn to diagrafw*/
            c=L_LookUp(sId,i);
        }
        if(c==1) {
            L_Delete(sId,i);
        }
    }
    for(i=0;i<MG;i++) {
        if(G[i].gId>=0 && G[i].gId<=65 && G[i].gsub!=NULL) {             /*tupwnw tis nees listes*/
            L_Print(i);
        }
    }
    return EXIT_SUCCESS;
}
int SubCount(){
    struct SubInfo* q;
    int i;
    int count=0;
    for(i=0;i<size;i++){
        q=T[i]; 
        while(q!=NULL){                  /*upologizw olous tous syndomhtes tou susthmatos kanontas traverse to list me tous subscribers*/
            q=q->snext;
            count=count+1;                                  
        }
    }
    return count;
}
/**
 * @brief Print sId Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
    int i,c,j;
    pS q,prev,qent;
    struct SubInfo ptr;
    struct SubInfo* q2;
    for(i=0;i<MG;i++) {
        if(G[i].gId>=0 && G[i].gId<=MG-1) {             /*an to gid einai egkuro tote metraw count++ tis omades*/    
            printf("GROUPID=<%d>, ",G[i].gId);
            printf("INFOLIST:");
            BST_Print(G[i].gr); 
            printf(", SUBLIST:");
            qent=G[i].gsub; 
            prev=G[i].gsub;
            while(qent!=NULL){   
                printf("%d ",qent->sId);             /* alliws diaxwrizetai me komma */          
                prev=qent;
                qent=qent->snext;
            }        
            printf("\n");   
        }
    }
    printf("\n");   
    HT_Print();
    printf("\n");     
    for(i=0;i<size;i++){
        q2=T[i];
        while(q2!=NULL) {
            printf("SUBSCRIBERID=<%d>, GROUPLIST=",q2->sId);                 /*tupwnw enan enan tous sundromhtes tou susthmatos*/
            for(j=0;j<MG;j++){
                q=G[j].gsub;
                while(q!=NULL){
                    if (q->sId==q2->sId) printf("%d ",G[j].gId);
                    q=q->snext;
                }
            }
            printf("\n");
            q2=q2->snext;
        }
    }                                                   
    printf("\nNO_GROUPS=<%d>, NO_SUBSCRIBERS=<%d>\n\n", MG, SubCount());                /*tupwnw ton arithmo twn groups(MG) kai ton arithmo twn sundromhtwn sto susthma*/
    return EXIT_SUCCESS;
}
