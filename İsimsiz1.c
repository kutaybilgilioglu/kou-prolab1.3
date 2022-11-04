#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
typedef struct node
{
    char *kelime;
    int frekans;
    struct node *next;
}
node;
void basa_ekle(node *head,node *current);
void araya_ekle(node *head,node *current,int sayac);
void sona_ekle(node *head,node *current);
bool check(node *head,char *word);
int sira(node *head,node *current);
void yazdir(node *head);

int cursor=0;
int main()
{
    setlocale(LC_ALL, "Turkish");
    FILE *text=fopen("test1.txt","r");
    if(text==NULL)
        return 1;
    node *head=malloc(sizeof(node));
    char compare[30];
    head->frekans=1;
    head->next=NULL;
    head->kelime=malloc(sizeof(node));
    int k=0;
    fscanf(text,"%c",&head->kelime[k]);
    cursor++;
    while((int)(head->kelime[k])!=32)
    {
        realloc(head->kelime,sizeof(char));
        fscanf(text,"%c",&head->kelime[k+1]);
        cursor++;
        k++;
    }
    head->kelime[k]='\0';
    while(!feof(text))
    {
        fscanf(text,"%s",compare);
        if(strcmpi(head->kelime,compare)==0)
            head->frekans++;
    }
    fseek(text,cursor,SEEK_SET);
    printf("%s",head->kelime);
    printf("%d",head->frekans);
    node *current2=malloc(sizeof(node));
    current2->frekans=0;
    current2->next=NULL;
    while(!feof(text))
    {
        node *current=malloc(sizeof(node));
        current->frekans=0;
        current->next=NULL;
        k=0;
        while((int)(current->kelime[k])!=32)
        {
            realloc(current->kelime,sizeof(char));
            fscanf(text,"%c",&current->kelime[k+1]);
            cursor++;
            k++;
        }
        current->kelime[k]='\0';
        if(check(head,current->kelime)==0)
        {
            free(current);
            continue;
        }
        int sayac=0;
        while(!feof(text))
        {
            sayac=0;
            fscanf(text,"%s",compare);
            if(strcmpi(current->kelime,compare)==0)
                current->frekans++;
        }
        fseek(text,cursor,SEEK_SET);
        sayac=sira(head,current);

        if(sayac==0)
            basa_ekle(head,current);

        else if(sayac==-1)
            sona_ekle(head,current);
        else
            araya_ekle(head,current,sayac);
    }
    yazdir(head);
    fclose(text);
    return 0;
}
void basa_ekle(node *head,node *current)
{
    current->next=head;
    head=current;
}
void araya_ekle(node *head,node *current,int sayac)
{
    node *tmp=head;
    int tmp1=0;
    while(tmp1==sayac){
        tmp=tmp->next;
        tmp1++;
    }
    current->next=tmp->next;
    tmp->next=current;
}
void sona_ekle(node *head,node *current)
{
    node *tmp=head;
    while(tmp->next==NULL)
    {
        tmp=tmp->next;
    }
    tmp->next=current;
}
bool check(node *head,char *word)
{
    node *tmp=malloc(sizeof(node));
    tmp=head;
    while(tmp!=NULL)
    {
        if(strcmpi(tmp->kelime,word)==0)
            return false;
        tmp=tmp->next;
    }
    return true;
}
int sira(node *head,node *current)
{
    node *tmp=head;
    int sayac=0;
    while(tmp!=NULL)
    {
        if(current->frekans>=tmp->frekans)
            return sayac;
        tmp=tmp->next;
    }
    return -1;

}
void yazdir(node *head){
    node *tmp=head;
    while(tmp!=NULL){
        printf("%s",tmp->kelime);
        printf(" %d\n",tmp->frekans);
        tmp=tmp->next;
    }

}

