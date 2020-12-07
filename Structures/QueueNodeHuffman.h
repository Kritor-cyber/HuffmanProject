#pragma once

/**
 * \file   QueueNodeHuffman.h
 * \brief  Header of the library containing \c QueueNodeHuffman structure and his basics functions.
 *
 * \author Thibault DENIER thibault.denier@efrei.net Alias Kritor-cyber
 * \date   December 2020
*/

#include "ListHuffman.h"


/**
 * \typedef struct QueueNodeHuffman
 * \brief QueueNodeHuffman is a queue of \c NodeHuffman that can be used to create a Huffman tree.
 */
typedef struct QueueNodeHuffman
{
	ListHuffman* start, *end; /**< first and last \c NodeHuffman of the queue */
	int size; /**< number of element in the queue */
} QueueNodeHuffman;

/**
 * \brief Function to initialize the queue by allocating it and initialize the variables.
 * \n Example:
 * \code{.c}
 * QueueNodeHuffman* myQueue = NULL;
 * InitializeQueue(&myQueue);
 * if (myQueue != NULL)
 * {
 * 	// Do things
 * }
 * else
 * 	printf("Error while initializing myQueue.");
 * \endcode
 * \param queue is a pointer to a pointer to the \c QueueNodeHuffman that will be initialize.
 */
void InitializeQueue(QueueNodeHuffman** queue);

/**
 * \brief Function to add a node of a \c ListHuffman in the queue \c QueueNodeHuffman.
 * \n Example:
 * \code{.c}
 * AddDataInQueue(myQueue, myData);
 * \endcode
 * \param queue is a pointer to the \c QueueNodeHuffman were the data will be add.
 * \param data is the data we want to add to the queue \c QueueNodeHuffman.
 */
void AddDataInQueue(QueueNodeHuffman* queue, NodeHuffman* data);

/**
 * \brief Function to get the first node of a \c ListHuffman in the queue \c QueueNodeHuffman.
 * \n Example:
 * \code{.c}
 * NodeHuffman* node = GetDataFromQueueNodeHuffman(myQueue);
 * \endcode
 * \param queue is a pointer to the \c QueueNodeHuffman we want the first data.
 * \return is the first data of the \c queue
 */
NodeHuffman* GetDataFromQueueNodeHuffman(QueueNodeHuffman* queue);

/**
 * \brief Function to free all nodes of the queue and the queue.
 * \n Example:
 * \code{.c}
 * FreeQueueNodeHuffman(myQueue);
 * myQueue = NULL;
 * \endcode
 * \param queue is a pointer to the \c QueueNodeHuffman we want to free.
 */
void FreeQueueNodeHuffman(QueueNodeHuffman* queue);