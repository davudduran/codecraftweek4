//İhtiyaç duyulan kütüphaneleri çağırır
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Hash tablosundaki bir düğümü temsil eder.
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash tablosundaki bucket(kova) sayısı
const unsigned int N = 26;

// Hash tablosu
node *hashtable[N];
int words=0;

//Kelimeyi bir sayıya hashler.
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Sözlüğü belleğe yükler, başarılı olursa true döndürür, değilse false değerini döndürür.
bool load(const char *dictionary)
{

    FILE *pointer1 = fopen(dictionary, "r");
    if(pointer1==NULL) return 0;
    char dicwords[LENGTH+1];
    while(fscanf(pointer1,"%s",dicwords)!=EOF){

        node *n = malloc(sizeof(node));
        if(n==NULL) return 0;

        strcpy(n->word,dicwords);

        int x=hash(dicwords);

        if(hashtable[x]==NULL) {
            n->next=NULL;
            hashtable[x]=n;}

        else {
            n->next = hashtable[x];
            hashtable[x]=n;
        }
        words++;
    }
    fclose(pointer1);
    return true;
}

//Sözlükteki kelime sayısını geri döndürür,
//Eğer sözlük yüklenemediyse 0 döndürür
unsigned int size(void)
{
    return words;
}

//Kelime sözlükte ise true değerini döndürür, değilse false değerini döndürür.
bool check(const char *word)
{
    int temp=hash(word);
    node *cursor=hashtable[temp];
    while(cursor!=NULL){
        if (strcasecmp(cursor->word, word) == 0) return true;
        cursor = cursor->next;
    }
    return 0;
}

// Sözlüğü bellekten temizler,başarılı olursa true döndürüyor olmazsa false döndürüyor.
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];
        node *temp = cursor;

        while(cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
