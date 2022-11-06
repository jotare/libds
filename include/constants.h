#ifndef CONSTANTS_H
#define CONSTANTS_H

typedef int status_t;

/** Operation succeed */
#define SUCCESS 0

/** Error while allocating memory */
#define ALLOC_ERROR 1

/** When trying to take from an empty data structure */
#define EMPTY_ERROR 2

/** When trying to insert into a full data structure */
#define FULL_ERROR 3

/** When trying to operate in an il·legal index/position */
#define INDEX_ERROR 4

/** When looking for an element and it's not found */
#define NOT_FOUND 5

#endif /* CONSTANTS_H */
