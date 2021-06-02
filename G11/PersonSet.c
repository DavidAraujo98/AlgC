// NMEC: ...
// NICK: ...

// Complete the functions (marked by ...)
// so that it passes all tests in Tests.

#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BSTree.h"

// NOTE THAT:
// - Field capacity was eliminated.
// - Field size was eliminated, because size==BSTreeGetNumberOfNodes(...).

// Definition of the structure
struct _PersonSet_
{
  BSTree *persons; // points to a BSTree of Person pointers
};

// Comparison function to be used in generic BSTree.
// Comparison is based on Person ID
static int cmpP(const void *a, const void *b)
{
  Person *p1 = (Person *)a;
  Person *p2 = (Person *)b;
  int d = p1->id - p2->id;
  return (d > 0) - (d < 0);
}

// Print function to be used in generic BSTree.
static void printP(void *p) { PersonPrintf((Person *)p, ""); }

// Create a PersonSet.
PersonSet *PersonSetCreate()
{
  PersonSet *p = (PersonSet *)malloc(sizeof(p));
  p->persons = BSTreeCreate(cmpP, printP);

  if (p == NULL)
    abort();

  return p;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps)
{
  assert(*pps != NULL);
  BSTreeDestroy(&((*pps)->persons));
  free((*pps)->persons);
  free(*pps);
  *pps = NULL;
}

int PersonSetSize(const PersonSet *ps)
{
  if (ps->persons == NULL)
  {
    printf("hi\n");
  }
  return BSTreeGetNumberOfNodes(ps->persons);
}

int PersonSetIsEmpty(const PersonSet *ps) { return BSTreeIsEmpty(ps->persons); }

// Print function to use in PersonSetPrint
static void printlnP(void *p) { PersonPrintf((Person *)p, ";\n"); }

void PersonSetPrint(const PersonSet *ps)
{
  printf("{\n");
  BSTreeTraverseINOrder(ps->persons, printlnP);
  printf("}(size=%d)\n", PersonSetSize(ps));
}

// Find node in BSTree ps->persons of person with given id.
// Return a pointer to the stored Person instance.
// Or NULL, if it does not belong to the BSTree.
// (INTERNAL function.)
static Person *search(const PersonSet *ps, int id)
{
  Person dummyPerson;
  dummyPerson.id = id;
  return BSTreeSearch(ps->persons, &dummyPerson);
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p)
{
  BSTreeAdd(ps->persons, p);
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps)
{
  assert(!PersonSetIsEmpty(ps));
  // It is easiest to pop and return the first person in the set!
  //...
  Person *p = (Person *)BSTreeGetMax(ps->persons);
  BSTreeRemove(ps->persons, BSTreeGetMax(ps->persons));
  return p;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id)
{
  // You may call search here!
  //...
  Person *p = search(ps, id);
  if (p != NULL)
  {
    BSTreeRemove(ps->persons, p);
  }
  return p;
}

// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id)
{
  // You may call search here!
  //...
  return search(ps, id);
}

// Return true (!= 0) if set contains person with given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id)
{
  return search(ps, id) != NULL;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //...

  Queue *q = BSTreeGetItems(ps1->persons);
  while (!QueueIsEmpty(q))
  {
    BSTreeAdd(ps->persons, QueueDequeue(q));
  }
  QueueDestroy(&q);

  q = BSTreeGetItems(ps2->persons);
  while (!QueueIsEmpty(q))
  {
    BSTreeAdd(ps->persons, QueueDequeue(q));
  }

  QueueDestroy(&q);
  free(q);

  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //...

  Queue *q = BSTreeGetItems(ps1->persons);
  while (!QueueIsEmpty(q))
  {
    Person *a = (Person *)QueueDequeue(q);
    if (BSTreeContains(ps2->persons, a))
      BSTreeAdd(ps->persons, a);
  }

  QueueDestroy(&q);

  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2)
{
  PersonSet *ps = PersonSetCreate();
  //...

  Queue *q = BSTreeGetItems(ps1->persons);
  while (!QueueIsEmpty(q))
  {
    BSTreeAdd(ps->persons, QueueDequeue(q));
  }
  QueueDestroy(&q);

  q = BSTreeGetItems(ps2->persons);
  while (!QueueIsEmpty(q))
  {
    Person *a = (Person *)QueueDequeue(q);
    if (!BSTreeContains(ps1->persons, a))
      BSTreeAdd(ps->persons, a);
  }

  QueueDestroy(&q);

  return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2)
{
  int i = 1;

  Queue *q = BSTreeGetItems(ps1->persons);

  while (!QueueIsEmpty(q))
  {
    if (!BSTreeContains(ps2->persons, (Person *)QueueDequeue(q)))
      i = 0;
  }

  QueueDestroy(&q);

  return i;
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2)
{
  return PersonSetSize(ps1) == PersonSetSize(ps2) &&
         PersonSetIsSubset(ps1, ps2);
}
