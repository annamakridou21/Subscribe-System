/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include "pss.h"

typedef struct Info* pI;
typedef struct Subscription* pS;
typedef struct SubInfo* p;

struct Group G[MG];
struct SubInfo *S;


/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(void){
    return EXIT_SUCCESS;
}


/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */

int free_all(void) {
    return EXIT_SUCCESS;
}

/**
 * INFO LIST - DOUBLY LINKED LIST 
 * AUKSOUSA TAKSINOMHSH WS PROS ITM
*/

int DL_Insert(pI current, int x, int y,int index) {
    pI newnode;                                                         /*ftiaxnw ton kainourgio komvo pou tha eisagw sth lista*/
    newnode=(struct Info*)malloc(sizeof(struct Info));
    if (!newnode) return 0;

    newnode->itm=x;
    newnode->iId=y;                                                    

    if(G[index].gfirst==NULL) {
        G[index].gfirst=newnode;                                    /*ama h lista einai adeia tote o deikths gfirst,glast deixnoun sto neo auto komvo*/
        G[index].glast=newnode;
    }
    else if(current->itm >= newnode->itm) {
        current->iprev=newnode;
        newnode->inext=current;                              /*h lista einai taksinomhmenh me auksousa seira. an o arithmos pou paw na eisagw einai mikroteros/isos apo to head ths listas tote prepei na mpei ws prwto stoixeio sth lista*/
        G[index].gfirst=newnode;                             /*epomenws vazw ton prev pointer tou head ths listas na deixnei sto kainourgio komvo kai orizw ws head to neo komvo. sunepws to prwhn head ths listas einai pleon to deutero stoixeio ths listas kai to kainourgio node einai to neo head*/
    }
    else { 
        current=G[index].gfirst;                                /*se kathe allh periptwsh diasxizoume th lista mexri na vroume enan arithmo MEGALUTERO h iso apo auton pou theloume na eisagoume. stamatame se auton ton arithmo kai eisagoume ton neo komvo PRIN apo auton ton arithmo*/
        while(current!=NULL){                                   /*estw h lista 5->7 kai thelw na eisagw to 6    5->6->7*/
                if(current->itm >=newnode->itm) {               /*vriskw ton amesws megalutero/iso arithmo apo auton pou thelw na eisagw (sto paradeigma mas ton 7)*/
                    current->iprev->inext=newnode;              /*o next pointer tou prohgoumenou arithmou apo autou pou stamathsame deixnei ston neo komvo,ara o neos komvos mpainei mia thesh prin. (sto paradeigma mas thelw na eisagw to 6. se auth th periptwsh to current->iprev einai to 5 kai theloume to current->iprev->inext na deixnei sto 6)*/
                    newnode->iprev=current->iprev;              /*o prev pointer tou neou arithmou deixnei ekei pou edeixne prin o megaluteros tou arithmos(sto paradeigma mas o iprev pointer tou 6 deixnei sto 5)*/
                    current->iprev=newnode;                     /*o prev pointer tou epomenou arithmou deixnei sto neo komvo. (sto paradeigma mas o prev pointer tou 7 deixnei sto 6)*/
                    newnode->inext=current;                     /*o next pointer tou newnode deixnei ston epomeno pou stamathsame thn anazhthsh (sto paradeigma mas o next pointer tou 6 deixnei sto 7)*/
                    break;
                }
                else if(current->inext==NULL) {                 /*se allh periptwsh stamathsame sto teleutaio stoixeio ths listas*/
                    current->inext=newnode;                     /*vazoume to next pointer tou teleutaiou stoixeiou na deixnei sto newnode anti na deixnei sto null.ara to teleutaio stoixeio einai auto pou eisagame*/
                    newnode->iprev=current;                     /*vazoume san proteleutaio stoixeio to stoixeio pou eixame prin ws teleutaio*/
                    G[index].glast=newnode;                     /*ara o pointer glast deixnei sto newnode*/
                    break;      
                }
                current=current->inext;
        } 
    }   
    return 0;
}

int DL_Delete(int key, int i) {
    pI current;
    current=G[i].gfirst;
    while(current->iId!=key && current!=NULL) {             /*psaxnw na vrw to iId pou thelw na diagrapsw*/
        current=current->inext;
    }
    if(current==G[i].gfirst) {
        G[i].gfirst=G[i].gfirst->inext;             /*ama einai to prwto stoixeio tote apla proxwraw to head kai to prwto stoixeio xanetai*/
    }
    else {                                                      /*estw h lista 4->5->6->7 kai thelw na svhsw to 6*/
        if(current->inext!=NULL) {
            current->inext->iprev=current->iprev;                       /*ama den einai to teleutaio stoixeio tote enwnw to prohgoumeno me to epomeno apo auto pou tha diagrapsw. sto paradeigma mas to current einai to 6 ara vazw ton prev pointer tou 7 na deixnei sto 5*/
        }
        if(current->iprev!=NULL) {
            current->iprev->inext=current->inext;                       /*ama den einai to prwto stoixeio tote vazw ton next pointer tou 5 na deixnei sto next tou 6, dhladh sto 7*/
        }
    } 
    return 0;
}

int DL_LookUp(pI current,int x, int i) {
    while(current!=NULL) {
        if(current->iId==x) return 1;                           /*epistrefw 1 an vrw to stoixeio pou psaxnw*/
        current=current->inext;
    }
    return 0;
}

void DL_Print(pI current,int i) {
    printf("GROUPID=<%d>, ",G[i].gId);
    printf("INFOLIST:");
        while(current!=NULL){
                    if(current->inext==NULL && current->iprev==NULL) {
                        printf("<%d>",current->iId);    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    }
                    else if(current->iprev==NULL) {         /* ama uparxoun parapanw apo ena stoixeia tote to prwto stoixeio ksekinaei me < */
                        printf("<%d,",current->iId);
                    } 
                    else if(current->inext==NULL){          /* kai to teleutaio stoixeio teleiwnei me >*/
                        printf("%d>",current->iId);
                    }
                    else{
                        printf("%d,",current->iId);             /* alliws diaxwrizetai me komma */
                    }
                    current=current->inext;
        }
        printf("\n");
}

/**
 * SUBSCRIPTION LIST - KAMIA TAKSINOMHSH
 * 
*/

int L_Insert(pS current,int x,int index) {
    pS newnode;
    pS last;
    newnode=(struct Subscription*)malloc(sizeof(struct Subscription));
    if (!newnode) return 0;
    last=G[index].ggsub;
    newnode->sId=x;
    newnode->snext=NULL;                                        
    if(current==NULL) {                                     /*an h lista einai adeia tote to newnode einai to head ths listas*/
        newnode->snext=G[index].ggsub;                          
        G[index].ggsub=newnode;
    }
    else{ 
        while(last->snext!=NULL) {                          /*alliws vazw to stoixeio sto telos ths listas. vriskw to telos ths listas me to last pointer*/
            last=last->snext;
        }       
        last->snext=newnode;                                    /*teleutaio stoixeio to newnode*/
    }
    return 0;
}


int L_Delete(int key,int i) {
    pS current;
    pS prev;
    current=G[i].ggsub;
    prev=current;
    while(current->sId!=key && current!=NULL) {                     /*psaxnw to stoixeio pou thelw na diagrapsw*/
        prev=current;                                               /*krataw kai enan prev pointer epeidh thelw o prev pointer na deixnei sto next tou stoixeiou pou tha diagrapsw*/
        current=current->snext;
    }
    if(current==G[i].ggsub) {                                       /*an thelw na diagrapsw to prwto stoixeio ths listas tote apla proxwraw to head kai xanetai to prwto stoixeio*/
        G[i].ggsub=G[i].ggsub->snext;
    }else{
        if(current->snext!=NULL) {
            prev->snext=current->snext;                             /*an den thelw na svhsw to teleutaio stoixeio tote o prev pointer deixnei sto next tou current.etsi to current xanetai*/
        }
        else prev->snext=NULL;                                      /*an thelw na svhsw to teleutaio stoixeio ths listas tote o next pointer tou prev deixnei sto null. ara to teleutaio stoixeio xanetai*/
    }
    return 0;
}

int L_LookUp(int x,int i) {
    pS current=G[i].ggsub;
    while(current!=NULL) {
        if(current->sId==x) return 1;                   /*epistrefw 1 an vrw to stoixeio pou psaxnw*/
        current=current->snext;
    }
    return 0;
}

int L_Print(int i) {
    pS current,prev;
    printf("GROUPID= <%d>, ",G[i].gId);
    printf("SUBLIST:");
        current=G[i].ggsub; 
        prev=G[i].ggsub;
            while(current!=NULL){   
                /*PRINTS*/
                 if(current->snext==NULL && current==G[i].ggsub) {
                        printf("<%d>",current->sId);                    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    }
                    else if(current->snext==NULL && prev!=NULL){          /* ama uparxoun parapanw apo ena stoixeia tote to teleutaio stoixeio teleiwnei me >*/
                        printf("%d>",current->sId);
                    }
                    else if(current==G[i].ggsub) {                      /*kai to prwto arxizei me <*/
                          printf("<%d,",current->sId);
                    }
                    else{
                        printf("%d,",current->sId);             /* alliws diaxwrizetai me komma */
                    }                
                prev=current;
                current=current->snext;                      /*kanw traverse th lista kai tupwnw ena ena to sId*/  
            }                            
    printf("\n");
    return 0;
}

/**
 * SUBINFO LIST - AUKSOUSA TAKSINOMHSH WS PROS STM
 * 
*/

int SL_Insert(p current, int x, int y) {
    p newnode;
    p prev;
    newnode=(struct SubInfo*)malloc(sizeof(struct SubInfo));
    if (!newnode) return 0;

    prev=current;                                                       
    newnode->sId=x;                                             
    newnode->stm=y;

    if(S==NULL) {                               /*an h lista einai adeia tote vazw ws head to newnode*/
        S=newnode;
    }
    else if(current->stm >= newnode->stm) {
        newnode->snext=S;                                 /*h lista einai taksinomhmenh me auksousa seira. an o arithmos pou paw na eisagw einai mikroteros/isos apo to head ths listas tote prepei na mpei ws prwto stoixeio sth lista*/
        S=newnode;
    }
    else{
        while(current!=NULL && current->stm <= newnode->stm) {              /*oso to neo stoixeio einai mikrotero proxwrame sth lista*/
            prev=current;
            current=current->snext;
        }                                                       /*estw h lista 5->7 kai thelw na eisagw to 6*/
        newnode->snext=prev->snext;                         /*o next pointer tou 6 deixnei sto next tou prev dhladh sto 7*/
        prev->snext=newnode;                                /*o next tou prev dhladh tou 5 deixnei sto newnode dhladh sto 6*/
    }    
    return 0;
}

int SL_Delete(int key) {
    p current;
    p prev;
    current=S;
    prev=current;
    while(current->sId!=key && current!=NULL) {                  /*psaxnw to stoixeio pou thelw na diagrapsw */
        prev=current;
        current=current->snext;
    }
    if(current==S) {                                                /*an einai to prwto stoixeio tote proxwraw to head*/
        S=S->snext;
    }else{
        if(current->snext!=NULL) {
            prev->snext=current->snext;                             /*vazw ton next pointer tou prev na deixnei sto epomeno tou current. etsi to current xanetai*/
        }
        else prev->snext=NULL;                                      /*an thelw na svhsw to teleutaio tote vazw ton next tou prev na deixnei sto null. etsi to teleutaio xanetai*/
    }
    return 0;
}

int SL_LookUp(int x) {
    p current=S;
    while(current!=NULL) {
        if(current->sId==x) return 1;                       /*an vrw to stoixeio pou psaxnw epistrefw 1*/
        current=current->snext;
    }
    return 0;
}

void SL_Print() {
    p current=S;
    printf("SUBSCRIBERLIST=");
            while(current!=NULL) {
                /*PRINTS*/
                if(current->snext==NULL && current==S) {
                        printf("<%d>",current->sId);    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    }
                    else if(current->snext==NULL){          /* an uparxoun parapanw apo ena stoixeia tote to teleutaio stoixeio teleiwnei me >*/
                        printf("%d>",current->sId);
                    }
                    else if(current==S) {                               /*kai to prwto arxizei me <*/
                          printf("<%d,",current->sId);
                    }
                    else{
                        printf("%d,",current->sId);             /* alliws diaxwrizetai me komma */
                    }              
                current=current->snext;                /*kanw traverse th lista kai tupwnw ena ena to sId*/
            }
    printf("\n");    
}

/**
 * SUBCOUNT - UPOLOGISMOS TWN SUBSCRIBERS
 * 
*/

int SubCount(){
    p q;
    int i;
    int count=0;
        q=S; 
        while(q!=NULL){                  /*upologizw olous tous syndomhtes tou susthmatos kanontas traverse to list me tous subscribers*/
            q=q->snext;
            count=count+1;                                  
        }
    return count;
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
    int i,j,b;
    struct Info ptr;
    for(i=0;i<MG;i++){
        G[i].gId=i;                     /*arxikopoihsh*/
        ptr.igp[i]=0;    
    }
    for(i=0;i<MG;i++){
        b=DL_LookUp(G[i].gfirst,iId,i);             /*ama uparxei hdh to iId sth lista tote kanw exit den mporw na eisagw ksana to idio iId*/
        if (b==1) return EXIT_FAILURE;
    }
    for(i=0;i<MG;i++) {                     /*gia kathe omada i*/
        for(j=0;j<size_of_gids_arr;j++){                        /*elegxw ama kapoio stoixeio tou gids_arr isoutai me kapoio apo ta gid twn omadwn*/
            if(G[i].gId==gids_arr[j] && gids_arr[j]!=-1) {              
                b=DL_LookUp(G[i].gfirst,iId,i);                     /*psaxnw na vrw to id sto infolist.an den uparxei hdh sto list tote to eisagw,alliws proxwraw*/
                if(b==0) {
                    DL_Insert(G[i].gfirst,iTM,iId,i);
                    ptr.igp[i]=1;                                   /*h plhroforia susxetizetai me thn omada i*/
                    DL_Print(G[i].gfirst,i);    
                }  
              
            }
        }
    }
    return EXIT_SUCCESS;
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
    int i,j,b,c,interest[MG];
    struct SubInfo ptr;
    b=SL_LookUp(sId);
    if (b==1) return EXIT_FAILURE;    /*an o subscriber uparxei hdh kanw exit. den mporw na egrapsw ksana ton idio subscriber*/               
    for(i=0;i<MG;i++){
        G[i].gId=i;                                   /*arxikopoiw ta gid*/
    }
    for(i=0;i<MG;i++) {
        for(j=0;j<size_of_gids_arr;j++){
            if(G[i].gId==gids_arr[j]) {
                if(gids_arr[j]!=-1){
                    b=SL_LookUp(sId);                         /*an to sid den uparxei sth lista sundromhtwn / lista sundromwn to eisagw*/
                    c=L_LookUp(sId,i);
                    if(c==0) {
                        L_Insert(G[i].ggsub,sId,i);                       
                    }
                    if(b==0) {
                        SL_Insert(S,sId,sTM);
                    }
                }
            }
        }    
    }
    SL_Print();
    for(i=0;i<MG;i++) {                                               /*tupwnw*/
        for(j=0;j<size_of_gids_arr;j++){
            if(G[i].gId==gids_arr[j] && gids_arr[j]!=-1) L_Print(i);                
        }
    }
    return EXIT_SUCCESS;
}

/**
 * VOHTHITIKH LISTA GIA TO CONSUME EVENT
 * 
*/

pS head;        /*head vohthitikhs listas*/
 
int LL_Insert(pS current,int x) {
    pS newnode;
    pS last;
    newnode=(struct Subscription*)malloc(sizeof(struct Subscription));
    if (!newnode) return 0;
    last=head;
    newnode->sId=x;
    newnode->snext=NULL;                                        
    if(current==NULL) {                                     /*an h lista einai adeia tote to newnode einai to head ths listas*/
        newnode->snext=head;                          
        head=newnode;
    }
    else{ 
        while(last->snext!=NULL) {                          /*alliws vazw to stoixeio sto telos ths listas. vriskw to telos ths listas me to last pointer*/
            last=last->snext;
        }       
        last->snext=newnode;                                    /*teleutaio stoixeio to newnode*/
    }
    return 0;
}

int LL_LookUp(int x) {
    int count=0;
    pS current=head;
    while(current!=NULL) {
        if(current->sId==x) {               /*upologizw poses fores emfanizetai o idios subscriber pou zhtaei consume*/
            count++;
        }                  
        current=current->snext;
    }
    return count;
}

/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */

int Consume(int sId){
   struct SubInfo ptr;
   struct Info* q;
    pS pt;
    int i,interest[MG],ans,b;
    b=SL_LookUp(sId);
    if(b==0) return EXIT_FAILURE;
    else{
        LL_Insert(head,sId);                    /*krataw se ena kainourgio linked list tous subscribers pou ekanan consume*/
        for(i=0;i<MG;i++){                      /*an enas subscriber thelei na ksanakanei consume prepei na to gnwrizw giati pleon to infolist tou tha periexei infos pou de exei katanalwsei*/
            interest[i]=0;                  /*o pinakas interest periexei poies omades endiaferetai o sundromhths*/
            if(G[i].gfirst==NULL){
                ptr.sgp[i]=NULL;                    /*opws anaferetai sthn ekfwnhsh ama to infolist einai adeio tote o sgp deixnei sto null*/
            }
            else{
                pt=G[i].ggsub;
                while(pt!=NULL){                            /*se periptwsh pou vrethei to anagnwristiko sto sublist kapoias omadas auto-*/                           
                    if(pt->sId==sId) {                          /*-shmainei oti o sundromhths endiaferetai gia tis plhrofories ths. ara thetw 1*/
                        interest[i]=1;
                        break;                              /*ama ton vrw stamataw to psaksimo, afou den uparxoun diplotupa id*/
                    }
                    pt=pt->snext;
                }
                if(interest[i]==0){
                    ptr.sgp[i]=(struct Info*)1;                 /*ama den endiaferetai tote to sgp deixnei sto 1, me to katallhlo cast*/
                }
                else if(interest[i]==1){
                    ans=LL_LookUp(sId);                                 /*1h periptwsh: psaxnw na dw an autos o subscriber exei ksanakanei consume*/
                    ptr.sgp[i]=G[i].gfirst;

                    if(ans>1){                                              /*ama vrw to id tou panw apo mia fora sth lista tote exei ksanakanei consume*/
                        while(ptr.sgp[i]->inext!=NULL) {                   /*afou exei kanei consume, to sgp tou deixnei sto newsgp*/
                            ptr.sgp[i]=ptr.sgp[i]->inext;                 
                        }
                        /*PRINTS*/
                        printf("GROUPID=%d, ",G[i].gId);
                        printf("INFOLIST:");
                        printf("<%d>",ptr.sgp[i]->iId);    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    
                        if(ptr.sgp[i]->inext==NULL) printf(", NEWSGP=<%d>", 0);                 /*an den exei alla info na katanalwsei tote deixnei sto 0. alliws deixnei sto epomeno pio prosfato stoixeio*/
                        else printf(", NEWSGP=%d", ptr.sgp[i]->inext->iId);
                        printf("\n");
                    }

                    else {         
                        printf("GROUPID=%d, ",G[i].gId);                                 /*2h periptwsh: o subscriber kanei prwth fora consume*/
                        printf("INFOLIST:");
                        q=ptr.sgp[i];
                        while(q->inext!=NULL) q=q->inext;

                        while(ptr.sgp[i]->inext!=NULL) {
                            /*PRINTS*/
                            if(ptr.sgp[i]->inext==q && ptr.sgp[i]->iprev==NULL) {
                                printf("<%d>",ptr.sgp[i]->iId);    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                            }
                            else if(ptr.sgp[i]->iprev==NULL && ptr.sgp[i]->inext!=NULL) {         /* to prwto stoixeio ksekinaei me < */
                                printf("<%d,",ptr.sgp[i]->iId);
                            } 
                            else if(ptr.sgp[i]->inext==q) printf("%d>",ptr.sgp[i]->iId);            /* to teleutaio stoixeio teleiwnei me > */
                            else{
                                printf("%d,",ptr.sgp[i]->iId);             /* alliws diaxwrizetai me komma */
                            }
                        ptr.sgp[i]=ptr.sgp[i]->inext;                   /*proxwraw ton sgp mexri to stoixeio pou topothetithike pio prosfata*/
                        }
                        printf(", NEWSGP=<%d>", ptr.sgp[i]->iId);                 
                        printf("\n");

                    }
                }  
            }
        }
    }
    return 0;
}

/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */

int Delete_Subscriber(int sId){
    int b,c,i;
    b=SL_LookUp(sId);
    if(b==1) {                          /*an uparxei to sid sth lista sundromhtwn tote mporw na to diagrapsw*/
        SL_Delete(sId);
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
    SL_Print();
    for(i=0;i<MG;i++) {
        if(G[i].gId>=0 && G[i].gId<=65 && G[i].ggsub!=NULL) {             /*tupwnw tis nees listes*/
            L_Print(i);
        }
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */

int Print_all(void){
    int i,count[64],c;
    pS q,prev,current;
    struct SubInfo ptr;
    p q2;
    for(i=0;i<MG;i++) {
        if(G[i].gId>=0 && G[i].gId<=MG-1) {             /*an to gid einai egkuro tote metraw count++ tis omades*/    
            printf("GROUPID=<%d>, ",G[i].gId);
            printf("INFOLIST:");
                while(G[i].gfirst!=NULL){
                    if(G[i].gfirst->inext==NULL && G[i].gfirst->iprev==NULL) {
                        printf("<%d>",G[i].gfirst->iId);    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    }
                    else if(G[i].gfirst->iprev==NULL) {         /* to prwto stoixeio ksekinaei me < */
                        printf("<%d,",G[i].gfirst->iId);
                    } 
                    else if(G[i].gfirst->inext==NULL){          /* to teleutaio stoixeio teleiwnei me >*/
                        printf("%d>",G[i].gfirst->iId);
                    }
                    else{
                        printf("%d,",G[i].gfirst->iId);             /* alliws diaxwrizetai me komma */
                    }
                    G[i].gfirst=G[i].gfirst->inext;
                }
            printf(", SUBLIST:");
            current=G[i].ggsub; 
            prev=G[i].ggsub;
            while(current!=NULL){   
                 if(current->snext==NULL && current==G[i].ggsub) {
                        printf("<%d>",current->sId);    /* ama uparxei mono ena stoixeio tote tupwnetai me th morfh <iId> */
                    }
                    else if(current->snext==NULL && prev!=NULL){          /* to teleutaio stoixeio teleiwnei me >*/
                        printf("%d>",current->sId);
                    }
                    else if(current==G[i].ggsub) {
                          printf("<%d,",current->sId);
                    }
                    else{
                        printf("%d,",current->sId);             /* alliws diaxwrizetai me komma */
                    }                 /*kanw traverse th lista kai tupwnw ena ena to sId*/
                prev=current;
                current=current->snext;
            }        
            printf("\n");   
        }
    }
    printf("\n");   
    SL_Print();
    printf("\n");     
    q2=S;
    while(q2!=NULL) {
        printf("SUBSCRIBERID=<%d>, GROUPLIST=",q2->sId);                 /*tupwnw enan enan tous sundromhtes tou susthmatos*/
        for(i=0;i<MG;i++){
            q=G[i].ggsub;
            while(q!=NULL) {                                                    /*gia kathe omada psaxnw na vrw sto susthma kathe sundromhth*/
                if (q->sId==q2->sId){                                           /*ama vrw ton sundromhth sthn omada i tote tupwnw to id ths omadas i*/
                    printf("%d ",G[i].gId); 
                }
            q=q->snext;
            }
        }
        printf("\n");
        q2=q2->snext;
    }                                                           
    printf("\nNO_GROUPS=<%d>, NO_SUBSCRIBERS=<%d>\n\n", MG, SubCount());                /*tupwnw ton arithmo twn groups(MG) kai ton arithmo twn sundromhtwn sto susthma*/
    return EXIT_SUCCESS;
}
