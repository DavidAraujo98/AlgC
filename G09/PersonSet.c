//NMEC: 93444
//NICK: David José Araújo Ferreira

// Complete the functions (marked by ...)
// so that it passes all tests in DateTimeTest.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PersonSet.h"

// Definition of the structure
struct _PersonSet_ {
  int capacity; // the current capacity of the array
  int size;     // the number of elements currently stored
  Person **array; // points to an array of pointers to persons
};

#define INITIAL_CAPACITY 4

// You may add auxiliary definitions and declarations here, if you need to.


// Create a PersonSet.
PersonSet* PersonSetCreate() {
  // You must allocate space for the struct and for the array.
  // The array should be created with INITIAL_CAPACITY elements.
  // (The array will be reallocated if necessary, when elements are appended.)
  PersonSet* p = (PersonSet*) malloc(sizeof(*p));
  p->array = (Person**)malloc((sizeof(*p)*INITIAL_CAPACITY));
  p->capacity = 4;
  p->size = 0;
  
  if (p == NULL) { perror("PersonSetCreate"); exit(2); }
  
  return p;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL);
  free(*pps);
  *pps = NULL;  
}

int PersonSetSize(const PersonSet *ps) {
  return ps->size;
}

int PersonSetIsEmpty(const PersonSet *ps) {
  return ps->size == 0;
}

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  for (int i = 0; i < ps->size; i++) {
    Person *p = ps->array[i];
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d, capacity=%d)\n", ps->size, ps->capacity);
}


// Find index in ps->array of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  int i;
  Person **array = ps->array;
  for(i = 0; i < ps->size; i++){
	Person *p = array[i];
	if(id == p->id){
		return i;
	}
  }
  i = 0;
  return i;
}

// Append person *p to *ps, without verifying presence.
// Use only when sure that *p is not contained in *ps!
// (INTERNAL function.)
static void append(PersonSet *ps, Person *p) {
  // MODIFY the function so that if the array is full,
  // use realloc to double the array capacity!
  //...
	ps->array = (Person**)realloc(ps->array,(ps->capacity * 2));
	ps->capacity = ps->capacity*2;
	ps->array[ps->size] = p;
	ps->size++;
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
	// You may call the append function here!
	//...
	int v = search(ps, p->id);
	if(v==0){
		append(ps, p);
	}
}

// Pop one person out of *ps.
Person* PersonSetPop(PersonSet *ps) {
	assert(!PersonSetIsEmpty(ps));
	// It is easiest to pop and return the person in the last position!
	//...
	Person *p = ps->array[(ps->size -1)];
	ps->array[(ps->size -1)]  = NULL;
	ps->size--;
	
	return p;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
	// You may call search here!
	//...
	Person *p = NULL;

	int v = search(ps, id);
	
	if(v != 0){
		p = ps->array[v];
		ps->array[v] = ps->array[(ps->size) - 1];;
		
		ps->array[(ps->size) - 1] = NULL;
	}

	ps->size--;
	
	return p;
}


// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  // You may call search here!
  //...
  Person* p = NULL;
  
  int v = search(ps, id);
  
  if(v > 0){
	p = ps->array[v];
  }
  
  return p;
}

// Return true (!= 0) if set contains person wiht given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) >= 0;
}


// Return a NEW PersonSet with the union of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) { perror("PersonSetUnion"); exit(2); PersonSetDestroy(&ps);}
  
  int i;
  for(i = 0; i < ps1->size; i++){
	PersonSetAdd(ps, ps1->array[i]);
  }
  for(i = 0; i < ps2->size; i++){
	PersonSetAdd(ps, ps2->array[i]);
  }
  
  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
	PersonSet *ps = PersonSetCreate();
	if (ps == NULL) { perror("PersonSetIntersection"); exit(2); PersonSetDestroy(&ps);}
	
	PersonSet *temp;
	PersonSet *tep;
	if(ps2->size > ps1->size){
		tep = ps2;
		temp = ps1;
	}else{
		tep = ps1;
		temp = ps2;
	}

	int y;
	for(y = 0; y < temp->size; y++){
		Person* t = temp->array[y];
		int v = search(tep, t->id);
		if(v != 0){
			PersonSetAdd(ps, t);
		}
	}

	return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
	PersonSet *ps = PersonSetCreate();
	if (ps == NULL) { perror("PersonSetUnion"); exit(2); PersonSetDestroy(&ps);}

	ps = PersonSetUnion(ps1, ps2);
	PersonSet *temp = PersonSetIntersection(ps1, ps2);

	int i;
	for(i = 0; i < ps->size; i++){
		Person* t = ps->array[i];
		int v = search(temp, t->id);
		if(v != 0){
			PersonSetRemove(ps, t->id);
		}
	}

	return ps;
	
	//Union set minus the intersection set should give the difference, why is it not working ?
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
	int b = 1;
	
	if(ps2->size >= ps1->size){
		int y;
		for(y = 0; y < ps1->size; y++){
			Person* t = ps1->array[y];
			int v = search(ps2, t->id);
			if(v == 0){
				b = 0;
				break;
			}
		}
	}else{
		b = 0;
	}
	
	return b; 
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
	int b = 1;
	
	if(ps2->size == ps1->size){
		PersonSet *intr = PersonSetIntersection(ps1, ps2);
		// Size of intersection set gives 0, but the intersection function is working properly on previous tests, what is the problem ??
		if(intr->size != ps1->size){
			b = 0;
		}
	}else{
		b = 0;
	}
	
	return b; 
}


