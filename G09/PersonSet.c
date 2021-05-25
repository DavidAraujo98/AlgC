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
	p->array = (Person**)malloc((sizeof(Person**)*INITIAL_CAPACITY));
	p->capacity = INITIAL_CAPACITY;
	p->size = 0;

	if (p == NULL) { perror("PersonSetCreate"); exit(2); }

	return p;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
	assert(*pps != NULL);
	free((*pps)->array);
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
		PersonPrintf(ps->array[i], ";\n");
	}
	printf("}(size=%d, capacity=%d)\n", ps->size, ps->capacity);
}


// Find index in ps->array of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  int i;
  for(i = 0; i < ps->size; i++){
	if(id == (ps->array[i])->id){
		return 1;
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
	if(ps->size == ps->capacity){
		ps->capacity = ps->capacity * 2;
		ps->array = (Person**)realloc(ps->array,sizeof(Person**)*ps->capacity);
	}
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
	
	PersonSetRemove(ps, (ps->array[(ps->size -1)])->id);
	
	return p;
}

// Remove the person with given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
	Person *p = NULL;

	int v = search(ps, id);
	
	if(v != 0){
		if( (ps->capacity > 4) & (ps->capacity/2 > ps->size) ){
			ps->capacity = ps->capacity / 2;
			ps->array = (Person**)realloc(ps->array,sizeof(Person**)*ps->capacity);
		}	
		p = ps->array[v];
		ps->array[v] = ps->array[(ps->size) - 1];
		ps->array[(ps->size) - 1] = NULL;
		ps->size--;
	}
	return p;
}


// Get the person with given id of *ps.
// return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
	Person* p = NULL;

	int i;
	for(i = 0; i < ps->size; i++){
		int v = search(ps, (ps->array[i])->id);
		if(v){
			p = ps->array[i];
		}
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
  if (ps == NULL) { perror("PersonSetUnion"); exit(2);}
  
  int i;
  for(i = 0; i < ps2->size; i++){
	PersonSetAdd(ps, ps2->array[i]);
  }
  for(i = 0; i < ps1->size; i++){
	PersonSetAdd(ps, ps1->array[i]);
  }
  
  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
	PersonSet *ps = PersonSetCreate();
	if (ps == NULL) { perror("PersonSetIntersection"); exit(2);}
	
	int y;
	for(y = 0; y < ps1->size; y++){
		int v = search(ps2, (ps1->array[y])->id);
		if(v != 0){
			PersonSetAdd(ps, ps1->array[y]);
		}
	}

	return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated.  Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
	PersonSet *ps = PersonSetCreate();
	if (ps == NULL) { perror("PersonSetUnion"); exit(2);}
	
	int i;
	for(i = 0; i < ps1->size; i++){
		PersonSetAdd(ps, ps1->array[i]);
	}
	
	for(i = 0; i < ps2->size; i++){
		int v = search(ps1, (ps2->array[i])->id);
		if(v == 0){
			PersonSetAdd(ps, ps2->array[i]);
		}else{
			PersonSetRemove(ps, (ps2->array[i])->id);
		}
	}
	
	return ps;
}

// Return true iff *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
	int b;
	
	PersonSet *temp = PersonSetCreate();
	temp = PersonSetIntersection(ps1, ps2);
	
	if(temp->size == ps1->size){
		b = 1;
	}else{
		b = 0;
	}
	
	PersonSetDestroy(&temp);
	
	return b; 
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
	int b = 1;
	
	if(ps2->size == ps1->size){
		int i;
		for(i = 0; i < ps2->size; i++){
			int v = search(ps1, (ps2->array[i])->id);
			if(!v){
				b = 0;
				break;
			}
		}
	}else{
		b = 0;
	}
	
	return b; 
}


