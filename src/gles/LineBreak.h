#ifndef _LINEBRRK_H_
#define _LINEBRK_H_

#include <stdio.h>
#include <string>

namespace LINE_BREAK
{
	typedef unsigned long		u32;

	#define CHAR_FIRST_CJK 0x2E80

	enum break_class
	{
		// input types
		OP = 0,	// open
		CL,	// closing punctuation
		CP,	// closing parentheses (from 5.2.0) (before 5.2.0 treat like CL)
		QU,	// quotation
		GL,	// glue
		NS,	// no-start
		EX,	// exclamation/interrogation
		SY,	// Syntax (slash)
		IS,	// infix (numeric) separator
		PR,	// prefix
		PO,	// postfix
		NU,	// numeric
		AL,	// alphabetic
		ID,	// ideograph (atomic)
		IN,	// inseparable
		HY,	// hyphen
		BA,	// break after
		BB,	// break before
		B2,	// break both
		ZW,	// ZW space
		CM,	// combining mark
		WJ, // word joiner

		// used for Korean Syllable Block pair table
		H2, // Hamgul 2 Jamo Syllable
		H3, // Hangul 3 Jamo Syllable
		JL, // Jamo leading consonant
		JV, // Jamo vowel
		JT, // Jamo trailing consonant

		// these are not handled in the pair tables
		SA, // South (East) Asian
		SP,	// space
		PS,	// paragraph and line separators
		BK,	// hard break (newline)
		CR, // carriage return
		LF, // line feed
		NL, // next line
		CB, // contingent break opportunity
		SG, // surrogate
		AI, // ambiguous
		XX, // unknown
	}; 


	// Break actions are the types of break opportunities that may occur at a particular
	// point in the input. Values for these are also needed in the UI portion of the code
	// so they are already defined here - for explanation see below in the line break
	// section.
	enum break_action
	{
		DIRECT_BRK,
		INDIRECT_BRK, 		
		COMBINING_INDIRECT_BRK, 	
		COMBINING_PROHIBITED_BRK, 	
		PROHIBITED_BRK,
		EXPLICIT_BRK,
		HANGUL_SPACE_BRK,
	};

	int classifyLnBrk(const wchar_t * pszText, break_class * pcls,  int cch);
	int findLineBrk(break_class *pcls, break_action *pbrk, int cch);
	int findComplexBreak(break_class cls, break_class *pcls, break_action *pbrk, int cch);

	break_class LBClassFromCh(wchar_t ch);
	int CharFromVisible(int ch);
	bool isIdeographic(wchar_t c);

}

#endif // ifndef _LINEBRK_H_
