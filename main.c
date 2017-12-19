#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
   int student_number;
   int score;
   struct tree *lchild;
   struct tree *rchild;
}bst,*Bst;


int search_tree(bst *t, bst **p, bst**q, int key)
{
    int flag = 0;
    *q = t;
    while(*q)
    {
        if(key > (*q)->score)
        {
            *p = *q;
            *q = (*q)->rchild;
        }
        else if(key < (*q)->score)
        {
            *p = *q;
            *q = (*q)->lchild;
        }
        else
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void insert_tree(Bst &t,int number,int key)
{
    if(t==NULL)
    {
        t = (bst *)malloc(sizeof(bst));
        t ->score = key;
        t ->student_number = number;
        t->lchild = NULL;
        t->rchild = NULL;
    }
    else if(key > t->score)                          //Ѱ�Ҵ˼�ֵ��Ӧ��Ӧ�ò���Ľ���λ��
        insert_tree(t->lchild,number,key);
    else
        insert_tree(t->rchild,number,key);
}

int Delete_tree(bst **t, int key)
{
    bst *p = *t, *q,*s,**f;
    int flag = 0;
    if (search_tree(*t,&p,&q,key) == 1)      //Ѱ��Ҫɾ���Ľ���Ƿ�����֪�Ķ�����������
    {
        flag = 1;
        if (p == q)                            //����Ϊ����
            f = &(*t);
        else
        {
            f = &(p->lchild);
            if (key > p->score)
                f = &(p->rchild);
        }
        if (!q->rchild)         //q���Ҷ���
        {
            *f = q ->lchild;
        }
        else if (!q->lchild)
        {
            *f = q ->rchild;
        }
        else
        {
            p = q->rchild;
            s = p;
            while(p->lchild)
            {
                s = p;
                p = p->lchild;
            }
            *f = p;
            p->lchild = q->rchild;
            if (s!=p)
            {
                s->lchild = p->rchild;
                p->rchild = q->rchild;
            }

        }
        free(q);
    }
    return flag;
}

bst *visit_score(bst *p,int number)
{
    bst *q = NULL;
    if(!p)
        return NULL;
    if(p->student_number == number)
        return p;
    if(p->lchild)
    {
        q = visit_score(p->lchild,number);
        if(q)
            return q;
    }
    if(p->rchild)
    {
        q = visit_score(p->rchild,number);
        if(q)
            return q;
    }
    return NULL;
}

void Print_tree(bst *p,FILE *fp)
{
    if (p)
    {
        Print_tree(p->lchild,fp);
        printf("%d  %d",p->student_number,p->score);
        //fprintf(fp,"%d\t%d\n",p->student_number,p->score);
        Print_tree(p->rchild,fp);
    }
}

int main()
{
    bst *Tree=NULL;
    bst *t;
    FILE *fp;
    int m,n;
    if ((fp = fopen("D:\\studentdata.txt","r")) == NULL)    /*��ֻ������ʽ���ļ���������ļ��Ƿ��*/
        exit(0);
    while(fscanf(fp,"%d",&m)!=EOF && fscanf(fp,"%d",&n)!=EOF)
    {
        insert_tree(Tree,m,n);
        printf("%d\t%d\n",m,n);
    }
    fclose(fp);
    while(1)
    {
        int k,x,y;
        printf("����0Ϊ����,����1Ϊ��ѯĳһ��ѧ���ɼ�������2Ϊ����һ��ѧ���ɼ�������3Ϊɾ��һ��ѧ���ɼ�������4Ϊ��ӡ�ɼ���\n");
        scanf("%d",&k);
        if(k==0)
            break;
        else if(k==1)
        {
            printf("������Ҫ���ҵ�ѧ��ѧ�ţ�\n");
            scanf("%d",&x);
            t = visit_score(Tree,x);
            if(t)
            {
                printf("���ҳɹ���\n");
                printf("��ѧ����ѧ�źͳɼ�Ϊ��");
                printf("%d   %d\n",t->student_number,t->score);
            }
            else
                printf("δ���ҵ��ý�㣡\n");

        }
        else if(k==2)
        {
            printf("������ѧ����ѧ�źͳɼ���\n");
            scanf("%d %d",&x,&y);
            //if(insert_tree(Tree,x,y))
                printf("����ɹ���\n");
           // else
                printf("����ʧ�ܣ��ý���Ѿ����ڣ�\n");
        }
        else if(k==3)
        {
            printf("������Ҫɾ����ѧ����ѧ�ţ�\n");
            scanf("%d",&x);
            t = visit_score(Tree,x);
            if(t)
             {
                Delete_tree(&Tree,t->score);
                printf("ɾ���ɹ���\n");
             }
            else
                printf("����Ҫɾ����ѧ�������ڣ�\n");
        }
        else if(k==4)
        {
            FILE *fp;
            if ((fp = fopen("D:\\Output.txt","w"))==NULL)          /*��д����ʽ���ļ���������ļ��Ƿ��*/
                exit(0);
            printf("ѧ��  �ɼ�\n");
            Print_tree(Tree,fp);
            fclose(fp);
        }

    }
    return 0;
}


