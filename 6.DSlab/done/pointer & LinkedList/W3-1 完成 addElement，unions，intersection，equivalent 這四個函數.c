//clear vers.

/*
Week 2 Question 3
Description

Please finish four function addElement, unions, intersection and equivalent.
Function addElement will add an element to the set, return true on success and false on not.
Function unions union two set and return the result.
Function intersection intersect two set and return the result.
Function equivalent return true if two set have the same element, return false if not.

*/
#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};
struct Set
{
    struct Node *element;
};

void Allocation_Node(struct Node **node_ptr, int number)
{
    *node_ptr = malloc(sizeof(struct Node));
    (*node_ptr)->data = number;
    (*node_ptr)->next = NULL;
    return;
}

void Allocation_Set(struct Set **set_ptr)
{
    *set_ptr = malloc(sizeof(struct Set));
    (*set_ptr)->element = NULL;
    return;
}


int addElement(struct Set *set, int e)
{
    //check multiple number
    struct Node *check_node = set->element;
    while(check_node != NULL)
    {
        if(check_node->data == e)
            return;
        check_node = check_node->next;
    }


    struct Node *nw_nod;
    Allocation_Node( &nw_nod, e);

    if( set->element == NULL)//no node in set
    {
        set->element = nw_nod;
        return 1;
    }

    if( set->element->next == NULL)//only one node in set
    {
        if( set->element->data > e)//added number smaller than the element of set
        {
            // e == nw_node->data
            nw_nod->next = set->element;
            set->element = nw_nod;
        }
        else
            set->element->next = nw_nod;
        return 1;
    }
    else
    {
        struct Node *curt_ptr = set->element, *next_ptr = set->element->next;

        while(curt_ptr != NULL)
        {
            if( e < curt_ptr->data)
            {
                set->element = nw_nod;
                nw_nod->next = curt_ptr;

                return 1;
            }
            if( e >= curt_ptr->data && e <= next_ptr->data)
            {
                nw_nod->next = next_ptr;
                curt_ptr->next = nw_nod;
                return 1;
            }
            if( e > curt_ptr->data && e > next_ptr->data)
            {
                curt_ptr = next_ptr;

                if(next_ptr->next == NULL)
                    next_ptr = NULL;
                else
                    next_ptr = next_ptr->next;

            }
            if(next_ptr == NULL)
            {
                curt_ptr->next = nw_nod;
                return 1;
            }
        }
    }
}
/*

struct Node* judges(struct Node **judging)
{
if( (*judging)->next != NULL)
return ( (*judging)->next) ;
else
return NULL;

}
*/

/* Debug using
struct Node *cur_p = union_set->element;
                while(cur_p != NULL)
                {
                    printf("%d ", cur_p->data);
                    cur_p = cur_p->next;
                }
                //printf("\n\n");
                */
struct Set *unions(struct Set *a, struct Set *b)
{
    struct Set *union_set;
    Allocation_Set(&union_set);
    while( a->element != NULL || b->element != NULL)
    {
        if( a->element != NULL && b->element != NULL)
        {
            int temp_a = a->element->data;
            int temp_b = b->element->data;
            if( temp_a == temp_b)
            {
                addElement(union_set, temp_a);

                if(a->element->next != NULL && b->element->next != NULL)
                {
                    a->element = a->element->next;
                    b->element = b->element->next;
                }
            }

            if(temp_a > temp_b)
            {
                addElement(union_set, temp_b);
                if(b->element->next != NULL)
                    b->element = b->element->next;
                else
                    b->element = NULL;
            }
            if(temp_a < temp_b)
            {
                addElement(union_set, temp_a);
                if(a->element->next != NULL)
                    a->element = a->element->next;
                else
                    a->element = NULL;
            }
        }

        if( a->element == NULL && b->element != NULL)
        {
            int temp_b = b->element->data;
            addElement(union_set, temp_b);
            if(b->element->next != NULL)
                b->element = b->element->next;
            else
                b->element = NULL;
        }
        if( a->element != NULL && b->element == NULL)
        {
            int temp_a = a->element->data;
            addElement(union_set, temp_a);
            if(a->element->next != NULL)
                a->element = a->element->next;
            else
                a->element = NULL;
        }
    }
    return union_set;
}



struct Set *intersetcions(struct Set *a,struct Set *b)
{
    struct Set *intersec_set = NULL;
    Allocation_Set(&intersec_set);

    if(a->element == NULL)
        printf("a--NULL\n");
    if(b->element == NULL)
        printf("b--NULL\n");

    while( a->element != NULL && b->element != NULL)
    {
        int temp_a = a->element->data;
        int temp_b = b->element->data;

        if( temp_a == temp_b)
        {
            addElement(intersec_set, temp_a);
            if(a->element->next != NULL && b->element->next != NULL)
            {
                a->element = a->element->next;
                b->element = b->element->next;
            }
        }

        if(temp_a > temp_b)
        {
            if(b->element->next != NULL)
                b->element = b->element->next;
            else
                b->element = NULL;
        }
        if(temp_a < temp_b)
        {
            if(a->element->next != NULL)
                a->element = a->element->next;
            else
                a->element = NULL;
        }
    }
    if( a->element == NULL && b->element != NULL)
        return intersec_set;

    if( a->element != NULL && b->element == NULL)
        return intersec_set;

    return intersec_set;
}

int equivalent(struct Set *a,struct Set *b)
{
    int flag = 1;
    while( a->element != NULL && b->element != NULL)
    {
        if(a->element->data == b->element->data)
        {
            a->element = a->element->next;
            b->element = b->element->next;
        }
        else
        {
            flag = 0;
            break;
        }
    }
if( a->element == NULL && b->element != NULL)
        flag = 0;
    if( a->element != NULL && b->element == NULL)
        flag = 0;
    if(flag == 1)
        return 1;
    else
        return 0;
}

int main()
{
    struct Set *a = (struct Set *)malloc(sizeof(struct Set));
    struct Set *b = (struct Set *)malloc(sizeof(struct Set));
    struct Set *c = NULL;
    struct Node *cur;

    a->element = NULL;
    b->element = NULL;

    addElement(a, 55);
    addElement(a, 45);
    addElement(a, 999);
    addElement(a, 1);
    addElement(b, 1);
    addElement(b, 45);
    addElement(b, 50);
    addElement(a, 89);
    addElement(b, 2);

    ///test for add_element
    struct Node *cur_a = a->element, *cur_b = b->element;
    while(cur_a != NULL)
    {
        printf("%d ", cur_a->data);
        cur_a = cur_a->next;
    }
    printf("\n\n");


    while(cur_b != NULL)
    {
        printf("%d ", cur_b->data);
        cur_b = cur_b->next;
    }
    printf("\n\n");


    struct Set *tmp_a = a->element;
    struct Set *tmp_b = b->element;
    ///test for unions
    c = unions(a, b);
    cur = c->element;
    while(cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("unions out \n\n");


    ///teat for intersections
    a->element = tmp_a;
    b->element = tmp_b;

    c = intersetcions(a, b);
    cur = c->element;

    if(cur == NULL)
        printf("cur--NULL\n");
    while(cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("intersection out \n\n");


    ///test for equivalent
    if(equivalent(a, b) == 0)
        printf("Not equivalent.\n");
    else
        printf("Equivalent!\n");

}
