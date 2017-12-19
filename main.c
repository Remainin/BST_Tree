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
    else if(key > t->score)                          //寻找此键值对应的应该插入的结点的位置
        insert_tree(t->lchild,number,key);
    else
        insert_tree(t->rchild,number,key);
}

int Delete_tree(bst **t, int key)
{
    bst *p = *t, *q,*s,**f;
    int flag = 0;
    if (search_tree(*t,&p,&q,key) == 1)      //寻找要删除的结点是否在已知的二叉排序树中
    {
        flag = 1;
        if (p == q)                            //若树为空树
            f = &(*t);
        else
        {
            f = &(p->lchild);
            if (key > p->score)
                f = &(p->rchild);
        }
        if (!q->rchild)         //q无右儿子
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
    if ((fp = fopen("D:\\studentdata.txt","r")) == NULL)    /*以只读的形式打开文件，并检查文件是否打开*/
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
        printf("输入0为结束,输入1为查询某一个学生成绩，输入2为插入一个学生成绩，输入3为删除一个学生成绩，输入4为打印成绩单\n");
        scanf("%d",&k);
        if(k==0)
            break;
        else if(k==1)
        {
            printf("请输入要查找的学生学号：\n");
            scanf("%d",&x);
            t = visit_score(Tree,x);
            if(t)
            {
                printf("查找成功！\n");
                printf("该学生的学号和成绩为：");
                printf("%d   %d\n",t->student_number,t->score);
            }
            else
                printf("未查找到该结点！\n");

        }
        else if(k==2)
        {
            printf("请输入学生的学号和成绩：\n");
            scanf("%d %d",&x,&y);
            //if(insert_tree(Tree,x,y))
                printf("插入成功！\n");
           // else
                printf("插入失败，该结点已经存在！\n");
        }
        else if(k==3)
        {
            printf("请输入要删除的学生的学号：\n");
            scanf("%d",&x);
            t = visit_score(Tree,x);
            if(t)
             {
                Delete_tree(&Tree,t->score);
                printf("删除成功！\n");
             }
            else
                printf("您所要删除的学生不存在！\n");
        }
        else if(k==4)
        {
            FILE *fp;
            if ((fp = fopen("D:\\Output.txt","w"))==NULL)          /*以写的形式打开文件，并检查文件是否打开*/
                exit(0);
            printf("学号  成绩\n");
            Print_tree(Tree,fp);
            fclose(fp);
        }

    }
    return 0;
}


