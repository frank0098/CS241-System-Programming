/** @file libdictioanry.c */

/*
* Machine Problem #1
* CS 241
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "libdictionary.h"

const int NO_KEY_EXISTS  = 1; /**< Return value if no key exists in the dictionary. @see dictionary_get() */
const int KEY_EXISTS     = 2; /**< Return value if a key exists in the dictionary. @see dictionary_add() */ 
const int ILLEGAL_FORMAT = 3; /**< Return value if the format of the input is illegal. @see dictionary_parse() */


/**
* Initializes the dictionary.  (If your data structure does not require any
* initialization logic, this function may be empty.)
*
* You may assume that:
* - This function will only be called once per dicitonary_t instance.
* - This function will be the first function called on each dictionary_t instance.
* - The dictionary pointer will be valid, non-NULL pointer.
*
* @param d
*   A pointer to the dictionary.  Since all values are passed by value in C,
*   you should never directly modify the parameter d.  For example:
*   @code
*     d = malloc( sizeof(dictionary_t) );
*     ...
*   @endcode
*   ...will not change d when d is returned to the caller.  Instead, you
*   should modify only the members of the structure that is pointed to by d,
*   such as:
*   @code
*     d->entry = malloc( sizeof(dictionary_entry_t) );
*     d->entry->value = ...
*     ...
*   @endcode
*/

struct _dictionary_t *head = NULL;



void dictionary_init(dictionary_t *d)
{
    head = NULL;
    
}


/**
* Adds the key-value pair (key, value) to the dictionary, if and only if
* the dictionary does not already contain a key with the same name as key.
* This function does NOT make a copy of the key or value.  (You should NOT
* use strcpy() in the function at all.)
*
* You may assume that:
* - The stirngs key and value will not be modified outside of the dictionary.
* - The parameters will be valid, non-NULL pointers.
*
* @param d
*   A pointer to an initalized dictionary data structure.
* @param key
*   The key to be added to the dictionary
* @param value
*   The value to be assoicated with the key in the dictionary.
*
* @retval 0
*   Success
* @retval KEY_EXISTS
*   The dictionary already contains they specified key.
*/
int dictionary_add(dictionary_t *d, const char *key, const char *value)
{
    struct _dictionary_t *new_node;
    struct _dictionary_t *curr;
    struct _dictionary_entry_t *new_entry;
    
    int flag=0;
    char *tkey,*tvalue;
    tkey=malloc(100*sizeof(char));
    tvalue=malloc(100*sizeof(char));
    new_entry = (struct dictionary_entry_t*)malloc( sizeof(dictionary_entry_t) );
    strcpy(tkey,key);
    strcpy(tvalue,value);
    new_entry->key = tkey;
    new_entry->value= tvalue;
    
    new_node = (struct dictionary_t*)malloc( sizeof(dictionary_t) );
    new_node->entry = new_entry;
    curr=head;
    
    if(head == NULL)
    {
        head = d;
        d->entry = new_entry;
        head -> next= NULL;
        return 0;
    }
    
    else
    {
        


        while(1)
        {
            //printf("key is %s,input key is %s\n",curr->entry->key,key);
		if(strcmp((curr->entry->key),key)==0)
            	{
                    flag=1;
                    
                }
            

            if(curr->next == NULL)
                break;
            curr=curr->next;

        }
            if(flag==1)
        	return -1;
        else
        {
        new_node->next = NULL;
        curr->next = new_node;
    	}
        return 0;
    }
}


/**
* Parses the key_value string and add the parsed key and value to the
* dictionary. This function must make a call to dictionary_add() when
* adding to the dictionary.
*
* The format of the key_value will be the format of an HTTP header
* (@link http://www.w3.org/Protocols/HTTP/1.0/draft-ietf-http-spec.html#Message-Headers
* you can read more aboud the headers here, but this is not necessary to understand @endlink),
* where the contents will be the KEY (one or more non-colon characters), a colon,
* a single space, and the rest will be the VALUE. (While the KEY cannot be an empty
* string, it is possible for the VALUE to be an empty string.)
*
* This function should NOT copy key_value and should NOT create any additional memory to store
* the KEY and VALUE pieces of the string.  Instead, this function should modify the key_value
* string in-place, if necessary.  If the function fails, key_value should be unmodified.
*
* Valid inputs:
* - "Host: www.cs.uiuc.edu"
* - "MyKey: MyValue"
* - "a: b"
* - "SomeLongKey: ", where there is a trailing space after the colon
* - "Strange: but:this:is:okay: and: so: is: this"
* - "e: :e"
* - "This is not common: but it's not illegal"
* - "Strange:   case", where the value would be "  case"
*
* Illegal inputs:
* - ": www.cs.uiuc.edu", since the KEY is zero-length
* - "MyKey, MyValue", since no colon, space exists
* - "a:b", since no colon, space exists.
* - "a:: b", since the first colon isn't followed by a space.
*
* You may assume that:
* - All whitespace surrounding key_value has been removed.
* - The parameters will be valid, non-NULL pointers.
*
* @param d
*   A pointer to an initalized dictionary data structure.
* @param key_value
*   The key-value pair that is to be parsed and added to the dictionary.
*
* @retval 0
*   Success (the key_value was parsed and added to the dictionary)
* @reval KEY_EXISTS
*   The dictionary already contains a key with the same name as the KEY in key_value
* @retval ILLEGAL_FORMAT
*   The format of key_value is illegal.
*/
int dictionary_parse(dictionary_t *d, char *key_value)
{
    return -1;
}


/**
* Returns the value of the key-value element for a specific key.
* If the key does not exist, this function returns NULL.
*
* You may assume that:
* - The parameters will be valid, non-NULL pointers.
*
* @param d
*   A pointer to an initalized dictionary data structure.
* @param key
*   The key to lookup in the dictionary.
*
* @return
*  - the value of the key-value element, if the key exists in the dictionary
*  - NULL, otherwise.
*/
const char *dictionary_get(dictionary_t *d, const char *key)
{
    
    struct _dictionary_t *ptr = d;
    
    
    int found=0;
    
    while( ptr != NULL )
    {
    	//printf("the key is %s\n ",(ptr->entry->key));
    	if(strcmp((ptr->entry->key),key)==0)
    	{
    		
    		found = 1;
    		break;
    	}
    	else
    	{
    	 	ptr = ptr->next;
    
    	}
    }
    
    if (found == 1)
    	return ptr->entry->value;
    else
    return NULL;
}


/**
* Removes the key-value pair for a given key from the dictionary, if it exists.
*
* You may assume that:
* - The parameters will be valid, non-NULL pointers.
*
* @param d
*   A pointer to an initalized dictionary data structure.
* @param key
*   The key to remove from the dictionary.
*
* @retval 0
*   Success.
* @retval NO_KEY_EXISTS
*   The dictionary did not contain key.
*/

int go(dictionary_t *d)
{
	struct _dictionary_t *ptr = d;
	while( ptr != NULL )
    {
    	printf("what in? %s\n ",(ptr->entry->key));
    	ptr = ptr->next;
    }

}
int dictionary_remove(dictionary_t *d, const char *key)
{
    struct _dictionary_t *ptr = d;
    struct _dictionary_t *tmp = d;
    struct _dictionary_entry_t *new_entry;
    
    while( ptr != NULL )
    {
    	//printf("the key is %s\n ",(ptr->entry->key));
    	
    	if(strcmp((ptr->entry->key),key)==0)
    	{
    		if(ptr == d)
    		{
    			new_entry=ptr->entry;
    			// free(new_entry->value);
    			// free(new_entry->key);
    			// free(d->entry);

    			tmp=d->next;
    			d=tmp;
    	 		head = d;
    	 		break;
    	 	}
    	 	else
    	 	{

    	 		new_entry=ptr->entry;
    			free(new_entry->value);
    			free(new_entry->key);
    	 		tmp->next=ptr->next;
    	 		free(ptr->entry);
    	 		
    	 	}

    	}
    		tmp = ptr;
    	 	ptr = ptr->next;
    	 	
    
    }
    
    return -1;
}


/**
* Frees any memory associated with the dictionary.
*
* You may assume that:
* - This function will only be called once per dicitonary_t instance.
* - This function will be the last function called on each dictionary_t instance.
* - The dictionary pointer will be valid, non-NULL pointer.
*
* (Since <tt>d</tt> was provided for you by the programmer and not something you
*  created, you should NOT free <tt>d</tt> itself.  Only free member elements of
*  the data structure.)
*
* @param d
*   A pointer to an initalized dictionary data structure.
*/
void dictionary_destroy(dictionary_t *d)
{
    struct _dictionary_t *ptr = d;
    struct _dictionary_t *tmp = d;
    struct _dictionary_entry_t *new_entry;
    
    while( 1 )
    {
            
        new_entry=ptr->entry;
        
        tmp=ptr;
        d=ptr->next;
        head=d;

        if(ptr->next == NULL)
            break;
        ptr=ptr->next;
        free(new_entry->value);
        free(new_entry->key);

        free(tmp->entry);
            
    }


}
