// 把单向链表 a1,a2,a3,a4,...,a7，a8,调整顺序为 a1, a8, a2, a7, a3, a6...这样穿插着的。要求空间复杂度为O(1)，时间复杂度为O(n)
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node_t
{
        int data;
        struct node_t * next;
}Node;

int reverse(Node ** h)
{
        Node * prev = NULL;
        Node * p = *h;
        while (p != NULL)
        {
                Node * tmp = p->next;
                p->next = prev;

                prev = p;
                p = tmp;
        }
        *h = prev;
}


int reorder(const Node * head)
{
        if (head == NULL) return -1;
        //统计长度
        int length = 0;
        Node *p = head;
        while (p->next != NULL) 
        {
                length++;
                p = p->next;
        }
        if (length <= 2) {return 0;}
        //把链表分成两段， 前半段和后半段
        Node * secondHdr = head;
        Node * nodeBeforeSecondHdr = NULL;
        for (int i = 0; i <= length / 2; ++i)
        {
                nodeBeforeSecondHdr = secondHdr;
                secondHdr = secondHdr->next;
        }
        if ( (length%2) == 1)
        {
                nodeBeforeSecondHdr = secondHdr;
                secondHdr = secondHdr->next;
        }
        nodeBeforeSecondHdr->next = NULL;
        //把后半段逆向
        printf("%d: %d\n", __LINE__, secondHdr->data);
        reverse(&secondHdr);
        printf("%d: %d\n", __LINE__, secondHdr->data);
        
        //交替着把两条链表拼起来
        p = head->next;
        while (secondHdr != NULL)
        {
                Node * tmp1 = p->next;
                Node * tmp2 = secondHdr->next;

                p->next = secondHdr;
                secondHdr->next = tmp1;
                p = tmp1;

                secondHdr = tmp2;
        }
        return 0;
}
int scan(const Node * head)
{
        if (head == NULL) return -1;
        Node *p = head->next;
        while (p != NULL)
        {
                printf("%d\t", p->data);
                p = p->next;
        }
        printf("\n\n");
        return 0;
}

int main()
{
        int i;
        Node head;
        Node * prev = &head;
        for (i = 0; i < 15; ++i)
        {
                Node *p = (Node*)malloc(sizeof(Node));
                p->data = i;
                p->next = NULL;

                prev->next = p;
                prev = p;
        }
        scan(&head);
        reorder(&head);
        scan(&head);
        return 0;
}
