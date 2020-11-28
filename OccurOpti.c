#include "OccurOpti.h"

#include "Structures/ListCharAndNbOcc.h"

NodeHuffman* createNodeHuffman(char car)
{
    NodeHuffman* new_node = NULL;
    new_node = (NodeHuffman*)malloc(sizeof(NodeHuffman));

    if (new_node == NULL)
        printf("can’t allocate memory to NodeHuffman in createNodeHuffman()\n");
    else {
        new_node->c = car;
        new_node->nbOcc = 1;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

void AddNodeHuffmanInArray(NodeHuffman** array, int arrSize, char car, int pos)
{
    if (array[pos] != NULL)
    {
        for (int i = arrSize; i > pos; i--)
            array[i] = array[i - 1];
    }

    array[pos] = createNodeHuffman(car);
}

NodeHuffman** OccurOpti(FILE* f, int* sizeTab)
{
    char car;
    int start, end, mid, found;
    int tabOcc[256] = { 0 };
    *sizeTab = 0;

    NodeHuffman** tab = (NodeHuffman**)calloc(256, sizeof(NodeHuffman*));

    fseek(f, 0, SEEK_SET);

    if (tab == NULL)
        printf("can’t allocate memory to array NodeHuffman in OccurOpti()\n");
    else {
        while ((car = fgetc(f)) != EOF) {
            start = 0;
            end = *sizeTab;
            found = 0;
            mid = 0;

            while (found == 0 && start <= end) {
                mid = (start + end) / 2;

                if (tab[mid] != NULL) {
                    if (tab[mid]->c == car)
                        found = 1;
                    else if (car > tab[mid]->c)
                        start = mid + 1;
                    else
                        end = mid - 1;
                }
                else
                    start = end + 1;
            }

            if (found != 0)
                tab[mid]->nbOcc++;
            else {
                if (tab[mid] != NULL && car > tab[mid]->c)
                    mid++;

                AddNodeHuffmanInArray(tab, *sizeTab, car, mid);
                *sizeTab = *sizeTab + 1;
            }
        }
    }
    return tab;
}

NodeHuffman** _OccurOpti(FILE* f, int* sizeTab)
{
    char car;
    int start, end, mid, found;
    int tabOcc[256] = { 0 };
    (*sizeTab) = 0;
    ListCharAndNbOcc* list = NULL;
    while ((car = fgetc(f)) != EOF)
    {
        tabOcc[car]++;
        if (tabOcc[car] == 1)
        {
            (*sizeTab) += 1;
        }
    }
    NodeHuffman** tab = (NodeHuffman**)malloc(*sizeTab * sizeof(NodeHuffman*));
    int i = 0;
    car = 0;
    while (i < *sizeTab)
    {
        while (tabOcc[car] == 0)
        {
            car++;
        }
        tab[i] = createNodeHuffman(car);
        tab[i]->nbOcc = tabOcc[car];
        i++;
        car++;
    }
    FreeList(list);
    return tab;
}