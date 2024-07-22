#include "regex.h"
#include <string.h>

pcre2_code* hproxy_regex_compile(const char *pattern_str)
{
	pcre2_code *re;
	PCRE2_SPTR pattern; 	/* PCRE2_SPTR is a pointer to unsigned code units of */

	int errornumber;
	PCRE2_SIZE erroroffset;
	
	if (!pattern_str)
		return NULL;

	pattern = (PCRE2_SPTR)pattern_str;

	/*************************************************************************
	* Now we are going to compile the regular expression pattern, and handle *
	* any errors that are detected.                                          *
	*************************************************************************/
	re = pcre2_compile(
	  pattern,               /* the pattern */
	  PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
	  0,                     /* default options */
	  &errornumber,          /* for error number */
	  &erroroffset,          /* for error offset */
	  NULL);                 /* use default compile context */

	return re;
}

bool hproxy_regex_match(pcre2_code *re, const char *subject_str)
{
	PCRE2_SPTR subject; 	/* the appropriate width (in this case, 8 bits). */	

	int rc;
	PCRE2_SIZE subject_length;
	
    pcre2_match_data *match_data;

	if (!re || !subject_str)
		return false;

	subject = (PCRE2_SPTR)subject_str;
	subject_length = (PCRE2_SIZE)strlen((char *)subject);	

	/*************************************************************************
	* If the compilation succeeded, we call PCRE2 again, in order to do a	 *
	* pattern match against the subject string. This does just ONE match. If *
	* further matching is needed, it will be done below. Before running the  *
	* match we must set up a match_data block for holding the result. Using  *
	* pcre2_match_data_create_from_pattern() ensures that the block is		 *
	* exactly the right size for the number of capturing parentheses in the  *
	* pattern. If you need to know the actual size of a match_data block as  *
	* a number of bytes, you can find it like this: 						 *
	*																		 *
	* PCRE2_SIZE match_data_size = pcre2_get_match_data_size(match_data);	 *
	*************************************************************************/
	match_data = pcre2_match_data_create_from_pattern(re, NULL);

	/* Now run the match. */
	rc = pcre2_match(
	  re,					/* the compiled pattern */
	  subject,				/* the subject string */
	  subject_length,		/* the length of the subject */
	  0,					/* start at offset 0 in the subject */
	  0,					/* default options */
	  match_data,			/* block for storing the result */
	  NULL);		

	pcre2_match_data_free(match_data);
	return (rc < 0) ? false: true;		
}

void hporxy_regex_release(pcre2_code *re)
{
	pcre2_code_free(re);
}

bool hporxy_regex_match_once(const char *pattern_str, const char *subject_str)
{
	pcre2_code *re;
	PCRE2_SPTR pattern; 	/* PCRE2_SPTR is a pointer to unsigned code units of */
	PCRE2_SPTR subject; 	/* the appropriate width (in this case, 8 bits). */	

	int errornumber;
	PCRE2_SIZE erroroffset;
	PCRE2_SIZE subject_length;
	
    pcre2_match_data *match_data;

	int rc;

	if (!pattern_str || !subject_str)
		return false;

	pattern = (PCRE2_SPTR)pattern_str;
	subject = (PCRE2_SPTR)subject_str;
	subject_length = (PCRE2_SIZE)strlen((char *)subject);	

	/*************************************************************************
	* Now we are going to compile the regular expression pattern, and handle *
	* any errors that are detected.                                          *
	*************************************************************************/
	re = pcre2_compile(
	  pattern,               /* the pattern */
	  PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
	  0,                     /* default options */
	  &errornumber,          /* for error number */
	  &erroroffset,          /* for error offset */
	  NULL);                 /* use default compile context */

    /* Compilation failed: print the error message and exit. */
	if (re == NULL)
	{
#ifdef HPROXY_DEBUG		
		PCRE2_UCHAR buffer[256];
		pcre2_get_error_message(errornumber, buffer, sizeof(buffer));			
		fprintf(stdout, "PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset,		
	  	buffer);
#endif
		return false;
	}

	/*************************************************************************
	* If the compilation succeeded, we call PCRE2 again, in order to do a	 *
	* pattern match against the subject string. This does just ONE match. If *
	* further matching is needed, it will be done below. Before running the  *
	* match we must set up a match_data block for holding the result. Using  *
	* pcre2_match_data_create_from_pattern() ensures that the block is		 *
	* exactly the right size for the number of capturing parentheses in the  *
	* pattern. If you need to know the actual size of a match_data block as  *
	* a number of bytes, you can find it like this: 						 *
	*																		 *
	* PCRE2_SIZE match_data_size = pcre2_get_match_data_size(match_data);	 *
	*************************************************************************/
	match_data = pcre2_match_data_create_from_pattern(re, NULL);

	/* Now run the match. */
	rc = pcre2_match(
	  re,					/* the compiled pattern */
	  subject,				/* the subject string */
	  subject_length,		/* the length of the subject */
	  0,					/* start at offset 0 in the subject */
	  0,					/* default options */
	  match_data,			/* block for storing the result */
	  NULL);		

    /* Matching failed: handle error cases */	  
	if (rc < 0) {
#ifdef HPROXY_DEBUG		
		switch(rc) {
	  	case PCRE2_ERROR_NOMATCH: printf("No match\n"); break;
		/*
		Handle other special cases if you like
		*/
	  	default: printf("Matching error %d\n", rc); break;
	  	}
#endif		
		pcre2_match_data_free(match_data);	 /* Release memory used for the match */
		pcre2_code_free(re);				 /*   data and the compiled pattern. */
		return false;
	}

#ifdef HPROXY_DEBUG
	PCRE2_SIZE *ovector;	

	/* Match succeded. Get a pointer to the output vector, where string offsets are
	stored. */	
	ovector = pcre2_get_ovector_pointer(match_data);
	printf("Match succeeded at offset %d\n", (int)ovector[0]);

    for (int i = 0; i < rc; i++) {
        PCRE2_SPTR8 substring_start = (PCRE2_SPTR8)subject + ovector[2*i];
        PCRE2_SIZE substring_length = ovector[2*i+1] - ovector[2*i];
        printf("Matched substring: %.*s\n", (int)substring_length, (char *)substring_start);
    }
#endif

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return true;	
}

