/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

node *hashtable[26];

int hash(const char* word)
{
    return (tolower(word[0])-97)%26;
}

int wordcount=0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    char w[LENGTH+1],l;
    for(int i=0;i<strlen(word);i++)
    {
        l=tolower(word[i]);
        w[i]=(char)l;
    }
    w[strlen(word)]='\0';
    node *p=hashtable[hash(w)];
    while(p!=NULL)
    {
        if(strcmp(p->word,word)==0)
        {
            return true;
        }
        p=p->next;
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    int hashvalue=0;
    char word[LENGTH+1],l;

    FILE *f=fopen(dictionary,"r");      //opening dictionary txt
    if(f==NULL)
    {
        printf("not able to open dictionary.txt\n");
        return false;
    }
    while(fscanf(f,"%s\n", word) != EOF)
    {
	    node* newnode = malloc(sizeof(node));       //making an empty node have word of length "LENGTH=45" as it data member.
	    for(int i=0;i<strlen(word);i++)
        {
            l=tolower(word[i]);
            newnode->word[i]=(char)l;               //input of given word into word array of node.
        }
        newnode->word[strlen(word)]='\0';
	   	hashvalue = hash(word);                     //finding position of the word in hashtable
	   	wordcount++;
	   	if(hashtable[hashvalue] == NULL)
	   	{
	   		hashtable[hashvalue] = newnode;         //if no value present at that location initially
	   		newnode->next = NULL;
	   	}
	   	else
	   	{
	   	     node *p=hashtable[hashvalue],*prev=NULL;
	   	    while(p && strcmp(p->word,newnode->word)<0){
                prev= p;
                p=p->next;
	   	    }
	   	    if(prev==NULL){
                newnode->next=p;
                hashtable[hashvalue]=newnode;
	   	    }
	   	    else{
                prev->next=newnode;
                newnode->next=p;
	   	    }
	   	}
	   	//free(newnode);
    }
    fclose(f);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    node* t = NULL;
	node* t2 = NULL;
	for(int i = 0; i < 26;i++)
	{
		t = hashtable[i];
		while(t)
		{
			t2=t->next;
			free(t);
			t=t2;
		}
		hashtable[i]=NULL;
	}
	return true;
}
